#ifndef SOLVERS_HPP
#define SOLVERS_HPP

#include "cities.hpp"
#include "utils.hpp"

//Solvers

// Parent
class Solver{
    public:
        Cities cities;
        uint number_of_cities;
        std::vector<int> best_path;
        float best_distance;
        long counter;
        bool solved;

        std::vector<int> path;
        uint number_of_points;
        std::vector<Point> points;
    
        Solver(Cities &cities);
        void solve(void);
        std::vector<int> get_best_path(void);
        float get_best_distance(void);
        bool is_solved(void);
        long get_counter(void);

        virtual void step(void){};
        virtual std::vector<int> get_path(void){return path;};
        virtual std::vector<Point> get_points(void){return points;};
        virtual uint get_number_of_points(void){return number_of_points;};    
};


class BruteForce: public Solver{
    private:
        //This solver
        std::vector<int> short_path;
    public:
        BruteForce(Cities &cities);
        void step(void) override;
        std::vector<int> get_path(void) override;
        std::vector<Point> get_points(void) override;
        uint get_number_of_points(void) override; 
};

class SOM: public Solver{
    private:
        //This solver
        std::vector<Point> cities_location;
        std::vector<std::vector<float>> neighboring;
        void update_neighboring(void);
        uint closest_point(uint city);
        float distance_city_point(uint point, uint city);
        void update_best_path(void);
        //Hyper params
        float nabla;
        float nabla_decay;
        float alpha;
        float alpha_decay;
        uint number_of_iterations;
        uint points_multiplier;
    public:
        SOM(Cities &cities, float nabla = 1.0, float nabla_decay = 0.0, float alpha = 500,
         float alpha_decay = 0.001, uint number_of_iterations = 10000, uint points_multiplier = 3);
        void step(void) override;
        std::vector<int> get_path(void) override;
        std::vector<Point> get_points(void) override;
        uint get_number_of_points(void) override;   
};

// class Genetic: public Solver{

//     private:

//         // Cities cities;

//     public:

//         Genetic(Cities &cities, uint individuals);

//         void step(void) override;

// };

#endif