#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "project1.h"

using namespace std;
//constructor
Item::Item(int id, int weight, int profit)
{
    id_      = id;
    weight_  = weight;
    profit_  = profit;
}
 
int Item::GreedyNoFrac(Item items[], int n, int W)
{
    //same thing for frac just a little different
    //sorting 
    int key=0;
    for (int i=1; i < n; i++)
    {
        key = items[i].getProfit();
        int j = i-1;
        while(j >= 0 && items[j].getProfit() < key)
        {
            items[j+1].setProfit(items[j].getProfit());
            j = j-1;
        }
        items[i].setProfit(key);
    }
    //if weight is less than or equal to unused then add to total profit - print out as selected 
    int unused = W;
    int totalProfit = 0;

    //loop through whole array of items (size n)
    for(int i=0; i < n; i++)
    {
        if(items[i].getWeight() <= unused)
        {
            //print out item as part of a solution set 
            totalProfit += items[i].getProfit();
            unused -= items[i].getWeight();
        }
    }
    cout<< "total profit is: " << totalProfit<<endl;
    return totalProfit;
    
}
int Item::GreedyFrac(Item items[], int n, int W)
{
    int key=0;
    for (int i=1;i < n; i++)
    {
        key = items[i].getProfit();
        int j = i-1;
        while(j >= 0 && items[j].getProfit() < key)
        {
            items[j+1].setProfit(items[j].getProfit());
            j = j-1;
        }
        items[i].setProfit(key);
    }
    //if weight is less than or equal to unused then add to total profit/ print out as selected 
    int unused = W;
    int totalProfit = 0;

    for (int i = 0; i < n; i++) 
    {
        //adding the whole 
        if (items[i].getWeight() <= unused) 
        {
            totalProfit += items[i].getProfit();
            unused -= items[i].getWeight();
        }
        else 
        {
            totalProfit += items[i].getProfit() * ((double)unused / items[i].getWeight());
            unused = 0;
            break;
        }
    }
    //loop through whole array of items - size n
    for(int i=0; i < n; i++)
    {
        if(items[i].getWeight() <= unused)
        {
            //print out item as part of solution set 
            totalProfit += items[i].getProfit();
            unused -= items[i].getWeight();
        }
    }
    cout<< "total profit is: " << totalProfit<<endl;
    return totalProfit; 
}

int Item::DynamicProg(Item items[], int n, int W)
{
    //used AI for this program 
    int** dp = new int*[n + 1];
    for (int i = 0; i <= n; i++)
        dp[i] = new int[W + 1]{};   

    // Fill table
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            // Option 1: skip item i
            dp[i][w] = dp[i - 1][w];

            // Option 2: take item i only if it fits
            if (items[i - 1].getWeight() <= w)
            {
                int valueIfTaken = dp[i - 1][w - items[i - 1].getWeight()]
                                   + items[i - 1].getProfit();

                if (valueIfTaken > dp[i][w])
                    dp[i][w] = valueIfTaken;
            }
        }
    }

    // Backtrack to find which items were selected
    cout << "\n--- Dynamic Programming (0-1) ---\n";
    cout << "Selected items:\n";

    int w = W;
    for (int i = n; i >= 1; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            cout << "  Item " << items[i - 1].getId()
                 << " (weight = " << " "<< items[i - 1].getWeight()<< " "
                 << "profit = " << " " << items[i - 1].getProfit() << ")\n";

            w -= items[i - 1].getWeight();
        }
    }

    int result = dp[n][W];
    cout << "Total profit: " << result << "\n"<<endl;

    for (int i = 0; i <= n; i++)
        delete[] dp[i];
    delete[] dp;

    return result;

}


int Item::getId()
{
    return id_;
}
void Item::setId(int id) 
{
    id_=id;
}
int Item::getWeight() 
{
    return weight_;
}
void Item::setWeight(int weight) 
{
    weight_=weight;
}
void Item::setProfit(int profit) 
{
    profit_= profit;
}
int Item::getProfit() 
{
    return profit_;
}

int main() 
{
    //creating the arrays so that you don't have to use different arrays for this 
    Item i{1,2,20};
    Item ii{2,5,30};
    Item iii{3,7,25};
    Item iiii{4,3,12};
    Item iiiii{5,1,3};
    Item items[]= {i,ii,iii,iiii,iiiii};
    int n= 5;
    int W = 9;

    items[0].GreedyNoFrac(items, n, W);
    items[0].GreedyFrac(items, n, W);
    items[0].DynamicProg(items, n, W);

}
