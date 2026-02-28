/* C File that stores the helper functions for graph processing
   Programmer: Stefan
   Code Tester: Martin and Stefan
*/
#include <stdio.h>
#include <string.h>
#include "sort.h"

//Typedef Declarations
typedef char vertex[9];
typedef char string[25];

//Function Prototypes
int checkEdge(vertex, vertex, vertex[], vertex[], int);

void DFS(FILE*, int[], vertex[20][20], int, int[20][20], int);

void BFS(vertex[20][20], int[20][20], int[], int [], int, int, int);

void redoMatrix(vertex[20][20], int[20][20], int);

void reformat(string);
