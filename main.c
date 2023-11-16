#include <math.h> 
#include <stdio.h>   
#include <stdlib.h>
#include <time.h>
#define length 100000

int* makeArray(int n)
{
    srand(time(NULL));
    int idx = 0;
    int i, j = 0;
    int* outArr = (int*)malloc(sizeof(int) * n);
    int* tmpArr = (int*)malloc(sizeof(int) * n * 100);

    for (i = 0; i < n * 100; i++) {
        tmpArr[i] = i; //tempArr=[0,1,2,3,4....100n-1]
    }

    idx = rand() % n; //나머지 0~n-1
    for (i = 0; i < idx; i++) { //ex n=10이라 하면 0<i<7
        j += (rand() % 10) + 1; //반복 한번당 1~10을 더함 
        outArr[i] = tmpArr[j]; //outArr[0]~[idx-1] 아무 수나 넣음
    }

    j = 0;
    for (i = idx; i < n; i++) {
        j += (rand() % 10) + 1;
        outArr[i] = tmpArr[j];
    }

    free(tmpArr);
    return outArr;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int array[], int n)
{
    int i, j, min_element;
    for (i = 0; i < n - 1; i++)
    {
        min_element = i;
        for (j = i + 1; j < n; j++)
            if (array[j] < array[min_element])
                min_element = j;
        swap(&array[min_element], &array[i]);
    }
}

void insertionSort(int array[], int n)
{
    int i, element, j;
    for (i = 1; i < n; i++) {
        element = array[i]; j = i - 1; while (j >= 0 && array[j] > element) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = element;
    }
}

int isSorted(int array[], int n)
{
    int i;
    for (i = 0; i < n-1; i++)
        if(array[i] > array[i+1])
            return 0;

    return 1;
}

long long arrSum(int array[], int n)
{
    int i;
    long long sum = 0;
    for (i = 0; i < n; i++)
        sum += array[i];

    return sum;
}

// or MySort(int array[], int l, int r) 
void MySort(int array[], int n) 
{
    // Implement your algorithm
}

int main()
{
    int* Data;
    int Data_copy[length];
    int i;
    double time_taken;
    clock_t t;
    
    // Data generation
    Data = makeArray(length);
    for (i = 0; i < length; i++) {
        Data_copy[i] = Data[i];
    }
    printf("Original Data Descriptions");
    printf("Are Data Sorted?: %d \n", isSorted(Data_copy, length));
    printf("Data Sum: %lld \n\n", arrSum(Data_copy, length));
    

    // Insertion Sort
    t = clock();
    insertionSort(Data_copy, length);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Insertion Sort took %f seconds to execute \n", time_taken);
    printf("Are Data Sorted?: %d \n", isSorted(Data_copy, length));
    printf("Data Sum: %lld \n\n", arrSum(Data_copy, length));


    // Selection Sort
    for (i = 0; i < length; i++) {
        Data_copy[i] = Data[i];
    }
    t = clock();
    selectionSort(Data_copy, length);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Selection Sort took %f seconds to execute \n", time_taken);
    printf("Are Data Sorted?: %d \n", isSorted(Data_copy, length));
    printf("Data Sum: %lld \n\n", arrSum(Data_copy, length));


    // MySort
    for (i = 0; i < length; i++) {
        Data_copy[i] = Data[i];
    }
    t = clock();
    MySort(Data_copy, length);
    // or MySort(Data_copy, 0, length - 1);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("My Sort took %f seconds to execute \n", time_taken);
    printf("Are Data Sorted?: %d \n", isSorted(Data_copy, length));
    printf("Data Sum: %lld \n\n", arrSum(Data_copy, length));

    return 0;
}
