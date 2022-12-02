

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

    opt.notAllowedPresents_ = new std::list<int>[infos[3] * 2];
    int previousIndex = 0;


    for ( int i = 0; i < opt.totalElementsL_ * 2; ++i ) {
      text >> item;

      if ( i % 2 == 0 ) {
        previousIndex = item;
      }else {

        opt.notAllowedPresents_[previousIndex-1].push_back(item-1); 
        opt.notAllowedPresents_[item-1].push_back(previousIndex-1); 

      }
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