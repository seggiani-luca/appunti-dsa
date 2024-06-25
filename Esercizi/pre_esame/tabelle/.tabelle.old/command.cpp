#include "command.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <unordered_map>
#include <utility>
#include "table.h"

extern std::unordered_map<std::string, Table*> master_map;

bool check_token(std::string token, std::string target) {
  std::transform(token.begin(), token.end(), token.begin(), ::tolower);
  std::transform(target.begin(), target.end(), target.begin(), ::tolower);
  return token == target;
}

Command* Command::create_command(std::vector<std::string>& tokens) {
  if(tokens.empty())
    return nullptr;
  Command* command = nullptr;

  std::string command_type = tokens[0];
  if(check_token(command_type, "CREATE")) {
    if(check_token(tokens[1], "TABLE") && check_token(tokens[3], "ATTRIBUTES")) {
      std::string table_name = tokens[2];
      std::vector<std::string> attributes;
      int i = 4;
      for(; i < tokens.size() && !check_token(tokens[i], "KEY"); i++) {
        attributes.push_back(tokens[i]);
      }
      int key = -1;
      if(check_token(tokens[i], "KEY")) {
        key = stoi(tokens[i + 1]);
      }
      command = new CreateTableCommand(table_name, attributes, key);
    }
  }
  if(check_token(command_type, "INSERT")) {
    if(check_token(tokens[1], "IN") && check_token(tokens[3], "VALUES")) {
      std::string table_name = tokens[2];
      std::unordered_map<std::string, std::string> ka_pairs;
      int i = 4;
      for(; i < tokens.size(); i += 2) {
        std::string key = tokens[i];
        std::string attribute = tokens[i + 1];
        ka_pairs.insert({key, attribute});
      }
      command = new InsertInCommand(table_name, ka_pairs);
    }
  }
  if(check_token(command_type, "LIST")) {
    if(check_token(tokens[1], "TABLES")) {
      command = new ListTablesCommand();
    }
    if(check_token(tokens[1], "TABLE")) {
      std::string table_name = tokens[2];
      command = new ListTableCommand(table_name);
    }
  }
  if(check_token(command_type, "QUIT")) {
    command = new QuitCommand();
  }

  return command;
}

std::string query_line() {
  std::string input;
  getline(std::cin, input);
  return input;
}

std::vector<std::string> tokenize(std::string str) {
  std::istringstream iss(str);
  std::vector<std::string> tokens;
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

void CreateTableCommand::execute() {
  std::string key_string;
  if(key == -1) key_string = "DEFAULT_KEY";
  else {
    key_string = attributes[key];
    attributes.erase(attributes.begin() + key);
  }
  Table* table = new Table(attributes, key_string);
  master_map.insert({table_name, table});
}

void InsertInCommand::execute() {
  auto table_iterator = master_map.find(table_name);
  if(table_iterator == master_map.end()) {
    std::cout << "Errore: tabella inesistente" << std::endl;
    return;
  }
  Table* table = table_iterator->second;
  auto key = ka_pairs.find(table->key);
  std::vector<std::string> attributes;
  for(int i = 0; i < table->attributes.size(); i++) {
    auto attribute_iterator = ka_pairs.find(table->attributes[i]);
    if(attribute_iterator == ka_pairs.end()) {
      std::cout << "Errore: attributo inesistente" << std::endl;
      return;
    }
    attributes.insert(attributes.begin(), attribute_iterator->second);
  }
  if(attributes.size() == table->attributes.size() && key != ka_pairs.end()) {
    table->insert(key->second, attributes);
  } else {
    std::cout << "Errore nell'inserzione nella tabella" << std::endl;
  }
}

void ListTablesCommand::execute() {
  for(const auto& pair : master_map) {
    std::cout << pair.first << " - KEY: " << pair.second->key << " - ATTRIBUTES: ";
    for(int i = 0; i < pair.second->attributes.size(); i++) {
      std::cout << pair.second->attributes[i] << " ";
    }
    std::cout << std::endl;
  }
}

void ListTableCommand::execute() {
  auto table_iterator = master_map.find(table_name);
  if(table_iterator == master_map.end()) {
    std::cout << "Errore: tabella inesistente" << std::endl;
    return;
  }
  Table* table = table_iterator->second;
  table->list();
}

void QuitCommand::execute() {
  std::cout << "Arrivederci!" << std::endl;
  exit(0);
}
