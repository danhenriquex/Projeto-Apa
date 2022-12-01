#ifndef GIFT_H
#define GIFT_H

class Gift {
  public:
    Gift( void ) {};
    Gift( const int& id, const int& weight ) {
      this->id_ = id;
      this->weight_ = weight;
    }

    int id_;
    int weight_;
    int idTreno_;
};

#endif