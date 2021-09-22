
#include <stdio.h> 

// deklarácia rekurzívnej funkcie, pomocou ktorej nájdeme kombinácie
void combinationUtil (int arr[], int data[], int start, int end, int index, int r); 
  
// hlavná funkcia, ktorá vypíše všetky kombinácie o veľkosti r z poľa arr[] s veľkosťou n
void printCombination(int arr[], int n, int r)  { 

    // pomocné pole na postupné ukladanie všetkých kombinácií
    int data[r]; 
  
    // vypísanie kombinácií pomocou poľa data[]
    combinationUtil (arr, data, 0, n-1, 0, r); 

    
    // Remove duplicates
        while (arr[i] == arr[i+1])
            i++;
} 

// arr[] --> vstup, data[] --> pomocné pole, start a end --> začiatočný a konečný index pola arr[]
// index --> aktuálne používaný index v poli data[], r --> želaná veľkosť kombinácie
void combinationUtil(int arr[], int data[], int start, int end, int index, int r) { 
    
    // ak máme kombináciu o správnej dĺžke
    if (index == r) { 
        for (int j = 0; j < r; j++) 
            printf ("%d ", data[j]); 
        printf ("\n"); 
        return; 
    } 

    // postupne nahradíme index v poli data[] všetkými možnýli elementmi pola arr[]
    // podmienka zabezpečí, že zahrnutie elementu do indexu spraví kombináciu s ostatnými elementami na zostávajúcej pozícií
    for (int i = start; i <= end && end-i+1 >= r-index; i++) { 
        data[index] = arr[i]; 
        combinationUtil (arr, data, i+1, end, index+1, r); 
    } 
} 
  
int main()  { 
    int arr[] = {1, 2, 3, 4}; 
    int r = 3; 
    int n = sizeof(arr) / sizeof(arr[0]); 

    // volanie hlavnej rekurzívnej funkcie
    printCombination (arr, n, r); 
} 