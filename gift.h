#ifndef GIFT_H
#define GIFT_H
#include <vector>


class Gift {
  public:
    Gift( void ) {};
    Gift( const int& id, const int& weight, const bool& in, const int& idTreno ) {
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
};

#endif