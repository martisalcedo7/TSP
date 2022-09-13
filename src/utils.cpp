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

void print_vector(const std::vector<int> &vector){
    size_t size = vector.size();
    for(size_t x=0; x<size; x++){
        std::cout << vector.at(x) << " ";
    }
    std::cout << "\n";
}

void print_vector(const std::vector<float> &vector){
    size_t size = vector.size();
    for(size_t x=0; x<size; x++){
        std::cout << vector.at(x) << " ";
    }
    std::cout << "\n";
}

std::string vector_to_string(const std::vector<int> &vector){
    size_t size = vector.size() - 1;
    std::string str;
    for(size_t x=0; x<size; x++){
        str += (std::to_string(vector.at(x)) + ",");
    }
    str += std::to_string(vector.back());
    return str;
}

sf::Vector2f point_to_vector2f(const Point &point){
    return sf::Vector2f(point.x, point.y);
}

void draw_lines_point(sf::RenderWindow &window, const std::vector<int> path, const std::vector<Point> &cities, sf::Color color){
    size_t number_of_cities = cities.size();
    for(size_t i=0; i<(number_of_cities-1); i++){
        sf::Vertex line[] =
        {
        sf::Vertex(point_to_vector2f(cities.at(path.at(i))), color),
        sf::Vertex(point_to_vector2f(cities.at(path.at(i+1))), color)
        };
        window.draw(line, 2, sf::Lines);
    }
    sf::Vertex line[] =
    {
    sf::Vertex(point_to_vector2f(cities.at(path.at(number_of_cities-1))), color),
    sf::Vertex(point_to_vector2f(cities.at(path.at(0))), color)
    };
    window.draw(line, 2, sf::Lines);
}