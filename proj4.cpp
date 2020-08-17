#include<bits/stdc++.h> 
using namespace std;

//declaring a struct edge
struct edge{
    int v1;
    int v2;
    int w;
};

//sort edges in a tree or array according to weights
void sortEdges(int size , struct edge * edges){
    for(int i=0;i<size;i++){
        for(int j=i+1;j<size;j++){
            if(edges[i].w > edges[j].w){
                struct edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

//print the final tree
void printTree(int n , struct edge * treeEdges){
    printf("Edges of the Minimum Spanning Tree are\n");
    for(int i=0;i<n;i++){
        printf("Edge %d : Vertices (%d-%d) , Weight %d\n",i+1,treeEdges[i].v1,treeEdges[i].v2,treeEdges[i].w);
    }
    cout<<"\n\n";
}

//-----------------prims---------------------------

void prims(int n, vector<vector<int> > a){
    int mstSet[n];  //array indicating whether node i is present in the set or not
    int nEdges=0;   //number of edges currently present in the mst
    struct edge treeEdges[n-1]; //minimum spanning tree
    
    for(int i=0;i<n;i++) mstSet[i]=0;   //initially no nodes are present in mst set
    mstSet[0]=1;    // add first node to mst set

    while(nEdges<n-1){      //keep on adding edges till n-1
        int min = 9999;
        int min_i=0,min_j=0;
        for(int i=0;i<n;i++){
            if(mstSet[i]==1){
                for(int j=0;j<n;j++){
                    if(a[i][j]>0 && mstSet[j]==0 && min>a[i][j]){
                        min=a[i][j];    //update minimum in each iteration
                        min_i=i;
                        min_j=j;
                    }
                }
            }
        }
        treeEdges[nEdges].v1=min_i;
        treeEdges[nEdges].v2=min_j;
        treeEdges[nEdges].w =min;
        nEdges++;
        mstSet[min_j]=1;    //add min_j to mst set
    }

    sortEdges(nEdges,treeEdges);    //sort edges in ascending order
    cout<<"Prims algorithm : \n";
    printTree(nEdges,treeEdges);

}

//------------------kruskals------------------------


int find3(int* parent , int v){         //return the root parent of the node
    while(parent[v]!=-1) v=parent[v];   
    return v;
}

int union3(int* parent , int u , int v){     //joins nodes u and v
    if(u!=v){
        parent[v]=u;
        return 1;
    }
    return 0;
}

void kruskals(int n , vector<vector<int> > a){
    int parent[n];
    struct edge edges[(n*(n+1))/2];       //all the edges
    int edgesSize=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){         //here it starts from j=i+1 because the graph is undirected
            if(a[i][j]!=0){
                edges[edgesSize].v1=i;
                edges[edgesSize].v2=j;
                edges[edgesSize].w =a[i][j];
                if(a[i][j]==0) edges[edgesSize].w=999;
                edgesSize++;
            }
        }
    }
    sortEdges(edgesSize,edges);             //sort all the edges
    for(int i=0;i<n;i++) parent[i]=-1;
    int nEdges=0;
    struct edge treeEdges[n-1];
    int treeSize=0;
    for(int i=0;i<edgesSize;i++){
        if(nEdges>=n) break;            //the most important condition
        int v1 = edges[i].v1;
        int v2 = edges[i].v2;
        int w = edges[i].w;
        v1 = find3(parent,v1);
        v2 = find3(parent,v2);
        if(union3(parent,v1,v2)){                       //joins if v1 and v2 are not same
            treeEdges[treeSize].v1=edges[i].v1;
            treeEdges[treeSize].v2=edges[i].v2;
            treeEdges[treeSize].w=edges[i].w;
            treeSize++;
        }
    }
    cout<<"Kruskal's algorithm : \n";
    printTree(n-1,treeEdges);
}



//-----------------main-------------------

void printMat(int n, vector<vector<int> >a){
    cout<<"\nGenerated adjacency matrix is : \n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) printf("%d ",a[i][j]);
        printf("\n");
    }
    cout<<"\n";
}

int main(){
    srand(time(NULL));
    int n;
    n = (rand()%6) + 5;
    cout<<"\nChosen n value is : "<<n<<"\n";
    // printf("Chose a n value : ");
    // scanf("%d",&n);
    vector<vector<int> > a( n , vector<int> (n));
    for(int i=0;i<n;i++){
        a[i][i]=0;
        for(int j=i+1;j<n;j++){
            a[i][j] = a[j][i] = (rand()%10) + 1;     //initiate to random values
        }
    }

    printMat(n,a);

    char algo[100];
    while(strcmp(algo,"prims")!=0&&strcmp(algo,"kruskals")!=0){
        printf("Please enter one of the following\nprims\nkruskals\n\n");
        scanf("%s",algo);
    }

    if(strcmp(algo,"prims")==0){
        prims(n,a);
    }

    else if(strcmp(algo,"kruskals")==0){
        kruskals(n,a);
    }
    
    return 0;
}
