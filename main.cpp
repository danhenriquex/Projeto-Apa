

#include "optmization.h"

using namespace std;

int main(void) {

  auto readFile = [](const std::string& file) {
    std::ifstream text(file);
    std::string temp;
    int item;
    std::vector<int> infos;

    text >> temp;

    for (int i = 0; i < 4; ++i) {
      text >> item;

      infos.push_back(item);
    }

    Optimization opt = Optimization(infos[0], infos[1], infos[2], infos[3]);
    for (int i = 0; i < opt.totalGifts_; ++i) {
      opt.allGiftsSortedIndex_[i] = i;

      text >> item;

      Gift gift = Gift(i, item, false, -1);

      opt.allGifts_.push_back(gift);
    }

    int item1;
    int item2;
    for (int i = 0; i < opt.totalElementsL_; ++i) {
      text >> item1;
      text >> item2;

      opt.allGifts_[item1 - 1].notAllowedPresents_.push_back(item2 - 1);
      opt.allGifts_[item2 - 1].notAllowedPresents_.push_back(item1 - 1);

    }

    for (int i = 0; i < opt.totalTrenos_; ++i) {

      Treno treno = Treno(i, opt.trenoCapacity_);

      opt.allTrenos_.push_back(treno);

    }

    return opt;
  };

  auto opt = readFile("./instancias/instances/n30_k150_A.txt");

  // opt.papaiNoel();
  cout << "Trenos: " << opt.allTrenos_.size() << endl;
  int solution = opt.ils();

  for (auto& treno : opt.allTrenos_) {
    cout << treno;
  }
  cout << "Trenos: " << solution << endl;

  return 0;

}


