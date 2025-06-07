// Created by Anand Damodaran on 07/06/2025.

#include "class.h"
#include <iostream>
#include <SFML/Graphics.hpp>

GameOfLife::GameOfLife(int win_width, int win_height):
    win_width(win_width),
    win_height(win_height),

    ant_position{0, 0},
    directions{0, 1, 2, 3},
    ant_direction{0},
    str_direction{"up   ", "right", "down ", "left "},

    // cell size
    size{0},
    row {0},
    row_size{0},
    col_size{0}
{};

void GameOfLife::antLogicHex(sf::RenderTexture &texture) {
    read_out = "Ant direction: " + str_direction[ant_direction] + " | ";
    if (colour_grid[ant_position[0]][ant_position[1]] == 0) {
        // White square right
        ant_direction = (ant_direction + 1) % directions.size();
        colour_grid[ant_position[0]][ant_position[1]] = 1;
        grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::White);
        texture.draw(grid[ant_position[0]][ant_position[1]]);
        read_out += "to Black | ";
    }
    else if (colour_grid[ant_position[0]][ant_position[1]] == 1) {
        // Green square right
        ant_direction = (ant_direction + 1) % directions.size();
        colour_grid[ant_position[0]][ant_position[1]] = 2;
        grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::Green);
        texture.draw(grid[ant_position[0]][ant_position[1]]);
        read_out += "to White | ";
    }
    else if (colour_grid[ant_position[0]][ant_position[1]] == 2) {
        // Magenta square left
        ant_direction = (ant_direction - 1 + directions.size()) % directions.size();
        colour_grid[ant_position[0]][ant_position[1]] = 3;
        grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::Magenta);
        texture.draw(grid[ant_position[0]][ant_position[1]]);
        read_out += "to Green | ";
    }
    else if (colour_grid[ant_position[0]][ant_position[1]] == 3) {
        // Black square left
        ant_direction = (ant_direction - 1 + directions.size()) % directions.size();
        colour_grid[ant_position[0]][ant_position[1]] = 0;
        grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::Black);
        texture.draw(grid[ant_position[0]][ant_position[1]]);
        read_out += "to Magenta | ";
    }
    else {
        std::cout << "Bool grid error!\n";
    }
}

void GameOfLife::antLogic(sf::RenderTexture &texture) {
    read_out = "Ant direction: " + str_direction[ant_direction] + " | ";
    if (colour_grid[ant_position[0]][ant_position[1]] == 0) {
        // White square right
        ant_direction = (ant_direction + 1) % directions.size();
        colour_grid[ant_position[0]][ant_position[1]] = 1;
        grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::White);
        texture.draw(grid[ant_position[0]][ant_position[1]]);
        read_out += "to Black | ";
    }
    else if (colour_grid[ant_position[0]][ant_position[1]] == 1) {
        // Black square left
        ant_direction = (ant_direction - 1 + directions.size()) % directions.size();
        colour_grid[ant_position[0]][ant_position[1]] = 0;
        grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::Black);
        texture.draw(grid[ant_position[0]][ant_position[1]]);
        read_out += "to Magenta | ";
    }
    else {
        std::cout << "Bool grid error!\n";
    }
}

void GameOfLife::antMovement(int cycles) {
    if (ant_direction == 0) { //move up
        ant_position[1] -= 1;
        read_out += " | moved up    ";
        if (ant_position[1] < 0) {
            ant_position[1] = grid[0].size() - 1; //loop around vertically
            read_out.insert(0, "Looped from top to bottom\n");
        }
    }
    else if (ant_direction == 1) { //move right
        ant_position[0] += 1;
        read_out += " | moved right ";
        if (ant_position[0] >= grid.size()) {
            ant_position[0] = 0; //loop horizontally
            read_out.insert(0, "Looped from right to left\n");
        }
    }
    else if (ant_direction == 2) { //move down
        ant_position[1] += 1;
        read_out += " | moved down  ";
        if (ant_position[1] >= grid[0].size()) {
            ant_position[1] = 0; //loop around vertically
            read_out.insert(0, "Looped from bottom to top\n");
        }
    }
    else if (ant_direction == 3) { //move left
        ant_position[0] -= 1;
        read_out += " | moved left  ";
        if (ant_position[0] < 0) {
            ant_position[0] = grid.size() - 1;
            read_out.insert(0, "Looped from left to right\n");
        }
    }
    read_out += " | cycles: " + std::to_string(cycles) + "\n";
}

// void GameOfLife::readOut() {
//
// }

void GameOfLife::createGrids(int s) {
    size = s;
    row = 0;
    for (int x = size; x < win_width - size; x += size) {
        grid.emplace_back();
        colour_grid.emplace_back();
        for (int y = size; y < win_height - size; y += size) {
            sf::RectangleShape next_cell;
            next_cell.setSize({static_cast<float>(size), static_cast<float>(size)});
            next_cell.setPosition({static_cast<float>(x), static_cast<float>(y)});
            next_cell.setFillColor(sf::Color::White);

            grid[row].push_back(next_cell);
            colour_grid[row].push_back(0);
        }

        row++;
    }

    row_size = grid.size();
    col_size = grid[0].size();
    ant_position = {row_size / 2, col_size / 2};
    std::cout << "Rows: " << row_size << " | Cols: " << col_size << std::endl;

}

