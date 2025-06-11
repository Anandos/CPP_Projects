//
// Created by Anand Damodaran on 07/06/2025.
//
#include "class.h"
#include <iostream>
#include <random>

bool getRandBool(int max) { // Generate bool based on ratio
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <int> dist(0, max);

    int result = dist(gen);
    return (result < 1) ? true : false;
}

LifeClass::LifeClass(int win_width, int win_height)
    : win_width{win_width} //iphone resolution
    , win_height{win_height}

    , living{0}
    , scan_size{1}
    , rand_max{5}

{};

void LifeClass::createGrids(int cell_size) {
    // Create entire grid for rectangles and bools and next
    int row{};
    int column{};
    // int cell_size = 1;
    for (int x = 10; x <= (win_width - 10 - cell_size); x += cell_size) {
        box_grid.emplace_back(); // create new vectors for the incoming column
        bool_grid.emplace_back();
        bool_grid_next.emplace_back();
        column = 0;
        for (int y = 10; y <= (win_height - 10 - cell_size); y += cell_size) {
            sf::RectangleShape next_box;
            next_box.setSize({static_cast<float>(cell_size), static_cast<float>(cell_size)});
            // next_box.setRadius(static_cast<float>(size) / 2);
            next_box.setPosition({static_cast<float>(x), static_cast<float>(y)});
            bool next_bool = getRandBool(rand_max);
            bool_grid[row].push_back(next_bool); // add bool to 2d vector
            bool_grid_next[row].push_back(next_bool); // add same bool to copy grid

            if (bool_grid[row].back()) next_box.setFillColor(sf::Color::White); //colour for alive or dead
            else next_box.setFillColor(sf::Color::Black);

            box_grid[row].push_back(next_box); // add finished block to 2d vector

            column ++;
        }
        row ++;
    }
}

void LifeClass::firstRender(sf::RenderTexture &texture) {
    // Renders entire grid
    for (int i = 0; i < box_grid.size(); i++) {
        for (int j = 0; j < box_grid[i].size(); j++) {
            texture.draw(box_grid[i][j]);
        }
    }
}

void LifeClass::scanNeighbours(int i, int j) {
    // Scan for living neighbours
    living = 0;
    for (int x = i - scan_size; x <= (i + scan_size); x++) { // rows
        for (int y = j - scan_size; y <= (j + scan_size); y++) { // columns
            if (x >= 0 && y >= 0) {
                if (x < box_grid.size() && y < box_grid[0].size()) {
                    if (bool_grid[x][y] == true) living++; // Count neighbours
                }
            }
        }
    }
}

void LifeClass::evolutionDayNight(sf::RenderTexture &texture) {
    // B3678 S34678
    rand_max = 1;
    for (int i = 0; i < box_grid.size(); i++) { // rows
        for (int j = 0; j < box_grid[i].size(); j++) { // columns

            // Scan for living neighbours
            scanNeighbours(i, j);

            // Survival rules
            if (bool_grid[i][j]) { // If Alive
                living -= 1; // don't count self
                if (living < 3 || living == 5) { //Die when 1 2 5
                    bool_grid_next[i][j] = false;
                    box_grid[i][j].setFillColor(sf::Color::Black);
                    texture.draw(box_grid[i][j]);
                }
            }
            else { // If Dead
                if (living == 3 || living > 5) { // Birth when: B3678
                    bool_grid_next[i][j] = true;
                    box_grid[i][j].setFillColor(sf::Color::White);
                    texture.draw(box_grid[i][j]);
                }
            }
        }
    }
}

void LifeClass::evolutionGameOfLife(sf::RenderTexture &texture) {
    // B3/S23
    rand_max = 5;
    for (int i = 0; i < box_grid.size(); i++) { // rows
        for (int j = 0; j < box_grid[i].size(); j++) { // columns

            // Scan for living neighbours
            scanNeighbours(i, j);

            // Survival rules
            if (bool_grid[i][j]) { // If Alive
                living -= 1; // don't count self
                if (living < 3 || living > 3) { //Die when
                    bool_grid_next[i][j] = false;
                    box_grid[i][j].setFillColor(sf::Color::Black);
                    texture.draw(box_grid[i][j]);
                }
            }
            else { // If Dead
                if (living == 3) { // Birth when:
                    bool_grid_next[i][j] = true;
                    box_grid[i][j].setFillColor(sf::Color::White);
                    texture.draw(box_grid[i][j]);
                }
            }
        }
    }
}

void LifeClass::evolutionB2(sf::RenderTexture &texture) {
    // B2 S12345678 / S2/3/0
    rand_max = 200;
    for (int i = 0; i < box_grid.size(); i++) { // rows
        for (int j = 0; j < box_grid[i].size(); j++) { // columns

            // Scan for living neighbours
            scanNeighbours(i, j);

            // Survival rules
            if (bool_grid[i][j]) { // If Alive
                living -= 1; // don't count self
                if (living > 8) { //Die when 1 2 5
                    bool_grid_next[i][j] = false;
                    box_grid[i][j].setFillColor(sf::Color::Black);
                    texture.draw(box_grid[i][j]);
                }
            }
            else { // If Dead
                if (living == 2) { // Birth when: B3678
                    bool_grid_next[i][j] = true;
                    box_grid[i][j].setFillColor(sf::Color::White);
                    texture.draw(box_grid[i][j]);
                }
            }
        }
    }
}

