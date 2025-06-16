//'conways-upgrade' created on 29/05/2025 by Anand Damodaran
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <thread>
#include <chrono>
#include "class.h"

using std::cout;using std::cin;using std::endl;

int main() {
    cout << "SFML version: " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << std::endl;
    const int win_width = 3840 / 2.25; //4k resolution on retina display with SFML rendering
    const int win_height = 2160 / 2.25;
    sf::RenderWindow window(sf::VideoMode({win_width, win_height}), "'Game of Life'");

    sf::RenderTexture texture({win_width, win_height});
    texture.clear(sf::Color::Black); // create texture background
    sf::Sprite sprite(texture.getTexture()); // connect texture to sprite
    LifeClass lifeObj(win_width, win_height);

    // Define 2D cell and bool grids
    lifeObj.createGrids(3);

    // Render all cells once at the start
    lifeObj.firstRender(texture);

    // Main game of life loop
    bool life = true;
    bool step = true;
    cout << "Opening window" << endl;
    while (window.isOpen())
    {
        if (life) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause

            // // Loop entire grid via index
            lifeObj.evolutionDayNight(texture);
        }

        // Copy next cell grid onto current cell grid for next life cycle
        lifeObj.copyGridNext();

        if (step) { //Pause until next step or unpaused
            life = false;
        }

        while (const std::optional event = window.pollEvent()) //User input Events
        {
            if (const auto *key_pressed = event->getIf<sf::Event::KeyPressed>()) {
                if(key_pressed->scancode == sf::Keyboard::Scancode::Escape ||
                    key_pressed->scancode == sf::Keyboard::Scancode::Q){ // Exit
                    cout << "Window closed" << endl;
                    window.close();
                }
                else if (key_pressed->scancode == sf::Keyboard::Scancode::P) { // Pause

                    if (life) { life = false; cout << "Paused" << endl; }
                    else { life = true; cout << "Unpaused" << endl; }
                    step = false;
                }
                else if (key_pressed->scancode == sf::Keyboard::Scancode::Space ||
                    key_pressed->scancode == sf::Keyboard::Scancode::S) { // Pause and stepped
                    cout << "Stepping" << endl;
                    step = true;
                    life = true;
                }
                else if (key_pressed->scancode == sf::Keyboard::Scancode::R) { // Restart
                    // Reboot entire grid system, populate with random
                    cout << "Rebooting grid" << endl;
                    lifeObj.rebootGrids();
                    lifeObj.firstRender(texture);
                }
            }

            if (event->is<sf::Event::Closed>()) { // Close window action
                window.close();
            }
        }

        //Render current frame
        texture.display(); //finished rendering to texture
        window.draw(sprite); //draw texture to window
        window.display(); //render window to display
    }

    cout << "Window closed, exiting" << endl;
}
