#include<stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "../include/graph.h"
#include "../include/route.h"
#include "../include/goloso.h"


/**
 * @brief Implements a greedy algorithm to solve the problem
 * The algorithm calculate for each connected subgraph the new cost
 * and selects the lowest.
 * The algoritm finishes when there's no exists another connected 
 * subgraph with a lower cost.
 * O((n*(n-3)*(n^2 - 7*n +14)/8)*n^3  ) ~ O(n^6)
 * 
 * @param g 
 */
void Goloso(Graph * g){
    int best_cost_index = 0;
    float best_cost = cost(g);
    int sub_connected_graphs = 0;
    float aux_cost = 0;
    #ifdef DEBUG
    printCurrent(g);
    #endif
    do{
        
        if(sub_connected_graphs > 0 ){
            deleteRoute(g,best_cost_index);
            #ifdef DEBUG
            printCurrent(g);
            #endif
        }
        sub_connected_graphs = 0;
        
        
        for (int i = 0; i < g->n_routes; i++)
        {   
           
            aux_cost = 0;
            if(isConnectedWhenRemoved(g, i,&aux_cost) == 1){
                
                if(aux_cost <= best_cost){
                    best_cost = aux_cost; //The best cost is the lower total cost from all subgraphs
                    best_cost_index = i;
                    sub_connected_graphs++;
                }
                
            }
        }
    }while(sub_connected_graphs > 0);

}