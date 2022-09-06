#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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
    std::cout << "Possible paths for " << number_of_cities << " cities: (" << number_of_cities << "-1)! / 2 = " << permutations << "\n";
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
    cities_location = cities.get_cities();
    alpha = 0.00001;///number_of_cities;
    nabla = 1.0;
    number_of_points = number_of_cities * 4;

    //Create random points
    points = std::vector<Point>(number_of_points);

    float radius = std::min(cities.get_map_size().x, cities.get_map_size().y) / 2.0;
    float angle_increment = 2 * M_PI / number_of_points;

    for(size_t x=0; x<number_of_points; x++){
        points.at(x).x = radius * cos(x * angle_increment) + cities.get_map_size().x / 2.0;
        points.at(x).y = radius * sin(x * angle_increment) + cities.get_map_size().y / 2.0;
        // points.at(x).x = random_number(cities.get_map_size().x);
        // points.at(x).y = random_number(cities.get_map_size().y);
        // std::cout << points.at(x).x << ", " << points.at(x).y << "\n";
    }

    //Create neighboring matrix
    neighboring = std::vector<std::vector<float>>(number_of_points, std::vector<float>(number_of_points));
    update_neighboring();

}

void SOM::update_neighboring(void){
    for(size_t x=0; x<number_of_points; x++){
        for(size_t y=0; y<number_of_points; y++){
            uint distance = std::abs(static_cast<int>(x)-static_cast<int>(y));
            if(distance>(number_of_points/2)){
                distance = number_of_points - distance;
            }
            if(distance == 0){
                neighboring.at(x).at(y) = 1.0;
            }else{
                neighboring.at(x).at(y) = std::exp(-alpha*std::pow(distance, 2.0));
            }
        }
        // print_vector(neighboring.at(x));
    }
}

void SOM::step(void){
    if(solved){
        return;
    }

    uint city = random_number(number_of_cities-1);

    uint c_point = closest_point(city);

    for(size_t x=0; x<number_of_points; x++){
        points.at(x).x = points.at(x).x + nabla * neighboring.at(c_point).at(x) * (cities_location.at(city).x - points.at(x).x);
        points.at(x).y = points.at(x).y + nabla * neighboring.at(c_point).at(x) * (cities_location.at(city).y - points.at(x).y);
    }

    alpha += 0.0001;
    nabla -= 0.000001;
    if(nabla <= 0.001){
        nabla = 0.001;
    }

    update_neighboring();

    counter++;

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

    std::vector<uint> indexes(number_of_cities);
    std::vector<uint> order(number_of_cities);

    for(size_t x=0; x<number_of_cities; x++){
        indexes.at(x) = closest_point(x);
        order.at(x) = closest_point(x);
    }

    std::stable_sort(order.begin(), order.end());
    best_path = std::vector<int>(number_of_cities);

    for(size_t x=0; x<number_of_cities; x++){
        for(size_t y=0; y<number_of_cities; y++){
            if(indexes.at(x) == order.at(y)){
                best_path.at(y) = x;
            }
        }
    }
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

std::vector<Point> SOM::get_points(void){
    return points;
}

uint SOM::get_number_of_points(void){
    return number_of_points;
}

uint SOM::closest_point(uint city){
    uint closest_point = 0;
    float shortest_distance = pow(cities_location.at(city).x - points.at(0).x, 2.0) + pow(cities_location.at(city).y - points.at(0).y, 2.0);
    for(size_t x=1; x<number_of_points; x++){
        float distance = pow(cities_location.at(city).x - points.at(x).x, 2.0) + pow(cities_location.at(city).y - points.at(x).y, 2.0);
        if(distance < shortest_distance){
            closest_point = x;
            shortest_distance = distance;
        }
    }
    return closest_point;
}

