#include <iostream>
#include <math.h>
#include <stdio.h>
#include <limits.h>

using namespace std;

// Number of vertices in the graph
int V;
double Matriz[100][100];

struct distPecas{
    double x,y;
    
};

double distancia(distPecas uno,distPecas dos){
    return sqrt((dos.x-uno.x)*(dos.x-uno.x)+(dos.y-uno.y)*(dos.y-uno.y));
}

// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    
    return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void printMST(int parent[]){
    double acum=0;
   // printf("Edge   Weight\n");
    for (int i = 1; i < V; i++){
        acum+=Matriz[i][parent[i]];
    }
printf("%.2f\n", acum);
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST()
{
    int parent[V]; // Array to store constructed MST
    int key[V];   // Key values used to pick minimum weight edge in cut
    bool mstSet[V];  // To represent set of vertices not yet included in MST
    
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    
    // Always include first 1st vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST
    
    // The MST will have V vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick thd minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
        
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
        
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < V; v++)
            
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (Matriz[u][v] && mstSet[v] == false && Matriz[u][v] <  key[v])
                parent[v]  = u, key[v] = Matriz[u][v];
    }
    
    // print the constructed MST
    printMST(parent);
}


// driver program to test above function
int main(){
    cin>>V;
    distPecas arr[100];
    
    for (int i=0; i<V; i++) {
        cin>>arr[i].x>>arr[i].y;
    }
    for (int j=0; j<V; j++) {
        Matriz[j][j]=0;
    }
    
    for (int ix=0; ix<V; ix++) {
        for (int iy=ix+1; iy<V; iy++) {
            Matriz[ix][iy]=Matriz[iy][ix]=distancia(arr[ix], arr[iy]);
        }
    }
    primMST();
    
    return 0;
}