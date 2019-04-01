rm *.o
rm *.out
g++ -o convex_hull_utility.o -c convex_hull_utility.cpp
g++ -o kirkpatrick_seidel.o -c kirkpatrick_seidel.cpp
g++  test.cpp convex_hull_utility.o kirkpatrick_seidel.o
