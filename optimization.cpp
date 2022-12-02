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

        if ( treno.gifts_.size() > 0 ) {

          bool isNotAllowed = false;

          for ( int i = 0; i < this->notAllowedPresents_.size(); ++i ) {

            int notAllowedGift = 0;

            if ( this->notAllowedPresents_[i] == gift.id_ ) {

              if ( i % 2 == 0 ) {

                notAllowedGift = this->notAllowedPresents_[i + 1];

              }else {

                notAllowedGift = this->notAllowedPresents_[i - 1];

              }

              for ( auto& trenoGifts : treno.gifts_ ) {

                if ( trenoGifts.id_ == notAllowedGift ) {
                  isNotAllowed = true;
                }

              }

            }
          }

          if ( isNotAllowed ) continue;

        }

        gift.isIn_ = true;
        treno.capacity_ -= gift.weight_;
        treno.gifts_.push_back( gift );
        gift.idTreno_ = treno.id_;
      }
    }
  }

  for ( auto& gift : this->allGifts_ ) {

    if ( !gift.isIn_ ) {

      Treno aux = this->allTrenos_[this->allTrenos_.size() - 1];

      if ( aux.capacity_ >= gift.weight_ ) {

        gift.isIn_ = true;
        this->allTrenos_[this->allTrenos_.size() - 1].capacity_ -= gift.weight_;
        this->allTrenos_[this->allTrenos_.size() - 1].gifts_.push_back( gift );
        
        continue;
      }

      Treno treno = Treno( this->allTrenos_.size() + 1, this->trenoCapacity_ );

      gift.isIn_ = true;
      treno.capacity_ -= gift.weight_;
      treno.gifts_.push_back( gift );

      this->allTrenos_.push_back( treno );
    }
  }

  this->showTrenoGifts();

  return this->allTrenos_.size();
}

void Optimization::sort( void ) {
  std::sort( this->allGifts_.begin(), this->allGifts_.end(), []( const Gift& a, const Gift& b ) {
    return a.weight_ < b.weight_;
  } );
}

void Optimization::papaiNoel( void ) { 
  this->heuristic();
  // std::cout << "solution: " << this->heuristic() << std::endl;
}

void Optimization::showTrenoGifts( void ) {
  for ( auto& treno : this->allTrenos_ ) {
    std::cout << "treno " << treno.id_ << std::endl;
    for ( auto& gift : treno.gifts_ ) {
      std::cout << "gift: " << gift.id_ << " peso: " << gift.weight_ << std::endl;
    }
  }
}