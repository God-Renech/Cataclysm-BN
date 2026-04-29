#include "catch/catch.hpp"

#include "cached_options.h"
#include "construction_search.h"
#include "catacharset.h"

TEST_CASE( "construction_search_scopes_pinyin_to_group_names", "[construction][pinyin]" )
{
    const auto old_use_pinyin_search = use_pinyin_search;
    const auto item_text = utf32_to_utf8( U"\u7269\u54c1" );

    use_pinyin_search = true;
    CHECK( construction_search::group_name_match( item_text, "wupin" ) );
    CHECK_FALSE( construction_search::basic_match( item_text, "wupin" ) );

    use_pinyin_search = false;
    CHECK_FALSE( construction_search::group_name_match( item_text, "wupin" ) );

    use_pinyin_search = old_use_pinyin_search;
}
