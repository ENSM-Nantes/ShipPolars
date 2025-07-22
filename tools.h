#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <string>
#include <vector>

void trim(std::string& inString, std::string trimChrs = " \f\n\r\t\v");
std::vector<std::string> split(const std::string &inputString, char delim);


#endif
