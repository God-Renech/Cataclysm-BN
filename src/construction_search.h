#pragma once

#include <string>

namespace construction_search
{

auto basic_match( const std::string &text, const std::string &query ) -> bool;
auto group_name_match( const std::string &text, const std::string &query ) -> bool;

} // namespace construction_search
