//
// Created by Anand Damodaran on 12/06/2025.
//

#include "class.h"
#include <iostream>
#include <random>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


int randomInt(int rand_max, bool colour_palette) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <int> dist(0, rand_max);

    int result = dist(gen);

    if (!colour_palette) {
        result = (result == 0) ? 1 : 0;
    }

    return result;
}

EvolutionClass::EvolutionClass(int win_width, int win_height, int size, int colour_palette, int border)
    : size(size)
    , win_width(win_width)
    , win_height(win_height)
    , colour_palette{false}
    , border(border)
    , rand_max{3}
    , random(true)
    , langton_direction{0}
    , langton_x{0}
    , langton_y{0}
{};

void EvolutionClass::createGrids() {
    // Create 2D grids based on window resolution
    int row = 0;
    for (int x = 10; x < win_width - 10; x += size) {
        cell_grid.emplace_back();
        cell_grid_colour.emplace_back();
        cell_grid_colour_next.emplace_back();

        // Each column
        for (int y = 10; y < win_height - 10; y += size) {
            // SDL rectangle creation and
            SDL_FRect rect(x, y, size - border, size - border);
            cell_grid[row].push_back(rect);

            // rectangle colour creation
            cell_grid_colour[row].push_back(1);
            cell_grid_colour_next[row].push_back(1);
        }
        row++;
    }
}

void EvolutionClass::renderAll(SDL_Renderer *renderer) {
    // Render 2D grid using referenced renderer object
    int fade_clr = 0;
    for (int row = 0; row < cell_grid.size(); row++) {
        for (int col = 0; col < cell_grid[0].size(); col++) {
            if (cell_grid_colour[row][col] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set colour black
            }
            else if (cell_grid_colour[row][col] < 0) {
                fade_clr = -cell_grid_colour[row][col];
                SDL_SetRenderDrawColor(renderer, fade_clr, fade_clr, fade_clr, 255); // set colour magenta
                cell_grid_colour[row][col]++;
            }
            else if (cell_grid_colour[row][col] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set colour white
            }
            else if (cell_grid_colour[row][col] == 2) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // set colour green
            }
            else if (cell_grid_colour[row][col] == 3) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // set colour magenta
            }
            SDL_RenderFillRect(renderer, &cell_grid[row][col]); // render cell
        }
    }
}

void EvolutionClass::antCentre() {
    langton_x = cell_grid_colour.size() / 2;
    langton_y = cell_grid_colour[0].size() / 2;
    langton_direction = 0;
}

void EvolutionClass::langtons(SDL_Renderer *renderer) {
    // White Right, Black Left

    if (cell_grid_colour[langton_x][langton_y] == 1) { // cell is alive, turn right
        langton_direction += 1;
        langton_direction %= 4;
        cell_grid_colour_next[langton_x][langton_y] = 0; // kill cell
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set colour black
        SDL_RenderFillRect(renderer, &cell_grid[langton_x][langton_y]); // render cell
    }
    else { // cell is dead, turn left
        langton_direction -= 1;
        langton_direction %= 4;
        cell_grid_colour_next[langton_x][langton_y] = 1; // birth cell
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set colour white
        SDL_RenderFillRect(renderer, &cell_grid[langton_x][langton_y]); // render cell
    }

    switch (langton_direction) {
        case 0:
            langton_y -= 1;
            if (langton_y < 0) langton_y = cell_grid_colour[0].size() - 1;
            break;
        case 1:
            langton_x += 1;
            if (langton_x >= cell_grid_colour.size()) langton_x = 0;
            break;
        case 2:
            langton_y += 1;
            if (langton_y >= cell_grid_colour[0].size()) langton_y = 0;
            break;
        case 3:
            langton_x -= 1;
            if (langton_x < 0) langton_x = cell_grid_colour.size() - 1;
            break;
        default:
            std::cout << "Ant direction error: " << langton_direction << std::endl;
    }

    // render ant
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // set colour black
    SDL_RenderFillRect(renderer, &cell_grid[langton_x][langton_y]); // render cell
}

void EvolutionClass::restartGrids() {
    // Re randomise entire grid
    for (int row = 0; row < cell_grid.size(); row++) {
        for (int col = 0; col < cell_grid[0].size(); col++) {
            cell_grid_colour[row][col] = 1;
            cell_grid_colour_next[row][col] = 1;
        }
    }
}

void EvolutionClass::copyGridNext() {
    // Copy entire calculated grid into first grid
    cell_grid_colour = cell_grid_colour_next;
}
