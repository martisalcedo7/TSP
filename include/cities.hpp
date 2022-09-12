#ifndef CITIES_HPP
#define CITIES_HPP

#include "SFML/Graphics.hpp"
#include <vector>

#include "utils.hpp"


class Cities{

    private:
        uint number_of_cities;
        std::vector<std::vector<float>> distance_matrix;
        std::vector<Point> cities;
        void calculate_distance_matrix(void);
        Point map_size;

    public:
        //Constructor
        Cities(const uint number_of_cities, const Point &map_size);
        //Getters
        std::vector<Point> get_cities(void);
        std::vector<std::vector<float>> get_distance_matrix(void);
        uint get_number_of_cities(void);
        //Functions
        float total_distance(const std::vector<int> &order);
        Point get_map_size(void);
};

#endif
