mkdir -p out
g++ ./omp_speed_test.cpp -o ./out/test -fopenmp
./out/test