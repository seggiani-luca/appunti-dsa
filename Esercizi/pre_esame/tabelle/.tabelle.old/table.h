#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <string>
#include <unordered_map>

class Table {
private:
  std::unordered_map<std::string, std::unordered_map<std::string, std::string>*> table_map;
public:
  std::vector<std::string> attributes;
  std::string key;
  Table(std::vector<std::string> a, std::string k) : attributes(a), key(k) {}
  void insert(std::string, std::vector<std::string>);
  void list();
};

#endif
