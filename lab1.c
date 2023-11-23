//Sujana Kabir UTA ID: 1002054937
//gcc -o t1 lab1.c
//t1 a.out < a.dat

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    int num1, num2, num3;
    scanf("%d %d %d", &num1, &num2, &num3);

    int *a = malloc((num1 + 2) * sizeof(int));
    int *b = malloc((num2 + 2) * sizeof(int));
    int *selection = malloc(num3 * sizeof(int));

    a[0] = -999999;
    a[num1+1] = 999999;
    for(int i = 1; i < num1+1; i++)
    {
        scanf("%d", &a[i]);
    }

    b[0] = -99999;
    b[num2+1] = 99999;
  
    for(int i = 1; i < num2+1; i++)
    {
        scanf("%d", &b[i]);
    }

    for(int i = 0; i < num3; i++)
    {
        scanf("%d", &selection[i]);
    }

    int leftnum,rightnum, i, j, maxSize;
    if(num1 < num2)
    { 
        maxSize = num2;
    }
    else
    {
        maxSize = num1;
    }

    int rank;
    for(int x = 0; x < num3; x++)
    {

    rank = selection[x];

    if(rank > maxSize)
    { 
      leftnum = rank - maxSize;
    }
    else
    {
      leftnum = 0;
    }
    if(rank > num1)
    { 
      rightnum = num1;
    }
    else
    {
      rightnum = rank;
    }

    while(leftnum <= rightnum)
    {
        i = (leftnum + rightnum)/2;
        if(i > num1+1)
        {
            i = num1;
        }

        printf("leftnum: %d,\t rightnum: %d\n", leftnum, rightnum);
        j = rank - i;

        if(a[i] <= b[j])
        {
            printf("i: %d,\t\t j: %d,\t\t\na[%d] = %d, b[%d]= %d ",i, j, i,a[i], j, b[j]);
            printf("a[%d]=%d\n", i+1, a[i+1]);
        }
        else
        {
            printf("i: %d, j: %d,\nb[%d] = %d, a[%d] = %d ",i, j, j,b[j], i, a[i]);
            printf("b[%d]=%d\n", j+1,b[j+1]);
        }

        if(i + j == rank && a[i] > b[j] && a[i] <= b[j+1])
        { 
          printf("a[%d]=%d has rank %d\n\n", i, a[i], rank);
          break;
        }
        else if(i + j == rank && a[i] <= b[j] && b[j] < a[i+1])
        { 
          printf("b[%d]=%d has rank %d\n\n", j, b[j], rank);
          break;
        }
        else if(a[i + 1] <= b[j])
        { 
            leftnum = i+1;
        }
        else
        { 
            rightnum = i-1;
        }

    }
  }

}