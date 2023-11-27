
#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 99999
#define INT_MIN -99999

struct Node
{
    int data;
    int length;
    struct Node *next;
};

struct Stack
{
    struct Node *top;
    int MinLength;
    int MaxLength;
};

struct Queue
{
    struct Stack *inStack;
    struct Stack *outStack;
    int totalLength;
    int text;
};

void insideStack(struct Stack *stack)
{
    stack->top = NULL;
    stack->MinLength = INT_MAX;
    stack->MaxLength = INT_MIN;
}

void insideQueue(struct Queue *queue)
{
    queue->inStack = (struct Stack *)malloc(sizeof(struct Stack));
    queue->outStack = (struct Stack *)malloc(sizeof(struct Stack));
    queue->totalLength = 0;
    queue->text = 0;

    insideStack(queue->inStack);
    insideStack(queue->outStack);
}

void push(struct Stack *stack, int value, int length)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->length = length;
    newNode->next = stack->top;

    stack->top = newNode;
    if (length < stack->MinLength)
    {
        stack->MinLength = length;
    }
    if (length > stack->MaxLength)
    {
        stack->MaxLength = length;
    }
}

struct Node *pop(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }

    struct Node *temp = stack->top;
    stack->top = stack->top->next;
    return temp;
}

int availableNodes = 0;
void enqueue(struct Queue *queue, int length)
{
    int value;
    push(queue->inStack, value, length);
    queue->totalLength += length;
    queue->text++;
    availableNodes++;

}

struct Node *dequeue(struct Queue *queue)
{
    if (queue->outStack->top == NULL)
    {
        while (queue->inStack->top != NULL)
        {
            struct Node *temp = pop(queue->inStack);
            push(queue->outStack, temp->data, temp->length);
            free(temp);
        }
    }

    if (queue->outStack->top == NULL)
    {
        return NULL;
    }

    struct Node *temp = pop(queue->outStack);
    queue->totalLength -= temp->length;
    queue->text--;

    return temp;
}

void computeAverage(struct Queue *queue)
{
    if (queue->text > 0)
    {
        double average = (double)queue->totalLength / queue->text;
        printf("average length: %.6f\n", average);
    }
    else
    {
        printf("Can't compute average for an empty queue\n");
    }
}

void printMinLength(struct Queue* queue)
{
    int MinLength = INT_MAX;

    
    struct Node* current_len = queue->inStack->top;
    while (current_len != NULL)
    {
        if (current_len->length < MinLength)
        {
            MinLength = current_len->length;
        }
        current_len = current_len->next;
    }

    
    current_len = queue->outStack->top;
    while (current_len != NULL)
    {
        if (current_len->length < MinLength)
        {
            MinLength = current_len->length;
        }
        current_len = current_len->next;
    }

    if (queue->text > 0)
    {
        printf("minimum length: %d\n", MinLength);
    }
    else
    {
        printf("Can't compute minimum for an empty queue\n");
    }
}

void printMaxLength(struct Queue* queue)
{
    int MaxLength = INT_MIN;

    
    struct Node* current_len = queue->inStack->top;
    while (current_len != NULL)
    {
        if (current_len->length > MaxLength)
        {
            MaxLength = current_len->length;
        }
        current_len = current_len->next;
    }

   
    current_len = queue->outStack->top;
    while (current_len != NULL)
    {
        if (current_len->length > MaxLength)
        {
            MaxLength = current_len->length;
        }
        current_len = current_len->next;
    }

    if (queue->text > 0)
    {
        printf("maximum length: %d\n", MaxLength);
    }
    else
    {
        printf("Can't compute maximum  for an empty queue\n");
    }
}

int main(int argc, char *argv[])
{
    int nodeNum;
    struct Queue myQueue;
    insideQueue(&myQueue);
    int command, value;

    while (1)
    {
        scanf("%d",&command);
        switch (command)
        {
        case 0:
            printf("0\n");
            printf("In stack available nodes %d Out of Stack available nodes %d\n", nodeNum, nodeNum);
            return 0;

        case 1:
            if (scanf("%d", &value) == 1)
            {
                enqueue(&myQueue, value);
                printf("Enqueued %d\n", value);
                if (nodeNum < availableNodes)
                {
                    nodeNum = availableNodes;
                }

            }
            else
            {
                printf("Invalid command format\n");
            }
            break;

        case 2:
        {
            availableNodes = 0;
            struct Node *node = dequeue(&myQueue);
            if (node != NULL)
            {
                printf("Dequeued %d\n", node->length);
                free(node);
            }
            else
            {
                printf("Can't dequeue for an empty queue\n");
            }
        }
        break;

        case 3:
            computeAverage(&myQueue);
            break;

        case 4:
            printMinLength(&myQueue);
            break;

        case 5:
            printMaxLength(&myQueue);
            break;

        default:
            printf("Invalid command\n");
        }
    }

    return 0;
}