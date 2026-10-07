#include <stdio.h>

int n;
int e[10][10], a[10][10], b[10][10];
int visited[10];

// Recursive function to calculate the epsilon-closure of a given state 's'
void closure(int s)
{
    int i;
    visited[s] = 1; // Mark the current state as visited
    for(i = 0; i < n; i++)
    {
        // If there is an epsilon transition to state 'i' and it is unvisited, explore it
        if(e[s][i] == 1 && !visited[i])
            closure(i);
    }
}

int main()
{
    int i, j, k;
    
    // Read the number of states
    printf("Enter number of states: ");
    scanf("%d", &n);
    
    // Read the epsilon transition matrix
    printf("Enter epsilon transition matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &e[i][j]);
            
    // Read the transition matrix for input symbol 'a'
    printf("Enter transition matrix for input a:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
            
    // Read the transition matrix for input symbol 'b'
    printf("Enter transition matrix for input b:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &b[i][j]);
            
    printf("\nEquivalent NFA without epsilon transitions:\n");
    
    // Calculate new transitions for each state
    for(i = 0; i < n; i++)
    {
        printf("\nState %d\n", i);
        
        // 1. Reset the visited array to prepare for the closure calculation
        for(j = 0; j < n; j++)
            visited[j] = 0;
            
        // 2. Find all states reachable from state 'i' via epsilon transitions
        closure(i);
        
        // 3. Find and print new transitions for input 'a'
        printf("a -> { ");
        for(j = 0; j < n; j++)
        {
            if(visited[j]) // If state 'j' is in the epsilon closure
            {
                for(k = 0; k < n; k++)
                {
                    if(a[j][k]) // If there is a transition from 'j' to 'k' on input 'a'
                        printf("%d ", k);
                }
            }
        }
        printf("}\n");
        
        // 4. Find and print new transitions for input 'b'
        printf("b -> { ");
        for(j = 0; j < n; j++)
        {
            if(visited[j]) // If state 'j' is in the epsilon closure
            {
                for(k = 0; k < n; k++)
                {
                    if(b[j][k]) // If there is a transition from 'j' to 'k' on input 'b'
                        printf("%d ", k);
                }
            }
        }
        printf("}\n");
    }
    return 0;
}