#include "optmization.h"

Optimization::Optimization(void) {

}

Optimization::Optimization(const int& totalGifts, const int& totalTrenos, const int& trenoCapacity, const int& totalElementsL):
  totalGifts_(totalGifts), trenoCapacity_(trenoCapacity), totalTrenos_(totalTrenos), totalElementsL_(totalElementsL) {
  this->allGiftsSortedIndex_ = new int[this->totalGifts_];
}


void Optimization::showPresents(void) {
  for (auto& obj : this->allGifts_) {
    std::cout << "id: " << obj.id_ << " weight: " << obj.weight_ << std::endl;
    for (auto& gift : obj.notAllowedPresents_) {
      std::cout << gift << ", ";
    }
    std::cout << std::endl;

  }
}

void Optimization::showSortedPresents(void) {
  for (int i = 0; i < this->totalGifts_; i++) {
    std::cout << "id: " << this->allGifts_[this->allGiftsSortedIndex_[i]].id_ << " weight: " << this->allGifts_[this->allGiftsSortedIndex_[i]].weight_ << std::endl;
    for (auto& gift : this->allGifts_[this->allGiftsSortedIndex_[i]].notAllowedPresents_) {
      std::cout << gift << ", ";
    }
    std::cout << std::endl;

  }
}

int Optimization::heuristic(void) {
  this->QuickSort(0, this->totalGifts_ - 1);

  for (int i = 0; i < this->totalGifts_; i++) {
    for (auto& treno : this->allTrenos_) {

      if (treno.gifts_.empty() && this->allGifts_[this->allGiftsSortedIndex_[i]].idTreno_ == -1) {

        this->allGifts_[this->allGiftsSortedIndex_[i]].idTreno_ = treno.id_;
        treno.gifts_.push_back(this->allGifts_[this->allGiftsSortedIndex_[i]].id_);
        treno.capacity_ = treno.capacity_ - this->allGifts_[this->allGiftsSortedIndex_[i]].weight_;

      }
      else {
        if (treno.capacity_ >= this->allGifts_[this->allGiftsSortedIndex_[i]].weight_ && this->allGifts_[this->allGiftsSortedIndex_[i]].idTreno_ == -1) {
          bool allowed = true;
          for (auto& giftCheck : treno.gifts_) {
            for (auto& j : this->allGifts_[giftCheck].notAllowedPresents_) {
              if (j == this->allGifts_[this->allGiftsSortedIndex_[i]].id_) {
                allowed = false;
              }
            }
          }
          if (allowed) {
            this->allGifts_[this->allGiftsSortedIndex_[i]].idTreno_ = treno.id_;
            treno.gifts_.push_back(this->allGifts_[this->allGiftsSortedIndex_[i]].id_);
            treno.capacity_ = treno.capacity_ - this->allGifts_[this->allGiftsSortedIndex_[i]].weight_;
          }
          else {
            if (treno.id_ == (this->totalTrenos_ - 1)) {
              Treno newTreno = Treno(this->totalTrenos_, this->trenoCapacity_);


              this->allGifts_[this->allGiftsSortedIndex_[i]].idTreno_ = newTreno.id_;
              newTreno.gifts_.push_back(this->allGifts_[this->allGiftsSortedIndex_[i]].id_);
              newTreno.capacity_ = newTreno.capacity_ - this->allGifts_[this->allGiftsSortedIndex_[i]].weight_;

              this->allTrenos_.push_back(newTreno);
              this->totalTrenos_ = this->totalTrenos_ + 1;
            }
          }
        }
      }
    }

  }

  int l = 0;

  while ( l < this->allTrenos_.size() ) {
    if ( this->allTrenos_[l].gifts_.size() == 0 ) {
      this->allTrenos_.erase( this->allTrenos_.begin() + l );
      l = 0;
      continue;
    }
    l++;
  }

  return 0;

}

void Optimization::papaiNoel(void) {
  this->heuristic();
}

void Optimization::showTrenoGifts(void) {
  for (auto& treno : this->allTrenos_) {
    std::cout << "treno " << treno.id_ << std::endl;
    for (auto& gift : treno.gifts_) {
      std::cout << "gift: " << this->allGifts_[gift].id_ << " peso: " << this->allGifts_[gift].weight_ << std::endl;
    }
  }
}

