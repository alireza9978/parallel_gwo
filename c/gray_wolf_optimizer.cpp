//
// Created by alireza on 16.02.21.
// Edited by amirho3ein on 17.04.21
//

#include "solution.cpp"
#include <iostream>
#include <limits>
#include <algorithm> // for std::find
#include <iterator>  // for std::begin, std::end
#include <math.h>
#include <ctime>
#include <string>
#include <list>
#include <stdio.h>
#include <cstring>

using namespace std;

class GrayWolf
{
private:
  double clip(double n, double lower, double upper)
  {
    return max(lower, min(n, upper));
  }

  string getDateTime()
  {
    time_t t = time(0); // get time now
    tm *now = localtime(&t);
    string time = to_string(now->tm_year + 1900).append("-").append(to_string(now->tm_mon + 1)).append("-").append(to_string(now->tm_mday)).append("-").append(to_string(now->tm_hour)).append("-").append(to_string(now->tm_min)).append("-").append(to_string(now->tm_sec));
    return time;
  }

public:
  Solution solve(double(objective_function)(double *),
                 double lower_band[],
                 double upper_band[],
                 int dimension,
                 int search_agents_number = 10,
                 int max_iteration = 100,
                 bool enable_print = 0)
  {

    srand(time(0));

    Solution my_solution(max_iteration);
    my_solution.startTime = getDateTime();

    //initialize alpha, beta, and delta_pos
    double alpha_pos[dimension];
    double alpha_score = std::numeric_limits<double>::infinity();

    double beta_pos[dimension];
    double beta_score = std::numeric_limits<double>::infinity();

    double delta_pos[dimension] = {};
    double delta_score = std::numeric_limits<double>::infinity();

    //Initialize the positions of search agents

    double positions[search_agents_number][dimension] = {};
    for (int i = 0; i < dimension; i++)
    {
      for (int j = 0; j < search_agents_number; j++)
      {
        positions[j][i] = ((rand() / ((double)RAND_MAX)) * (upper_band[i] - lower_band[i]) + lower_band[i]);
      }
    }

    double convergence_curve[max_iteration] = {};
    double fitnesses[search_agents_number] = {};

    for (int iteration_number = 0; iteration_number < max_iteration; iteration_number++)
    {
      for (int i = 0; i < search_agents_number; i++)
      {
        //Return back the search agents that go beyond the boundaries of the search space
        for (int j = 0; j < dimension; j++)
        {
          positions[i][j] = clip(positions[i][j], lower_band[j], upper_band[j]);
        }
        
        //Calculate objective function for each search agent
        fitnesses[i] = (*objective_function)(positions[i]);
      }

      double fitness;
      for (int i = 0; i < search_agents_number; i++)
      {
        fitness = fitnesses[i];
        //Update Alpha, Beta, and Delta
        if (fitness < alpha_score)
        {
          delta_score = beta_score; //Update delta
          memcpy(delta_pos, beta_pos, sizeof(delta_pos));
          beta_score = alpha_score; //Update beta
          memcpy(beta_pos, alpha_pos, sizeof(beta_pos));
          alpha_score = fitness;
          //Update alpha
          memcpy(alpha_pos, positions[i], sizeof(alpha_pos));
        }
        if (alpha_score < fitness && fitness < beta_score)
        {
          delta_score = beta_score; //Update delta
          memcpy(delta_pos, beta_pos, sizeof(delta_pos));
          beta_score = fitness; //Update beta
          memcpy(beta_pos, positions[i], sizeof(beta_pos));
        }
        if (alpha_score < fitness && fitness < delta_score && fitness > beta_score)
        {
          delta_score = fitness; //Update delta
          memcpy(delta_pos, positions[i], sizeof(delta_pos));
        }
      }
      //a decreases linearly from 2 to 0
      int a = 2 - iteration_number * (2 / max_iteration);
      //Update the Position of search agents including omegas
      for (int i = 0; i < search_agents_number; i++)
      {
        for (int j = 0; j < dimension; j++)
        {
          double r1 = (double)rand() / (RAND_MAX); //r1 is a random number in [0,1]
          double r2 = (double)rand() / (RAND_MAX); //r2 is a random number in [0,1]

          double a1 = 2 * a * r1 - a;
          //Equation (3.3)
          double c1 = 2 * r2;
          //Equation (3.4)

          double d_alpha = fabs(c1 * alpha_pos[j] - positions[i][j]);
          //Equation (3.5)-part 1
          double x1 = alpha_pos[j] - a1 * d_alpha;
          //Equation (3.6)-part 1

          r1 = (double)rand() / (RAND_MAX);
          r2 = (double)rand() / (RAND_MAX);

          double a2 = 2 * a * r1 - a;
          //Equation (3.3)
          double c2 = 2 * r2;
          //Equation (3.4)

          double d_beta = fabs(c2 * beta_pos[j] - positions[i][j]);
          //Equation (3.5)-part 2
          double x2 = beta_pos[j] - a2 * d_beta;
          //Equation (3.6)-part 2

          r1 = (double)rand() / (RAND_MAX);
          r2 = (double)rand() / (RAND_MAX);

          double a3 = 2 * a * r1 - a;
          //Equation (3.3)
          double c3 = 2 * r2;
          //Equation (3.4)

          double d_delta = fabs(c3 * delta_pos[j] - positions[i][j]);
          //Equation (3.5)-part 3
          double x3 = delta_pos[j] - a3 * d_delta;
          //Equation (3.5)-part 3

          positions[i][j] = (x1 + x2 + x3) / 3; //Equation (3.7)
        }
      }

      convergence_curve[iteration_number] = alpha_score;
      my_solution.bestValue = alpha_score;

      if (enable_print)
      {
        if (iteration_number % 5 == 0)
        {
          cout << "[At iteration_number " << to_string(iteration_number) << " the best fitness is " << to_string(alpha_score) << "]" << endl;
        }
      }
    }

    my_solution.endTime = getDateTime();
    memcpy(my_solution.bestAnswers, convergence_curve, sizeof(convergence_curve));
    return my_solution;
  }
};
