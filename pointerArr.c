// This file is just for explanation. Only huffmanEncoding.c is required for actual decoding.

#include <stdlib.h>
#include <stdio.h>

struct Node
{
  char data;
  int freq;
  struct Node *left, *right; // 'left' and 'right' are pointers to two different nodes.
};

int main()
{
  // Creation of ('temp') pointer to a new node and accessing node properties through the pointer using '->' operator.
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
  temp->left = temp->right = NULL;
  temp->data = 10;
  temp->freq = 20;
  // 'arr' is a pointer to an array of 'node pointers'
  struct Node **arr = (struct Node **)malloc(3 * sizeof(struct Node *));
  arr[0] = temp;
  printf("%p %p %p\n", arr, arr[0], temp);
  printf("%d %d %d\n", (*arr)->data, arr[0]->data, temp->data);
  printf("%d %d %d\n", (*arr)->freq, arr[0]->freq, temp->freq);
  return 0;
}
