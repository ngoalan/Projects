#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds


//DECLARATIONS
void Quicksort_Midpoint(int numbers[], int i, int k); 
//this function sorts the given array in the range from i to k using quicksort method. 
//In this function, pivot is the midpoint element (numbers[(i+k)/2]). 
//(implementation of this function is given in section 21.5)

void Quicksort_MedianOfThree(int numbers[], int i, int k);
// this function utilizes different pivot selection technique in quicksort algorithm. 
//The pivot is the median of the following three values: leftmost (numbers[i]), 
    //midpoint (numbers[(i+k)/2]) and rightmost (numbers[k]). 
//You should modify the partition function given in section 21.5 to
    //select the pivot using median-of-three technique.

void InsertionSort(int numbers[], int numbersSize);
// this function sorts the given array using InsertionSort method. 
//(implementation of this method is provided in section 21.3).

int genRandInt(int low, int high);
void fillArrays(int arr1[], int arr2[],int arr3[]);
int Partition(int numbers[], int lowIndex, int highIndex);
int Partition2(int numbers[], int lowIndex, int highIndex);

int main() {

    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    fillArrays(arr1, arr2, arr3);


    clock_t Start = clock();
    Quicksort_Midpoint(arr1, 0, NUMBERS_SIZE - 1);
    clock_t End = clock();
    int elapsedTime1 = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime1 << endl;

    Start = clock();
    Quicksort_MedianOfThree(arr2, 0, NUMBERS_SIZE - 1);
    End = clock();
    int elapsedTime2 = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime2 << endl;
    
    Start = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    End = clock();
    int elapsedTime3 = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime3 << endl;

    return 0;
}


//IMPLEMENTATIONS
int genRandInt(int low, int high) {
    return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]) {
    for(int i = 0; i < NUMBERS_SIZE; ++i) {
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void Quicksort_Midpoint(int numbers[], int i, int k) {
    if (i >= k) {
        return;
    }

   int lowEndIndex = Partition(numbers, i, k);
   Quicksort_Midpoint(numbers, i, lowEndIndex);
   Quicksort_Midpoint(numbers, lowEndIndex + 1, k);
}

//partition for midpoint quicksort
int Partition(int numbers[], int lowIndex, int highIndex) {
   // Pick middle element as pivot
   int midpoint = lowIndex + (highIndex - lowIndex) / 2;
   int pivot = numbers[midpoint];
 
   bool done = false;
   while (!done) {
      while (numbers[lowIndex] < pivot) {
         lowIndex += 1;
      }
    
      while (pivot < numbers[highIndex]) {
         highIndex -= 1;
      }
    
    //if one element or zero remains, all are partitioned
      if (lowIndex >= highIndex) {
         done = true;
      }
      else {
         // Swap [lowIndex] and [highIndex]
         int temp = numbers[lowIndex];
         numbers[lowIndex] = numbers[highIndex];
         numbers[highIndex] = temp;
       
         // update
         lowIndex += 1;
         highIndex -= 1;
      }
   }
 
   return highIndex;
}


void Quicksort_MedianOfThree(int numbers[], int i, int k){
        if (i >= k) {
        return;
    }

   int lowEndIndex = Partition2(numbers, i, k);
   Quicksort_MedianOfThree(numbers, i, lowEndIndex);
   Quicksort_MedianOfThree(numbers, lowEndIndex + 1, k);
}

int Partition2(int numbers[], int lowIndex, int highIndex) {
       //middle is pivot
    int pivot;
    int midpoint = lowIndex + (highIndex - lowIndex) / 2;
    if (numbers[lowIndex] > numbers[highIndex]) {
        if (numbers[lowIndex] > numbers[midpoint]) {
            if (numbers[highIndex] > numbers[midpoint]) {
                pivot = numbers[highIndex];
            }
            else {
                pivot = numbers[midpoint];
            }
        }
        else {
            pivot = numbers[lowIndex];
        }
    }
    else {
        if (numbers[highIndex] > numbers[midpoint]) {
            if (numbers[lowIndex] > numbers[midpoint]) {
                pivot = numbers[lowIndex];
            }
            else {
                pivot = numbers[midpoint];
            }
        }
        else {
            pivot = numbers[highIndex];
        }
    }
 
   bool done = false;
   while (!done) {
      // Increment lowIndex while numbers[lowIndex] < pivot
      while (numbers[lowIndex] < pivot) {
         lowIndex += 1;
      }
    
      // Decrement highIndex while pivot < numbers[highIndex]
      while (pivot < numbers[highIndex]) {
         highIndex -= 1;
      }
    
      // If zero or one elements remain, then all numbers are
      // partitioned. Return highIndex.
      if (lowIndex >= highIndex) {
         done = true;
      }
      else {
         // Swap [lowIndex] and [highIndex]
         int temp = numbers[lowIndex];
         numbers[lowIndex] = numbers[highIndex];
         numbers[highIndex] = temp;
       
         // Update lowIndex and highIndex
         lowIndex += 1;
         highIndex -= 1;
      }
   }
 
   return highIndex;
}

// this function sorts the given array using InsertionSort method. 
void InsertionSort(int numbers[], int numbersSize){
    for (int i = 1; i < numbersSize; ++i) {
        int j = i;
        // Insert numbers[i] into sorted part 
        // stopping once numbers[i] in correct position
        while (j > 0 && numbers[j] < numbers[j - 1]) {
                
            // Swap [j] and [j - 1]
            int temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            --j;
        }
    }
}
