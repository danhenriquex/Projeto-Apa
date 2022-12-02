#ifndef GIFT_H
#define GIFT_H

class Gift {
  public:
    Gift( void ) {};
    Gift( const int& id, const int& weight, const bool& in ) {
      this->id_ = id;
      this->weight_ = weight;
      this->isIn_ = in;
    }

    int id_;
    int weight_;
    int idTreno_;
    bool isIn_;
};

#endif