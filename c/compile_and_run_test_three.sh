mkdir -p out
g++ ./omp_speed_test_three.cpp -o ./out/test_three -fopenmp
./out/test_three