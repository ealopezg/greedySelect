#include<stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "../include/graph.h"
#include "../include/route.h"
#include "../include/goloso.h"



int main(int argc, char const *argv[])
{
    if(argc !=3){ //The program needs the input and output filename
        return 0;
    }
    Graph *g = openFile(argv[1]); // Creates the Config object
    if(g != NULL){
        Goloso(g); //Runs the algorithm
        writeFile(g,argv[2]); //Saves the file
        freeGraph(g);
    }
    return 0;
}
