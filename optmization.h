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
  int* allGiftsSortedIndex_;

  std::vector<Gift> allGifts_;
  std::vector<Treno> allTrenos_;

  int heuristic(void);
  void papaiNoel(void);
  void showPresents(void);
  void showTrenoGifts(void);
  void showSortedPresents(void);


  void QuickSort(int inicio, int fim);
  // list<Treno> swap_gifts(void);
  int reinsertion(void);
  void removeAllTrenosEmpty(void);
  list<Treno> swap_gifts(void);
  int mergeTrenos(void);

  int vnd(void);

  void perturbation(void);
  int ils(void);
};

#endif
