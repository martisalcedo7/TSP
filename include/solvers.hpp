#ifndef SOLVERS_HPP
#define SOLVERS_HPP

#include "cities.hpp"
#include "SFML/Graphics.hpp"
#include "utils.hpp"

//Solvers

class BruteForce{

    private:
        Cities cities;
        uint number_of_cities;
        std::vector<int> best_path;
        float best_distance;
        long counter;
        bool solved;

        //This solver
        std::vector<int> path;
        std::vector<int> short_path;

    public:

        BruteForce(Cities &cities);

        void step(void);
        void solve(void);

        std::vector<int> get_best_path(void);
        std::vector<int> get_path(void);
        float get_best_distance(void);
        bool is_solved(void);
        long get_counter(void);
    
};

class SOM{

    private:
        Cities cities;
        uint number_of_cities;
        uint number_of_points;
        std::vector<int> best_path;
        float best_distance;
        long counter;
        bool solved;
        std::vector<sf::Vector2f> cities_location;

        //This solver
        std::vector<Point> points;
        std::vector<std::vector<float>> neighboring;
        void update_neighboring(void);
        uint closest_point(uint city);
        float distance_city_point(uint point, uint city);

        //Hyper params
        float nabla;
        float nabla_decay;
        float alpha;
        float alpha_decay;
        uint number_of_iterations;
        uint points_multiplier;

    public:

        SOM(Cities &cities, float nabla = 1.0, float nabla_decay = 0.0, float alpha = 500,
         float alpha_decay = 0.001, uint number_of_iterations = 20000, uint points_multiplier = 3);

        void step(void);
        void solve(void);

        std::vector<int> get_best_path(void);
        float get_best_distance(void);
        bool is_solved(void);
        long get_counter(void);
        std::vector<Point> get_points(void);
        uint get_number_of_points(void);
    
};

#endif