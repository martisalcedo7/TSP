#include <iostream>
#include <vector>
#include <algorithm>
#include "solvers.hpp"
// Local libs
#include "cities.hpp"

long factorial(const int n)
{
    long f = 1;
    for (int i=1; i<=n; ++i)
        f *= i;
    return f;
}

std::vector<int> brute_force(int number_of_cities, const std::vector<std::vector<float>> &distances){

    std::vector<int> path(number_of_cities-1, 0);
    std::vector<int> real_path(number_of_cities, 0);

    for(int x=0; x<number_of_cities-1; x++){
        path.at(x) = x+1;
        // std::cout << x+1 << " ";
    }
    // std::cout << "\n";

    long permutations = factorial(number_of_cities-1)/2.0;
    std::cout << "Possible permutations: (num_cities-1)! / 2 = " << permutations << "\n";

    float best_distance;
    std::vector<int> best_path(number_of_cities, 0);

    long counter = 0;
    do {

        for(int x=0; x<number_of_cities-1; x++){
            real_path.at(x+1) = path.at(x);
        }
        float distance = total_distance(real_path, distances);
        if(counter == 0){
            best_distance = distance;
            best_path = real_path;
        }else{
            if(distance < best_distance){
                best_distance = distance;
                best_path = real_path;
            }
        }

        std::cout << counter << ": ";
        for(int x=0; x<number_of_cities; x++){
            std::cout << real_path.at(x) << " ";
        }
        std::cout << "\n";
        counter++;
    } while (std::next_permutation(path.begin(), path.end()) && counter < permutations);

    return best_path;
}