using namespace std;

list<Treno> Optimization::swap_gifts(void) {


  Treno& treno1 = this->allTrenos_[rand() % this->allTrenos_.size()];
  Treno& treno2 = this->allTrenos_[rand() % this->allTrenos_.size()];

  Gift gift1 = this->allGifts_[treno1.gifts_[rand() % treno1.gifts_.size()]];
  Gift gift2;

  vector<int> notAllowedPresents = gift1.notAllowedPresents_;

  for (auto& gift : treno2.gifts_) {
    for (auto& value : notAllowedPresents) {
      if (this->allGifts_[gift].id_ == value) {
        gift2 = this->allGifts_[gift];
      }
    }
  }

  treno1.remove_gift(gift1);
  treno2.remove_gift(gift2);

  bool treno1Capacity = treno1.capacity_ - gift2.weight_ >= 0;
  bool treno2Capacity = treno2.capacity_ - gift1.weight_ >= 0;


  if (treno1Capacity && treno2Capacity) {

    treno1.add_gift(gift2);
    treno2.add_gift(gift1);

    return { treno1, treno2 };

  }

  treno1.add_gift(gift1);
  treno2.add_gift(gift2);

  return this->swap_gifts();

}

void Optimization::QuickSort(int inicio, int fim) {

  int i, j, pivo, aux;
  if (inicio < fim) {
    pivo = this->allGifts_[this->allGiftsSortedIndex_[inicio]].weight_;
    i = inicio;
    j = fim;

    while (i < j) {
      while (this->allGifts_[this->allGiftsSortedIndex_[i]].weight_ <= pivo && i < fim)
        i++;
      while (this->allGifts_[this->allGiftsSortedIndex_[j]].weight_ > pivo)
        j--;

      if (i < j) {
        aux = this->allGiftsSortedIndex_[i];
        this->allGiftsSortedIndex_[i] = this->allGiftsSortedIndex_[j];
        this->allGiftsSortedIndex_[j] = aux;
      }
    }
    aux = this->allGiftsSortedIndex_[inicio];
    this->allGiftsSortedIndex_[inicio] = this->allGiftsSortedIndex_[j];
    this->allGiftsSortedIndex_[j] = aux;
    this->QuickSort(inicio, j - 1);
    this->QuickSort(j + 1, fim);

  }
}

void Optimization::mergeTrenos( void ) {

  for ( int i = 0; i < this->allTrenos_.size(); ++i ) {

    for ( int j = 0; j < this->allTrenos_.size(); ++j ) {
      
      if ( i == j ) continue;

      const int treno1Capacity = this->trenoCapacity_ - this->allTrenos_[i].capacity_;
      const int treno2Capacity = this->trenoCapacity_ - this->allTrenos_[j].capacity_;
      const int trenoSum = treno1Capacity + treno2Capacity;
      bool allowed = false;

      if ( trenoSum <= this->trenoCapacity_ ) {
        allowed = true;
        for ( auto& gift1 : this->allTrenos_[i].gifts_ ) {
          for ( auto& gift2 : this->allTrenos_[j].gifts_ ) {
            for ( auto& notAllowed : this->allGifts_[gift1].notAllowedPresents_ ) {
              if ( notAllowed == this->allGifts_[gift2].id_ ) {
                allowed = false;
              }
            }
          }
        }

        // todo: 1-10 / 2-1

        if ( allowed ) {
          for ( auto& gift : this->allTrenos_[j].gifts_ ) {
            this->allTrenos_[i].add_gift( this->allGifts_[gift] );
         }



         int value = this->allTrenos_[j].gifts_.size();

         for ( int k = 0; k < value; ++k ) {
            this->allTrenos_[j].gifts_.pop_back(); 
         }
        }
      }
      }

     
  }

  int l = 0;

  while ( l < this->allTrenos_.size() ) {
    if ( this->allTrenos_[l].gifts_.size() == 0 ) {
      this->allTrenos_.erase( this->allTrenos_.begin() + l );
      l = 0;
      continue;
    }
    l++;
  }

  // for ( int i = 0; i < this->allTrenos_.size(); ++i ) {
  //   if ( this->allTrenos_[i].gifts_.size() == 0 ) {
  //     this->allTrenos_.erase( this->allTrenos_.begin() + i );
  //   }
  // }

}
