#ifndef CITIES_HPP
#define CITIES_HPP

#include "SFML/Graphics.hpp"
#include <vector>


class Cities{

    private:
        uint number_of_cities;
        std::vector<std::vector<float>> distance_matrix;
        std::vector<sf::Vector2f> cities;
        void calculate_distance_matrix(void);
        sf::Vector2i map_size;

    public:
        //Constructor
        Cities(const uint number_of_cities, const sf::Vector2i &map_size);
        //Getters
        std::vector<sf::Vector2f> get_cities(void);
        std::vector<std::vector<float>> get_distance_matrix(void);
        uint get_number_of_cities(void);
        //Functions
        float total_distance(const std::vector<int> &order);
        sf::Vector2i get_map_size(void);
};

#endif
