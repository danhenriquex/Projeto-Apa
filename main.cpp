#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Gift {
  public:
    int id;
    int weight;
};

class Treno {
  public:
    int capacity;
    std::vector<Gift> gifts;
};

class Optimization {
  public:
    int oi;
};

int main( void ) {
  auto readFile = []( const std::string& file ) {
    std::ifstream text(file);

    if ( text.is_open() ) {
      std::string value;

      while( !text.eof() ) {
        std::getline(text, value);
        std::cout << "value: " << value << std::endl;
      }
    }
  };

  readFile("./instance.txt");

  std::cout << "Initial commit" << std::endl;

  return 0;
}