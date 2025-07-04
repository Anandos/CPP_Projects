//
// Created by Anand Damodaran on 12/06/2025.
//

#ifndef CLASS_H
#define CLASS_H

#include <random>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int randomInt(int rand_max, bool colour_palette);

class EvolutionClass {
public:
    EvolutionClass(int win_width, int win_height, int size, int colour_palette, int border);

    int size;
    int win_width;
    int win_height;
    bool colour_palette;
    int border;
    int survivors;
    int rand_max;
    int rand_lower;

    // Cell SDL rectangles and their positions across the screen
    std::vector<std::vector<SDL_FRect>> cell_grid;

    // Grid cell states
    std::vector<std::vector<int>> cell_grid_colour;

    // Grid cell states for next frame
    std::vector<std::vector<int>> cell_grid_colour_next;

    void createGrids();
    void renderGrids(SDL_Renderer *renderer);
    void restartGrids();
    void copyGridNext();
    int scanNeighbours(int row, int col);

    void conways(SDL_Renderer *renderer);
    void conwaysDayNight(SDL_Renderer *renderer);
    void conwaysVirus(SDL_Renderer *renderer);
    void conwaysMaze(SDL_Renderer *renderer);

};

#endif //CLASS_H
