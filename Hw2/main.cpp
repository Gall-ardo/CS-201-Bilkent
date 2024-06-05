/*
 * Name: Halil Arda Ozongun
 * Student ID: 22202709
 * Date: 08/04/2024
 */

#include <iostream>
#include <cmath>

// Comparing the heights of a pair of trees takes 1 second.
const int COMPARE_COST = 1;
// Changing the position of each tree takes 5 seconds
const int SWAP_COST = 5;

int swap(int &a, int &b);
int insertionSort(int*& arr, const int size);
int selectionSort(int*& arr, const int size);
int bubbleSort(int*& arr, const int size);
void quickSort(int*& arr, int low, int high, int& cost);
int partition(int*& arr, int low, int high, int& cost);
int* generateRandomArray(const int size);
int* generateSortedArray(const int size);
int* generateAlmostSortedArray(const int size);
void selectionSortWithTwoIndex(int*& arr, const int size, int& costOfFirstWorker, int& costOfSecondWorker);
void partitionForDualWorkerQuickSort(int* arr, int low, int high, int& lp, int& rp, int& costLeft, int& costRight);
void DualWorkerQuickSort(int* arr, int low, int high, int& costOfFirstWorker, int& costOfSecondWorker);


int main() {
    // To generate different random numbers each time
    srand((unsigned int)time(NULL));

    // For the first part, generate random arrays of size 2^3 to 2^12
    // for each size, create five random arrays and sort them using each of the four sorting algorithms
    // calculate the average cost of sorting for each algorithm and plot the results
    std::cout << "First Part\n";
    for (int i = 3; i <= 12; i++) {
        int size = pow(2, i);
        int totalInsertionCost = 0, totalSelectionCost = 0, totalBubbleCost = 0, totalQuickCost = 0;

        for (int j = 0; j < 5; j++) {
            int* arr = generateRandomArray(size);
            int* arr2 = new int[size];
            int* arr3 = new int[size];
            int* arr4 = new int[size];
            // to create a deep copy of the array
            for (int k = 0; k < size; k++) {
                arr2[k] = arr[k];
                arr3[k] = arr[k];
                arr4[k] = arr[k];
            }

            totalInsertionCost += insertionSort(arr, size);
            totalSelectionCost += selectionSort(arr2, size);
            totalBubbleCost += bubbleSort(arr3, size);
            int cost = 0;
            quickSort(arr4, 0, size - 1, cost);
            totalQuickCost += cost;


            delete[] arr;
            delete[] arr2;
            delete[] arr3;
            delete[] arr4;
        }
        std::cout << "Average sorting cost for size " << size << " (Insertion Sort): " << totalInsertionCost / 5 << "\n";
        std::cout << "Average sorting cost for size " << size << " (Selection Sort): " << totalSelectionCost / 5 << "\n";
        std::cout << "Average sorting cost for size " << size << " (Bubble Sort): " << totalBubbleCost / 5 << "\n";
        std::cout << "Average sorting cost for size " << size << " (Quick Sort): " << totalQuickCost / 5 << "\n";
        std::cout << "\n";
    }



    // For the second part, generate random "almost sorted" arrays and rest same as the first part
    std::cout << "Second Part\n";
    for (int i = 3; i <= 12; i++) {
        int size = pow(2, i);
        int totalInsertionCost = 0, totalSelectionCost = 0, totalBubbleCost = 0, totalQuickCost = 0;

        for (int j = 0; j < 5; j++) {
            int* arr = generateAlmostSortedArray(size);
            int* arr2 = new int[size];
            int* arr3 = new int[size];
            int* arr4 = new int[size];
            for (int k = 0; k < size; k++) {
                arr2[k] = arr[k];
                arr3[k] = arr[k];
                arr4[k] = arr[k];
            }

            totalInsertionCost += insertionSort(arr, size);
            totalSelectionCost += selectionSort(arr2, size);
            totalBubbleCost += bubbleSort(arr3, size);
            int cost = 0;
            quickSort(arr4, 0, size - 1, cost);
            totalQuickCost += cost;

            delete[] arr;
            delete[] arr2;
            delete[] arr3;
            delete[] arr4;
        }

        std::cout << "Average sorting cost for size " << size << " (Insertion Sort): " << totalInsertionCost / 5 << "\n";
        std::cout << "Average sorting cost for size " << size << " (Selection Sort): " << totalSelectionCost / 5 << "\n";
        std::cout << "Average sorting cost for size " << size << " (Bubble Sort): " << totalBubbleCost / 5 << "\n";
        std::cout << "Average sorting cost for size " << size << " (Quick Sort): " << totalQuickCost / 5 << "\n";
        std::cout << "\n";
    }

    // For the third part, generate random arrays of size 2^3 to 2^12 and sort them using the two worker suitable algorithms
    // and compare them with normal algorithms
    std::cout << "Third Part\n";
    for (int i = 3; i <= 12; i++) {
        int size = pow(2, i);

        int totalSelectionCost = 0, totalQuickSortCost = 0, totalSelectionCostFirstWorker = 0, totalSelectionCostSecondWorker = 0, totalDualPivotCostFirstWorker = 0, totalDualPivotCostSecondWorker = 0;

        for (int j = 0; j < 5; j++) {
            int *arr = generateRandomArray(size);
            int *arr2 = new int[size];
            int *arr3 = new int[size];
            int *arr4 = new int[size];
            for (int k = 0; k < size; k++) {
                arr2[k] = arr[k];
                arr3[k] = arr[k];
                arr4[k] = arr[k];
            }

            totalSelectionCost += selectionSort(arr, size);
            selectionSortWithTwoIndex(arr2, size, totalSelectionCostFirstWorker, totalSelectionCostSecondWorker);
            quickSort(arr3, 0, size - 1, totalQuickSortCost);
            DualWorkerQuickSort(arr4, 0, size - 1, totalDualPivotCostFirstWorker, totalDualPivotCostSecondWorker);

            delete[] arr;
            delete[] arr2;
            delete[] arr3;
            delete[] arr4;
        }
        // Results as seconds, not as costs
        std::cout << "Average sorting cost for size " << size << " (Selection Sort): " << totalSelectionCost / 5 << "\n";
        std::cout << "Average sorting cost for first worker for size " << size << " (Selection Sort with Two Index): " << totalSelectionCostFirstWorker  / 5 << "\n";
        std::cout << "Average sorting cost for second worker for size " << size << " (Selection Sort with Two Index): " << totalSelectionCostSecondWorker / 5 << "\n";
        std::cout << "Average sorting cost for size " << size << " (Selection Sort with Two Index): " << (totalSelectionCostFirstWorker + totalSelectionCostSecondWorker) / 5 << "\n";
        std::cout << "Average sorting cost for size " << size << " (Quick Sort): " << totalQuickSortCost / 5 << "\n";
        std::cout << "Average sorting cost for first worker for size " << size << " (Dual Pivot Quick Sort): " << totalDualPivotCostFirstWorker / 5 << "\n";
        std::cout << "Average sorting cost for second worker for size " << size << " (Dual Pivot Quick Sort): " << totalDualPivotCostSecondWorker / 5 << "\n";
        std::cout << "Average sorting cost for size " << size << " (Dual Pivot Quick Sort): " << (totalDualPivotCostFirstWorker + totalDualPivotCostSecondWorker) / 5 << "\n";
        std::cout << "\n";

    }

    return 0;
}


