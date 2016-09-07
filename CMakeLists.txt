cmake_minimum_required(VERSION 3.6)
project(Project2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ArrayStack.cpp
    ArrayStack.hpp
    AVLDict.cpp
    AVLDict.hpp
    BagOfMazeStates.hpp
    DoubleHashDict.cpp
    DoubleHashDict.hpp
    HeapPriorityQueue.cpp
    HeapPriorityQueue.hpp
    LinearHashDict.cpp
    LinearHashDict.hpp
    LinkedListDict.cpp
    LinkedListDict.hpp
    LinkedListStack.cpp
    LinkedListStack.hpp
    MazeState.hpp
    PredDict.hpp
    SliderPuzzle.cpp
    SliderPuzzle.hpp
    solve.cpp
    Sudoku.cpp
    Sudoku.hpp
    TextMaze.cpp
    TextMaze.hpp
    UnsortedPriorityQueue.cpp
    UnsortedPriorityQueue.hpp)

add_executable(Project2 ${SOURCE_FILES})