#ifndef __CONFIG_FILE_H__
#define __CONFIG_FILE_H__

#include <string>
#include <map>
#include <fstream>
#include "Chameleon.h"

class ConfigFile {
  std::map<std::string,Chameleon> content_;

public:
  ConfigFile(std::string const& configFile);

  Chameleon const& Value(std::string const& section, std::string const& entry) const;

  Chameleon const& Value(std::string const& section, std::string const& entry, double value);
  Chameleon const& Value(std::string const& section, std::string const& entry, std::string const& value);
  bool is_empty(std::ifstream& pFile);
};

#endif
