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

// sf::Vertex line[] =
// {
// sf::Vertex(sf::Vector2f(10, 10)),
// sf::Vertex(sf::Vector2f(150, 150))
// };
// ​
// window. draw(line, 2, sf::Lines);

void draw_lines(sf::RenderWindow &window, const std::vector<int> path, const std::vector<sf::Vector2f> &cities){
    size_t number_of_cities = cities.size();
    for(size_t i=0; i<(number_of_cities-1); i++){
        sf::Vertex line[] =
        {
        sf::Vertex(cities.at(path.at(i))),
        sf::Vertex(cities.at(path.at(i+1)))
        };
        window.draw(line, 2, sf::Lines);
    }
    sf::Vertex line[] =
    {
    sf::Vertex(cities.at(path.at(number_of_cities-1))),
    sf::Vertex(cities.at(path.at(0)))
    };
    window.draw(line, 2, sf::Lines);
}

int main(void) {

    constexpr int num_cities = 10;
    sf::Vector2i map_size(400, 400);
    std::vector<sf::Vector2f> cities = generate_cities(num_cities, map_size);
    std::vector<std::vector<float>> distances = distance_matrix(cities);

    float radius = 5.0;
    std::vector<sf::CircleShape> circles(num_cities, sf::CircleShape(radius));
    for(size_t i=0; i<num_cities; i++){
        circles.at(i).setFillColor(sf::Color::Green);
        circles.at(i).setPosition(cities.at(i).x-radius, cities.at(i).y-radius);
    }

    // Define running period
    // constexpr std::chrono::milliseconds period = std::chrono::milliseconds(20); //ms
    std::vector<int> solution = brute_force(num_cities, distances);
    for(int x=0; x<num_cities; x++){
        std::cout << solution.at(x) << " ";
    }
    std::cout << "\n";

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(map_size.x, map_size.y), "SFML window");
    // sf::CircleShape shape(10.f);
    // shape.setFillColor(sf::Color::Green);

    // sf::CircleShape shape2(200.f);
    // shape.setFillColor(sf::Color::Blue);
    // shape.setPosition(200, 200);
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


        // Clear screen
        window.clear();

        // Draw stuff in the screen
        for(size_t i=0; i<num_cities; i++){
            window.draw(circles.at(i));
        }
        draw_lines(window, solution, cities);

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
