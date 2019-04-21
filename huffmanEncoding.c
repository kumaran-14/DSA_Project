// C Program for Efficient Huffman Coding for Sorted input
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 500

// A Node of Huffman tree (Min-Heap) and a Node of Queue array.
struct HNode
{
  char data;
  int freq;
  struct HNode *left, *right;
};

struct charData
{
  char c;
  int freq;
  char code[30];
};

struct charData text[60];
int idx = 0;
char buffer[MAX_INPUT_LENGTH];

// Function to create a new HNode pointer and return it.
struct HNode *newHNode(char data, int freq)
{
  struct HNode *temp_node = (struct HNode *)malloc(sizeof(struct HNode));
  temp_node->left = temp_node->right = NULL;
  temp_node->data = data;
  temp_node->freq = freq;
  return temp_node;
}

// Structure for Queue: collection of Huffman Tree Nodes (or HNodes)
struct Queue
{
  // refer to pointerArr.c for explanation of 'array of pointers'
  struct HNode **array;
  // Max no of nodes in this array. 'front' and 'back' refers to 0th idx and size-1 th idx.
  int size;
  int front, back;
};

// Function to create a Queue of given size
struct Queue *createQueue(int size)
{
  struct Queue *temp_queue = (struct Queue *)malloc(sizeof(struct Queue));
  temp_queue->size = size;
  // Empty array . Hence 'front' and 'back' = -1
  temp_queue->front = temp_queue->back = -1;
  // Allocate memory - 'size' times 'memory of Each Node'
  temp_queue->array = (struct HNode **)malloc(size * sizeof(struct HNode *));
  return temp_queue;
}

// Function to check if given queue is empty.
int isEmpty(struct Queue *queue)
{
  return queue->front == -1;
}

// Function to check if size of given queue is 1, i.e only one node pointer in queue.
int isSizeOne(struct Queue *queue)
{
  return queue->front == queue->back && queue->front != -1;
}

// Function to add an item at the beginning of a queue.
void enQueue(struct Queue *queue, struct HNode *item)
{
  //queue->array's size reached, i.e array is fully populated
  if (queue->back == queue->size - 1)
    return;
  queue->back = queue->back + 1;
  queue->array[queue->back] = item;
  // case where first item is added.
  if (queue->front == -1)
    queue->front = queue->front + 1; // or 0
}

// A utility function to remove an item from queue
struct HNode *deQueue(struct Queue *queue)
{
  if (isEmpty(queue))
    return NULL;
  struct HNode *temp_node = queue->array[queue->front];
  if (queue->front == queue->back) // If there is only one item in queue
    queue->front = queue->back = -1;
  else
    queue->front = queue->front + 1;
  return temp_node;
}

// Function to get 'front' node pointer of queue
struct HNode *getFront(struct Queue *queue)
{
  if (isEmpty(queue))
    return NULL;
  return queue->array[queue->front];
}

/* Function to get minimum item from two queues */
struct HNode *getMinFreqNode(struct Queue *queue_1, struct Queue *queue_2)
{
  // If first queue is empty, dequeue from second queue. That will be the minimum
  if (isEmpty(queue_1))
    return deQueue(queue_2);

  // If second queue is empty, dequeue from first queue. That will be minimum
  if (isEmpty(queue_2))
    return deQueue(queue_1);

  // Else, compare the 'front' node of two queues and dequeue minimum
  if (getFront(queue_1)->freq < getFront(queue_2)->freq)
    return deQueue(queue_1);

  return deQueue(queue_2);
}

// The function that builds Huffman tree
struct HNode *buildHuffmanTree(char data[], int freq[], int size)
{
  // Tree nodes
  struct HNode *left, *right, *top;

  // Create two empty queues
  struct Queue *queue_1 = createQueue(size);
  struct Queue *queue_2 = createQueue(size);

  // Step 2:Create a leaf HNode for each unique character and Enqueue it to the first queue in increasing order of frequency.
  for (int i = 0; i < size; ++i)
    enQueue(queue_1, newHNode(data[i], freq[i]));
  // The second queue is empty at the start.

