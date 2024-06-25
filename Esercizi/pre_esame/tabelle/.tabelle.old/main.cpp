#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "command.h"
#include "table.h"
using namespace std;

extern string query_line();
extern vector<string> tokenize(string);

unordered_map<string, Table*> master_map;

int main() {
  while(true) {
    string line = query_line();
    vector<string> tokens = tokenize(line);
    Command* command = Command::create_command(tokens);
    if(command)
      command->execute();
    else
      cout << "Errore nell'esecuzione del comando" << endl;
    delete command;
  }
  return 0;
}
