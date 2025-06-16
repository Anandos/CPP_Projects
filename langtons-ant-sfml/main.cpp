//'langtons-ant-hex' created on 01/06/2025 by Anand Damodaran
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "class.h"

using std::cout;using std::cin;using std::endl;

int main() {
    int win_width = 1600;
    int win_height = 800;

    // Render Window definition
    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned int>(win_width), static_cast<unsigned int>(win_height)}),
        "Langton's Ant");

    // Texture to capture ant
    sf::RenderTexture texture({static_cast<unsigned int>(win_width), static_cast<unsigned int>(win_height)});

    bool running = true;
    bool paused = true;
    int speed = 0; //fastest
    int cycles = 1'000'000;

    // Initialise 2D grids and Ant
    GameOfLife lifeObj(win_width, win_height);

    // Build 2D box grid and bool grid
    int size = 3;
    lifeObj.createGrids(size);

    std::string read_out; //string to print during while loop

    // Current time
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Time elapsed from here
    auto start = std::chrono::high_resolution_clock::now();
    auto interval = std::chrono::high_resolution_clock::now();

    // window.clear(sf::Color::White);
    texture.clear(sf::Color::Black);
    sf::Sprite sprite(texture.getTexture());

    // Main loop ----------
    while (window.isOpen() && running) {
        cycles--;
        if (cycles <= 0) paused = true;

        if (!paused) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(speed));

            // Rule set
            // lifeObj.antLogicHex(texture); // brain effect
            lifeObj.antLogic(texture); //regular effect

            // Calculate next ant position and loop across edges - LLRR, 0123
            lifeObj.antMovement(cycles);
        }

        // Print out current frame info
        if (cycles % 10'000 == 0 && !paused) {
            cout << read_out;

            // Current time
            now = std::chrono::system_clock::now();
            currentTime = std::chrono::system_clock::to_time_t(now);
            cout << std::ctime(&currentTime);

            // Time elapsed
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            auto inter_duration = std::chrono::duration_cast<std::chrono::seconds>(end - interval);
            cout << "Total Time Elapsed: " << duration.count() << " seconds ";
        }

        //User input Events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                cout << "Window closed\n";
                window.close(); //Close window to exit
            }
            else if (const auto *key_pressed = event->getIf<sf::Event::KeyPressed>()) {
                if (key_pressed->scancode == sf::Keyboard::Scancode::Escape) {
                    cout << "Exiting\n";
                    running = false; //Escape Key to exit
                }
                if (key_pressed->scancode == sf::Keyboard::Scancode::P) {
                    paused = !paused;
                    cout << ((paused) ? "Paused\n" : "Unpaused\n");
                }
                if (key_pressed->scancode == sf::Keyboard::Scancode::S) {
                    if (speed == 100) speed = 500;
                    else speed = 100;
                }
            }
        }

        // Rendering
        texture.display(); //finished rendering to texture
        window.draw(sprite); //draw texture to window frame
        window.display(); //render update to display
    }

}