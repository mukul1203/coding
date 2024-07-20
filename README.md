Hello world!

Downloaded catch test framework files from 
https://github.com/catchorg/Catch2/blob/devel/extras/catch_amalgamated.cpp
https://github.com/catchorg/Catch2/blob/devel/extras/catch_amalgamated.hpp

To get started with solving a coding problem:
1. Create a folder parallel to 1_parity e.g. 2_longest_common_subsequence.
2. Add a main.cpp, write your code in it.
3. DON'T add a main() function, just write functions and catch TEST_CASE's for your functions.
4. On saving the file, it will compile and run the executable, so anytime you want to build and run, just save.
5. It is recommended to first write test cases for the problem, then write a sort of first solution to the problem (under a v1 namespace),
and try to get the test cases passing. Once they pass, now you can write v2 version of the solution (an optimized one or a different approach)
and hit save. All tests should still pass for your solution to be equivalent of first one.
6. If a test case fails and you want to debug, put breakpoints, go to Run And Debug section of VSCode on left and hit the play button, it will launch the executable through gdb (that is what is specified in launch.json, this json is solely for launching and debugging purposes. Build happens via tasks.json).
7. If you see {?} being printed by REQUIRE macros in your tests, it is because Catch doesn't know how to print your object. You need to define operator<< for it,
BEFORE including the catch header. So typically it is then better to include the header just above the starting TEST_CASE and include the operators above that,
so that all your custom structs etc. along with your program are above the header and accessible to define the operator.
8. For more logging to debug test case failures, check out https://catch2-temp.readthedocs.io/en/latest/logging.html. Check 12_two_stock_sale folder for an example.

A common Makefile is used for all the problems, as we know there will be a main.cpp file in every problem folder. When you trigger a build, it runs the build task from tasks.json, which is nothing but a make command with this Makefile. That builds all the dependencies that changes since last build, and puts the build output in separate build folder.
