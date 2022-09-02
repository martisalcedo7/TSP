#include <iostream>
#include <math.h>
#include <vector>
#include "SFML/Graphics.hpp"
#include <cassert>
#include "cities.hpp"
#include "utils.hpp"


Cities::Cities(const uint number_of_cities, const sf::Vector2i &map_size): number_of_cities{number_of_cities}{

    std::vector<sf::Vector2f> cities_vector(number_of_cities, sf::Vector2f(0, 0));
    for(size_t i=0; i<number_of_cities; i++){
        sf::Vector2f city(random_number(map_size.x), random_number(map_size.y));
        cities_vector.at(i) = city;
    }
    cities = cities_vector;

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

std::vector<sf::Vector2f> Cities::get_cities(void){
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

