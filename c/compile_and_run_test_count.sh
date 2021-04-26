mkdir -p out
g++ ./omp_count_test.cpp -o ./out/test -fopenmp
./out/test