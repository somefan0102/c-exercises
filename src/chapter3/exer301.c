#include <stdio.h>
#include <time.h> // Used to measure time for each, pretending to know how this works.

int binsearch(int, int[], int);
int betterbinsearch(int, int[], int);

int main(void) {
    clock_t time;

    double takens[2];
    double result;

    int arr[] = {-48, -17, -10, -4, -3, 0, 2, 5, 6, 7, 8, 13, 14, 24, 32, 42, 64, 66, 69, 81, 99, 101};
    int size = sizeof(arr)/sizeof(int);

    printf("Using regular binary search.\n");
    time = clock();
    for (int i = 0; i < size; i++) {
        printf("%3i is located at %3i\n", arr[i], binsearch(arr[i], arr, size));
    }
    time = clock() - time;
    takens[0] = ((double)time)/CLOCKS_PER_SEC;
    putchar('\n');

    printf("Using optimized binary search.\n");
    time = clock();
    for (int i = 0; i < size; i++) {
        printf("%3i is located at %3i\n", arr[i], betterbinsearch(arr[i], arr, size));
    }
    time = clock() - time;
    takens[1] = ((double)time)/CLOCKS_PER_SEC;
    putchar('\n');

    printf("Regular function loop took %f seconds to finish.\n", takens[0]);
    printf("Optimized function loop took %f seconds to finish.\n", takens[1]);
    putchar('\n');

    result = takens[0] - takens[1];
    printf("Result: Optimized is faster than regular by %f seconds.\n", result);
    if (result <= 0.0) {
        printf("Wow.\n");
    }

    return 0;
}

int binsearch(int x, int arr[], int size) {
    int low, mid, high;

    low = 0;
    high = size;

    while (low <= high) {
        mid = (low + high) / 2;

        if (x < arr[mid]) {
            high = mid;
        } else if (x > arr[mid]) {
            low = mid;
        } else {
            return mid;
        }
    }

    return -1;
}

int betterbinsearch(int x, int arr[], int size) {
    int low = 0;
    int mid;
    int high = size;

    do {
        mid = (low + high) / 2;

        if (x < arr[mid]) {
            high = mid;
        } else if (x > arr[mid]) {
            low = mid;
        }
    } while (low <= high && x != arr[mid]);

    // I use a do-while loop instead of while loop because the second condition (`x != arr[mid]`)
    // would generate unexpected behavior since `mid` wouldn't be defined until after the condition.
    // I would just duplicated the `mid = (low + high) / 2` outside the loop, but this is supposed to be optimized.

    return (x == arr[mid]) ? mid : -1;
}

/*
301: Our binary search makes two tests inside the loop, when one would suffice (at
     the price of more tests outside.) Write a version with only one test inside the loop and
     measure the difference in run-time.
*/