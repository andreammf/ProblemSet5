// #include <iostream>
// #include "Foo.h"
// using namespace std;

// int main(int argc, char* argv[]) {
//     cout << foobar() << endl;
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 32;
const int MAX_ARRAY_SIZE = 196605;

void sort(char array[MAX_ARRAY_SIZE][SIZE], int size);
void countUniqueItems(int n, char ngram[MAX_ARRAY_SIZE][SIZE]);

int main(int argc, char *argv[]){
  int size = 0;
  char ngram[MAX_ARRAY_SIZE][SIZE];

  // Open text file in read mode
  FILE *readFile;
  readFile = fopen("Ngram.txt", "r");

  if(readFile == NULL){
    printf("File cannot be opened or does not exist.\n");
    return 1; //Return error
  }

  // Read each line in the text file using fgets()
  while(fgets(ngram[size], SIZE, readFile) != NULL){
    // Remove new line from the item
    for(int i = 0; i < SIZE; i++){
      if(ngram[size][i] == '\n'){
        ngram[size][i] = '\0';
      }
    }

    //Check to make sure we don't read more items than we can store in the ngram array
    if(size >= MAX_ARRAY_SIZE){
      fprintf(stderr, "Reached the maximum number of strings that the ngram array can hold.\n");
      break;
    }

    size++;
  }

  // Close the file since we are done reading it.
  if(!readFile) fclose(readFile);

  // Sort our ngram  
  sort(ngram, size);

  // Count unique items in the array and print it out on CLI
  countUniqueItems(size, ngram);

  return 0;
}

void sort(char array[MAX_ARRAY_SIZE][SIZE], int size){
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (strcmp(array[i],array[j]) > 0) {
                char tmp[SIZE];
                strcpy(tmp, array[i]);
                strcpy(array[i], array[j]);
                strcpy(array[j], tmp);
            }
        }
    }
}

void countUniqueItems(int n, char ngram[MAX_ARRAY_SIZE][SIZE]) {
    int cont = 1;
    int last = 0;
    for (int i = 1; i < n; i++) {
        if (strcmp(ngram[i], ngram[last]) != 0) {
            printf("%s -> %d\n", ngram[i], cont);
            last = i; cont = 1;
        } else {
            cont++;
        }
    }
    printf("%s -> %d\n", ngram[last], cont);
}