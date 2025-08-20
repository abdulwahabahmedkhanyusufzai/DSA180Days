What's a Vector?
A std::vector is a dynamic array. Unlike a traditional C-style array, which has a fixed size determined at compile time, a vector can change its size dynamically during runtime. This means you don't need to know the number of elements you'll need when you declare it.

Vectors store elements in contiguous memory, just like arrays. This gives them the same efficiency for element access using an index.

To use vectors, you must include the <vector> header.

Declaring and Initializing a Vector
You can declare and initialize a vector in several ways:

Empty Vector: Creates an empty vector that you can add elements to later.

C++

#include <vector>
std::vector<int> myVector;
Size-based Initialization: Creates a vector with a specified number of elements, all initialized to a default value (e.g., 0 for integers).

C++

std::vector<int> myVector(5); // Creates a vector of 5 integers, all with the value 0
Initialization with Values: Initializes a vector with a set of values, similar to how you would with an array.

C++

std::vector<int> myVector = {10, 20, 30, 40, 50}; // Automatically sized to 5
Common Vector Operations
Here are some of the most common and useful operations you'll perform with vectors:

Adding Elements: The push_back() method is the most common way to add an element to the end of a vector.

C++

std::vector<int> numbers;
numbers.push_back(10); // numbers now contains: {10}
numbers.push_back(20); // numbers now contains: {10, 20}
Accessing Elements: You can access elements using the [] operator or the .at() method. The .at() method provides bounds checking, which can help prevent errors.

C++

// Access using []
int first_element = numbers[0]; 

// Access using .at()
int last_element = numbers.at(1);
Getting the Size: The .size() method returns the number of elements in the vector.

C++

std::cout << "Vector size: " << numbers.size();
Removing Elements:

pop_back(): Removes the last element from the vector.

clear(): Removes all elements from the vector.

C++

numbers.pop_back(); // numbers now contains: {10}
numbers.clear();    // numbers is now empty
Iterating: You can iterate through a vector using a traditional for loop with an index or a more modern range-based for loop.

Why Use Vectors over Arrays?
Dynamic Size: The ability to grow or shrink is a huge advantage. You don't have to worry about allocating too little or too much memory upfront.

Bounds Checking: The .at() method provides a safe way to access elements, throwing an exception if you try to access an invalid index.

Ease of Use: Vectors come with built-in functions for common operations like sorting, reversing, and resizing, which are not available for raw C-style arrays.

Memory Management: Vectors handle their own memory management, automatically reallocating memory when needed. This simplifies your code and reduces the risk of memory leaks.