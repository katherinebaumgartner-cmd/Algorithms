#ifndef PROJECT1_H
#define PROJECT1_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Item {
private:
    int id_;
    int weight_;
    int profit_;

public:
       Item();
       Item(int id, int weight, int profit);
       int getId();
       void setId(int id);
       int getWeight();
       void setWeight(int weight) ;
       void setProfit(int profit); 
       int getProfit();
       int GreedyFrac(Item items[], int n, int W);
       int GreedyNoFrac(Item items[], int n, int W);
       int DynamicProg(Item items[], int n, int W);


};

#endif
