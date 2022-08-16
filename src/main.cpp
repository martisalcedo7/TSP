#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>
#include "SFML/Graphics.hpp"

constexpr float period = 0.020;
constexpr float g = 9.81;
constexpr float mass = 1;

sf::Vector2f main_loop(void){
    static float x = 50;
    static float prev_x = 50;
    static float y = 80;
    static float prev_y = 80;

    float a_y = g;
    float a_x = 0;

    if(std::sqrt((std::pow(y-200, 2) + std::pow(x-200, 2))) >= 200.0){
        x = prev_x;
        y = prev_y;
    }

    float new_x = 2.0 * x - prev_x + a_x * period * period;
    float new_y = 2.0 * y - prev_y + a_y * period * period;

    prev_x = x;
    x = new_x;

    prev_y = y;
    y = new_y;

    sf::Vector2f position(x, y);

    return position;
}

int main(void) {

    constexpr std::chrono::milliseconds period = std::chrono::milliseconds(20); //ms

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);

    sf::CircleShape shape2(200.f);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(200, 200);

    while (window.isOpen())
    {   
        auto start = std::chrono::system_clock::now();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f const position = main_loop();

        std::cout << position.x << ", " << position.y << "\n";

        shape.setPosition(position);

        window.clear();
        window.draw(shape2);
        window.draw(shape);
        window.display();

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end-start;
        if(elapsed < std::chrono::milliseconds(period)){
            std::this_thread::sleep_for(std::chrono::milliseconds(period) - elapsed);
        }
        // auto end2 = std::chrono::high_resolution_clock::now();
        // std::chrono::duration<double, std::milli> elapsed2 = end2-start;
        // std::cout << (1000.0/elapsed2.count()) << " FPS\n";
    }

    return 0;
//   // create an object of `steady_clock` class
//     constexpr std::chrono::milliseconds period = std::chrono::milliseconds(20); //ms
//     while(true){
//         auto start = std::chrono::high_resolution_clock::now();
//         main_loop();
//         auto end = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<double, std::milli> elapsed = end-start;
//         // std::cout << (elapsed.count()) << "\n";
//         if(elapsed < std::chrono::milliseconds(period)){
//             std::this_thread::sleep_for(std::chrono::milliseconds(period) - elapsed);
//         }
//         // auto end2 = std::chrono::high_resolution_clock::now();
//         // std::chrono::duration<double, std::milli> elapsed2 = end2-start;
//         // std::cout << (1000.0/elapsed2.count()) << "\n";
//     }

//     return 0; 
}
