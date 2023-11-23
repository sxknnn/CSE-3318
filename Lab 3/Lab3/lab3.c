// Sujana Kabir ID: 1002054937
// gcc -o main main.c; ./main < a.dat

#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a > b ? a : b)

const int max_value = 51;

typedef struct Intervel
{
    int start;
    int end;
    int weight;
} Intervel;

int binary_search(Intervel *intervel, int n, int time)
{

    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (intervel[mid].end <= time)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return high;
}

int get_max_weight(Intervel *arr, size_t n)
{

    int dp_table[max_value][max_value];
    int p[max_value];

    Intervel *room1 = (Intervel *)malloc((n + 1) * sizeof(Intervel));
    Intervel *room2 = (Intervel *)malloc((n + 1) * sizeof(Intervel));
    int room1_count = 0;
    int room2_count = 0;

    p[0] = -1;

    for (int i = 1; i <= n; i++)
    {
        p[i] = binary_search(arr, n + 1, arr[i].start);
    }

    printf("%-3s %-3s %-3s %-3s %-3s\n", "i", "s", "f", "w", "p");
    for (int i = 1; i <= n; i++)
    {
        printf("%-3d %-3d %-3d %-3d %-3d\n", i, arr[i].start, arr[i].end, arr[i].weight, p[i]);
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == j)
            {
                if (i == 0)
                {
                    dp_table[i][j] = 0;
                }
                else
                {
                    dp_table[i][j] = dp_table[i][i - 1];
                }
            }
            else
            {
                if (i > j)
                {
                    dp_table[i][j] = max(dp_table[p[i]][j] + arr[i].weight, dp_table[i - 1][j]);
                }
                else
                {
                    dp_table[i][j] = max(dp_table[i][p[j]] + arr[j].weight, dp_table[i][j - 1]);
                }
            }
        }
    }

    printf("\n");
    int s = 0;

    // print dp_table
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            printf("%-3d ", dp_table[i][j]);
        }
        printf("\n");
    }

    // backtracing

    int j;
    int i = j = n;
    while (1)
    {
        if (i == 0 && j == 0)
        {
            break;
        }

        if (i == j)
        {
            j--;
        }
        else if (i > j)
        {
            if (dp_table[i][j] == dp_table[p[i]][j] + arr[i].weight)
            {
                room1[room1_count++] = arr[i];
                s += arr[i].weight;
                i = p[i];
            }
            else
            {
                i--;
            }
        }
        else
        {
            if (dp_table[i][j] == dp_table[i][p[j]] + arr[j].weight)
            {
                room2[room2_count++] = arr[j];
                s += arr[j].weight;
                j = p[j];
            }
            else
            {
                j--;
            }
        }
    }

    printf("%d\n", room1_count);
    for (int i = room1_count - 1; i >= 0; i--)
    {

        printf("%d %d %d\n", room1[i].start, room1[i].end, room1[i].weight);
    }

    printf("%d\n", room2_count);

    for (int i = room2_count - 1; i >= 0; i--)
    {

        printf("%d %d %d\n", room2[i].start, room2[i].end, room2[i].weight);
    }

    return dp_table[n][n];
}

int main()
{

    int n = 0;

    scanf("%d", &n);

    Intervel *intervel = (Intervel *)malloc((n + 1) * sizeof(Intervel));
    intervel[0].start = 0;
    intervel[0].end = -9999999;
    intervel[0].weight = 0;

    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d %d", &intervel[i].start, &intervel[i].end, &intervel[i].weight);
    }

    int maxWeight = get_max_weight(intervel, n);

    printf("%d\n", maxWeight);

    free(intervel);
    return 0;
}
