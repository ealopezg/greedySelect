#ifndef GRAPH_H
#define GRAPH_H
typedef struct Route Route;
typedef struct Graph
{
    int countries; 
    Route * routes;
    Route * removed_routes;
    int n_routes;
    int n_removed_routes;
} Graph;

Graph* openFile(const char *filename);
void writeFile(Graph * g,const char* filename);
void printCurrent(Graph * g);
char* graphToString(Graph * g);
void freeGraph(Graph * g);
#endif