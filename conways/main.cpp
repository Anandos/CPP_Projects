//'conways-upgrade' created on 29/05/2025 by Anand Damodaran
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <thread>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;

bool getRandBool() { //Generate bool based on ratio
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <int> dist(0, 3);

    int result = dist(gen);
    return (result < 1) ? true : false;
}

int main() {
    cout << "SFML version: " << SFML_VERSION_MAJOR << ".";
    cout << SFML_VERSION_MINOR << std::endl;
    const int win_width = 1700;
    const int win_height = 850;
    sf::RenderWindow window(sf::VideoMode({1700, 850}), "SFML Application");

    // 2D grids for boxes and the box grid's bools
    std::vector<std::vector<sf::RectangleShape>> box_grid;
    std::vector<std::vector<bool>> bool_grid;
    std::vector<std::vector<bool>> bool_grid_next;

    int row{};
    int column{};
    int size = 2;
    for (int x = 10; x <= (win_width - 10 - size); x += size) {
        box_grid.emplace_back(); //create new vectors for the incoming column
        bool_grid.emplace_back();
        bool_grid_next.emplace_back();
        column = 0;
        for (int y = 10; y <= (win_height - 10 - size); y += size) {
            sf::RectangleShape next_box;
            next_box.setSize({static_cast<float>(size), static_cast<float>(size)});
            next_box.setPosition({static_cast<float>(x), static_cast<float>(y)});
            bool next_bool = getRandBool();
            bool_grid[row].push_back(next_bool); //add bool to 2d vector
            bool_grid_next[row].push_back(next_bool); //add same bool to copy grid

            if (bool_grid[row].back()) next_box.setFillColor(sf::Color::White); //colour for alive or dead
            else next_box.setFillColor(sf::Color::Black);

            box_grid[row].push_back(next_box); //add finished block to 2d vector

            column ++;
        }
        row ++;
    }

    bool life = true;
    bool step = false;
    cout << "Opening window" << endl;
    while (window.isOpen())
    {
        if (life) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause

            for (int i = 0; i < box_grid.size(); i++) { //rows
                for (int j = 0; j < box_grid[i].size(); j++) { //columns
                    // Conway's Life of Game algorithm
                    //Survive with 2 or 3 neighbours
                    //Die with 0 or 1 neighbours
                    //Birth with exactly 3 neighbours when dead
                    int living{};
                    // Scan neighbours for living
                    for (int x = i - 1; x <= (i + 1); x++) { //rows
                        for (int y = j - 1; y <= (j + 1); y++) { //columns
                            if (x >= 0 && y >= 0) {
                                if (x < box_grid.size() && y < box_grid[0].size()) {
                                    if (bool_grid[x][y] == true) living++; //Count neighbours
                                }
                            }
                        }
                    }

                    if (bool_grid[i][j] == true) { //Survive with 2 or 3 neighbours
                        living -= 1; //don't count self
                        if (living < 2 || living > 3) { //Die unless 2 or 3 neighbours
                            bool_grid_next[i][j] = false;
                            box_grid[i][j].setFillColor(sf::Color::Black);
                        }
                    }
                    else {
                        if (living == 3) {
                            bool_grid_next[i][j] = true; //Birth from dead when exactly 3 neighbours
                            box_grid[i][j].setFillColor(sf::Color::White);
                        }
                    }
                }
            }
        }
        bool_grid = bool_grid_next; //Copy incoming grid over old grid for next life cycle


        if (step) { //Pause until next step or unpaused
            life = false;
        }

        while (const std::optional event = window.pollEvent()) //User input Events
        {
            if (event->is<sf::Event::Closed>()) {
                window.close(); //Close window to exit
            }
            else if (const auto *key_pressed = event->getIf<sf::Event::KeyPressed>()) {
                if(key_pressed->scancode == sf::Keyboard::Scancode::Escape){ // Escape to Close
                    cout << "Window closed" << endl;
                    window.close();
                }
                else if (key_pressed->scancode == sf::Keyboard::Scancode::P) { // Pause
                    cout << "Paused" << endl;
                    if (life) life = false;
                    else life = true;
                    step = false;
                }
                else if (key_pressed->scancode == sf::Keyboard::Scancode::Space) { // Pause and stepped
                    cout << "Stepping" << endl;
                    step = true;
                    life = true;
                }
                else if (key_pressed->scancode == sf::Keyboard::Scancode::R) { // Pause and stepped
                    // Reboot entire grid system, populate with random
                    cout << "Rebooting grid" << endl;
                    for (int i = 0; i < box_grid.size(); i++) {
                        for (int j = 0; j < box_grid[i].size(); j++) {
                            bool next_bool = getRandBool();
                            if (next_bool) {
                                bool_grid[i][j] = true;
                                bool_grid_next[i][j] = true;
                                box_grid[i][j].setFillColor(sf::Color::White);
                            }
                            else {
                                bool_grid[i][j] = false;
                                bool_grid_next[i][j] = false;
                                box_grid[i][j].setFillColor(sf::Color::Black);
                            }
                        }
                    }
                }
            }
        }

        //Render current frame
        window.clear();
        for (int i = 0; i < box_grid.size(); i++) { //Render grid
            for (int j = 0; j < box_grid[i].size(); j++) {
                window.draw(box_grid[i][j]);
            }
        }
        window.display();
    }

    cout << "Window closed, exiting" << endl;
}
