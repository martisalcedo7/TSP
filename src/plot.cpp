#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>
#include <random>
#include "SFML/Graphics.hpp"
#include <vector>
#include <algorithm>

// Local libs
#include "cities.hpp"
#include "solvers.hpp"
#include "utils.hpp"

// sf::Vertex line[] =
// {
// sf::Vertex(sf::Vector2f(10, 10)),
// sf::Vertex(sf::Vector2f(150, 150))
// };
// ​
// window. draw(line, 2, sf::Lines);


void draw_lines(sf::RenderWindow &window, const std::vector<int> path, const std::vector<sf::Vector2f> &cities, sf::Color color){
    size_t number_of_cities = cities.size();
    for(size_t i=0; i<(number_of_cities-1); i++){
        sf::Vertex line[] =
        {
        sf::Vertex(cities.at(path.at(i)), color),
        sf::Vertex(cities.at(path.at(i+1)), color)
        };
        window.draw(line, 2, sf::Lines);
    }
    sf::Vertex line[] =
    {
    sf::Vertex(cities.at(path.at(number_of_cities-1)), color),
    sf::Vertex(cities.at(path.at(0)), color)
    };
    window.draw(line, 2, sf::Lines);
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

int main(int argc, char** argv) {

    if(argc < 2){
        std::cout << "Number of cities not given\n";
        return 0;
    }

    uint num_cities = std::stoi(argv[1]);
    sf::Vector2i map_size(780, 550);

    Cities cities_map(num_cities, map_size);
    // BruteForce solver(cities_map);

    SOM som(cities_map);

    std::vector<Point> points = som.get_points();
    uint number_of_points = som.get_number_of_points();


    std::vector<sf::Vector2f> cities = cities_map.get_cities();

    std::vector<int> som_solution(number_of_points, 0);
    for(size_t x=1; x<number_of_points; x++){
        som_solution.at(x)=x;
    }


    // Create circles for cities
    float radius = 4.0;
    std::vector<sf::CircleShape> circles(num_cities, sf::CircleShape(radius));
    for(size_t i=0; i<num_cities; i++){
        circles.at(i).setFillColor(sf::Color::Green);
        circles.at(i).setPosition(cities.at(i).x-radius, cities.at(i).y-radius);
    }

    //Create circles for points
    float radius_points = 4.0;
    std::vector<sf::CircleShape> circles_points(number_of_points, sf::CircleShape(radius_points));
    for(size_t i=0; i<number_of_points; i++){
        circles_points.at(i).setFillColor(sf::Color::Blue);
        circles_points.at(i).setPosition(points.at(i).x-radius_points, points.at(i).y-radius_points);
    }

    //Create Texts

    // Select the font
    sf::Font font;
    font.loadFromFile("arial.ttf");

    // Create text for cities
    std::vector<sf::Text> labels(num_cities, sf::Text());
    for(size_t i=0; i<num_cities; i++){
        labels.at(i).setFillColor(sf::Color::White);
        labels.at(i).setPosition(cities.at(i).x, cities.at(i).y);
        labels.at(i).setFont(font);
        labels.at(i).setCharacterSize(16);
        labels.at(i).setString(std::to_string(i));
    }

    // Create text for points
    // std::vector<sf::Text> labels_points(number_of_points, sf::Text());
    // for(size_t i=0; i<number_of_points; i++){
    //     labels_points.at(i).setFillColor(sf::Color::White);
    //     labels_points.at(i).setPosition(points.at(i).x, points.at(i).y);
    //     labels_points.at(i).setFont(font);
    //     labels_points.at(i).setCharacterSize(18);
    //     labels_points.at(i).setString(std::to_string(i));
    // }

    //Create other texts
    sf::Text text_info;
    text_info.setFillColor(sf::Color::Blue);
    text_info.setFont(font); // font is a sf::Font
    text_info.setCharacterSize(18);
    text_info.setPosition(0, map_size.y+20);

    // Define running period
    // constexpr std::chrono::milliseconds period = std::chrono::milliseconds(20); //ms

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(map_size.x+20, map_size.y+50), "SFML window");

    //Start main loop
    while (window.isOpen())
    {   
        //Capture time
        // auto start = std::chrono::system_clock::now();

        //Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ///// MAIN LOOP
        // break;
        // solver.step();
        // std::vector<int> solution = solver.get_best_path();
        // std::vector<int> path = solver.get_path();
        // float best_distance = solver.get_best_distance();

        // text_info.setString("Steps: " + std::to_string(solver.get_counter()) + "  Best path: " + vector_to_string(solution) + " Best distance: " + std::to_string(best_distance));

        text_info.setString("Steps: " + std::to_string(som.get_counter()) + "  Best path: " + vector_to_string(som.get_best_path()));

        som.step();
        points = som.get_points();
        for(size_t i=0; i<number_of_points; i++){
            circles_points.at(i).setPosition(points.at(i).x-radius_points, points.at(i).y-radius_points);
            // labels_points.at(i).setPosition(points.at(i).x, points.at(i).y);
        }


        //Clear screen
        window.clear();

        // Draw stuff in the screen
        // if(!solver.is_solved()){
        //     draw_lines(window, path, cities, sf::Color::White);
        // }
        draw_lines_point(window, som_solution, points, sf::Color::Blue);
        // draw_lines(window, solution, cities, sf::Color::Red);
        for(size_t i=0; i<number_of_points; i++){

            // window.draw(circles_points.at(i));
            // window.draw(labels_points.at(i));
        }
        for(size_t i=0; i<num_cities; i++){
            window.draw(circles.at(i));
            // window.draw(labels.at(i));
        }

        window.draw(text_info);

        // Update the window
        window.display();

        ///// END OF MAIN LOOP

        // //Adjust time
        // auto end = std::chrono::system_clock::now();
        // std::chrono::duration<double, std::milli> elapsed = end-start;
        // if(elapsed < std::chrono::milliseconds(period)){
        //     std::this_thread::sleep_for(std::chrono::milliseconds(period) - elapsed);
        // }

    //     // auto end2 = std::chrono::high_resolution_clock::now();
    //     // std::chrono::duration<double, std::milli> elapsed2 = end2-start;
    //     // std::cout << (1000.0/elapsed2.count()) << " FPS\n";
    }

    return 0;
}