// Sorting algorithms and helper functions
int swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    return 3*SWAP_COST;
}

int insertionSort(int*& arr, const int size) {
    int cost = 0;

    int key, j;
    for (int i = 1; i < size; i++) {
        key = arr[i];
        cost += SWAP_COST;
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            cost += COMPARE_COST;
            arr[j + 1] = arr[j];
            cost += SWAP_COST;
            j = j - 1;
        }
        arr[j + 1] = key;
        cost += SWAP_COST;
    }

    return cost;
}

int selectionSort(int*& arr, const int size) {
    int cost = 0;

    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            cost += COMPARE_COST;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        cost += swap(arr[i], arr[minIndex]);
    }
    return cost;
}

int bubbleSort(int*& arr, const int size) {
    int cost = 0;
    bool flag;
    for (int i = 0; i < size - 1; i++) {
        flag = false;
        for (int j = 0; j < size - i - 1; j++) {
            cost += COMPARE_COST;
            if (arr[j] > arr[j + 1]) {
                cost += swap(arr[j], arr[j + 1]);
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }
    return cost;
}

void quickSort(int*& arr, int low, int high, int& cost) {
    if (low < high) {
        int pi = partition(arr, low, high, cost);

        quickSort(arr, low, pi - 1, cost);
        quickSort(arr, pi + 1, high, cost);
    }
}

int partition(int*& arr, int low, int high, int& cost) {
    int pivot = arr[high]; // choosing the last element as pivot
    // that might not be the best choice but I will stick with it
    cost += SWAP_COST;
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        cost += COMPARE_COST;
        if (arr[j] <= pivot) {
            i++;
            cost += swap(arr[i], arr[j]);
        }
    }
    cost += swap(arr[i + 1], arr[high]);
    return (i + 1);
}


// Generate  arrays
int* generateRandomArray(const int size) {
    if(size==0){
        return nullptr;
    }

    int* arr = new int[size];
    for(int i = 0; i < size; ++i) {
        arr[i] = std::rand() % size;
    }
    return arr;
}

int* generateSortedArray(const int size) {
    if(size==0){
        return nullptr;
    }
    int* newArray = new int[size];
    for (int i = 0; i < size; i++) {
        newArray[i] = i;
    }
    return newArray;
}

int* generateAlmostSortedArray(const int size) {
    int* arr = generateSortedArray(size);
    // shuffle 6% of the elements
    for (int i = 0; i < size * 0.03; i++) {
        int index1 = std::rand() % size;
        int index2 = std::rand() % size;
        swap(arr[index1], arr[index2]);
    }
    return arr;
}


// For part 3, 2 worker suitable algorithms
void selectionSortWithTwoIndex(int*& arr, const int size, int& costOfFirstWorker, int& costOfSecondWorker) {
    int iteratorRight = 0, iteratorLeft = size - 1;

    while (iteratorRight < iteratorLeft) {
        int minIndex = iteratorRight;
        int maxIndex = iteratorLeft;

        for (int j = iteratorRight; j <= iteratorLeft; j++) {
            costOfFirstWorker += COMPARE_COST;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
            costOfSecondWorker += COMPARE_COST;
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }
        costOfFirstWorker += swap(arr[iteratorRight], arr[minIndex]);

        // There is an edge case, if the maxIndex is equal to the iteratorRight, we need to update the maxIndex
        if (maxIndex == iteratorRight) {
            maxIndex = minIndex;
        }

        costOfSecondWorker += swap(arr[iteratorLeft], arr[maxIndex]);
        iteratorRight++;
        iteratorLeft--;
    }
}

void partitionForDualWorkerQuickSort(int* arr, int low, int high, int& lp, int& rp, int& costLeft, int& costRight) {
    // defined dividers, which are used to divide the array into 3 parts, smaller, between, bigger
    int firstDividerIndex = low + 1;
    int secondDividerIndex = high - 1;
    bool checkIsDone; // a boolean, which checks if compare cost added to any of the workers

    // We are trying to divide 3, smaller, between, bigger so we must be sure right pivot is bigger than left pivot
    if (arr[low] > arr[high]) {
        if(costLeft < costRight){
            costLeft += swap(arr[low], arr[high]);
        }else {
            costRight += swap(arr[low], arr[high]);
        }
    }

    // The aim of pivots, are same with the classic quick sort
    int rightPivot = arr[high];
    int leftPivot = arr[low];

    // iterating from the begining untill the second divider
    // second divider shows the end of the middle part, which means beyond the second driver, all elements are bigger than right pivot so they are already handled
    for (int iterator = low + 1; iterator <= secondDividerIndex; iterator++) {
        checkIsDone = false;

        // if the element is smaller than left pivot, swap it with the first divider and increase the first divider
        if (arr[iterator] < leftPivot) {
            costLeft += swap(arr[iterator], arr[firstDividerIndex]); // Cost for swapping less than pivot attributed to the left worker
            firstDividerIndex++;
            costRight += COMPARE_COST;
            checkIsDone = true;

        // if the element is bigger than right pivot, swap it with the second divider and decrease the second divider
        } else if (arr[iterator] >= rightPivot) {

            // trying to find the first element from the end, which is smaller than right pivot
            while (arr[secondDividerIndex] > rightPivot && iterator < secondDividerIndex) {
                secondDividerIndex--;
                costRight += COMPARE_COST;
            }
            // after finding the element, swap it with the second divider and decrease the second dividers index
            costRight += swap(arr[iterator], arr[secondDividerIndex]);
            secondDividerIndex--;
            // if the new iterator is smaller than left pivot, swap it with the first divider and increase the first divider
            if (arr[iterator] < leftPivot) {
                costLeft += swap(arr[iterator], arr[firstDividerIndex]);
                firstDividerIndex++;
            }
            costLeft += COMPARE_COST;
            checkIsDone = true;

        }

        // if the element is in the middle, compare costs should be added to both workers
        if(!checkIsDone){
                costRight += COMPARE_COST;
                costLeft += COMPARE_COST;
        }

    }
    // change positions of pivots
    costLeft += swap(arr[low], arr[firstDividerIndex-1]);
    costRight += swap(arr[high], arr[secondDividerIndex+1]);

    // update lp and rp
    lp = firstDividerIndex-1;
    rp = secondDividerIndex+1;
}

void DualWorkerQuickSort(int* arr, int low, int high, int& costOfFirstWorker, int& costOfSecondWorker) {
    if (low < high) {
        int lp, rp; // Left and right pivots
        partitionForDualWorkerQuickSort(arr, low, high, lp, rp, costOfFirstWorker, costOfSecondWorker);

        DualWorkerQuickSort(arr, low, lp - 1, costOfFirstWorker, costOfSecondWorker); // Sorting first part
        DualWorkerQuickSort(arr, lp + 1, rp - 1, costOfFirstWorker, costOfSecondWorker); // Sorting middle part
        DualWorkerQuickSort(arr, rp + 1, high, costOfFirstWorker, costOfSecondWorker); // Sorting last part
    }
}