  // Run while Queues contain more than one HNode. Finally, first queue will be empty and second queue will contain only one HNode
  while (!(isEmpty(queue_1) && isSizeOne(queue_2)))
  {
    // Dequeue two HNodes with the minimum frequency by examining the front of both queues
    left = getMinFreqNode(queue_1, queue_2);
    right = getMinFreqNode(queue_1, queue_2);

    // Step 4: Create a new internal HNode with frequency equal to the sum
    // of the two HNodes frequencies. Enqueue this HNode to second queue.
    top = newHNode('_', left->freq + right->freq);
    top->left = left;
    top->right = right;
    enQueue(queue_2, top);
  }
  // root node of Huffman tree.
  return deQueue(queue_2);
}

// Function to check if this HNode is leaf
int isLeafNode(struct HNode *root)
{
  return !(root->left) && !(root->right);
}

// A utility function to print an array of size n
void printArr(int arr[], int n, char *str)
{
  int i;
  for (i = 0; i < n; ++i)
  {
    printf("%d", arr[i]);
    char s[100];
    sprintf(s, "%d", arr[i]);
    strcat(str, s);
  }
  printf("\n");
}

int linearSearch(struct charData *text, int l, int r, char x)
{
  int result = -1;
  for (int i = l; i <= r; ++i)
  {
    if (text[i].c == x)
      result = i;
  }
  return result;
}
// Recursive function to print huffman codes from the root of Huffman Tree.(Post-order traversal)
void printHuffmanCodes(struct HNode *root, int arr[], int top)
{
  // Assign 0 to left edge and recur
  if (root->left)
  {
    arr[top] = 0;
    printHuffmanCodes(root->left, arr, top + 1);
  }

  // Assign 1 to right edge and recur
  if (root->right)
  {
    arr[top] = 1;
    printHuffmanCodes(root->right, arr, top + 1);
  }

  // If this is a leaf HNode, then it contains one of the input
  // characters, print the character and its code from arr[]
  if (isLeafNode(root))
  {
    printf("   %c -> ", root->data);
    //print values from 0 - (top -1)
    char str[50] = "";
    printArr(arr, top, str);
    int result = linearSearch(text, 0, idx, root->data);
    strcpy(text[result].code, str);
  }
}

// The main function that builds a Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
  // Construct Huffman Tree
  struct HNode *root = buildHuffmanTree(data, freq, size);

  // Print Huffman codes using the Huffman tree built above, 100 is the max tree height
  int arr[100], top = 0;

  printf("\n  Characters and their Huffman codes :\n\n");
  printHuffmanCodes(root, arr, top);
}

void swap(struct charData *xp, struct charData *yp)
{
  struct charData temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(struct charData text[], int n)
{
  int i, j;
  for (i = 0; i < n - 1; i++)
    // Last i elements are already in place
    for (j = 0; j < n - i - 1; j++)
      if (text[j].freq > text[j + 1].freq)
        swap(&text[j], &text[j + 1]);
}

int main()
{
  // initalise array of structs to 0 frequencies
  for (int i = 0; i <= 60; ++i)
  {
    text[i].freq = 0;
  }
  FILE *fp = fopen("text.txt", "r");
  fgets(buffer, sizeof(buffer), fp);

  for (int i = 0; i < MAX_INPUT_LENGTH - 1; ++i)
  {
    if (buffer[i] == ' ')
      continue;
    int result = linearSearch(text, 0, idx, buffer[i]);

    if (result == -1)
    {
      text[idx].c = buffer[i];
      text[idx].freq = 1;
      idx += 1;
    }
    else
    {
      text[result].freq += 1;
    }
  };
  // sort characters in increasing order according to their frequencies.
  bubbleSort(text, idx);
  fclose(fp);
  char arr[idx];
  int freq[idx];
  for (int i = 0; i < idx; ++i)
  {
    arr[i] = text[i].c;
    freq[i] = text[i].freq;
  }

  printf("\n  Characters and their frequencies of occurrence in 'text.txt' file :\n\n");
  for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); ++i)
  {
    printf("    %c -> %d \n", arr[i], freq[i]);
  }

  int size = sizeof(arr) / sizeof(arr[0]);
  HuffmanCodes(arr, freq, size);

  char encodedString[2000] = "";

  for (int i = 0; i < MAX_INPUT_LENGTH - 1; ++i)
  {
    if (buffer[i] == ' ')
      continue;
    int result = linearSearch(text, 0, idx, buffer[i]);
    strcat(encodedString, text[result].code);
  }
  // printf("\n    %s")
  printf("\n  Huffman encoded data :\n\n   %s\n\n", encodedString);

  printf("\n  Huffman decoded data :\n\n   %s\n\n", buffer);
  return 0;
}
