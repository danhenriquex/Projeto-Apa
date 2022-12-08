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
  // cout << this->allTrenos_[trenoId];]
  // std::cout << "Depois do swap: " << std::endl;
  // for (auto& treno : trenoToSwap) {
  //   std::cout << treno;
  // }

  // select a random gift
  Gift gift1 = this->allGifts_[rand() % this->allGifts_.size()];
  Gift gift2 = this->allGifts_[rand() % this->allGifts_.size()];

  do {
    gift2 = this->allGifts_[rand() % this->allGifts_.size()];
  } while ( gift1.id_ == gift2.id_ || !gift2.isIn_);

  // verify if the gift is allowed to be swapped
  for ( auto& value : this->notAllowedPresents_[gift1.id_] ) {
    if ( this->allGifts_[value].idTreno_ == gift2.idTreno_ ) {
      // choose another gift
      gift2 = this->allGifts_[rand() % this->allGifts_.size()];
    }
  }

  Treno treno1 = this->allTrenos_[gift1.idTreno_];
  Treno treno2 = this->allTrenos_[gift2.idTreno_];

  bool treno1IsAbleToSwap = treno1.capacity_ - gift1.weight_ + gift2.weight_ >= 0;
  bool treno2IsAbleToSwap = treno2.capacity_ - gift2.weight_ + gift1.weight_ >= 0;

  std::cout << "Antes do swap" << std::endl;
  std::cout << treno1;
  std::cout << treno2;

  // std::cout << "Gifts" << std::endl;
  // std::cout << gift1;
  // std::cout << gift2;

  if (treno1IsAbleToSwap && treno2IsAbleToSwap) {

    treno1.remove_gift(gift1);
    treno2.remove_gift(gift2);

    treno1.add_gift(gift2);
    treno2.add_gift(gift1);
  }

  std::cout << "Depois do swap" << std::endl;
  std::cout << treno1;
  std::cout << treno2;

  // std::cout << "Gifts" << std::endl;
  // std::cout << gift1;
  // std::cout << gift2;

  // verificar se o presente pode ser colocado no treno
  // std::cout << treno1;
  // std::cout << treno2;


  // std::cout << gift1;
  // std::cout << gift2;

}

Treno Optimization::get_treno_to_swap( void ) {
  int trenoId = rand() % this->allTrenos_.size();
  
  return this->allTrenos_[trenoId];
}

Gift Optimization::get_gift_to_swap( Treno treno1, Treno treno2 ) {
  int giftId = rand() % treno1.gifts_.size();

  Gift gift = treno1.gifts_[giftId];

  // verify if the gift is allowed to be swapped
  for ( auto& value : this->notAllowedPresents_[gift.id_] ) {
    if ( this->allGifts_[value].idTreno_ == treno2.id_ ) {
      giftId = rand() % treno1.gifts_.size();
      gift = treno1.gifts_[giftId];
    }
  }
 
  return this->allGifts_[giftId];
}