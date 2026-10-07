#include <stdio.h>

int n;
int a[10][10], b[10][10];
int dfa[20];
int trans[20][2];
int count = 0;

// Checks if a generated DFA state subset already exists in our list
int exists(int x)
{
    int i;
    for(i = 0; i < count; i++)
        if(dfa[i] == x)
            return 1;
    return 0;
}

// Calculates the combined transition from a subset of states on a given symbol
int move(int state, int symbol)
{
    int i, j, result = 0;
    for(i = 0; i < n; i++)
    {
        // Check if state 'i' is present in the current subset using bitwise AND
        if(state & (1 << i))
        {
            for(j = 0; j < n; j++)
            {
                // Symbol 0 represents 'a'
                if(symbol == 0 && a[i][j])
                    result |= (1 << j); // Add state 'j' to result using bitwise OR
                
                // Symbol 1 represents 'b'
                if(symbol == 1 && b[i][j])
                    result |= (1 << j);
            }
        }
    }
    return result;
}

// Converts the bitmask back to a readable subset notation (e.g., bitmask 3 becomes {01})
void printSet(int state)
{
    int i;
    printf("{");
    for(i = 0; i < n; i++)
        if(state & (1 << i))
            printf("%d", i);
    printf("}");
}

int main()
{
    int i, j;
    
    // Read the number of states and transition matrices
    printf("Enter number of states: ");
    scanf("%d", &n);
    
    printf("Enter transition matrix for input a:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
            
    printf("Enter transition matrix for input b:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &b[i][j]);
            
    // Step 4: Consider the start state {0} as the first DFA state
    // State 0 is represented as the 0th bit (1 << 0) which equals 1
    dfa[count++] = 1;
    
    // Step 8: Repeat until no new subsets are generated
    for(i = 0; i < count; i++)
    {
        // Step 5: Find all possible transitions for input a (0) and b (1)
        trans[i][0] = move(dfa[i], 0);
        trans[i][1] = move(dfa[i], 1);
        
        // Step 7: If the subset is not already present and not empty, add it as a new DFA state
        if(trans[i][0] && !exists(trans[i][0]))
            dfa[count++] = trans[i][0];
        if(trans[i][1] && !exists(trans[i][1]))
            dfa[count++] = trans[i][1];
    }
    
    // Step 9: Print the DFA transition table
    printf("\nDFA Transition Table\n\n");
    printf("State\t\ta\t\tb\n");
    
    for(i = 0; i < count; i++)
    {
        printSet(dfa[i]);
        printf("\t\t");
        printSet(trans[i][0]);
        printf("\t\t");
        printSet(trans[i][1]);
        printf("\n");
    }
    return 0;
}