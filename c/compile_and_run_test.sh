mkdir -p out
g++ ./omp_speed_test_two.cpp -o ./out/test -fopenmp
./out/test