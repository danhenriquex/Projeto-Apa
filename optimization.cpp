#include "optmization.h"

Optimization::Optimization( void ) {

}

Optimization::Optimization( const int& totalGifts, const int& totalTrenos, const int& trenoCapacity, const int& totalElementsL ):
  totalGifts_(totalGifts), trenoCapacity_(trenoCapacity), totalTrenos_(totalTrenos), totalElementsL_(totalElementsL) {}


void Optimization::showPresents( void ) {
  for ( auto& obj : this->allGifts_ ) {
    std::cout << "id: " << obj.id_ << " weight: " << obj.weight_ << std::endl;
  }
}

int Optimization::heuristic( void ) { 
  this->sort();

  for ( auto& treno : this->allTrenos_ ) {

    for ( auto& gift : this->allGifts_ ) {

      if ( gift.isIn_ ) continue;
      
      if ( treno.capacity_ >= gift.weight_ ) {

        bool isNotAllowed = false;

        for ( auto& value : this->notAllowedPresents_[gift.id_] ) {

          if ( this->allGifts_[value].idTreno_ == treno.id_ ) {

            isNotAllowed = true;
            
          }else {
            
            for ( int i = 0; i < this->allGifts_.size(); ++i ) {

              if ( this->allGifts_[i].id_ == value ) {

                this->allGifts_[i].idTreno_ = treno.id_;

              }
            }
          }
        }

        if ( !isNotAllowed ) {

          gift.isIn_ = true;
          gift.idTreno_ = treno.id_;
          treno.capacity_ -= gift.weight_;
          treno.gifts_.push_back( gift );

        }
      }
    }
  }

  this->showTrenoGifts();

  std::cout << "initial solution: " << this->allTrenos_.size() << std::endl;;

  return this->allTrenos_.size();
}

void Optimization::sort( void ) {
  std::sort( this->allGifts_.begin(), this->allGifts_.end(), []( const Gift& a, const Gift& b ) {
    return a.weight_ < b.weight_;
  } );
}

void Optimization::papaiNoel( void ) { 
  this->heuristic();
}

void Optimization::showTrenoGifts( void ) {
  for ( auto& treno : this->allTrenos_ ) {
    std::cout << "treno " << treno.id_ << std::endl;
    for ( auto& gift : treno.gifts_ ) {
      std::cout << "gift: " << gift.id_ << " peso: " << gift.weight_ << std::endl;
    }
  }
}

void Optimization::swap_gifts( void ) {
  // select a two random treno
  int trenoId = rand() % this->allTrenos_.size();
  int trenoId2 = rand() % this->allTrenos_.size();

  // select a two random gift
  int giftId = rand() % this->allTrenos_[trenoId].gifts_.size();
  int giftId2 = rand() % this->allTrenos_[trenoId2].gifts_.size();

  cout << this->allTrenos_[trenoId];
}