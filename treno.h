#ifndef TRENO_H
#define TRENO_H

#include "gift.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

class Treno
{
public:
  Treno(void);
  Treno(const int& id, const int& capacity): id_(id), capacity_(capacity) {};

  int capacity_;
  int id_;
  std::vector<int> gifts_;

  void add_gift(Gift& gift)
  {

    if (this->capacity_ < gift.weight_)
      return;

    this->gifts_.push_back(gift.id_);
    this->capacity_ -= gift.weight_;

    gift.idTreno_ = this->id_;
    gift.isIn_ = true;
  }

  void remove_gift(Gift& gift)
  {

    for (int i = 0; i < this->gifts_.size(); ++i)
    {

      if (this->gifts_[i] == gift.id_)
      {

        this->gifts_.erase(this->gifts_.begin() + i);
        this->capacity_ += gift.weight_;
        gift.isIn_ = false;
        gift.idTreno_ = -1;
        break;
      }
    }
  }

  int get_capacity(void) {
    return this->capacity_;
  }

  // overload operator << to print the sled
  friend std::ostream& operator<<(std::ostream& os, const Treno& treno)
  {
    os << "Treno " << treno.id_ << " (capacity: " << treno.capacity_ << ")" << std::endl;
    os << "Presentes: " << std::endl;
    for (int i = 0; i < treno.gifts_.size(); ++i)
    {
      os << treno.gifts_[i] << " ";
    }
    os << std::endl << std::endl;
    return os;
  }

  friend bool operator==(const Treno& a, const Treno& b)
  {
    return a.id_ == b.id_ && a.capacity_ == b.capacity_ && a.gifts_ == b.gifts_;
  }
};

#endif