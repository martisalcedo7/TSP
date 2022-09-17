#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>
#include <random>
#include "SFML/Graphics.hpp"
#include <vector>
#include <algorithm>
#include <memory>

// Local libs
#include "cities.hpp"
#include "solvers.hpp"
#include "utils.hpp"


int main(int argc, char** argv) {

    if(argc < 2){
        std::cout << "Number of cities not given.\n";
        return 0;
    }
    // Get number of cities from the args
    uint num_cities = std::stoi(argv[1]);
    // Define map size
    Point map_size;
    map_size.x = 1366;
    map_size.y = 708;
    // Instantiate cities class
    // std::vector<Point> cities_coordinates = generate_random_cities(num_cities, map_size);
    std::vector<Point> cities_coordinates = cities_from_file("/home/ms/repositories/simulation/data/cities_copy.csv");

    Cities cities_map(cities_coordinates);

    // Initialise solvers
    std::unique_ptr<Solver> solver; 
    int solving_method = 0;
    switch(solving_method){
        case 0:
            solver = std::make_unique<BruteForce>(cities_map);
            break;
        case 1:
            solver = std::make_unique<SOM>(cities_map);
            break;
        default:
            return 0;
    }

    // Convert points coordinates into map coordinates
    std::vector<Point> map_coord_points =  transform_points_to_map_coordinates(solver->get_points(), map_size, cities_map.get_min_coordinates(), cities_map.get_max_coordinates());
    //Create circles for points
    float radius_points = 4.0;
    std::vector<sf::CircleShape> circles_points(solver->get_number_of_points(), sf::CircleShape(radius_points));
    for(size_t i=0; i<solver->get_number_of_points(); i++){
        circles_points.at(i).setFillColor(sf::Color::White);
        circles_points.at(i).setPosition(map_coord_points.at(i).x-radius_points, map_coord_points.at(i).y-radius_points);
    }

    // Convert cities coordinates into map coordinates
    std::vector<Point> map_coord_cities =  transform_points_to_map_coordinates(cities_map.get_cities(), map_size, cities_map.get_min_coordinates(), cities_map.get_max_coordinates());
    // Create circles for cities
    float radius = 4.0;
    std::vector<sf::CircleShape> circles(cities_map.get_number_of_cities(), sf::CircleShape(radius));
    for(size_t i=0; i<cities_map.get_number_of_cities(); i++){
        circles.at(i).setFillColor(sf::Color::Green);
        circles.at(i).setPosition(map_coord_cities.at(i).x-radius, map_coord_cities.at(i).y-radius);
    }

    //Create Texts

    // Select the font
    sf::Font font;
    font.loadFromFile("arial.ttf");

    // Create text for cities
    std::vector<sf::Text> labels(cities_map.get_number_of_cities(), sf::Text());
    for(size_t i=0; i<cities_map.get_number_of_cities(); i++){
        labels.at(i).setFillColor(sf::Color::White);
        labels.at(i).setPosition(map_coord_cities.at(i).x, map_coord_cities.at(i).y);
        labels.at(i).setFont(font);
        labels.at(i).setCharacterSize(16);
        labels.at(i).setString(std::to_string(i));
    }

    //Create info text
    sf::Text text_info;
    text_info.setFillColor(sf::Color::Red);
    text_info.setFont(font); // font is a sf::Font
    text_info.setCharacterSize(18);
    text_info.setPosition(0, map_size.y+15);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(map_size.x, map_size.y+60), "SFML window");

    //Start main loop
    while (window.isOpen())
    {   

        //Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Run a solver step
        solver->step();

        // Convert new points coordinates into map coordinates
        map_coord_points =  transform_points_to_map_coordinates(solver->get_points(), map_size, cities_map.get_min_coordinates(), cities_map.get_max_coordinates());

        // Update text with info
        text_info.setString("Cities: " + std::to_string(cities_map.get_number_of_cities()) + " Steps: " + std::to_string(solver->get_counter())
        + " Best distance: " + std::to_string(solver->get_best_distance()) + "\nBest path: " + vector_to_string(solver->get_best_path()));

        //Clear screen
        window.clear();

        // Draw solving procedure lines and points
        if(!solver->is_solved()){
            draw_lines_point(window, solver->get_path(), map_coord_points, sf::Color::White);
            for(size_t i=0; i<solver->get_number_of_points(); i++){
                circles_points.at(i).setPosition(map_coord_points.at(i).x-radius_points, map_coord_points.at(i).y-radius_points);
                window.draw(circles_points.at(i));
            }
        }
        // Draw solution lines
        draw_lines_point(window, solver->get_best_path(), map_coord_cities, sf::Color::Red);
        // Draw cities labels and circles
        for(size_t i=0; i<cities_map.get_number_of_cities(); i++){
            window.draw(circles.at(i));
            window.draw(labels.at(i));
        }
        // Draw text with info
        window.draw(text_info);

        // Update the window
        window.display();
    }

    // Print the cities
    std::cout << "Cities:\n";
    for(size_t i=0; i<cities_map.get_number_of_cities(); i++){
        std::cout << cities_map.get_cities().at(i).x << "," << cities_map.get_cities().at(i).y << "\n";
    }
    // Print the solution
    std::cout << "Best path: [" << vector_to_string(solver->get_best_path()) << "]\n";
    std::cout << "Best distance: " << solver->get_best_distance() << "\n";


    return 0;
}
