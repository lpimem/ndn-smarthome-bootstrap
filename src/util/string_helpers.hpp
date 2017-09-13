//
// Created by Lei Pi on 2/26/17.
//

#ifndef HOMESEC_STRING_HELPERS_HPP
#define HOMESEC_STRING_HELPERS_HPP

#include <sstream>
#include <string>
#include <vector>

namespace ndn {
namespace homesec {

// http://stackoverflow.com/a/236803
template<typename Out>
void
split(const std::string& s, char delim, Out result);

std::vector<std::string>
split(const std::string& s, char delim);

std::string
randomHex();

} // namespace homesec
} // namespace ndn
#endif //HOMESEC_STRING_HELPERS_HPP
