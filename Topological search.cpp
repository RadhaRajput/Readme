#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
struct node{
    int data;
    struct node *next;
};
int main()
{
//read the input from input textfile 
  ifstream thefile;
    thefile.open("topologicalinput.txt");
    if (thefile.fail()) {
        cout << "failures:" << endl;
        return 0;
    }
    
    int v1, v2, n, e, i;
   // number of node and edges read from textfile
    thefile >>n >>e;
    int inDegree[n];
   // create one pointer of array 
    struct node *head[n];
    for(i=0;i<n;i++){
        head[i]=new struct node();
        head[i]->next=NULL;
        inDegree[i]=0;
    }
 //  iterate i till end of the edges 
    for (int i = 0; i < e; i++) {
    	// read vertices from textfile  
        thefile >> v1 >> v2;
        struct node *temp;
        temp = new struct node();
        temp->data=v2;
        temp->next=head[v1]->next;
        head[v1]->next=temp;
        inDegree[v2]++;
}

 thefile.close();
  //create four struct type pointer
    struct node *l,*s,*curr_l,*curr_s;
    l=new struct node();
    s=new struct node();
    l->next=NULL;
    s->next=NULL;
    curr_l=l;
    curr_s=s;
    
   // traverse all the nodes 
        for(i=0;i<n;i++){
    //currrent current node has no incoming edges 
        if(inDegree[i]==0){
            struct node *temp=new struct node();
            temp->data=i;
            temp->next=NULL;
            curr_s->next=temp;
            curr_s=temp;
        }
    }
    
    while(s->next!=NULL){
        int vertex=s->next->data;
        struct node *temp=new struct node();
        temp->data=vertex;
        temp->next=NULL;
        curr_l->next=temp;
        curr_l=temp;
        struct node *ptr=head[vertex]->next;
        while(ptr!=NULL){
            inDegree[ptr->data]--;
            if(inDegree[ptr->data]==0){
                 struct node *temp1=new struct node();
                 temp1->data=ptr->data;
                 temp1->next=NULL;
                 curr_s->next=temp1;
                 curr_s=temp1;
            }
            ptr=ptr->next;
        }
        s->next=s->next->next;
    }
    for(i=0;i<n;i++){
    	//current node has no incoming edge then graph has at least one cycle
        if(inDegree[i]!=0){
            cout<<"Graph has cycle";
            return 0;
        }
    }
    struct node *ptr=l->next;
    
    printf("Topological sort is\n");
    
    //write the output in textfile
    ofstream outfile;
      outfile.open("Topologicaloutput.txt");
   
    while(ptr!=NULL){
        outfile << ptr->data<<" ";
        ptr=ptr->next;
    }
    outfile.close();
    return 0;
}

