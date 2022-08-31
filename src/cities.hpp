#ifndef CITIES_HPP
#define CITIES_HPP

#include "SFML/Graphics.hpp"
#include <vector>

int random_number(int max);
std::vector<sf::Vector2f> generate_cities(const size_t number_of_cities, const sf::Vector2i &map_size);
std::vector<std::vector<float>> distance_matrix(const std::vector<sf::Vector2f> &cities);
float total_distance(const std::vector<int> &order, const std::vector<std::vector<float>> &distances);

#endif
