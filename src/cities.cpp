#include <iostream>
#include <math.h>
#include <vector>
#include <cassert>
#include "cities.hpp"
#include "utils.hpp"


Cities::Cities(const std::vector<Point> &cities_vector){

    cities = cities_vector;
    number_of_cities = cities.size();

    min_coordinates.x = cities.at(0).x;
    max_coordinates.x = cities.at(0).x;
    min_coordinates.y = cities.at(0).y;
    max_coordinates.y = cities.at(0).y;

    for(size_t i=1; i<number_of_cities; i++){
        if(cities.at(i).x < min_coordinates.x){min_coordinates.x = cities.at(i).x;};
        if(cities.at(i).x > max_coordinates.x){max_coordinates.x = cities.at(i).x;};
        if(cities.at(i).y < min_coordinates.y){min_coordinates.y = cities.at(i).y;};
        if(cities.at(i).y > max_coordinates.y){max_coordinates.y = cities.at(i).y;};
    }

    calculate_distance_matrix();
}

void Cities::calculate_distance_matrix(void){
    std::vector<std::vector<float>> matrix(number_of_cities, std::vector<float>(number_of_cities, 0));
    for(size_t c_1 = 0; c_1 < number_of_cities; c_1++) {
        for(size_t c_2 = c_1; c_2 < number_of_cities; c_2++) {
            if(c_1 == c_2){
                continue;
            }
            float x = cities.at(c_1).x - cities.at(c_2).x; //calculating number to square in next step
            float y = cities.at(c_1).y - cities.at(c_2).y;
            float dist;
            dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	        dist = sqrt(dist);
            matrix.at(c_1).at(c_2) = dist;
            matrix.at(c_2).at(c_1) = dist; //Symmetric matrix
        }
    }
    distance_matrix = matrix;
}

std::vector<Point> Cities::get_cities(void){
    return cities;
}

std::vector<std::vector<float>> Cities::get_distance_matrix(void){
    return distance_matrix;
}

float Cities::total_distance(const std::vector<int> &path){
    float distance = 0;
    assert(number_of_cities == path.size() && "Path size and number of cities do not match!");
    for(size_t i=0; i<(number_of_cities-1); i++){
        distance += distance_matrix.at(path.at(i)).at(path.at(i+1));
    }
    distance += distance_matrix.at(path.at(number_of_cities-1)).at(path.at(0));
    return distance;
}

uint Cities::get_number_of_cities(void){
    return number_of_cities;
}

Point Cities::get_min_coordinates(void){
    return min_coordinates;
}

Point Cities::get_max_coordinates(void){
    return max_coordinates;
}

// void Cities::set_cities_from_vector(std::vector<Point> cities_vector){
//     number_of_cities = cities_vector.size();
//     cities = cities_vector;
//     calculate_distance_matrix();
// }

