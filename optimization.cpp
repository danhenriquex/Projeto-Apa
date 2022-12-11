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

  return this->allTrenos_.size();

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

  vector<Treno> trenos = this->allTrenos_;

  Treno trenoMinGifts = trenos[0];
  int minGifts = trenoMinGifts.gifts_.size();
  vector<int> gifts = trenoMinGifts.gifts_;

  for (auto& treno : trenos) {
    if (treno.gifts_.size() < minGifts && treno.gifts_.size() > 1) {
      minGifts = treno.gifts_.size();
      trenoMinGifts = treno;
      gifts = treno.gifts_;
    }
  }

  for (auto& gift : gifts) {
    for (auto& treno : trenos) {
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
      for (auto& treno : trenos) {
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
    trenos.erase(trenos.begin() + trenoMinGifts.id_);
  }

  return trenos.size();

}

int Optimization::mergeTrenos(void) {

  vector<Treno> trenos = this->allTrenos_;

  for (int i = 0; i < trenos.size(); ++i) {

    for (int j = i; j < trenos.size(); ++j) {

      if (i == j) continue;

      const int treno1Capacity = this->trenoCapacity_ - trenos[i].capacity_;
      const int treno2Capacity = this->trenoCapacity_ - trenos[j].capacity_;
      const int trenoSum = treno1Capacity + treno2Capacity;
      bool allowed = false;

      if (trenoSum <= this->trenoCapacity_) {
        allowed = true;
        for (auto& gift1 : trenos[i].gifts_) {
          for (auto& gift2 : trenos[j].gifts_) {
            for (auto& notAllowed : this->allGifts_[gift1].notAllowedPresents_) {
              if (notAllowed == this->allGifts_[gift2].id_) {
                allowed = false;
              }
            }
          }
        }

        if (allowed) {
          for (auto& gift : trenos[j].gifts_) {
            trenos[i].add_gift(this->allGifts_[gift]);
          }

          int value = trenos[j].gifts_.size();

          for (int k = 0; k < value; ++k) {
            trenos[j].gifts_.pop_back();
          }
        }
      }
    }
  }

  this->removeAllTrenosEmpty();

  return trenos.size();
}

int Optimization::vnd(void) {

  this->papaiNoel();

  int k = 1;
  int r = 2;

  int best = this->allTrenos_.size();
  int current = best;

  while (k <= r) {

    switch (k)
    {
    case 1:
      current = this->mergeTrenos();
      break;

    case 2:
      current = this->reinsertion();
      break;
    }

    if (current < best) {
      best = current;
      k = 1;
    }
    else {
      k++;
    }

  }

  this->removeAllTrenosEmpty();

  return best;

}

void Optimization::perturbation(void) {

  // escolhe um presente aleatorio e um treno
  int randomGift = rand() % this->allGifts_.size();
  int randomTreno = rand() % this->allTrenos_.size();

  // escolhe um treno aleatorio pra receber o presente
  int randomTreno2 = rand() % this->allTrenos_.size();

  // verifica se o treno tem capacidade pra receber o presente

  bool isPerturbated = false;
  int maxTries = this->allTrenos_.size() * this->allTrenos_.size();

  while (!isPerturbated && maxTries > 0) {

    if (this->allTrenos_[randomTreno2].capacity_ - this->allGifts_[randomGift].weight_ >= 0) {

      for (auto& gift : this->allTrenos_[randomTreno].gifts_) {

        // verifica se o presente aleatorio esta no treno aleatorio
        if (gift == randomGift) {
          // verifica se o presente esta no treno que vai receber
          for (auto& gift2 : this->allTrenos_[randomTreno2].gifts_) {
            if (gift2 == randomGift) {
              return;
            }
          }
          // verifica se o presente nao esta na lista de nao permitidos
          for (auto& notAllowed : this->allGifts_[randomGift].notAllowedPresents_) {
            if (notAllowed == this->allGifts_[randomGift].id_) {
              return;
            }
          }

          // remove o presente do treno
          this->allTrenos_[randomTreno].remove_gift(this->allGifts_[randomGift]);

          // adiciona o presente no treno novo
          this->allTrenos_[randomTreno2].add_gift(this->allGifts_[randomGift]);

          isPerturbated = true;
        }

        if (isPerturbated) {
          break;
        }
      }
    }

    randomGift = rand() % this->allGifts_.size();
    randomTreno = rand() % this->allTrenos_.size();
    randomTreno2 = rand() % this->allTrenos_.size();

    while (randomTreno == randomTreno2) {
      randomTreno2 = rand() % this->allTrenos_.size();
    }

    maxTries--;

  }

  /*
    apaga todos o presentes repetidos e adiciona o id do treno que o presente esta
  */
  for (auto& treno : this->allTrenos_) {
    for (auto& gift : treno.gifts_) {
      if (this->allGifts_[gift].idTreno_ == -1) {
        this->allGifts_[gift].idTreno_ = treno.id_;
      }
      else if (this->allGifts_[gift].idTreno_ != treno.id_) {
        treno.remove_gift(this->allGifts_[gift]);
      }
    }
  }

}

int Optimization::ils(void) {

  int best = this->allTrenos_.size();
  int current = best;

  for (int i = 0; i < 20000; ++i) {

    current = this->vnd();

    if (current < best) {
      best = current;
    }
    else {
      this->perturbation();
    }
  }

  for (auto& treno : this->allTrenos_) {
    cout << treno;
  }

  return best;
}