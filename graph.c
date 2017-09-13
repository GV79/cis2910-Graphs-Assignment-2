#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*****************************
CIS2910 Assignment 5 Question
Author: Giavinh Lam
Assumptions: Proper format of
input text, number of vertices
<= 2000 and the adjacency
matrix is n rows, n columns
*****************************/

int returnDegree(char input[100]);

int main(int argc, char ** argv)
{
    if (argc != 2) // Must also include input file as an argument
    {
        printf("Error - Not enough arguments. Must specify input file.\n");
        exit(0);
    }

    FILE * data;
    int degreeOne[10000]; // assume n <= 2000 (# of vertices)
    char dataText[5000];
    int length = 0;
    int i = 0;
    int j = 0;
    int biggestDegree = 0;
    int sumDegree = 0;
    int counter = 0;
    int numOdd = 0;
    int graph = 1;

    data = fopen(argv[1], "r");

    while (fgets(dataText, 5000, data))
    {
        if (strchr(dataText, ' ') == NULL)
        {
            length = atoi(dataText); // n vertices
        }
        else
        {
            counter++;
            if (counter != length) //if counter != length, not at the end of matrix
            {
                degreeOne[i] = returnDegree(dataText);
                i++;
            }
            else
            {
                for (j = 0; j < 2000; j++) // find information we want
                {
                    sumDegree = sumDegree + degreeOne[j];
                    if (biggestDegree <= degreeOne[j])
                    {
                        biggestDegree = degreeOne[j];
                    }

                    if (degreeOne[j]%2 != 0) //odd degrees
                    {
                        numOdd++;
                    }
                }

                if (numOdd == 2 || numOdd == 0) // Graphs with 2 odd vertices or 0 odd vertices will have Eulerian path
                    printf("Graph %d: %d edges, largest degree %d, Eulerian\n", graph, sumDegree/2, biggestDegree);
                else
                    printf("Graph %d: %d edges, largest degree %d, NOT Eulerian\n", graph, sumDegree/2, biggestDegree);

                sumDegree = 0; // Reset variables for next graph
                biggestDegree = 0;
                memset(degreeOne, 0, 10000);
                counter = 0;
                graph++;
                i = 0;
                numOdd = 0;
            }
        }
    }
    return 0;
}

int returnDegree(char input[100]) // Finds degree of a vertice (row) by finding total number of ones
{
    int totalDegree = 0;
    int j = 0;

    for (j = 0; j < strlen(input); j++)
    {
        if (input[j] == '1')
        {
            totalDegree++;
        }
    }
    return totalDegree;
}
