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
        // Point map_size;
        Point min_coordinates;
        Point max_coordinates;
        // float min_x_coordinate;
        // float max_x_coordinate;
        // float min_y_coordinate;
        // float max_y_coordinate;

    public:
        //Constructor
        Cities(const std::vector<Point> &cities_vector);
        //Getters
        std::vector<Point> get_cities(void);
        std::vector<std::vector<float>> get_distance_matrix(void);
        uint get_number_of_cities(void);
        //Functions
        float total_distance(const std::vector<int> &order);
        Point get_min_coordinates(void);
        Point get_max_coordinates(void);
        // void set_cities_from_vector(std::vector<Point> cities_vector);
};

#endif
