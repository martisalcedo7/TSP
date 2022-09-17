#include <random>
#include <vector>
#include "utils.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>

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

std::vector<Point> cities_from_file(const std::string &path){
    std::vector<Point> cities_vector;
    std::string line;
    std::ifstream my_file(path);
    if (my_file.is_open()){
        while(getline(my_file, line)){
            // std::cout << line << '\n';
            uint coma_location = line.find(",");
            std::string x_str = line.substr(0, coma_location);
            std::string y_str = line.substr(coma_location+1, line.length());
            float x = std::stof(x_str);
            float y = std::stof(y_str);
            Point p;
            p.x = x;
            p.y = y;
            cities_vector.push_back(p);
            // std::cout << p.x << ": " << p.y << '\n';
        }
        my_file.close();
    }else{
        std::cout << "Error: Unable to open file\n";
        exit(EXIT_FAILURE);
    }
    if(cities_vector.size() < 3){
        std::cout << "Error: The file must contain at least 3 cities\n";
        exit(EXIT_FAILURE);
    }
    return cities_vector;
}

std::vector<Point> generate_random_cities(const uint number_of_cities, const Point &map_size){
    std::vector<Point> cities_vector(number_of_cities);
    for(size_t i=0; i<number_of_cities; i++){
        Point city;
        city.x = random_number(map_size.x);
        city.y = random_number(map_size.y);
        cities_vector.at(i) = city;
    }
    return cities_vector;
}

std::vector<Point> transform_points_to_map_coordinates(const std::vector<Point> &points, const Point &map_size, const Point min_coord, const Point max_coord){
    float x_margin = map_size.x * 0.05;
    float y_margin = map_size.y * 0.05;
    float map_width = map_size.x - 2.0 * x_margin;
    float map_heigh = map_size.y - 2.0 * y_margin;
    float width = max_coord.x-min_coord.x;
    float heigh = max_coord.y-min_coord.y;
    uint number_of_points = points.size();
    std::vector<Point> new_points(number_of_points);
    for(size_t i=0; i<number_of_points; i++){
        Point point;
        point.x = map_width*(points.at(i).x-min_coord.x)/width + x_margin;
        point.y = map_heigh*(points.at(i).y-min_coord.y)/heigh + y_margin;
        new_points.at(i) = point;
    }
    return new_points;
}
