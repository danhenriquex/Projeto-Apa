

#include "optmization.h"

using namespace std;

int main( void ) {
  auto readFile = []( const std::string& file ) {
    std::ifstream text(file);
    std::string temp;
    int item;
    std::vector<int> infos;

    text >> temp;

    for ( int i = 0; i < 4; ++i ) {
      text >> item;

      infos.push_back( item ); 
    }

    Optimization opt = Optimization( infos[0], infos[1], infos[2], infos[3] );

    for ( int i = 0; i < opt.totalGifts_; ++i ) {
      text >> item;

      Gift gift = Gift( i + 1, item, false );

      opt.allGifts_.push_back( gift );
    }

    for ( int i = 0; i < opt.totalElementsL_ * 2; ++i ) {
      text >> item;

      opt.notAllowedPresents_.push_back( item );
    }

    for ( int i = 0; i < opt.totalTrenos_; ++i ) {
      Treno treno = Treno( i, opt.trenoCapacity_ );

      opt.allTrenos_.push_back( treno );
    }

    return opt;
  };

  auto opt = readFile( "./instancias/instances/instance.txt" );

  opt.papaiNoel();
  
  return 0;
}