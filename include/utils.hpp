#ifndef UTILS_HPP
#define UTILS_HPP

#include "SFML/Graphics.hpp"

struct Point{
    float x;
    float y;
};

int random_number(int max);
long factorial(const int n);
void print_vector(const std::vector<int> &vector);
void print_vector(const std::vector<float> &vector);
std::string vector_to_string(const std::vector<int> &vector);
sf::Vector2f point_to_vector2f(const Point &point);
void draw_lines_point(sf::RenderWindow &window, const std::vector<int> path, const std::vector<Point> &cities, sf::Color color);

#endif
