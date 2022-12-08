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
  Treno(const int &id, const int &capacity) : id_(id), capacity_(capacity){};

  int capacity_;
  int id_;
  std::vector<Gift> gifts_;

  void add_gift(const Gift &gift)
  {

    if (this->capacity_ < gift.weight_)
      return;

    this->gifts_.push_back(gift);
    this->capacity_ -= gift.weight_;
  }

  void remove_gift(const Gift &gift)
  {

    for (int i = 0; i < this->gifts_.size(); ++i)
    {

      if (this->gifts_[i].id_ == gift.id_)
      {

        this->gifts_.erase(this->gifts_.begin() + i);
        this->capacity_ += gift.weight_;
        break;
      }
    }
  }

  int get_capacity( void ) {
    return this->capacity_;
  }

  // overload operator << to print the sled
  friend std::ostream &operator<<(std::ostream &os, const Treno &treno)
  {
    os << "Treno " << treno.id_ << " (capacity: " << treno.capacity_ << ")" << std::endl;
    os << "Presentes: " << std::endl;
    for (int i = 0; i < treno.gifts_.size(); ++i)
    {
      os << treno.gifts_[i].id_ << " ";
    }
    os << std::endl;
    return os;
  }
};

#endif