void LifeClass::evolutionB3(sf::RenderTexture &texture) {
    // B3 S12345678 / S23
    rand_max = 70;
    for (int i = 0; i < box_grid.size(); i++) { // rows
        for (int j = 0; j < box_grid[i].size(); j++) { // columns

            // Scan for living neighbours
            scanNeighbours(i, j);

            // Survival rules
            if (bool_grid[i][j]) { // If Alive
                living -= 1; // don't count self
                if (living > 8) { //Die when 1 2 5
                    bool_grid_next[i][j] = false;
                    box_grid[i][j].setFillColor(sf::Color::Black);
                    texture.draw(box_grid[i][j]);
                }
            }
            else { // If Dead
                if (living == 3) { // Birth when: B3678
                    bool_grid_next[i][j] = true;
                    box_grid[i][j].setFillColor(sf::Color::White);
                    texture.draw(box_grid[i][j]);
                }
            }
        }
    }
}

void LifeClass::evolutionCells(sf::RenderTexture &texture) {
    // Cells - B2/S no survivors
    rand_max = 100;
    for (int i = 0; i < box_grid.size(); i++) { // rows
        for (int j = 0; j < box_grid[i].size(); j++) { // columns

            // Scan for living neighbours
            scanNeighbours(i, j);

            // Survival rules
            if (bool_grid[i][j]) { // If Alive
                living -= 1; // don't count self
                if (living > 0) { //Die when 1 2 5
                    bool_grid_next[i][j] = false;
                    box_grid[i][j].setFillColor(sf::Color::Black);
                    texture.draw(box_grid[i][j]);
                }
            }
            else { // If Dead
                if (living == 2) { // Birth when: B3678
                    bool_grid_next[i][j] = true;
                    box_grid[i][j].setFillColor(sf::Color::White);
                    texture.draw(box_grid[i][j]);
                }
            }
        }
    }
}

void LifeClass::evolutionVirus(sf::RenderTexture &texture) {
    // Virus - B36/S235
    rand_max = 20;
    for (int i = 0; i < box_grid.size(); i++) { // rows
        for (int j = 0; j < box_grid[i].size(); j++) { // columns

            // Scan for living neighbours
            scanNeighbours(i, j);

            // Survival rules
            if (bool_grid[i][j]) { // If Alive
                living -= 1; // don't count self
                if (living < 2 || living > 5 || living == 4) { //Die when 1 2 5
                    bool_grid_next[i][j] = false;
                    box_grid[i][j].setFillColor(sf::Color::Black);
                    texture.draw(box_grid[i][j]);
                }
            }
            else { // If Dead
                if (living == 3 || living == 6) { // Birth when: B3678
                    bool_grid_next[i][j] = true;
                    box_grid[i][j].setFillColor(sf::Color::White);
                    texture.draw(box_grid[i][j]);
                }
            }
        }
    }
}

void LifeClass::evolutionMaze(sf::RenderTexture &texture) {
    // Maze - B3/S12345
    rand_max = 200;
    for (int i = 0; i < box_grid.size(); i++) { // rows
        for (int j = 0; j < box_grid[i].size(); j++) { // columns

            // Scan for living neighbours
            scanNeighbours(i, j);

            // Survival rules
            if (bool_grid[i][j]) { // If Alive
                living -= 1; // don't count self
                if (living > 5) { //Die when 1 2 5
                    bool_grid_next[i][j] = false;
                    box_grid[i][j].setFillColor(sf::Color::Black);
                    texture.draw(box_grid[i][j]);
                }
            }
            else { // If Dead
                if (living == 3) { // Birth when: B3678
                    bool_grid_next[i][j] = true;
                    box_grid[i][j].setFillColor(sf::Color::White);
                    texture.draw(box_grid[i][j]);
                }
            }
        }
    }
}

void LifeClass::evolutionStarTrek(sf::RenderTexture &texture) {
    // Star Trek - B3/S0248
    rand_max = 7;
    for (int i = 0; i < box_grid.size(); i++) { // rows
        for (int j = 0; j < box_grid[i].size(); j++) { // columns

            // Scan for living neighbours
            scanNeighbours(i, j);

            // Survival rules
            if (bool_grid[i][j]) { // If Alive
                living -= 1; // don't count self
                if (living == 0 || living == 2 || living == 4 || living == 8) {//Die when 1 2 5
                    // continue;
                }
                else{
                    bool_grid_next[i][j] = false;
                    box_grid[i][j].setFillColor(sf::Color::Black);
                    texture.draw(box_grid[i][j]);
                }
            }
            else { // If Dead
                if (living == 3) { // Birth when: B3678
                    bool_grid_next[i][j] = true;
                    box_grid[i][j].setFillColor(sf::Color::White);
                    texture.draw(box_grid[i][j]);
                }
            }
        }
    }
}

void LifeClass::copyGridNext() {
    bool_grid = bool_grid_next;
}

void LifeClass::rebootGrids() {
    for (int i = 0; i < box_grid.size(); i++) {
        for (int j = 0; j < box_grid[i].size(); j++) {
            bool next_bool = getRandBool(rand_max);
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
