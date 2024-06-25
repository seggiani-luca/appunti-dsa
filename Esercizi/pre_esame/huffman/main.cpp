#include <bitset>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "heap.h"

struct heap_node {
  char symbol;
  int frequency;
  heap_node* left, *right;
  heap_node(char s, int f) : symbol(s), frequency(f), left(nullptr), right(nullptr) {}
  heap_node() : symbol('@'), frequency(0), left(nullptr), right(nullptr) {} 
  bool operator>(heap_node& second) {
    return frequency > second.frequency;
  }
  bool operator<(heap_node& second) {
    return frequency < second.frequency;
  }
};

std::vector<char> get_alphabet(std::ifstream& file) {
  std::unordered_set<char> set;
  while(!file.eof()) {
    char c = file.get();
    set.insert(c);
  }
  std::vector<char> vec;
  for(const auto& c: set) {
    vec.push_back(c);
  }
  return vec;
}

Heap<heap_node> get_heap(std::ifstream& file, std::vector<char>& alphabet) {
  std::unordered_map<char, int> freq_map;
  for(int i = 0; i < alphabet.size(); i++)
    freq_map.emplace(alphabet[i], 0);
  file.clear();
  file.seekg(0);
  //int count = 0;
  while(!file.eof()) {
    char c = file.get();
    freq_map.find(c)->second++;
    //count++;
  }
  //std::cout << "Text is made up of " << count << " characters" << std::endl;
  std::cout << "Got character - frequency pairs:" << std::endl;

  Heap<heap_node> heap(alphabet.size());
  for(const auto& kv_pair: freq_map) {
    heap_node node = heap_node(kv_pair.first, kv_pair.second);
    heap.insert(node);
    std::cout << kv_pair.first << " - " << kv_pair.second << std::endl;
  }
  return heap;
}

heap_node* get_huffman_tree(Heap<heap_node>& H, int n) {
  for(int i = 0; i < n - 1; i++) {
    heap_node node;
    node.left = new heap_node(H.extract());
    node.right = new heap_node(H.extract());
    node.frequency = node.left->frequency + node.right->frequency;
    H.insert(node);
  }
  return new heap_node(H.extract());
}

void get_codes(heap_node* node, std::unordered_map<char, std::string>& map, std::string current_code = "") {
  if(!node) return;
  if(node->symbol != '@')
    map.emplace(node->symbol, current_code);
  get_codes(node->left, map, current_code + '0');
  get_codes(node->right, map, current_code + '1'); 
}

void deltree(heap_node* node) {
  if(!node) return;
  deltree(node->left);
  deltree(node->right);
  delete node;
}

void serialize_tree(heap_node* node, std::ostream& out) {
  if(!node) {
    out.put('#');
    return;
  }
  out.put(node->symbol);
  serialize_tree(node->left, out);
  serialize_tree(node->right, out);
}

heap_node* deserialize_tree(std::istream& in) {
  char marker = in.get();
  if(marker == '#')
    return nullptr;
  heap_node* node = new heap_node(marker, 0);
  node->left = deserialize_tree(in);
  node->right = deserialize_tree(in);
  return node;
}

