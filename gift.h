#ifndef GIFT_H
#define GIFT_H
#include <vector>


#include <iostream>

class Gift {
public:
  Gift(void) {};
  Gift(const int& id, const int& weight, const bool& in, const int& idTreno) {
    this->id_ = id;
    this->weight_ = weight;
    this->isIn_ = in;
    this->idTreno_ = idTreno;
  }

  std::vector<int> notAllowedPresents_;
  int id_;
  int weight_;
  int idTreno_;
  bool isIn_;

  friend std::ostream& operator<<(std::ostream& os, const Gift& gift) {
    os << "Presente " << gift.id_ + 1 << std::endl;
    os << "weight: " << gift.weight_ << std::endl;
    os << "is in: " << (gift.isIn_ ? "Sim" : "Nao") << std::endl;
    os << "idTreno: " << gift.idTreno_ << std::endl;
    os << std::endl;
    return os;
  }

  friend bool operator==(const Gift& a, const Gift& b) {
    return a.id_ == b.id_ && a.weight_ == b.weight_ && a.isIn_ == b.isIn_ && a.idTreno_ == b.idTreno_;
  }

};

#endif