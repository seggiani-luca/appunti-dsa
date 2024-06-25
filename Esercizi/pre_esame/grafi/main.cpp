#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include "graph.h"

#define UNIT "km"

bool is_integer(const std::string& s, int& result) {
    std::istringstream iss(s);
    iss >> result;
    return !iss.fail() && iss.eof();
}

int main() {
  Graph graph;
  bool silent = false;
  while(true) {
    bool exit = false;
    if(!silent)
      std::cout << std::endl << " - Scegli un' operazione: 'n' - Inserisci nodo; 'a' - Inserisci arco; " 
                    "'p' - Stampa grafo; 'd' - Visita in profondita'; 'b'  Visita in ampiezza; "
                    "'t' - Trova tragitto fra due nodi; 'q' - Termina l'esecuzione" << std::endl;
    char c;

    if(std::cin >> c) {
      switch(c) {
        case '#': {
          silent = !silent;
          break;
        }
        case 'n': {
          if(!silent)
            std::cout << "Inserisci il nome del nodo" << std::endl;
          std::string name;
          std::cin.ignore();
          std::getline(std::cin, name);
          graph.insert_node(name);
          std::cout << "Inserito il nodo \"" << name << "\"" << std::endl;
          break;
        }
        case 'a': {
          if(!silent)
            std::cout << "Inserisci gli indici (o nomi) dei nodi di partenza e destinazione dell'arco" << std::endl;
          std::string str1, str2;
          std::cin >> str1 >> str2;
          if(!silent)
            std::cout << "Inserisci la lunghezza dell'arco" << std::endl;
          float distance;
          std::cin >> distance;
          int node1, node2;
          if(is_integer(str1, node1) && is_integer(str2, node2)) {
            graph.insert_bidirectional(node1, node2, distance);
            std::cout << "Inserito arco dal nodo " << node1 << " (" << graph.get_node(node1) << 
                         ") al nodo " << node2 << " (" << graph.get_node(node2) << ") con distanza " << distance << UNIT << std::endl;
          } else {
            graph.insert_bidirectional(str1, str2, distance);
            std::cout << "Inserito arco dal nodo " << graph.string_to_node(str1) << " (" << str1 << 
                       ") al nodo " << graph.string_to_node(str2) << " (" << str2 << ") con distanza " << distance << UNIT << std::endl;
          }
         
          break;
        }
        case 'p': {
          std::cout << graph;
          break;
        }
        case 'd': {
          std::cout << "La visita in profondita' e':" << std::endl;
          graph.depth_visit(std::cout);
          break;
        }
        case 'b': {
          std::cout << "La visita in ampiezza e':" << std::endl;
          graph.breadth_visit(std::cout);
          break;
        }
        case 't': {
          if(!silent)
            std::cout << "Inserisci gli indici (o nomi) dei nodi di partenza e destinazione" << std::endl;
          std::string str1, str2;
          std::cin >> str1 >> str2;
          float distance;
          int node1, node2;
          std::list<int> sequence;
          if(is_integer(str1, node1) && is_integer(str2, node2)) {
            sequence = graph.shortest_path(node1, node2, &distance);
            std::cout << "Puoi arrivare da " << graph.get_node(node1) << " a " << graph.get_node(node2) << " passando da: " << std::endl;
          } else {
            sequence = graph.shortest_path(str1, str2, &distance);
            std::cout << "Puoi arrivare da " << str1 << " a " << str2 << " passando da: " << std::endl;
          }
          for(const auto& node: sequence) {
            std::cout << graph.get_node(node);
            if(node != sequence.back()) std::cout << " -> ";
          }
          std::cout << std::endl << "La distanza totale da percorrere è " << distance << UNIT << std::endl;
          break;
        }
        case 'q': {
          std::cout << "Arrivederci" << std::endl;
          exit = true;
        }
      }
    }
    if(exit) break;
  }
  return 0;
}
