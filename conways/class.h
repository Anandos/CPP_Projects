//
// Created by Anand Damodaran on 07/06/2025.
//

#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <SFML/Graphics.hpp>

bool getRandBool(int max);

class LifeClass {
public:
    // variables, constructor, methods
    int win_width; //iphone resolution
    int win_height;
    std::vector<std::vector<sf::RectangleShape>> box_grid;
    std::vector<std::vector<bool>> bool_grid;
    std::vector<std::vector<bool>> bool_grid_next;

    int living;
    int scan_size;
    int rand_max;

    LifeClass(int win_width, int win_height);
    void createGrids(int cell_size);
    void firstRender(sf::RenderTexture &texture);
    void scanNeighbours(int i, int j);
    void evolutionDayNight(sf::RenderTexture &texture);
    void evolutionGameOfLife(sf::RenderTexture &texture);
    void evolutionB2(sf::RenderTexture &texture);
    void evolutionB3(sf::RenderTexture &texture);
    void evolutionCells(sf::RenderTexture &texture);
    void evolutionVirus(sf::RenderTexture &texture);
    void evolutionMaze(sf::RenderTexture &texture);
    void evolutionStarTrek(sf::RenderTexture &texture);
    void copyGridNext();
    void rebootGrids();
};





#endif //CLASS_H
