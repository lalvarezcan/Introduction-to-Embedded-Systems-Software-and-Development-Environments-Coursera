/******************************************************************************
 * Copyright (C) 2024 by Luis Alvarez
 * 
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Luis Alvarez is not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file stats.c 
 * @brief Program which computes some stats of an array of numbers
 *
 *
 * @author Alvarez Luis
 * @date 02/20/2024
 *
 */



#include <stdio.h>
#include <stdint.h>
#include "stats.h"


/* Size of the Data Set */
#define SIZE (40)

void main() {

  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  87,  25,  23,
                              200, 122, 150, 90,   92,  87, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90,};

  /* Other Variable Declarations Go Here */
  /* Statistics and Printing Functions Go Here */

  // Create Struct
  stat a;

  // Initialize Struct
  a.numArray = test;
  a.arrayLength = SIZE;
  a.max = 0;
  a.min = 0xFF;
  a.mean = 0;
  a.median = 0;

  // Process Data
  sort_array(a.numArray, a.arrayLength);
  a.min = find_min(a.numArray, a.arrayLength);
  a.max = find_max(a.numArray, a.arrayLength);
  a.mean = find_mean(a.numArray, a.arrayLength);
  a.median = find_median(a.numArray, a.arrayLength);
  print_array(a.numArray, a.arrayLength);
  print_statistics(a);
}

void print_statistics(stat ArrayStats){
  printf("Array Min: %u\n", ArrayStats.min);
  printf("Array Max: %u\n", ArrayStats.max);
  printf("Array Mean: %u\n", ArrayStats.mean);
  printf("Array Median: %u\n", ArrayStats.median);
  printf("Array Size: %u\n", ArrayStats.arrayLength);
}

void print_array(uint8_t *arrayPtr, uint8_t arrayLength){
  // Loop through and print the array
  for(uint8_t i=0; i<arrayLength; i++){
    printf("array[%u]: %u\n", i, *(arrayPtr + sizeof(char)*i));
  }
  printf("\n");
  return;
}

void sort_array(uint8_t *arrayPtr, uint8_t arrayLength) {
  uint8_t i, j;
  uint8_t temp;
  
  for (i = 1; i < arrayLength; i++) {
    temp = arrayPtr[i];
    j = i;
    while (j > 0 && arrayPtr[j - 1] > temp) {
      arrayPtr[j] = arrayPtr[j - 1];
      j--;
    }
    arrayPtr[j] = temp;
  }
}

uint8_t find_min(uint8_t *arrayPtr, uint8_t arrayLength){
  uint8_t minValue=0xFF;

  for (uint8_t i=0; i<arrayLength; i++){
    if (arrayPtr[i] < minValue){
      minValue = arrayPtr[i];
    }
  }

  return minValue;
}

uint8_t find_max(uint8_t *arrayPtr, uint8_t arrayLength){
  uint8_t maxValue=0;

  for (uint8_t i=0; i<arrayLength; i++){
    if (arrayPtr[i] > maxValue){
      maxValue = arrayPtr[i];
    }
  }

  return maxValue;
}

uint8_t find_mean(uint8_t *arrayPtr, uint8_t arrayLength){
  uint32_t avg=0;

  // Add up all the numbers in the array
  for(uint8_t i=0; i<arrayLength; i++){
    avg+= arrayPtr[i];
  }
  
  // Integer division using a Length
  return (avg/arrayLength);
}

uint8_t find_median(uint8_t *arrayPtr, uint8_t arrayLength){
  // Make sure array is sorted first
  sort_array(arrayPtr, arrayLength);

  // Case where array length is odd
  if (arrayLength%2){
    return arrayPtr[arrayLength/2];
  }

  // Case where array length is even.  Average between two middle values is necessary
  uint8_t avg = (arrayPtr[arrayLength/2 - 1]+arrayPtr[arrayLength/2])/2;
  return avg;
}
