/* C File that stores the main driver for the graph processing 
   Programmer: Stefan
   Code Tester: Martin and Stefan
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort.h"
#include "output.h"
#include "helpers.h"

//Typedef Declarations
typedef char vertex[9];
typedef char string[25];

//Function Prototypes
int ReadInputFile(string fileName, vertex adj[20][20]);
void ProduceOutputFiles(string fileName, vertex adj[20][20], int vCount);


int main() {

	int size;
	string fileName;
	vertex adj[20][20] = {{{0},{0}}}; //Storing vertices
	
	printf("Input filename: ");
	scanf("%s", fileName);
	
	size = ReadInputFile(fileName, adj);
	
	/* Checks for ReadInputFile and if it returns a 0, 
       then it indicates that the file name was invalid and no output files must be generated
	*/

	if(size > 0)
		ProduceOutputFiles(fileName, adj, size);
	else
		printf("File %s not found", fileName);

}

// Function for processing the input file and copying its data into the matrix graph
int ReadInputFile(string fileName, vertex adj[20][20]){

	int vCount = 0;
	int stop;
	vertex temp;
	FILE* ptr;
	ptr = fopen(fileName, "r");
	
	//Checker to only start adding data into the adjacency matrix if a file has been successfully opened or not
	if(ptr != NULL){ 

		fscanf(ptr,"%d", &vCount);
	
		for(int i = 0; i < vCount; i++){

			stop = 1; 

			for(int j = 0; j <= vCount && stop == 1; j++){

				fscanf(ptr, "%s", temp);

				// Keeps on adding data to the current row until a "-1" is read
				if(strcmp(temp,"-1")) 
					strcpy(adj[i][j], temp);
				else
					stop = 0; // Prematurely ends the for loop and moves on to the next row

			}
		}
	}
	
	fclose(ptr);
	
	return vCount;
}

// Function for processing the multiple output files
void ProduceOutputFiles(string fileName, vertex adj[20][20], int vCount){

	int success;
	string outName;
	int adj2[20][20]; // Initializing a 2d int array for the adjacency matrix to be passed on for traversals
	
	strncpy(outName, fileName, 1); // Copying only the first character of fileName into outName
	
	outName[1] = '\0';// Formatting outName for proper concatenation
	ProduceOutputFile3(strcat(outName, "-LIST.TXT"), adj, vCount);
	
	outName[1] = '\0'; 

	ProduceOutputFile4(strcat(outName, "-MATRIX.TXT"), adj, vCount, adj2);	

	rowSort(adj, vCount); // Sorts the graph's rows since the following outputs require it to be in ascending order

	colSort(adj, vCount); // Sorts the graph's columns since the following outputs require it to be in ascending order

	redoMatrix(adj, adj2, vCount); // Regenerates adjacency matrix to account for the swapping of rows and columns

	outName[1] = '\0';
	success = ProduceOutputFile5(strcat(outName, "-BFS.TXT"), adj, vCount, adj2); // Function returns either the index of the starting vertex or -1
	
	// Checks if the ProduceOutputFile5 function returned a -1 that indicates an invalid starting vertex so forego the ProduceOutputFile6 function entirely
	if(success >- 1){ 

		outName[1] = '\0';
		ProduceOutputFile6(strcat(outName, "-DFS.TXT"), adj, vCount, success, adj2);

	}
	
	outName[1] = '\0';
	ProduceOutputFile1(strcat(outName, "-SET.TXT"), adj, vCount);
	
	outName[1] = '\0';
	ProduceOutputFile2(strcat(outName, "-DEGREE.TXT"), adj, vCount); 
}

