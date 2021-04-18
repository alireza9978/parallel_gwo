mkdir -p out
g++ ./main.cpp ./EvaluationFunctions.cpp ./solution.cpp -o ./out/output -fopenmp
./out/output