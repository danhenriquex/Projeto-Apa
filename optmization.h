#ifndef OPTMIZATION_H
#define OPTMIZATION_H

#include "treno.h"

class Optimization {
public:
  Optimization(void);
  Optimization(const int& totalGifts, const int& totalTrenos, const int& trenoCapacity, const int& totalElementsL);

  int totalGifts_;
  int totalTrenos_;
  int trenoCapacity_;
  int totalElementsL_;
  std::vector<Gift> allGifts_;
  std::vector<Treno> allTrenos_;
  std::list<int>* notAllowedPresents_;

  int heuristic(void);
  void papaiNoel(void);
  void sort(void);

  void showPresents(void);
  void showTrenoGifts(void);

  bool swap_gifts(void);


private:
  Treno get_treno_to_swap(void);
  Gift get_gift_to_swap(Treno treno1, Treno treno2);
  bool gifts_can_to_be_together(const Gift& gift1, const Gift& gift2);
};

#endif
