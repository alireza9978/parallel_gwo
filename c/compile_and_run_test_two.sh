mkdir -p out
g++ ./omp_speed_test_three.cpp -o ./out/test_two -fopenmp
./out/test_two