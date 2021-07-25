## Data Structures C

This project is started for me to learn to implement the basic data structures that I use daily, in order to reinforce my grasp on them. This is just one of the 3 projects which I intend to write, (data-structures-python, data-structures-c, data-structures-java).

Each project will be with the implementation of the selected data structures and the unit testing to cover all the functions as much as possible. The data structures will be implemented without using any built-in advanced functions as much as possible, to get as close to the original implementation as close as possible.

### Requirements

This C Project requires the following to be installed.

- gcc
- make
- cmake
- cmocka (will consider shipping the project with the cmake)

### Compilation and testing

```bash
cmake . && cmake --build .
ctest # should run all the tests
```

### Data structures implemented
- stack
- linked list
- double linked list
- ring : ring buffer also known as memory ring

### Algorithms implemented
Sorting Algorithm
- bubble sort