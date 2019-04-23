/* 
* Name: Zachary Robin
* Date: 4/18/2019
* Title: Lab3 - Part 1 
* Description: This program copies a binary/text file to another file. 
*/
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h>

int main( int argc, char * argv[]) {
    FILE *fptr1, *fptr2; 
    char filename[100], c; 

    // Open one file for reading 
    fptr1 = fopen("helloworld.txt", "r"); 
    if (fptr1 == NULL) 
    { 
        printf("Cannot open file %s \n", filename); 
        exit(0); 
    } 
  
    // Open another file for writing 
    fptr2 = fopen("out.txt", "w"); 
    if (fptr2 == NULL) 
    { 
        printf("Cannot open file %s \n", filename); 
        exit(0); 
    } 
  
    // Read contents from file 
    c = fgetc(fptr1); 
    while (c != EOF) 
    { 
        fputc(c, fptr2); 
        c = fgetc(fptr1); 
    } 
  
    printf("\nContents copied to new file"); 
  
    fclose(fptr1); 
    fclose(fptr2); 
    return 0; 
} 