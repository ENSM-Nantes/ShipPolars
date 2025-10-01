#include "tools.h"
#include <iostream>
#include <sstream>

void trim(std::string& inString, std::string trimChrs)
{
  if(inString.empty()) {
    return;
  }

  std::size_t firstScan = inString.find_first_not_of(trimChrs);
  std::size_t first     = firstScan == std::string::npos ? inString.length() : firstScan;
  std::size_t last      = inString.find_last_not_of(trimChrs);
  inString = inString.substr(first, last-first+1);
}



std::vector<std::string> split(const std::string &inputString, char delim)
{
  std::vector<std::string> splitStrings;
  std::stringstream ss(inputString);
  std::string item;
  
  while (std::getline(ss, item, delim))
    {
    // Trim blank spaces from the string
    trim(item);
    splitStrings.push_back(item);
  }
  //Special case - if the final character is the delimitor, add an empty string at the end
  if (inputString.length() > 0) {
    if (inputString.at(inputString.length()-1) == delim ) {
      splitStrings.push_back("");
    }
  }

  return splitStrings;
}
