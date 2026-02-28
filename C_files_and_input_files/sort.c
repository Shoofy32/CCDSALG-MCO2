/* C File that stores the sorting algorithms for sorting graph vertices and edges
   Programmer: Stefan and Martin 
   Code Tester: Martin and Stefan
*/
#include <string.h>

// Typedef declarations
typedef char vertex[9]; // For vertexes
typedef char string[25]; // For strings

// Selection sort algorithm to sort the columns in ascending order
void colSort(vertex adj[20][20], int vCount){

	// Temp variables
	vertex temp1;

	/* Since each row is randomized differently, iteration mus be done by going through each row and sorting them individually.
       This requires a triple nested for loop to sort the columns or edges of each vertex lexicographically
	*/
	for(int i = 0; i < vCount; i++){ //Iterate through the rows

		//Selection sort algorithm
		for(int j = 1; j < vCount - 1; j++){

			int min = j;

			for(int k = j + 1; k < vCount; k++)
				if(strcmp(adj[i][k], adj[i][min]) < 0 && strcmp(adj[i][k], "\0"))
					min = k;
			
			strcpy(temp1, adj[i][j]);
			strcpy(adj[i][j], adj[i][min]);
			strcpy(adj[i][min], temp1);
		}
	}
	
}

// Selection sort algorithm to sort rows in ascending order
void rowSort(vertex adj[20][20], int vCount){

	//Temp variable
	vertex temp1;
	
	//Selection Sort for rows
	for(int i = 0; i < vCount - 1; i++){

		int min = i;

		for(int j = i + 1; j < vCount; j++)
			if(strcmp(adj[j][0], adj[min][0])<0 && strcmp(adj[j][0], "\0"))
				min = j;

		for(int k = 0; k < vCount; k++){

			strcpy(temp1,adj[i][k]);
			strcpy(adj[i][k],adj[min][k]);
			strcpy(adj[min][k],temp1);

		}
		
	}
}
