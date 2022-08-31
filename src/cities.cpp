#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include "SFML/Graphics.hpp"
#include <cassert>
#include "cities.hpp"

int random_number(int max){
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distribution(0, max);
    return distribution(generator);
}

std::vector<sf::Vector2f> generate_cities(const size_t number_of_cities, const sf::Vector2i &map_size){
    std::vector<sf::Vector2f> cities(number_of_cities, sf::Vector2f(0, 0));
    for(size_t i=0; i<number_of_cities; i++){
        sf::Vector2f city(random_number(map_size.x), random_number(map_size.y));
        cities[i] = city;
    }
    return cities;
}

std::vector<std::vector<float>> distance_matrix(const std::vector<sf::Vector2f> &cities){
    size_t number_of_cities = cities.size();
    std::vector<std::vector<float>> dist_matrix(number_of_cities, std::vector<float>(number_of_cities, 0));
    for(size_t c_1 = 0; c_1 < number_of_cities; c_1++) {
        for(size_t c_2 = c_1; c_2 < number_of_cities; c_2++) {
            if(c_1 == c_2){
                continue;
            }
            float x = cities[c_1].x - cities[c_2].x; //calculating number to square in next step
            float y = cities[c_1].y - cities[c_2].y;
            float dist;
            dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	        dist = sqrt(dist);
            dist_matrix[c_1][c_2] = dist;
            dist_matrix[c_2][c_1] = dist; //Symmetric matrix
        }
    }
    return dist_matrix;
}

float total_distance(const std::vector<int> &order, const std::vector<std::vector<float>> &distances){
    float distance = 0;
    size_t number_of_cities = order.size();
    assert(number_of_cities == distances.at(0).size());
    for(size_t i=0; i<(number_of_cities-1); i++){
        distance += distances[order[i]][order[i+1]];
    }
    distance += distances[order[number_of_cities-1]][order[0]];
    return distance;
}