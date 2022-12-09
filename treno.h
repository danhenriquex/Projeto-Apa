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

class Treno {
  public:
    Treno( void );
    Treno( const int& id, const int& capacity ) : id_(id), capacity_(capacity) {};
    
    int capacity_;
    int id_;
    std::vector<int> gifts_;
};

#endif