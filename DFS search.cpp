#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;
struct node{
	int data;
	struct node *next;
};
ofstream outfile;
void dfs(int i,bool visited[],struct node *head[]){
 //mark the current node as visited and print it
    visited[i]=true;
    outfile<<i<<" ";
    struct node *ptr;
    ptr=head[i]->next;
    while(ptr!=NULL){
    	//mark data these vertices are not visited 
        if(visited[ptr->data]==false){
        	//recursive function call for dfs to traverse every vertices  
            dfs(ptr->data,visited,head);
        }
        ptr=ptr->next;
    }
}
int main()
{   

//read input from input textfile
    ifstream thefile;
    thefile.open("input.txt");
    if (thefile.fail()) {
        cout << "failures:" << endl;
        return 0;
    }
    int v1,v2, n, e,i;
   // read nodes and edges from input text file
    thefile >> n >> e;
   struct node *head[n];
   bool visited[n];
   for(i=0;i<n;i++){
       head[i]=new struct node();
       head[i]->next=NULL;
       visited[i]=false;
   }
   //iterate i till all the edges
    for (int i = 1; i < e; i++) {
//read vertices from input text file
        thefile >> v1 >> v2;
       struct node *temp;
       temp=new struct node();
       temp->data=v2;
       temp->next=head[v1]->next;
       head[v1]->next=temp;
   }
   thefile.close();
   
   // write the textfile for write the output in textfile 
   outfile.open("DFSoutput.txt");
   outfile<<"dfs traversal is"<<endl;
   //printf("dfs traversal is\n");
   // these vertices are not visited
   for(i=0;i<n;i++){
       if(visited[i]==false){
    //call the dfs function to print all the vertices
           dfs(i,visited,head);
       }
   }
outfile.close();
    return 0;
}


