#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

class Command {
public:
  virtual void execute() = 0;
  static Command* create_command(std::vector<std::string>& tokens); 
  virtual ~Command() {}
};

class CreateTableCommand : public Command {
  std::string table_name;
  std::vector<std::string> attributes;
  int key;
public:
  void execute() override;
  CreateTableCommand(std::string t, std::vector<std::string> a, int k)
  : table_name(t), attributes(a), key(k) {}
};

class InsertInCommand : public Command {
  std::string table_name;
  std::unordered_map<std::string, std::string> ka_pairs;
public:
  void execute() override;
  InsertInCommand(std::string t, std::unordered_map<std::string, std::string> ka)
  : table_name(t), ka_pairs(ka) {};
};

class ListTablesCommand : public Command {
public:
  void execute() override;
};

class ListTableCommand : public Command {
  std::string table_name;
public:
  void execute() override;
  ListTableCommand(std::string t)
  : table_name(t) {}
};

class QuitCommand : public Command {
public:
  void execute() override;
};

#endif
