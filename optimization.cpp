#include "optmization.h"

Optimization::Optimization(void) {

}

Optimization::Optimization(const int& totalGifts, const int& totalTrenos, const int& trenoCapacity, const int& totalElementsL):
  totalGifts_(totalGifts), trenoCapacity_(trenoCapacity), totalTrenos_(totalTrenos), totalElementsL_(totalElementsL) {}


void Optimization::showPresents(void) {
  for (auto& obj : this->allGifts_) {
    std::cout << "id: " << obj.id_ << " weight: " << obj.weight_ << std::endl;
  }
}

int Optimization::heuristic(void) {
  this->sort();

  for (auto& treno : this->allTrenos_) {

    for (auto& gift : this->allGifts_) {

      if (gift.isIn_) continue;

      if (treno.capacity_ >= gift.weight_) {

        bool isNotAllowed = false;

        for (auto& value : this->notAllowedPresents_[gift.id_]) {

          if (this->allGifts_[value].idTreno_ == treno.id_) {

            isNotAllowed = true;

          }
          else {

            for (int i = 0; i < this->allGifts_.size(); ++i) {

              if (this->allGifts_[i].id_ == value) {

                this->allGifts_[i].idTreno_ = treno.id_;

              }
            }
          }
        }

        if (!isNotAllowed) {

          gift.isIn_ = true;
          gift.idTreno_ = treno.id_;
          treno.capacity_ -= gift.weight_;
          treno.gifts_.push_back(gift);

        }
      }
    }
  }

  this->showTrenoGifts();

  std::cout << "initial solution: " << this->allTrenos_.size() << std::endl;;

  return this->allTrenos_.size();
}

void Optimization::sort(void) {
  std::sort(this->allGifts_.begin(), this->allGifts_.end(), [](const Gift& a, const Gift& b) {
    return a.weight_ < b.weight_;
    });
}

void Optimization::papaiNoel(void) {
  this->heuristic();
}

void Optimization::showTrenoGifts(void) {
  for (auto& treno : this->allTrenos_) {
    std::cout << "treno " << treno.id_ << std::endl;
    for (auto& gift : treno.gifts_) {
      std::cout << "gift: " << gift.id_ << " peso: " << gift.weight_ << std::endl;
    }
  }
}

using namespace std;

bool Optimization::swap_gifts(void) {


  Treno& treno1 = this->allTrenos_[rand() % this->allTrenos_.size()];
  Treno& treno2 = this->allTrenos_[rand() % this->allTrenos_.size()];

  Gift gift1 = treno1.gifts_[rand() % treno1.gifts_.size()];
  Gift gift2;

  list<int> notAllowedPresents = this->notAllowedPresents_[gift1.id_];

  for (auto& gift : treno2.gifts_) {
    for (auto& value : notAllowedPresents) {
      if (gift.id_ == value) {
        gift2 = gift;
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

    return true;

  }
  else {

    treno1.add_gift(gift1);
    treno2.add_gift(gift2);

    return false;

  }

}

bool Optimization::gifts_can_to_be_together(const Gift& gift1, const Gift& gift2) {

  for (auto& value : this->notAllowedPresents_[gift1.id_]) {

    if (value == gift2.id_) {

      return false;

    }
  }

  return true;
}