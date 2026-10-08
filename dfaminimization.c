#include <stdio.h>

int main()
{
    int n, i, j;
    int a[10], b[10];
    int final[10];
    int mark[10][10];
    int changed;

    // Read the number of states
    printf("Enter number of states: ");
    scanf("%d", &n);

    // Read transition table for input 'a'
    printf("Enter transition for input a:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // Read transition table for input 'b'
    printf("Enter transition for input b:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &b[i]);

    // Read final/accepting states
    printf("Enter final states (1 for Final, 0 for Non-Final):\n");
    for(i = 0; i < n; i++)
        scanf("%d", &final[i]);

    // Initialize the marking table to 0 (unmarked)
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            mark[i][j] = 0;

    // STEP 5: Initial marking - Mark pairs where one is final and the other is not
    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(final[i] != final[j])
                mark[i][j] = 1;
        }
    }

    // STEP 6-8: Iterative marking of distinguishable pairs
    do
    {
        changed = 0;
        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                // Only evaluate pairs that are not yet marked
                if(mark[i][j] == 0)
                {
                    // Check transitions for input 'a'
                    int x = a[i], y = a[j];
                    if(x != y)
                    {
                        // Ensure we always check mark[smaller][larger]
                        if(x < y)
                        {
                            if(mark[x][y])
                            {
                                mark[i][j] = 1;
                                changed = 1;
                                continue; // Already marked, no need to check 'b'
                            }
                        }
                        else
                        {
                            if(mark[y][x])
                            {
                                mark[i][j] = 1;
                                changed = 1;
                                continue;
                            }
                        }
                    }

                    // Check transitions for input 'b'
                    x = b[i];
                    y = b[j];
                    if(x != y)
                    {
                        if(x < y)
                        {
                            if(mark[x][y])
                            {
                                mark[i][j] = 1;
                                changed = 1;
                            }
                        }
                        else
                        {
                            if(mark[y][x])
                            {
                                mark[i][j] = 1;
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
    } while(changed); // Repeat until no new markings are made

    // STEP 9: Print equivalent state pairs (those that remain unmarked)
    printf("\nEquivalent States:\n");
    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(mark[i][j] == 0)
                printf("(%d, %d)\n", i, j);
        }
    }

    return 0;
}