#include <stdio.h>
#include <stdlib.h>

// Function to compare intervals based on finish time for sorting
int compareIntervals(const void *a, const void *b)
{
    return ((*(int **)a)[1] - (*(int **)b)[1]);
}

void weightedIntervalScheduling(int **intervals, int n)
{
    // Sort intervals by finish time
    qsort(intervals, n, sizeof(int *), compareIntervals);

    // Initialize DP table
    int M[n + 1][n + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            M[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int start = intervals[i - 1][0];
            int finish = intervals[i - 1][1];
            int weight = intervals[i - 1][2];

            // Two possibilities: include the interval in room 1 or room 2
            int includeInRoom1 = M[i - 1][j]; // Interval not included in room 2
            int includeInRoom2 = M[i][j - 1]; // Interval not included in room 1

            if (j > i)
            {
                // Interval i can only go in room 1
                M[i][j] = includeInRoom1 + weight;
            }
            else
            {
                // Choose the maximum weight
                M[i][j] = (includeInRoom1 > (includeInRoom2 + weight)) ? includeInRoom1 : (includeInRoom2 + weight);
            }
        }
    }

    // Traceback to find assigned intervals
    int room1Intervals[n][3];
    int room2Intervals[n][3];
    int i = n, j = n;
    int room1Count = 0, room2Count = 0;

    while (i > 0 && j > 0)
    {
        if (M[i][j] == M[i - 1][j])
        {
            // Interval i is not in room 1
            j--;
        }
        else if (M[i][j] == M[i][j - 1])
        {
            // Interval i is not in room 2
            i--;
        }
        else
        {
            // Interval i is in room 1
            for (int k = 0; k < 3; k++)
            {
                room1Intervals[room1Count][k] = intervals[i - 1][k];
            }
            room1Count++;
            j--;
        }
    }

    // The remaining intervals go to room 2
    for (int k = 1; k <= n; k++)
    {
        int found = 0;
        for (int l = 0; l < room1Count; l++)
        {
            if (intervals[k - 1][0] == room1Intervals[l][0] && intervals[k - 1][1] == room1Intervals[l][1] && intervals[k - 1][2] == room1Intervals[l][2])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            for (int m = 0; m < 3; m++)
            {
                room2Intervals[room2Count][m] = intervals[k - 1][m];
            }
            room2Count++;
        }
    }

    // Print the results
    printf("Input Intervals:\n");
    for (int i = 0; i < n; i++)
    {
        printf("(%d, %d, %d)\n", intervals[i][0], intervals[i][1], intervals[i][2]);
    }

    printf("\nRoom 1 Intervals:\n");
    for (int i = 0; i < room1Count; i++)
    {
        printf("(%d, %d, %d)\n", room1Intervals[i][0], room1Intervals[i][1], room1Intervals[i][2]);
    }

    printf("\nRoom 2 Intervals:\n");
    for (int i = 0; i < room2Count; i++)
    {
        printf("(%d, %d, %d)\n", room2Intervals[i][0], room2Intervals[i][1], room2Intervals[i][2]);
    }

    printf("\nTotal Weight Achieved: %d\n", M[n][n]);
}

int main()
{
    int intervals[][3] = {{1, 3, 1}, {2, 4, 2}, {4, 6, 3}, {6, 8, 4}, {8, 10, 5}};
    int n = sizeof(intervals) / sizeof(intervals[0]);

    weightedIntervalScheduling(intervals, n);

    return 0;
}
