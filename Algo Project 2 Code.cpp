#include <iostream>
#include <array>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>

//item struct 
struct item {
  int id;
  int weight; 
  int profit; 
};

struct Node{
    int index;
    int weight; 
    int profit; 
    float bound;  
     
};

struct Compare {
    bool operator()(Node const& a, Node const& b) {
        return a.bound < b.bound; // higher bound = higher priority
    }
};

float bound(Node u, int n, int W, int weight[], int profit[]){
    if(u.weight >= W){
        return 0; 
    }

    float result = u.profit; 
    int j = u.index + 1; 
    int totweight = u.weight; 

    while(j < n && totweight + weight[j] <= W){
        totweight += weight[j]; 
        result += profit[j]; 
        j++;
    }

    if(j < n){
        result += (W - totweight) * ((float)profit[j] / weight[j]); 
    }

    return result; 
}

int backtracking(int W, int n, int weight[], int profit[] )
{
    std::stack<Node> st; 
    
    Node u, v;
    int maxprofit = 0; 

    //root node
    v.index = -1; 
    v.profit = 0; 
    v.weight = 0;
    v.bound = bound(v, n, W, weight, profit);  

    st.push(v); 

    while(!st.empty()){
        v = st.top(); 
        st.pop(); 

   
        
        if(v.bound > maxprofit){
            u.index = v.index + 1; 

            if(u.index >= n) continue; 

            //include
            u.weight = v.weight + weight[u.index]; 
            u.profit = v.profit + profit[u.index];

            if(u.weight <= W && u.profit > maxprofit){
                maxprofit = u.profit; 
            }

            u.bound = bound(u, n, W, weight, profit); 

            if(u.bound > maxprofit){
                st.push(u); 
            }

            //exclude
            u.weight = v.weight; 
            u.profit = v.profit; 
            u.index = v.index + 1; 
            u.bound = bound(u, n, W, weight, profit); 

            if(u.bound > maxprofit){
                st.push(u); 
            }
        }
    }

    return maxprofit; 
        
}

int breathFirstSearch(int W, int n, int weight[], int profit[]){
    int maxProfit = 0; 
    std::queue<Node> q; 

    Node u, v; 
    v.index = -1; 
    v.profit = 0; 
    v.weight = 0; 
    v.bound = bound(v, n, W, weight, profit); 

    q.push(v); 

    while(!q.empty()){
        v = q.front(); 
        q.pop(); 

        //only continue if promising 
        if(v.bound > maxProfit){
            u.index = v.index + 1; 
            
            if(u.index >= n){
                continue; 
            }

            //include
            u.weight = v.weight + weight[u.index]; 
            u.profit = v.profit + profit[u.index]; 

            if(u.weight <= W && u.profit > maxProfit){
                maxProfit = u.profit; 
            }

            u.bound = bound(u, n, W, weight, profit); 

            if(u.bound > maxProfit){
                q.push(u); 
            }

            //exclude
            u.weight = v.weight; 
            u.profit = v.profit; 

            u.bound = bound(u, n, W, weight, profit); 
            if(u.bound > maxProfit){
                q.push(u); 
            }
        }
    }

    return maxProfit; 
    
}

int bestFirstSearch(int W, int n, int weight[], int profit[]){
    int maxProfit = 0; 
    std::priority_queue<Node, std::vector<Node>, Compare> pq; 

    Node u, v; 
    v.index = -1; 
    v.profit = 0; 
    v.weight = 0; 
    v.bound = bound(v, n, W, weight, profit); 

    pq.push(v); 

    while(!pq.empty()){
        v = pq.top(); 
        pq.pop(); 

        //only continue if promising 
        if(v.bound > maxProfit){
            u.index = v.index + 1; 
            
            if(u.index >= n){
                continue; 
            }

            //include
            u.weight = v.weight + weight[u.index]; 
            u.profit = v.profit + profit[u.index]; 

            if(u.weight <= W && u.profit > maxProfit){
                maxProfit = u.profit; 
            }

            u.bound = bound(u, n, W, weight, profit); 

            if(u.bound > maxProfit){
                pq.push(u); 
            }

            //exclude
            u.weight = v.weight; 
            u.profit = v.profit; 

            u.bound = bound(u, n, W, weight, profit); 
            if(u.bound > maxProfit){
                pq.push(u); 
            }
        }
    }

    return maxProfit; 
    
}



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) 
{
    int weight[] = {2, 5, 7, 3, 1}; 
    int profit[] = {20, 30, 35, 12, 3}; 
    int W = 9; 
    int n = 5; 

    std::vector<item> items;

    for (int i = 0; i < n; i++) {
        items.push_back({i, weight[i], profit[i]});
    }

    std::sort(items.begin(), items.end(), [](item a, item b){
        return (double)a.profit/a.weight > (double)b.profit/b.weight; 
    });

    for(int i = 0; i < n; i++){
        weight[i] = items[i].weight; 
        profit[i] = items[i].profit; 
    }
    
    int backtrack = backtracking(W, n, weight, profit); 
    int bfs = breathFirstSearch(W, n, weight, profit); 
    int bestfirst = bestFirstSearch(W, n, weight, profit); 

    std::cout << "MAX PROFIT (Backtracking): " << backtrack << std::endl; 
    std::cout << "MAX PROFIT (BFS): " << bfs << std::endl; 
    std::cout << "MAX PROFIT (Best First): " << bestfirst << std::endl; 


    return EXIT_SUCCESS;
};
