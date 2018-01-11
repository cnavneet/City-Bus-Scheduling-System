#include <iostream>
using namespace std;
#include <stdio.h>
#include <limits.h>
#define V 9
// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
// Function to print shortest path from source to j
// using parent array
void printPath(int parent[], int j)
{
    if (parent[j]==-1)
        return;
    printPath(parent, parent[j]);
    printf("%d ", j);
}
// A utility function to print the constructed distance
// array
int printSolution(int dist[], int n, int parent[])
{
    int src = 0;
    printf("Vertex\t  Distance\tPath");
    for (int i = 1; i < V; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
}

void allotment(char busn[][5], int dist[], int parent[],int n)
{int order[V];
  for(int i=0;i<V;i++)
     order[i]=dist[i];
   int temp;
    for(int k = 0; k< V-1; k++) {
        for(int i = 0; i < V-k-1; i++) {
            if(order[ i ] < order[ i+1] ) {
                temp = order[ i ];
                order[ i ] = order[ i+1 ];
                order[ i + 1] = temp;
            }
        }
    }
   for(int i=0;i<n;i++)
   {

       for(int j=0;j<V;j++)
       {
           if(order[i%(V-1)]==dist[j])
           {
       cout<<"\n";
           for(int m=0;m<5;m++)
                cout<<busn[i][m];
        cout<<"\t is scheduled along :\t\t"<<0<<" ";
         printPath(parent,j);
           }
       }
   }
   return;
}

// Function that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V];  // The output array. dist[i] will hold
                  // the shortest distance from src to i
    bool sptSet[V];
    int parent[V];
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // print the constructed distance array
    printSolution(dist, V, parent);
    int n;
    cout<<"\n Enter number of buses available at the depot:";
    cin>>n;
    char busn[n][5];
    for(int i=0;i<n;i++)
    {
	cout<<"\n Enter bus no: ";
	cin>>busn[i];
    }
    allotment(busn,dist,parent,n);
}

// driver program to test above function

int main()
{
    cout<<" ******************************************************************************"<<endl;
		cout<<" ******* ******* ******* ******* ******* ******* ******* ******* *******"<<endl;
		cout<<"		       * City Bus Scheduling System*"<<endl;
		cout<<"		       * Mumbai Transport Service *"<<endl;
		cout<<" ******* ******* ******* ******* ******* ******* ******* ******* *******"<<endl;
		cout<<" ******************************************************************************"<<endl;

    /* Let us create the example graph discussed above */
    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 0, 10, 0, 2, 0, 0},
                       {0, 0, 0, 14, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}
                      };

    dijkstra(graph, 0);
    return 0;
}
