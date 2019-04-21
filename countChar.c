//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 50


struct charData
{
  char c;
  int freq;
};

int linearSearch(struct charData text[], int l, int r, char x) {
  int result = -1;
  for (int i = l; i <= r; ++i) {
    if (text[i].c == x)
      result = i;
  }
  return result;
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

void main()
{
  struct charData text[52];
  for (int i = 0; i <= 52; ++i) {
    text[i].freq = 0;
  }
  int index = 0;
  char buffer[MAX_INPUT_LENGTH];
  char plainString[MAX_INPUT_LENGTH];
  FILE *fp = fopen("text.txt", "r"); // do not use "rb"
  fgets(buffer, sizeof(buffer), fp);
  for (int i = 0; i < MAX_INPUT_LENGTH -1; ++i)
  {
    if (buffer[i] == ' ')
      continue;
    int result = linearSearch(text, 0, index, buffer[i]);
    if (result == -1)
    {
      text[index].c = buffer[i];
      text[index].freq = 1;
      index += 1;
    }
    else
    {
      text[result].freq += 1;
    }
  };

  // sort by frequencies
  bubbleSort(text, index-1);
  fclose(fp);

  char charArr[index];
  int freqArr[index];
  for (int i = 0; i < index - 1; ++i) {
    charArr[i] = text[i].c;
    freqArr[i] = text[i].freq;
  }
  printf("  Characters and their frequencies of occurrence in 'text.txt' file.\n");
  for (int i = 0; i < index - 1; ++i)
  {
    printf("  %c : %d \n", charArr[i], freqArr[i]);
  }
}
