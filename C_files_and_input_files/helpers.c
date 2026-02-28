/* C File that stores the helper functions for graph processing
   Programmer: Stefan
   Code Tester: Martin and Stefan
*/
#include <stdio.h>
#include <string.h>
#include "sort.h"

//typedef declaration of custom string types to be used
typedef char vertex[9];
typedef char string[25];

//Checker to avoid redundant edges being added into the edges array 
//ex. edge "(B,A)" is not added into the edges array because "(A,B)" already exists
int checkEdge(vertex a, vertex b, vertex first[], vertex second[], int maxEdges){
	for (int i=0; i<maxEdges; i++){
		if(strcmp(a,second[i])==0 && strcmp(b,first[i])==0) //compares the first half of the edge to the array of second halves and vice versa
			return 0;									    
	}
	return 1;
}

//Checker to avoid redundant vertices from being added into the queue array
int checkDuplicate(vertex adj[20][20], int queue[], int key, int qIndex){
	int retval=1;
	
	for (int i=0; i<qIndex; i++){
		if(queue[i]==key)
			retval=0;
	}
	
	return retval;
}

//Recursive function for Depth First Search traversal
void DFS(FILE* ptr, int visited[], vertex adj[20][20], int start, int adj2[20][20], int vCount){
	fprintf(ptr,"%s ", adj[start][0]);
    visited[start]=1; //marks the current vertex as visited
	
	for(int j=0; j<vCount; j++) //for loop to iterate through the current vertex's edges
       if(!visited[j] && adj2[start][j]==1) //when a vertex shares an edge with the current vertex and also has not been visited, call DFS again to repeat the process for that vertex
            DFS(ptr,visited,adj,j,adj2,vCount); //recursive call for the function
}

//Function to add indexes in the queue array for BFS
void Add(int queue[], int add, int vCount){
	int go=1;
	
	for(int i=0; i<vCount && go; i++)
		if(queue[i]==-1){
			queue[i]=add;
			go=0;
		}
}

//Recursive function for Breadth First Search traversal
void BFS(vertex adj[20][20], int adj2[20][20], int visited[], int queue[], int start, int vCount, int main){
	
	visited[start]=1; //mark the current vertex as visited
	
	if (main)	//Will only run once upon the first call of the function since all vertices will be added in the for loop below
		Add(queue, start, vCount);
	
	for (int i=0; i<vCount; i++)
        if (adj2[start][i] && !visited[i] && checkDuplicate(adj, queue, i, vCount))	
        	Add(queue, i, vCount); //adding the vertex's edges into the queue array 
	
    if(main){ //This for loop will only run for the main call of the function
    	for (int i=1; i<vCount; i++){ //since the current vertex's ID has already been placed in the queue array, we start processing the entries after them
			if(queue[i]!=-1)
	    		BFS(adj, adj2, visited, queue, queue[i], vCount, 0); //recursive call for the function
	    }
	}

}

//Regenerates the adjacency matrix to account for the column and row swaps done in order to sort the vertices and edges in ascending order
void redoMatrix(vertex adj[20][20], int adj2[20][20], int vCount){
	
	for(int i=0; i<vCount; i++){
		for(int j=0; j<vCount; j++)
			adj2[i][j]=-1;
	}
	
	vertex comp[vCount];
	//Copies the vertex IDs into a 1D array to be used for comparing
	for(int i=0; i<vCount; i++)
		strcpy(comp[i],adj[i][0]);
	/*
	Triple nested for loop for populating the the adjacency matrix.
	First loop iterates through the 1D comp matrix 
	Second loop iterates through the rows/vertices of the matrix/graph
	Third loop iterates through the edges of the current vertex
	*/
	for(int i=0; i<vCount; i++){
		for(int j=0; j<vCount; j++){
			for(int k=0; k<vCount; k++){
				if(strcmp(adj[j][k],comp[i])==0) 
					adj2[j][i]=1;				 
				else if (adj2[j][i]!=1) //if condition to ensure that further iterations don't overwrite previously populated elements 		 
					adj2[j][i]=0;
			}
		}
	}
	
	for (int i=0; i<vCount;i++)
		adj2[i][i]=0;
}

void reformat(string temp){
	int len=strlen(temp);
	temp[0]='(';
	
	for(int i=1; i<len; i++)
		temp[i]='\0';
}
