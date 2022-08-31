#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include "SFML/Graphics.hpp"
#include <cassert>
#include "cities.hpp"

int main(void) {

    sf::Vector2i map_size(100, 100);
    std::vector<sf::Vector2f> cities = generate_cities(4, map_size);
    std::vector<std::vector<float>> distances = distance_matrix(cities);
    
    std::vector<int> order {0,1,2,3};

    float total_dist = total_distance(order, distances);

    // for(const auto& city: cities){
    //     std::cout << city.x << ", " << city.y << "\n";
    // }

    // for(const auto& dist: distances) {
    //     for(const auto& d: dist){
    //         std::cout << d << " ";
    //     }
    //     std::cout << "\n";
    // }

    // std::cout << total_dist << "\n";

    return 0;
}
