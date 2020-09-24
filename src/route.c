#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"../include/graph.h"
#include"../include/route.h"

/**
 * @brief Inserts a Route in the array
 * Complexity: O(1)
 * @param routes Array of Route
 * @param n Pointer to the length of the array
 * @param r Route to be inserted
 * @return Route* 
 */
Route * insert_route(Route * routes,int *n,Route r){
    Route * out = malloc(sizeof(Route)*(*n+1));
    memcpy(out,routes,sizeof(Route)*(*n));
    *n = *n + 1;
    out[*n-1] = r;
    free(routes);
    return out;
}

/**
 * @brief Removes a Route in the array
 * Complexity: O(1)
 * @param routes Array of Route
 * @param n Pointer to the length of the array
 * @param i Index of the route to be removed
 * @return Route* 
 */
Route * remove_route(Route * routes,int *n,int i){
    Route * out = malloc(sizeof(Route)*(*n-1));
    memmove(&out[0],routes,sizeof(Route)*i);
    if(i < *n-1){
        memmove(&out[i],&routes[i+1],sizeof(Route)*(*n-i-1));
    }
    *n = *n - 1;
    free(routes);
    return out;
}


/**
 * @brief Checks if the r route is adjacent to rr Route,
 * making more easy and simple to read
 * Complexity: O(1)
 * @param r 
 * @param rr 
 * @return int 
 */
int isAdjacentRoute(Route r, Route rr){
    return (r.a == rr.a && r.b != rr.b ) || (r.a != rr.a && r.b == rr.b ) || (r.b == rr.a && r.a != rr.b) || (r.b != rr.a && r.a == rr.b);
}

/**
 * @brief Deletes a Route from the config:
 * - Counts the adjacent routes
 * - Apply the new cost for every adjacent route
 * - Adds the route to the deleted array
 * - Removes from the routes array
 * Complexity: O(n)
 * @param g Graph Struct
 * @param route_index Index of the route in the g->routes[] array to be deleted
 */
void deleteRoute(Graph * g, int route_index){
    int n = 0;
    for (int i = 0; i < g->n_routes; i++)
    {
        if(isAdjacentRoute(g->routes[i],g->routes[route_index])){
            n++;
        }
    }
    for (int i = 0; i < g->n_routes; i++)
    {
        if(isAdjacentRoute(g->routes[i],g->routes[route_index])){
            g->routes[i].cost = g->routes[i].cost + (g->routes[route_index].cost)/(n+1);
        }
    }
    g->removed_routes = insert_route(g->removed_routes,&g->n_removed_routes,g->routes[route_index]);
    g->routes = remove_route(g->routes,&g->n_routes,route_index);
}

/**
 * @brief Calculates the cost of the graph
 * Complexity: O(n)
 * @param g Graph struct
 * @return float total cost of the graph
 */
float cost(Graph * g){
    float total_cost = 0;
    for (int i = 0; i < g->n_routes; i++){
        total_cost = total_cost + g->routes[i].cost;
    }
    return total_cost;
}


/**
 * @brief Checks if the graph is completed if the i-route is removed
 * This is the most important function here.
 * - Creates a 2-dimensional integer array with 1 and 0
 * - Generates the graph in the array as an Adjacency Matrix
 * - Traverse the graph
 * Complexity: O(n^2+n+n(n+1)/2+n^3) ~ O(n^3)
 * @param g 
 * @param index 
 * @param cost 
 * @return int 
 */
int isConnectedWhenRemoved(Graph * g,int index,float * cost){
    int graph[g->countries][g->countries]; //Creates the array
    int left = g->countries*g->countries;
    /**
     * @brief If LEFT equals to zero after the algorithm this means that the graph 
     * is connected. Because every node can reach all of the other nodes using 1
     * or more edges.
     */
    int left_c[g->countries]; //Array to store number of nodes that every node has to visit.

    //Initialize the array
    for (int i = 0; i < g->countries; i++)
    {   
        for (int j = 0; j < g->countries; j++)
        {
            graph[i][j] = 0;
        }
        
    }
    //Inserts the (u,u) edges.
    for (int i = 0; i < g->countries; i++)
    {
        graph[i][i] = 1;
        left--;
        left_c[i] = g->countries-1;
    }
    int n = 0;
    //Inserts the (u,v) from the routes array in the graph, excepts the desired i-route
    for (int i = 0; i < g->n_routes; i++)
    {
        if(index != i){
            graph[g->routes[i].a-1][g->routes[i].b-1] = 1;
            graph[g->routes[i].b-1][g->routes[i].a-1] = 1;
            left = left - 2;
            left_c[g->routes[i].b-1]--;
            left_c[g->routes[i].a-1]--;
            *cost = *cost + g->routes[i].cost; // Sums the total_cost
            if(isAdjacentRoute(g->routes[i],g->routes[index])){ 
                n++;
            }
        }
    }
    *cost = *cost + (n*g->routes[index].cost)/(n+1); //The new total cost
    
    // Every complete graph is a connected graph
    if(left == 0){
        return 1;
    }
    
    /**
     * @brief The algorithm tries to search by transitivity all the possible 
     * nodes that it can reach using 1 or more edges.
     * This means if (a,b) and (b,c) => (a,c).
     * If (a,b) exists with 1 or more edges, graph[a][b] and graph[b][a] has to be 1.
     * 
     * Example:
     * If 'i' is the node, for every adjacent node 'j'. The algorithm will search for every
     * adjacent node 'k':  (i,j) and (j,k) exists => (i,k) exists. If exists means the 'i' and 'k'
     * nodes has one less node to visit. And there are two less nodes to visit.
     */
    for (int i = 0; i < g->countries; i++)
    {
        for (int j = 0; j < g->countries; j++)
        {
            if(i != j && graph[i][j] == 1){ 
                for (int k = 0; k < g->countries; k++)
                    {
                        //If LEFT is equal or below to zero, the graph is a connected graph
                        if(left <= 0){
                            return 1;
                        }
                        if( k!=i && k!=j && graph[j][k] == 1 && graph[i][k]== 0){
                            graph[i][k] = 1;
                            graph[k][i] = 1;
                            left = left-2;
                            left_c[i]--;
                            left_c[k]--;
                        }
                        //If the node i has 0 nodes to visit continues to the next node
                        if(left_c[i] == 0){
                            break;
                        }
                    }
            }
        }
    }
    if(left == 0){
        return 1;
    }
    return 0;
}
