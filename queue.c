#include <stdlib.h>
#include <stdio.h>

// Linked List Node declaration
struct node {
  int data;
  struct node *next;
};

// Linked List Queue declaration
struct Queue {
  struct node *front, *back;
};

// Function to create Linked List Node
struct node* createNode(int data) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->data = data;
  temp->next = NULL;
  return temp;
}

// Function to create Queue using Linked List
struct Queue* createQueue() {
  struct Queue *temp = (struct Queue *)malloc(sizeof(struct Queue));
  temp->front = temp->back = NULL;
  return temp;
}

// Function to populate Queue with a Node
void enQueue(struct Queue *q, int data)
{
  struct node *newNode = createNode(data);
  // Queue is empty
  if (q->front == NULL && q->back == NULL) {
    q->front = q->back = newNode;
    return;
  }
  // Queue is not empty
  q->back->next = newNode;
  q->back = newNode;
}

// Function to remove the front Node in Queue. (FIRST IN FIRST OUT)
struct node* deQueue(struct Queue *q) {
  //Empty Queue
  if (q->front == NULL)
      return NULL;

  // Store previous front and move front one node ahead
  struct node *temp = q->front;
  q->front = q->front->next;

  // Empty Queue after deQueueing
  if (q->front == NULL)
      q->back = NULL;

  return temp;
}

int main()
{
    struct Queue *q = createQueue();
    enQueue(q, 10);
    enQueue(q, 20);
    deQueue(q);
    deQueue(q);
    enQueue(q, 30);
    enQueue(q, 40);
    enQueue(q, 50);
    struct node *n = deQueue(q);
    if (n != NULL)
      printf("Dequeued item is %d \n", n->data);
    if (n != NULL)
      printf("Dequeued item is %d \n", (deQueue(q))->data);
    if (n != NULL)
      printf("Dequeued item is %d \n", (deQueue(q))->data);
    return 0;
}
