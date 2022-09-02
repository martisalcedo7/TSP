#include <iostream>
#include <vector>
#include <algorithm>
#include "solvers.hpp"
#include "cities.hpp"
#include "utils.hpp"

// Brute Force

BruteForce::BruteForce(Cities &cities): cities {cities}{
    solved = false;
    counter = 0;
    number_of_cities = cities.get_number_of_cities();

    path = std::vector<int>(number_of_cities, 0);
    short_path = std::vector<int>(number_of_cities-1, 0);

    for(size_t x=1; x<number_of_cities; x++){
        short_path.at(x-1)=x;
        path.at(x)=x;
    }

    best_distance = cities.total_distance(path);
    best_path = path;

    long permutations = factorial(number_of_cities-1)/2.0;
    std::cout << "Possible permutations: (num_cities-1)! / 2 = " << permutations << "\n";
}

void BruteForce::step(void){
    if(solved){
        return;
    }

    for(size_t x=0; x<number_of_cities-1; x++){
        path.at(x+1) = short_path.at(x);
    }

    float distance = cities.total_distance(path);

    if(distance < best_distance){
        best_distance = distance;
        best_path = path;
    }

    counter++;

    // std::cout << counter << "\n";

    while(true){
        if(!std::next_permutation(short_path.begin(), short_path.end())){
            solved = true;
            break;
        }
        if(short_path.at(0) < short_path.back()){
            break;
        }
    }
}

void BruteForce::solve(void){
    while(!solved){
        step();
        // std::cout << counter << "\n";
    }
}

std::vector<int> BruteForce::get_best_path(void){
    return best_path;
}

std::vector<int> BruteForce::get_path(void){
    return path;
}

float BruteForce::get_best_distance(void){
    return best_distance;
}

bool BruteForce::is_solved(void){
    return solved;
}

long BruteForce::get_counter(void){
    return counter;
}


// SOM solver

SOM::SOM(Cities &cities): cities {cities}{
    solved = false;
    counter = 0;
    number_of_cities = cities.get_number_of_cities();

    // points = std::vector<Point>(number_of_cities, Point);



}

void SOM::step(void){
    if(solved){
        return;
    }


}

void SOM::solve(void){
    while(!solved){
        step();
    }

    //Select random city
    //Find closest dot
    //update all dots based on closest dot
}

std::vector<int> SOM::get_best_path(void){
    return best_path;
}

float SOM::get_best_distance(void){
    return best_distance;
}

bool SOM::is_solved(void){
    return solved;
}

long SOM::get_counter(void){
    return counter;
}

