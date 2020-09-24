#include<stdio.h>
#include<stdlib.h>

#include"../include/route.h"
#include"../include/graph.h"

/**
 * @brief Opens the input file and
 * creates a Graph object
 * 
 * @param filename i.e entrada1.in
 * @return Graph* 
 */
Graph * openFile(const char * filename){
    
    FILE * f;
    f = fopen (filename, "r");
    if(f == NULL){
        fclose(f);
        return NULL;
    }
    // If the file is not null
    char buffer[1000]; // Buffer to store the entire file
    Graph *g = malloc(sizeof(Graph)); // Create a new graph object

    char ch;
    int i = 0;
    while ((ch = fgetc(f)) != EOF) // Reads the file until EOF
    {   
        if(ch == '\n'){  // Replaces the newline with an space
            buffer[i] = ' ';
        }
        else{
            buffer[i] = ch;
        }
        i++;
    }
    fclose(f); // Closes the file
    
    buffer[i] = '\0';
    int n = 0;
    char *aux = &buffer[0]; // Pointer to the start to buffer

    sscanf(aux, "%d %n" ,&g->countries,&n); //Saves the number of countries, the &n stores the bytes left in the pointer
    aux = aux + n;

    g->n_routes = ((g->countries*(g->countries -1))/2);
    g->routes = malloc( g->n_routes * sizeof(Route)); //Creates the array of Routes
    g->n_removed_routes = 0;
    for (int i = 0; i < g->n_routes; i++)
    {
        sscanf(aux, "%d %d %f %n", &g->routes[i].a, &g->routes[i].b ,&g->routes[i].cost,&n); //Store the nodes of each edge and the cost
        aux = aux + n; //Moves the pointer
    }
    return g;
}

/**
 * @brief Write a file with solution of the problem.
 * 
 * @param c Graph Object
 * @param st Optimal Status
 * @param filename i.e salida.out
 */
void writeFile(Graph * g,const char*filename){
    char * buffer = graphToString(g);
    FILE *fp;
    fp = fopen(filename, "w+");
    fputs(buffer,fp);
    fclose(fp);
    free(buffer);

}
#ifdef DEBUG
/**
 * @brief Prints the actual status of the graph
 * 
 * @param g Graph
 */
void printCurrent(Graph * g){
    char * buffer = graphToString(g);
    printf("Estado actual:\n%s\n\n",buffer);
    free(buffer);
}
#endif

/**
 * @brief Transform the graph to an string
 * to show or save to a file
 * 
 * @param g Graph
 * @return char* String
 */
char * graphToString(Graph * g){
    char*buffer=malloc(sizeof(char)*1000);
    int a = 0;
    float total_cost = 0;
    for(int i=0;i<g->n_removed_routes;i++){
        a = snprintf(buffer+a,1000-a,"%d %d %.1f\n",g->removed_routes[i].a,g->removed_routes[i].b,g->removed_routes[i].cost)+a;
    }
    a = snprintf(buffer+a,1000-a,"--\n")+a;
    for (int i = 0; i < g->n_routes; i++)
    {
        a = snprintf(buffer+a,1000-a,"%d %d %.1f\n",g->routes[i].a,g->routes[i].b,g->routes[i].cost)+a;
        total_cost = total_cost + g->routes[i].cost;
    }
    
    a = snprintf(buffer+a,1000-a,"--\ncosto total: %.1f",total_cost)+a;
    return buffer;
}


/**
 * @brief To free up the memory
 * 
 * @param g 
 */
void freeGraph(Graph * g){
    free(g->routes);
    free(g->removed_routes);
    free(g);
}