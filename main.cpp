

#include "optmization.h"

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

      Gift gift = Gift( i, item, false, -1 );

      opt.allGifts_.push_back( gift );
    }

    for ( int i = 0; i < opt.totalElementsL_ * 2; ++i ) {
      text >> item;

      // std::cout << "mzr do item: " << item << std::endl;

      // opt.notAllowedPresents_.push_back( item );
    }

    // std::cout << "to morrendo aqui";
    opt.notAllowedPresents_ = new std::list<int>[infos[3] * 2];

    opt.notAllowedPresents_[0].push_back(1);
    opt.notAllowedPresents_[0].push_back(3);
    opt.notAllowedPresents_[1].push_back(0);
    // opt.notAllowedPresents_[1].push_back(3);
    opt.notAllowedPresents_[3].push_back(0);
    // opt.notAllowedPresents_[3].push_back(1);

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