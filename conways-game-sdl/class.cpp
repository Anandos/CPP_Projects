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
    , survivors{0}
    , rand_max{2}
    , rand_lower{0}
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
            int cell_colour = randomInt(rand_max, false);

            cell_grid_colour[row].push_back(cell_colour);
            cell_grid_colour_next[row].push_back(cell_colour);
        }
        row++;
    }
}

void EvolutionClass::renderGrids(SDL_Renderer *renderer) {
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

int EvolutionClass::scanNeighbours(int row, int col) {
    // Scan around current cell
    survivors = 0;
    for (int x = row - 1; x <= row + 1; x++) {
        for (int y = col - 1; y <= col + 1; y++) {
            // check scan is within grid
            if (x >= 0 && y >= 0) {
                if (x < cell_grid.size() && y < cell_grid[0].size()) {
                    if (cell_grid_colour[x][y] > 0) survivors++; // add up surviving neighbours
                }
            }
        }
    }

    return survivors;
}

void EvolutionClass::conways(SDL_Renderer *renderer) {
    // B3/S23
    rand_max = 2;
    for (int row = 0; row < cell_grid.size(); row++) {
        for (int col = 0; col < cell_grid[0].size(); col++) {
            // Scan around current cell
            survivors = scanNeighbours(row, col);

            // Apply rules to current cell
            if (cell_grid_colour[row][col] > 0) { // if cell is alive
                survivors -= 1;
                if (survivors < 2 || survivors > 3) {
                    cell_grid_colour_next[row][col] = -126; // kill cell
                    SDL_SetRenderDrawColor(renderer, 126, 0, 0, 255); // set colour black
                    SDL_RenderFillRect(renderer, &cell_grid[row][col]); // render cell
                }
            }
            else { // cell is dead
                if (survivors == 3) {
                    cell_grid_colour_next[row][col] = 1; // birth cell
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set colour white
                    SDL_RenderFillRect(renderer, &cell_grid[row][col]); // render cell
                }
            }
        }
    }
}

void EvolutionClass::conwaysDayNight(SDL_Renderer *renderer) {
    // B3678/S34678
    rand_max = 1;
    for (int row = 0; row < cell_grid.size(); row++) {
        for (int col = 0; col < cell_grid[0].size(); col++) {
            // Scan around current cell
            survivors = scanNeighbours(row, col);

            // Apply rules to current cell
            // B3/S23
            if (cell_grid_colour[row][col] > 0) { // if cell is alive
                survivors -= 1;
                if (survivors < 3 || survivors == 5) {
                    cell_grid_colour_next[row][col] = 0; // kill cell
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set colour black
                    SDL_RenderFillRect(renderer, &cell_grid[row][col]); // render cell
                }
            }
            else { // cell is dead
                if (survivors == 3 || survivors > 5) {
                    cell_grid_colour_next[row][col] = 1; // birth cell
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set colour white
                    SDL_RenderFillRect(renderer, &cell_grid[row][col]); // render cell
                }
            }
        }
    }
}

void EvolutionClass::conwaysVirus(SDL_Renderer *renderer) {
    // B36/S235
    rand_max = 50;
    for (int row = 0; row < cell_grid.size(); row++) {
        for (int col = 0; col < cell_grid[0].size(); col++) {
            // Scan around current cell
            survivors = scanNeighbours(row, col);

            // Apply rules to current cell
            // B36/S235
            if (cell_grid_colour[row][col] > 0) { // if cell is alive
                survivors -= 1;
                if (survivors < 2 || survivors == 4 || survivors > 5) {
                    cell_grid_colour_next[row][col] = 0; // kill cell
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set colour black
                    SDL_RenderFillRect(renderer, &cell_grid[row][col]); // render cell
                }
            }
            else { // cell is dead
                if (survivors == 3 || survivors == 6) {
                    cell_grid_colour_next[row][col] = 1; // birth cell
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set colour white
                    SDL_RenderFillRect(renderer, &cell_grid[row][col]); // render cell
                }
            }
        }
    }
}

void EvolutionClass::conwaysMaze(SDL_Renderer *renderer) {
    // B3/S12345
    rand_max = 200;
    for (int row = 0; row < cell_grid.size(); row++) {
        for (int col = 0; col < cell_grid[0].size(); col++) {
            // Scan around current cell
            survivors = scanNeighbours(row, col);

            // Apply rules to current cell
            // B3/S12345
            if (cell_grid_colour[row][col] > 0) { // if cell is alive
                survivors -= 1;
                if (survivors > 5 || survivors == 0) {
                    cell_grid_colour_next[row][col] = 0; // kill cell
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set colour black
                    SDL_RenderFillRect(renderer, &cell_grid[row][col]); // render cell
                }
            }
            else { // cell is dead
                if (survivors == 3) {
                    cell_grid_colour_next[row][col] = 1; // birth cell
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set colour white
                    SDL_RenderFillRect(renderer, &cell_grid[row][col]); // render cell
                }
            }
        }
    }
}



void EvolutionClass::restartGrids() {
    // Re randomise entire grid
    int cell_colour = 1;
    for (int row = 0; row < cell_grid.size(); row++) {
        for (int col = 0; col < cell_grid[0].size(); col++) {
            cell_colour = randomInt(rand_max, false);
            cell_grid_colour[row][col] = cell_colour;
            cell_grid_colour_next[row][col] = cell_colour;
        }
    }
}

void EvolutionClass::copyGridNext() {
    // Copy entire calculated grid into first grid
    cell_grid_colour = cell_grid_colour_next;
}
