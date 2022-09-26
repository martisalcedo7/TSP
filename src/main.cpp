#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>
#include <random>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

// External libs
#include "SFML/Graphics.hpp"

// Local libs
#include "cities.hpp"
#include "solvers.hpp"
#include "utils.hpp"
#include "font_data.hpp"


int main(int argc, char** argv) {

    std::string help_message = "Usage: TSP [-m solving method] [-r number_of_cities"
    " || -f csv_path]\n -m : Method to solve the problem.\n      bf -> brute force\n     "
    " som -> Self Organizing maps\n -r : Random generated cities. Number of cities to generate.\n"
    " -f : Load cities from file. Path to the csv file.\n";

    // Check that the number of given args is correct
    if(argc < 4){
        std::cout << "Too few arguments.\n";
        std::cout << help_message;
        return 0;
    }

    // Parse given args
    std::string method_flag = argv[1];
    std::string method = argv[2];
    std::string cities_flag = argv[3];
    std::string cities = argv[4];

    // Select solving method based on args
    if(method_flag != "-m" || (method != "bf" && method != "som")){
        std::cout << "Incorrect method.\n";
        std::cout << help_message;
        return 0;
    }
    uint solving_method = 0;
    if(method == "bf"){
        solving_method = 0;
    }else if(method == "som"){
        solving_method = 1;
    }

    //Empty vector of cities coordinates
    std::vector<Point> cities_coordinates;

    // Define map size
    Point map_size;
    map_size.x = 1366;
    map_size.y = 708;

    // Create cities vector based on args
    if(cities_flag == "-r"){
        uint num_cities = std::stoi(argv[4]);
        cities_coordinates = generate_random_cities(num_cities, map_size);
    }else if(cities_flag == "-f"){
        std::string file_path = argv[4];
        cities_coordinates = cities_from_file(file_path);
    }else{
        std::cout << "Incorrect cities definition.\n";
        std::cout << help_message;
        return 0;
    }

    
    // Instantiate cities class
    Cities cities_map(cities_coordinates);

    // Initialise solvers depending on the selected method
    std::unique_ptr<Solver> solver; 
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
    // font.loadFromFile("arial.ttf");
    // sf::Font font;
    font.loadFromMemory(&arial_ttf, arial_ttf_len);

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
    std::cout << "Cities(" << cities_map.get_number_of_cities() <<"):\n";
    for(size_t i=0; i<cities_map.get_number_of_cities(); i++){
        std::cout << cities_map.get_cities().at(i).x << "," << cities_map.get_cities().at(i).y << "\n";
    }
    // Print the solution
    std::cout << "Best path: [" << vector_to_string(solver->get_best_path()) << "]\n";
    std::cout << "Best distance: " << solver->get_best_distance() << "\n";


    return 0;
}
