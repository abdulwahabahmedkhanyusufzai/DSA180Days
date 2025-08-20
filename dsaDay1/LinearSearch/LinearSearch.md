Linear search, also known as a sequential search, is a simple algorithm for finding a specific value within a list of items. It works by checking each item in the list one by one, in sequential order, until the desired value is found or the end of the list is reached.

How It Works
The process is straightforward:

Start at the beginning of the list (the first element).

Compare the current element with the value you're searching for.

If they match, the search is successful, and you return the index (or position) of the element.

If they don't match, move on to the next element in the list.

Repeat steps 2-4 until the end of the list is reached.

If you reach the end and haven't found the value, it means the value is not in the list.

Example in C++
Here's a C++ implementation of a linear search function:

C++

#include <iostream>

// The function takes an array, its size, and the value to find.
int linearSearch(int arr[], int size, int target) {
    // Loop through each element of the array from index 0 to size-1
    for (int i = 0; i < size; ++i) {
        // Check if the current element is equal to the target value
        if (arr[i] == target) {
            // If a match is found, return the index of the element
            return i;
        }
    }
    // If the loop finishes without finding the target, return -1
    // to indicate that the value was not found.
    return -1;
}

int main() {
    int myArray[] = {25, 17, 34, 56, 12, 8};
    int n = sizeof(myArray) / sizeof(myArray[0]); // Calculate the size of the array
    int valueToFind = 34;
    
    int result = linearSearch(myArray, n, valueToFind);
    
    if (result != -1) {
        std::cout << "Element found at index: " << result << std::endl;
    } else {
        std::cout << "Element not found in the array." << std::endl;
    }

    return 0;
}
In this code, the linearSearch function iterates through the myArray. When it finds the value 34 at index 2, it immediately returns 2. If you were searching for a value like 99, the loop would complete without finding a match, and the function would return -1.

Time Complexity
The efficiency of an algorithm is measured using time complexity, which describes how the runtime of an algorithm grows as the size of the input grows.

Best Case: O(1). This happens when the value you're searching for is the very first element of the list. You only need to perform one comparison.

Worst Case: O(n). This occurs when the value is the last element in the list or is not in the list at all. The algorithm must check every single element, where 'n' is the number of elements in the list.

Average Case: O(n). On average, you can expect to check roughly half of the elements.

Because its time complexity is proportional to the size of the list, linear search is best suited for small or unsorted lists. For large, sorted lists, more efficient search algorithms like binary search are a better choice.