//
// Created by alireza on 16.02.21.
// Edited by amirho3ein on 17.04.21
//

#include "gray_wolf_optimizer.h"
#include <iostream>
#include <limits>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include <math.h>
#include <ctime>
#include <string>

using namespace std;

solution gray_wolf_optimizer::solve() {
    solution my_solution = solution();

    return my_solution;
}

double clip(double n, double lower, double upper) {
  return std::max(lower, std::min(n, upper));
}

string getDateTime(){
	time_t t = time(0);   // get time now
    tm* now = localtime(&t);
	string time = to_string(now->tm_year + 1900).append("-").append(to_string(now->tm_mon + 1)).append("-").append(to_string(now->tm_mday))
	.append("-").append(to_string(now->tm_hour)).append("-").append(to_string(now->tm_min)).append("-").append(to_string(now->tm_sec));
	return time;
}

int func(int (*objective_function)(int*),
				int lower_band,
				int upper_band,
				int dimension,
				int search_agents_number = 10,
				int max_iteration = 100,
				bool enable_print = 0){
	
	srand( (unsigned)time(NULL));
	
	//initialize alpha, beta, and delta_pos
	int alpha_pos[dimension]= {};
    float alpha_score = (float) std::numeric_limits<double>::infinity();

    int beta_pos[dimension] = {};
    float beta_score = (float) std::numeric_limits<double>::infinity();

    int delta_pos[dimension] = {};
    float delta_score = (float) std::numeric_limits<double>::infinity();
    
	//?????????
	//	if not isinstance(lower_band, list):
	//    lower_band = [lower_band] * dimension
	//	
	//    if not isinstance(upper_band, list):
	//        upper_band = [upper_band] * dimension

	//Initialize the positions of search agents
    int positions[search_agents_number][dimension] = {};
    for(int i = 0 ; i < dimension ; i++)
    	for(int j = 0 ; j <search_agents_number ; j++)
        	positions[j][i] = (((double) rand() / (RAND_MAX)) * (upper_band - lower_band) + lower_band);
    
    int convergence_curve[max_iteration] = {};
    
    if (enable_print){
    	cout << "GWO is optimizing '" << __func__ <<"'"<< endl;
	}
	
	string startTime = getDateTime();
	
    for(int iteration_number = 0 ; iteration_number < max_iteration ; iteration_number++){
    	for(int i = 0 ; i < search_agents_number ; i++){
	        //Return back the search agents that go beyond the boundaries of the search space
	        for(int j = 0 ; j < dimension ; j++){
	            positions[i][j] = clip(positions[i][j], lower_band, upper_band);
			}
			//Calculate objective function for each search agent
            int fitness = objective_function(positions[i]);
            
            //Update Alpha, Beta, and Delta
            if (fitness < alpha_score){
                delta_score = beta_score;  //Update delta
                delta_pos = beta_pos;
                beta_score = alpha_score;  //Update beta
                beta_pos = alpha_pos;
                alpha_score = fitness;
                //Update alpha
                alpha_pos = positions[i];
            }
            if (alpha_score < fitness && fitness < beta_score){
                delta_score = beta_score;  //Update delta
                delta_pos = beta_pos;
                beta_score = fitness;  //Update beta
                beta_pos = positions[i];
            }
            if (alpha_score < fitness && fitness < delta_score && fitness > beta_score){
                delta_score = fitness;  //Update delta
                delta_pos = positions[i];
            }
            
        
		}
		//a decreases linearly from 2 to 0
        int a = 2 - iteration_number * (2 / max_iteration);
        
        //Update the Position of search agents including omegas
        for(int i = 0 ; i < search_agents_number ; i++){
            for(int j = 0 ; j < dimension){
                double r1 = (double) rand() / (RAND_MAX); //r1 is a random number in [0,1]
                double r2 = (double) rand() / (RAND_MAX);  //r2 is a random number in [0,1]

                double a1 = 2 * a * r1 - a;
                //Equation (3.3)
                double c1 = 2 * r2;
                //Equation (3.4)

				//????????
                //double d_alpha = fabs(c1 * alpha_pos[j] - positions[i][j]);
                //Equation (3.5)-part 1
                //????????
                //double x1 = alpha_pos[j] - a1 * d_alpha;
                //Equation (3.6)-part 1

                double r1 = (double) rand() / (RAND_MAX);
                double r2 = (double) rand() / (RAND_MAX);

                double a2 = 2 * a * r1 - a;
                //Equation (3.3)
                double c2 = 2 * r2;
                //Equation (3.4)

				//???????
                //d_beta = fabs(c2 * beta_pos[j] - positions[i][j]);
                //Equation (3.5)-part 2
                //???????
                //x2 = beta_pos[j] - a2 * d_beta
                //Equation (3.6)-part 2

                double r1 = (double) rand() / (RAND_MAX);
                double r2 = (double) rand() / (RAND_MAX);

                double a3 = 2 * a * r1 - a;
                //Equation (3.3)
                double c3 = 2 * r2;
                //Equation (3.4)
				
				//????????
                //d_delta = fabs(c3 * delta_pos[j] - positions[i][j]);
                //Equation (3.5)-part 3
                //????????
                //x3 = delta_pos[j] - a3 * d_delta;
                //Equation (3.5)-part 3

                positions[i][j] = (x1 + x2 + x3) / 3;  //Equation (3.7)
            }
		}
		
		convergence_curve[iteration_number] = alpha_score;
		
		if (enable_print){
            if (iteration_number % 5 == 0){
                cout<<"[At iteration_number " << to_string(iteration_number) << " the best fitness is " << to_string(alpha_score) << "]";
            }
        }
		
    }
    
	string endTime = getDateTime();
	
}
