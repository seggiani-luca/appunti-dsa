#include "table.h"
#include <unordered_map>
#include <iostream>

void Table::insert(std::string key, std::vector<std::string> attributes) {
  if(attributes.size() != this->attributes.size()) return;
  std::unordered_map<std::string, std::string>* record_map = new std::unordered_map<std::string, std::string>;
  for(int i = 0; i < attributes.size(); i++) {
    record_map->insert({this->attributes[i], attributes[i]});
  }
  table_map.insert({key, record_map});
}

void Table::list() {
  std::cout << key << "\t";
  for(int i = 0; i < attributes.size(); i++) {
    std::cout << attributes[i] << " \t";
  }
  std::cout << std::endl;
  for(const auto& record_pair : table_map) {
    std::cout << record_pair.first << "\t";
    for(const auto& attribute_pair : *record_pair.second) {
      std::cout << attribute_pair.second << "\t";
    }
    std::cout << std::endl;
  }
}
