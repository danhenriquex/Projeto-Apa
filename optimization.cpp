#include "optmization.h"

Optimization::Optimization( void ) {

}

Optimization::Optimization( const int& totalGifts, const int& totalTrenos, const int& trenoCapacity, const int& totalElementsL ):
  totalGifts_(totalGifts), trenoCapacity_(trenoCapacity), totalTrenos_(totalTrenos), totalElementsL_(totalElementsL) {}


void Optimization::showPresents( void ) {
  for( auto& obj : this->allGifts_ ) {
    std::cout << "id: " << obj.id_ << " weight: " << obj.weight_ << std::endl;
  }
}