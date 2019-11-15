// uloha6-1.c -- Emma Macháčová, 2.11.2019 23:38

#include <stdio.h>
#include <stdlib.h>

int main() 
{ 
    FILE *fptr, *fp; 
    char c,s;
    scanf("%c",&s);
    fptr = fopen("znak.txt", "r"); 
    fp = fopen("novy.txt", "w"); 
    if (fptr == NULL) 
    { 
        printf("Cannot open file \n"); 
        exit(0); 
    } 
    
    if (s=='s'){
        c = fgetc(fptr); 
        while (c != EOF) { 
            fprintf (fp, "%c", c); 
            c = fgetc(fptr); 
        } 
    }
    else {
        c = fgetc(fptr); 
        while (c != EOF) { 
            fprintf (fp, "%c", c); 
            c = fgetc(fptr); 
        } 
    }
    
    fclose(fptr); 
    return 0; 
}