#include <stdio.h>

// Function to print the output
void printTheArray(int arr[], int n)
{
    printf("%s\n", arr);

}

// Function to generate all binary strings
void generateAllBinaryStrings(int n, char arr[], int i)
{
    if (i == n) {
        printTheArray(arr, n);
        return;
    }

    arr[i] = '0';
    generateAllBinaryStrings(n, arr, i + 1);

    arr[i] = '1';
    generateAllBinaryStrings(n, arr, i + 1);
}

// Driver Code
int main()
{
    int n = 13;

    char arr[20];

    // Print all binary strings
    generateAllBinaryStrings(n, arr, 0);

    return 0;
}