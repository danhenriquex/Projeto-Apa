#ifndef OPTMIZATION_H
#define OPTMIZATION_H

#include "treno.h"

class Optimization {
  public:
    Optimization( void );
    Optimization( const int& totalGifts, const int& totalTrenos, const int& trenoCapacity, const int& totalElementsL );

    int totalGifts_;
    int totalTrenos_;
    int trenoCapacity_;
    int totalElementsL_;
    std::vector<Gift> allGifts_;
    std::vector<Treno> allTrenos_;
    std::list<int>* notAllowedPresents_;

    int heuristic( void );
    void papaiNoel( void );
    void sort( void );

    void showPresents( void );
    void showTrenoGifts( void );

    void swap_gifts( void );
};

#endif
