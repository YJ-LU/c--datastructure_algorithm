cmake_minimum_required(VERSION 3.20)
project(leetcodeNotes)

set(CMAKE_CXX_STANDARD 14)



file (GLOB_RECURSE files *.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file} 206ReverseList.cpp 15ThreeSum.cpp 704BinarySearch.cpp 154RotateArray.cpp 21MergeSortList.cpp)
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()
