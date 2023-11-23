// Name: Sujana Kabir
// UTA ID: 1002054937
// Command: gcc lab2.c -o lab2

#include <stdio.h>
#include <stdlib.h>

int sequence_finder(int *sequence, int *subsequence, int sequence_length, int subsequence_length, int factor)
{

   for (int i = 0, j = 0; i < subsequence_length; i++)
   {
      int repeat = 0;
      while (1)
      {
         if (sequence[j++] == subsequence[i])
         {
            if (++repeat == factor)
            {
               break;
            }
         }
         else if (j >= sequence_length)
         {
            return 0;
         }
      }
   }
   return 1;
}

int binary_search_numbers(int *A, int *B, int A_length, int B_length, int max_sub_length)
{
   int low = 0;
   int high = max_sub_length;
   int buffer = 0;
   while (low <= high)
   {
      int mid = (low + high) / 2;
      int sub_finding = sequence_finder(A, B, A_length, B_length, mid);
      if (sub_finding == 0)
      {
         printf("low %d mid %d high %d failed\n", low, mid, high);
         high = mid - 1;
      }
      else
      {
         printf("low %d mid %d high %d passed\n", low, mid, high);
         buffer = mid > buffer ? mid : buffer;
         low = mid + 1;
      }
   }
   return buffer;
}

int main()
{
   int A_length = 0;
   int B_length = 0;
   int *A = NULL;
   int *B = NULL;
   int i, max_sub_length, high_factor;

   scanf("%d", &A_length);
   scanf("%d", &B_length);

   A = malloc(A_length * sizeof(int));
   B = malloc(B_length * sizeof(int));
   max_sub_length = A_length / B_length;

   for (i = 0; i < A_length; i++)
   {
      scanf("%d", &A[i]);
   }
   scanf("%d", &i);

   if (i != -999999999)
   {
      printf("Something's gone wrong reading A.\n");
      exit(1);
   }
   for (i = 0; i < B_length; i++)
   {
      scanf("%d", &B[i]);
   }
   scanf("%d", &i);
   if (i != -999999999)
   {
      printf("Something's gone wrong reading B.\n");
      exit(1);
   }

   high_factor = binary_search_numbers(A, B, A_length, B_length, max_sub_length);
   printf("Maximum repeats is %d\n", high_factor);

   return 0;
}