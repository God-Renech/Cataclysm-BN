#include "construction_search.h"

#include "cached_options.h"
#include "catacharset.h"
#include "pinyin.h"
#include "string_utils.h"

#include <algorithm>
#include <locale>
#include <string>

namespace
{

auto basic_lcmatch( const std::string &text, const std::string &query ) -> bool
{
    const auto temp_locale = std::locale{};
    if( temp_locale.name() != "en_US.UTF-8" && temp_locale.name() != "C" ) {
        auto &facet = std::use_facet<std::ctype<wchar_t>>( temp_locale );
        auto wide_query = utf8_to_wstr( query );
        auto wide_text = utf8_to_wstr( text );

        facet.tolower( wide_text.data(), wide_text.data() + wide_text.size() );
        facet.tolower( wide_query.data(), wide_query.data() + wide_query.size() );

        return wide_text.find( wide_query ) != std::wstring::npos;
    }

    auto lowered_query = std::string{};
    lowered_query.reserve( query.size() );
    std::transform( query.begin(), query.end(), std::back_inserter( lowered_query ), tolower );

    auto lowered_text = std::string{};
    lowered_text.reserve( text.size() );
    std::transform( text.begin(), text.end(), std::back_inserter( lowered_text ), tolower );

    return lowered_text.find( lowered_query ) != std::string::npos;
}

} // namespace

namespace construction_search
{

auto basic_match( const std::string &text, const std::string &query ) -> bool
{
    return basic_lcmatch( text, query );
}

auto group_name_match( const std::string &text, const std::string &query ) -> bool
{
    if( basic_lcmatch( text, query ) ) {
        return true;
    }

    if( use_pinyin_search ) {
        return pinyin::pinyin_match( utf8_to_utf32( to_lower_case( text ) ),
                                     utf8_to_utf32( to_lower_case( query ) ) );
    }

    return false;
}

} // namespace construction_search
