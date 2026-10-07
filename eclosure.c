#include <stdio.h>

int n;
int e[10][10];
int a[10][10];
int b[10][10];
int visited[10];

// Recursive function to find and print reachable states via epsilon transitions
void eclosure(int state)
{
    int i;
    visited[state] = 1; // Mark current state as visited
    printf("%d ", state); // Print the current state as part of the closure
    
    // Check all possible next states
    for(i = 0; i < n; i++)
    {
        // If an epsilon transition exists and the state hasn't been visited yet
        if(e[state][i] == 1 && !visited[i])
            eclosure(i); // Recursively find closures of the reachable state
    }
}

int main()
{
    int i, j;
    
    // Read total number of states
    printf("Enter number of states: ");
    scanf("%d", &n);
    
    // Read epsilon transition matrix
    printf("Enter epsilon transition matrix (0/1):\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &e[i][j]);
        }
    } 
    
    // Read input 'a' transition matrix
    printf("Enter transition matrix for a (0/1):\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    
    // Read input 'b' transition matrix
    printf("Enter transition matrix for b (0/1):\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &b[i][j]);
        }
    }
    
    printf("\nEpsilon Closures:\n");
    
    // Calculate and print the closure for each state
    for(i = 0; i < n; i++)
    {
        // Reset visited array for the current state's search
        for(j = 0; j < n; j++)
            visited[j] = 0;
            
        printf("E-Closure(%d) = { ", i);
        eclosure(i);
        printf("}\n");
    }
    
    return 0;
}