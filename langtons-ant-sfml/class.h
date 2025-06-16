// Created by Anand Damodaran on 07/06/2025.

#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class GameOfLife {
public:
    // window size
    int win_width;
    int win_height;

    // 2D grids
    std::vector<std::vector<sf::RectangleShape>> grid;
    std::vector<std::vector<int>> colour_grid;

    std::vector<int> ant_position;
    std::vector<int> directions;
    int ant_direction;
    std::vector<std::string> str_direction;

    // SFML texture
    // sf::RenderTexture texture;

    // cell size
    int size;
    int row;
    int row_size;
    int col_size;

    // print out
    std::string read_out;

    // Constructor
    GameOfLife(int win_width, int win_height);

    // Methods
    void antLogicHex(sf::RenderTexture &texture);
    void antLogic(sf::RenderTexture &texture);

    void antMovement(int cycles);
    void readOut();
    void createGrids(int s);

    // create texture


};

#endif //CLASS_H
