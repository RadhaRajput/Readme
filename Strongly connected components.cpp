#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<fstream>
using namespace std;
ofstream outfile;
struct node{
    int data;
    struct node *next;
};
// implement for dfs traverse  
void dfs(struct node *adj[],bool visited[],int v,struct node *stack){
	// Mark the current node as visited start from v
    visited[v]=true;
    struct node *ptr=adj[v]->next;
    while(ptr!=NULL){
        if(visited[ptr->data]==false){
        //recursive call for dfs function
            dfs(adj,visited,ptr->data,stack);
        }
        ptr=ptr->next;
    }
    
    struct node *temp=new struct node();
    temp->data=v;
    temp->next=stack->next;
    stack->next=temp;
   
}
 
void displayConnectedComponents(struct node *adj[],bool visited[],int v){
//Mark the current node as visited and print i
     outfile<<v<<" ";
    visited[v]=true;
    struct node *ptr=adj[v]->next;
    while(ptr!=NULL){
        if(visited[ptr->data]==false){
        //recursive function call 
            displayConnectedComponents(adj,visited,ptr->data);
        }
        ptr=ptr->next;
        
    }
   
}
int main()
{
  //Read the input textfile 
ifstream thefile;
    thefile.open("input3.txt");
    if (thefile.fail()) {
        cout << "failures:" << endl;
        return 0;
    }
    int v1, v2, n, e, i;
   // number of nodes and edges read from textfile
    thefile >>n >>e;	
    struct node *adj[n],*transpose[n];
    bool visited[n];
    for(i=0;i<n;i++){
        adj[i]=new struct node();
        adj[i]->next=NULL;
        transpose[i]=new struct node();
        transpose[i]->next=NULL;
        visited[i]=false;
    }
    // iterate i for all the edges 
    for (int i = 0; i < e; i++) {
        thefile >> v1 >> v2;
        struct node *temp=new struct node();
        temp->data=v2;
        temp->next=adj[v1]->next;
        adj[v1]->next=temp;
    //create(transpose) for reverse of the graph (node)
        struct node *transpose_temp= new struct node();
        transpose_temp->data=v1;
        transpose_temp->next=transpose[v2]->next;
        transpose[v2]->next=transpose_temp;
    }
    //close  the readfile
    thefile.close();
    //create stack
    struct node *stack = new struct node();
    
    stack->next=NULL;
    for(i=0;i<n;i++){
 // Mark the current node as visited
        if(visited[i]==false){
    //call for dfs function t
            dfs(adj,visited,i,stack);
        }
    }
     for(i=0;i<n;i++){
        visited[i]=false;
    }
   // writing the outputtext file 
  outfile.open("SSCoutput.txt");
  outfile<<"Connected components are"<<endl;
    struct node *ptr=stack->next;
    while(ptr!=NULL){
        if(visited[ptr->data]==false){
        displayConnectedComponents(transpose,visited,ptr->data);
            outfile<<endl;
        }
        ptr=ptr->next;
       }
 // close the outpul textfile   
outfile.close();
    return 0;
}
