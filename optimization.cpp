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

  for ( auto& gift : this->allGifts_ ) {

    for ( auto& treno : this->allTrenos_ ) {

      if ( gift.isIn_ ) continue;
        std::cout << "aaaa: " << gift.id_ << "allow: " << gift.idTreno_ << std::endl;
      
      if ( treno.capacity_ >= gift.weight_ ) {

        bool isNotAllowed = false;


        for ( auto& value : this->notAllowedPresents_[gift.id_] ) {

          std::cout << "value: " << treno.id_ << "this value: " << this->allGifts_[value].idTreno_ << std::endl;

          if ( this->allGifts_[value-1].idTreno_ == treno.id_ ) {

            isNotAllowed = true;
            
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

  // for ( auto& gift : this->allGifts_ ) {

  //   std::cout << gift.id_ << " " << gift.weight_ << " treno que eu tou " << gift.idTreno_ << std::endl;

  // }

  // for ( auto& treno : this->allTrenos_ ) {
  //   std::cout << "Treno: " << treno.id_ << std::endl;

  //   for ( auto& gift : treno.gifts_ ) {
  //     std::cout << "id: " << gift.id_ << " weight: " << gift.weight_ << "trenoId: " << gift.idTreno_ << std::endl;
  //   }
  // }

  this->showTrenoGifts();

  // for ( auto& gift : this->allGifts_ ) {

  //   if ( !gift.isIn_ ) {

  //     Treno aux = this->allTrenos_[this->allTrenos_.size() - 1];

  //     if ( aux.capacity_ >= gift.weight_ ) {

  //       gift.isIn_ = true;
  //       this->allTrenos_[this->allTrenos_.size() - 1].capacity_ -= gift.weight_;
  //       this->allTrenos_[this->allTrenos_.size() - 1].gifts_.push_back( gift );
        
  //       continue;
  //     }

  //     Treno treno = Treno( this->allTrenos_.size() + 1, this->trenoCapacity_ );

  //     gift.isIn_ = true;
  //     treno.capacity_ -= gift.weight_;
  //     treno.gifts_.push_back( gift );

  //     this->allTrenos_.push_back( treno );
  //   }
  // }

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