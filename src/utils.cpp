#include <random>
#include <vector>
#include "utils.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

int random_number(int max){
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distribution(0, max);
    return distribution(generator);
}

long factorial(const int n)
{
    long f = 1;
    for (int i=1; i<=n; ++i)
        f *= i;
    return f;
}

sf::Vector2f point_to_vector2f(const Point &point){
    return sf::Vector2f(point.x, point.y);
}

Point vector2f_to_point(const sf::Vector2f &vector2f){
    Point p;
    p.x = vector2f.x;
    p.y = vector2f.y;
    return p;
}

void print_vector(const std::vector<int> &vector){
    size_t size = vector.size();
    for(size_t x=0; x<size; x++){
        std::cout << vector.at(x) << " ";
    }
    std::cout << "\n";
}

std::string vector_to_string(const std::vector<int> &vector){
    size_t size = vector.size();
    std::string str;
    for(size_t x=0; x<size; x++){
        str += (std::to_string(vector.at(x)) + " ");
    }
    return str;
}