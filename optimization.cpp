#include "optmization.h"

Optimization::Optimization( void ) {

}

Optimization::Optimization( const int& totalGifts, const int& totalTrenos, const int& trenoCapacity, const int& totalElementsL ):
  totalGifts_(totalGifts), trenoCapacity_(trenoCapacity), totalTrenos_(totalTrenos), totalElementsL_(totalElementsL) {
    this->allGiftsSortedIndex_ = new int[this->totalGifts_];
  }


void Optimization::showPresents( void ) {
  for ( auto& obj : this->allGifts_ ) {
    std::cout << "id: " << obj.id_ << " weight: " << obj.weight_ << std::endl;
    for (auto& gift : obj.notAllowedPresents_){
      std::cout << gift << ", ";
    }
    std::cout << std::endl;
     
  }
}

void Optimization::showSortedPresents( void ) {
  for ( int i =0; i < this->totalGifts_; i++ ) {
    std::cout << "id: " << this->allGifts_[this->allGiftsSortedIndex_[i]].id_ << " weight: " << this->allGifts_[this->allGiftsSortedIndex_[i]].weight_ << std::endl;
    for (auto& gift : this->allGifts_[this->allGiftsSortedIndex_[i]].notAllowedPresents_){
      std::cout << gift << ", ";
    }
    std::cout << std::endl;
     
  }
}

int Optimization::heuristic( void ) { 
  this->QuickSort(0, this->totalGifts_-1);

  for (int i = 0; i < this->totalGifts_; i++){
    for (auto& treno : this->allTrenos_){
    
      if(treno.gifts_.empty() && this->allGifts_[this->allGiftsSortedIndex_[i]].idTreno_ == -1){

        this->allGifts_[this->allGiftsSortedIndex_[i]].idTreno_ = treno.id_;
        treno.gifts_.push_back(this->allGifts_[this->allGiftsSortedIndex_[i]].id_);
        treno.capacity_ = treno.capacity_ - this->allGifts_[this->allGiftsSortedIndex_[i]].weight_;

      }else{
        
      }
    }
  
  }
  return 0;
 
}
  
void Optimization::papaiNoel( void ) { 
  this->heuristic();
}

void Optimization::showTrenoGifts( void ) {
  for ( auto& treno : this->allTrenos_ ) {
    std::cout << "treno " << treno.id_ << std::endl;
    for ( auto& gift : treno.gifts_ ) {
      std::cout << "gift: " << this->allGifts_[gift].id_ << " peso: " << this->allGifts_[gift].weight_ << std::endl;
    }
  }
}


void Optimization::QuickSort(int inicio, int fim){

    int i,j,pivo,aux;
    if(inicio < fim){  
      pivo = this->allGifts_[this->allGiftsSortedIndex_[inicio]].weight_;
      i = inicio;
      j = fim;

      while(i < j){
        while(this->allGifts_[this->allGiftsSortedIndex_[i]].weight_ <= pivo && i < fim)
          i++;
        while(this->allGifts_[this->allGiftsSortedIndex_[j]].weight_ > pivo)
          j--;
      
        if(i < j){
          aux = this->allGiftsSortedIndex_[i];
          this->allGiftsSortedIndex_[i] = this->allGiftsSortedIndex_[j];
          this->allGiftsSortedIndex_[j] = aux;
        }
      }
      aux = this->allGiftsSortedIndex_[inicio];
      this->allGiftsSortedIndex_[inicio] = this->allGiftsSortedIndex_[j];
      this->allGiftsSortedIndex_[j] = aux;
      this->QuickSort(inicio,j-1);
      this->QuickSort(j+1,fim);

  }
}
