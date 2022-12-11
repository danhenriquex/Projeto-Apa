#include "optmization.h"

using namespace std;

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

  this->removeAllTrenosEmpty();

  return 0;

}

void Optimization::removeAllTrenosEmpty(void) {
  int i = 0;
  while (i < this->allTrenos_.size()) {
    if (this->allTrenos_[i].is_empty()) {
      this->allTrenos_.erase(this->allTrenos_.begin() + i);
      i = 0;
    }
    else {
      i++;
    }
  }
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

int Optimization::reinsertion(void) {

  Treno trenoMinGifts = this->allTrenos_[0];
  int minGifts = trenoMinGifts.gifts_.size();
  vector<int> gifts = trenoMinGifts.gifts_;

  for (auto& treno : this->allTrenos_) {
    if (treno.gifts_.size() < minGifts && treno.gifts_.size() > 1) {
      minGifts = treno.gifts_.size();
      trenoMinGifts = treno;
      gifts = treno.gifts_;
    }
  }

  for (auto& gift : gifts) {
    for (auto& treno : this->allTrenos_) {
      if (treno.id_ != trenoMinGifts.id_) {
        if (treno.capacity_ - this->allGifts_[gift].weight_ >= 0 && !treno.is_empty()) {

          bool isAllowed = true;
          for (auto& notAllowed : this->allGifts_[gift].notAllowedPresents_) {
            if (notAllowed == this->allGifts_[gift].id_) {
              isAllowed = false;
            }
          }

          if (isAllowed) {
            trenoMinGifts.remove_gift(this->allGifts_[gift]);
            treno.add_gift(this->allGifts_[gift]);
            break;
          }
        }
      }
    }
  }

  if (!trenoMinGifts.is_empty()) {
    for (auto& gift : gifts) {
      for (auto& gift2 : trenoMinGifts.gifts_) {
        if (gift != gift2) {
          trenoMinGifts.gifts_.push_back(gift);
        }
      }
      for (auto& treno : this->allTrenos_) {
        if (treno.id_ != trenoMinGifts.id_) {
          for (auto& gift2 : treno.gifts_) {
            if (gift == gift2) {
              treno.remove_gift(this->allGifts_[gift]);
            }
          }
        }
      }
    }

  }
  else {
    this->allTrenos_.erase(this->allTrenos_.begin() + trenoMinGifts.id_);
  }

  int i = 0;
  while (i < this->allTrenos_.size()) {
    if (this->allTrenos_[i].is_empty()) {
      this->allTrenos_.erase(this->allTrenos_.begin() + i);
      i = 0;
    }
    else {
      i++;
    }
  }

  return this->allTrenos_.size();
}
