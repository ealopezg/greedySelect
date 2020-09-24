#ifndef ROUTE_H
#define ROUTE_H
typedef struct Graph Graph;
typedef struct Route
{
    int a,b;
    float cost;
} Route;
Route * insert_route(Route * routes,int *n,Route r);
Route * remove_route(Route * routes,int *n,int i);
void deleteRoute(Graph * g, int route_index);
int isAdjacentRoute(Route r, Route rr);
float cost(Graph * g);
int isConnectedWhenRemoved(Graph * g,int index,float * cost);
#endif