void encode() {
  //get file
  std::cout << "Input file name" << std::endl;
  std::string file_name; std::cin >> file_name;
  std::ifstream input_file(file_name);
  if(!input_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
    exit(1);
  }
  std::cout << "Opened file " << file_name << std::endl;

  //get huffman tree
  std::cout << "Encoding file" << std::endl;
  std::cout << "Got alphabet:" << std::endl;
  std::vector<char> alphabet = get_alphabet(input_file); 
  for(int i = 0; i < alphabet.size(); i++) {
    std::cout << alphabet[i] << " ";
  } 
  std::cout << std::endl;

  Heap<heap_node> heap = get_heap(input_file, alphabet); 
  heap_node* tree = get_huffman_tree(heap, alphabet.size());

  std::unordered_map<char, std::string> code_map;
  get_codes(tree, code_map);
  std::cout << "Got codes:" << std::endl; 
  for(const auto& code: code_map) {
    std::cout << code.first << " : " << code.second << std::endl;
  }

  //now actually encode
  input_file.clear();
  input_file.seekg(0);
  std::string encoded_data;
  uint32_t data_size = 0; 

  std::cout << "Encoded data:" << std::endl;
  while(!input_file.eof()) {
    char c = input_file.get();
    std::string code = code_map.find(c)->second;
    encoded_data += code;
    data_size += code.size();
    std::cout << "Encoded character " << c << " as " << code_map.find(c)->second << std::endl;
  }
  std::cout << std::endl;
  input_file.close();
  
  std::string o_name = file_name + ".huf";
  std::ofstream output_file(o_name, std::ios::binary);
  if(!output_file) {
    std::cout << "Error creating file" << std::endl;
    exit(1);
  }

  std::stringstream tree_stream;
  serialize_tree(tree, tree_stream);
  std::string serialized_tree = tree_stream.str();
  uint32_t tree_size = serialized_tree.size();
  output_file.write(reinterpret_cast<char*>(&tree_size), sizeof(tree_size));
  output_file.write(serialized_tree.c_str(), tree_size);
  
  std::cout << "Appended serialized tree:\n" << serialized_tree << std::endl
    << "with size " << serialized_tree.size() << std::endl;

  output_file.write(reinterpret_cast<char*>(&data_size), sizeof(data_size));
  std::cout << "Inserting data block after size indicator of value " << data_size << std::endl;
  
  for(int i = 0; i < encoded_data.size(); i+= 8) {
    std::bitset<8> byte(encoded_data.substr(i, 8));
    output_file.put(static_cast<unsigned char>(byte.to_ulong()));
    std::cout << "Appending byte at position " << i << " as " << byte << std::endl;
  }

  deltree(tree);
}
void decode() {
  //get file
  std::cout << "Input file name" << std::endl;
  std::string file_name; std::cin >> file_name;
  std::ifstream input_file(file_name, std::ios::binary);
  if(!input_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
    exit(1);
  }
  std::cout << "Opened file " << file_name << std::endl;

  //get tree
  std::cout << "Decoding file" << std::endl;
  
  uint32_t tree_size;
  input_file.read(reinterpret_cast<char*>(&tree_size), sizeof(tree_size));
  std::cout << "Tree size: " << tree_size << std::endl;

  std::string tree_str(tree_size, '\0');
  input_file.read(&tree_str[0], tree_size);
  std::cout << "Got serialized tree:" << std::endl;
  std::cout << tree_str << std::endl;

  std::istringstream tree_stream(tree_str);
  heap_node* tree = deserialize_tree(tree_stream);

  uint32_t data_size;
  input_file.read(reinterpret_cast<char*>(&data_size), sizeof(data_size));

  std::string encoded_data;
  while (!input_file.eof()) {
    char c = input_file.get();
    std::bitset<8> bits(static_cast<unsigned char>(c));
    encoded_data += bits.to_string();
  }
  input_file.close();

  //now decode file from tree
  std::cout << "Decoded file:\n" << std::endl;
  heap_node* currentNode = tree;
  //std::string char_string; //for debugging
  for (char bit : encoded_data) {
    if(data_size == 3) { //i dont know 
      std::cout << "\nEnding tree traversal, end of data_size" << std::endl;
      break;
    }
    if (bit == '0') {
      currentNode = currentNode->left;
      //char_string += '0';
    } else {
      currentNode = currentNode->right;
      //char_string += '1';
    }
    if (!currentNode->left && !currentNode->right) {
      std::cout.put(currentNode->symbol);
      //std::cout << "Got character " << char_string << " and decoded as " << currentNode->symbol << std::endl;
      //std::cout << "Currently at data_size: " << data_size << std::endl; 
      currentNode = tree;
      //char_string = "";
    }
    data_size--;
  }
}

int main() {
  std::cout << "Encode or decode? (e, d)" << std::endl;
  char c; std::cin >> c;
  switch(c) {
    case('e'):
      encode();
      break;
    case('d'):
      decode();
      break;
  } 
  
  return 0;
}

