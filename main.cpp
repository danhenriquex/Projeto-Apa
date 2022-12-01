

#include "treno.h"

using namespace std;

class Optimization {
  public:
    int totalGifts_;
    int totalTrenos_;
    int trenoCapacity_;
    int elementsL_;
    std::vector<Gift> allGifts_;
};

int main( void ) {
  auto readFile = []( const std::string& file ) {
    std::ifstream text(file);

    Optimization opt = Optimization();

    bool isGift = true;
    bool isTreno = false;
    bool isCapacity = false;

    if ( text.is_open() ) {
      std::string value;

      while( !text.eof() ) {
        std::getline(text, value);

        if ( isGift ) {
          for ( int i = 1; i <= stoi(value); ++i ) {
            Gift gift = Gift( i, -1 );
            opt.allGifts_.push_back( gift );
          }

          isGift = false;
          isTreno = true;
        }

        if ( isTreno ) {

        }

      }
    }
  };

  readFile("./instance.txt");

  std::cout << "Initial commit" << std::endl;

  return 0;
}