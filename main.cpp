

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

  auto opt = readFile("./instancias/instances/n120_k150_B.txt");
  // auto opt = readFile("./instancias/instancias_grandes/n1000_k200_B.txt");

  int initial_trenos = opt.allTrenos_.size();
  auto startH = chrono::high_resolution_clock::now();
  int solucaoHeuristica = opt.heuristic();
  auto finishH = chrono::high_resolution_clock::now();

  chrono::duration<double> elapsedH = finishH - startH;

  cout << "Heuristica" << endl;
  cout << "Tempo de execução: " << elapsedH.count() * 1000 << " ms\n";
  cout << "Quantidade de trenos iniciais: " << initial_trenos << endl;
  cout << "Quantidade de trenos após o algortimo: " << solucaoHeuristica << endl;

  auto startVND = chrono::high_resolution_clock::now();
  int solutionVND = opt.vnd();
  auto finishVND = chrono::high_resolution_clock::now();

  chrono::duration<double> elapsedVND = finishVND - startVND;

  cout << endl << "VND" << endl;
  cout << "Tempo de execução: " << elapsedVND.count() * 1000 << " ms\n";
  cout << "Quantidade de trenos iniciais: " << initial_trenos << endl;
  cout << "Quantidade de trenos após o algortimo: " << solutionVND << endl;


  auto start = chrono::high_resolution_clock::now();
  int solution = opt.ils();
  auto finish = chrono::high_resolution_clock::now();

  chrono::duration<double> elapsed = finish - start;

  cout << endl << "ILS" << endl;
  cout << "Tempo de execução: " << elapsed.count() * 1000 << " ms\n";
  cout << "Quantidade de trenos iniciais: " << initial_trenos << endl;
  cout << "Quantidade de trenos após o algortimo: " << solution << endl;

  return 0;

}


