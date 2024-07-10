#include <iostream>
#include <random>
using namespace std;

int keys = 0; // Record key operations

// Output array
void displayArray(string name, int inArray[], int inSize) {
    cout << name << " = [";
    for (int x = 0; x <= inSize; x++) {
        cout << inArray[x];
        if (x != inSize) cout << ", ";
    } // End For
    cout << "]" << endl;
}

// Return random number
int getRandomNumber(int min, int max) {
    random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist(min,max);
    int number = dist(rng);
    if (number < min) number = min;
    else if (number > max) number = max;
    return number;
}

void merge(int *array, int start, int center, int end) {

   int x, y;
   int k;
   int leftPart, rightPart;

   // Set size of left and right partitions
   leftPart = center-start+1; 
   rightPart = end-center;
   int leftArray[leftPart], rightArray[rightPart];

   //Fill left and right partitions
   for(x = 0; x<leftPart; x++)
      leftArray[x] = array[start+x]; keys++;
   for(y = 0; y<rightPart; y++)
      rightArray[y] = array[center+1+y]; keys++;

   x = 0; y = 0; k = start;

   // Combine partitions
   while(x < leftPart && y<rightPart) {
      if(leftArray[x] <= rightArray[y]) {
         array[k] = leftArray[x]; keys++;
         x++; keys++;
      }else{
         array[k] = rightArray[y]; keys++;
         y++; keys++;
      }
      k++; keys++;
   } // End While

   // Account for extra elements
   while(x<leftPart) {
      array[k] = leftArray[x]; keys++;
      x++; k++; keys+=2;
   } // End While

   while(y<rightPart) {
      array[k] = rightArray[y]; keys++;
      y++; k++; keys+=2;
   } // End While

}

void mergeSort(int *array, int start, int end) {
    int center;

    // Return when sort recursion is complete
    if (end > start) {
        
        // Determine center
        int center = start+(end-start)/2;

        // Sort partitions
        mergeSort(array, start, center);
        mergeSort(array, center+1, end);

        // Merge
        merge(array, start, center, end);
    }
      
   
}

int partition(int inArray[], int start, int end)
{
    int pivot = inArray[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (inArray[i] <= pivot)
            count++; keys++;
    } // End For
 
    // Position pivot
    int pivotIndex = start + count;
    swap(inArray[pivotIndex], inArray[start]); keys++;
 
    // Sort elements surrounding pivot
    int left = start, right = end;
    while (left < pivotIndex && right > pivotIndex) {
 
        while (inArray[left] <= pivot) {
            left++; keys++;
        } // End While
 
        while (inArray[right] > pivot) {
            right--; keys++;
        } // End While
 
        if (left < pivotIndex && right > pivotIndex) {
            swap(inArray[left++], inArray[right--]); keys++;
        } // End While
    } // End While
 
    return pivotIndex;
}
 
void quickSort(int inArray[], int start, int end)
{
 
    // Return when sort recursion is complete
    if (start >= end) return;
 
    // Define partition
    int selectedPartition = partition(inArray, start, end);
 
    // Quick sort left partition
    quickSort(inArray, start, selectedPartition - 1);
 
    // Quick sort right partition
    quickSort(inArray, selectedPartition + 1, end);
}

void bubbleSort(int inArray[], int n) 
{ 
    int x, y; 
    for (x = 0; x <= n - 1; x++) {

        for (y = 0; y <= n - x - 1; y++) {
            if (inArray[y] > inArray[y + 1]) {
                swap(inArray[y], inArray[y + 1]); keys++;
            }
        } // End For
    } // End For

}

void insertionSort(int inArray[], int n)
{
    int currentElement;
    int x, y;
    for (x = 1; x <= n; x++) {
        currentElement = inArray[x]; keys++;
        y = x - 1; keys++;
 
        while (y >= 0 && inArray[y] > currentElement) {
            inArray[y + 1] = inArray[y]; keys++;
            y = y - 1; keys++;
        } // End While
        inArray[y + 1] = currentElement; keys++;
    } // End For
}

int main()
{

    // Create initial array
    int size = 7;
    int initialArray[size];


    // Fill initial array
    for(int x = 0; x <= size; x++) {
        initialArray[x] = getRandomNumber(1, 10);
    }

    // Create copy arrays
    int array1[size], array2[size], array3[size], array4[size];
    for (int x = 0; x <= size; x++) {
        array1[x] = initialArray[x];
        array2[x] = initialArray[x];
        array3[x] = initialArray[x];
        array4[x] = initialArray[x];
    } // End For

    // Print initial array
    displayArray("Initial Array", initialArray, size);
    cout << endl;

    // Sort Arrays
    int keyOperationsData[4] = {0,0,0,0};

    // Merge Sort
    keys = 0;
    mergeSort(array4, 0, size);
    keyOperationsData[0] = keys;

    // Quick Sort
    keys = 0;
    quickSort(array1, 0, size);
    keyOperationsData[1] = keys;

    // Bubble Sort
    keys = 0;
    bubbleSort(array2, size);
    keyOperationsData[2] = keys;

    // Insertion Sort
    keys = 0;
    insertionSort(array3, size);
    keyOperationsData[3] = keys;



    // Display Sorted Arrays
    displayArray("Quick Sort", array1, size);
    cout << "Key Operations: " << keyOperationsData[0] << "\n\n";
    displayArray("Bubble Sort", array2, size);
    cout << "Key Operations: " << keyOperationsData[1] << "\n\n";
    displayArray("Insertion Sort", array3, size);
    cout << "Key Operations: " << keyOperationsData[2] << "\n\n";
    displayArray("Merge Sort", array4, size);
    cout << "Key Operations: " << keyOperationsData[3] << "\n\n";

}