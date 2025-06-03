//'langtons-ant' created on 01/06/2025 by Anand Damodaran
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

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

    // 2D vector for grid
    // Ant position
    // Ant movement logic
    // -ant flips the colour of current square
    // -if ant on white square, turn right, move forward one
    // -if any on black square, turn left, move forward one

    std::vector<std::vector<sf::RectangleShape>> grid;
    std::vector<std::vector<int>> colour_grid;
    std::vector<int> ant_position{0, 0};
    std::vector<int> directions = {0, 1, 2, 3};
    int ant_direction = 0;
    std::vector<std::string> str_direction{"up   ", "right", "down ", "left "};

    int size = 3;
    int row = 0;
    // Build 2d rectangle and bool grid
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
    int row_size = grid.size();
    int col_size = grid[0].size();
    ant_position = {row_size / 2, col_size / 2};
    cout << "Rows: " << row_size << " | Cols: " << col_size << endl;
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

    while (window.isOpen() && running) {
        cycles--;
        if (cycles <= 0) paused = true;

        if (!paused) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(speed));
            read_out = "Ant direction: " + str_direction[ant_direction] + " | ";

            // Change direction based on current square and change current square colour
            if (colour_grid[ant_position[0]][ant_position[1]] == 0) {
                // White square
                ant_direction = (ant_direction + 1) % directions.size();
                colour_grid[ant_position[0]][ant_position[1]] = 1;
                grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::White);
                texture.draw(grid[ant_position[0]][ant_position[1]]);
                read_out += "to Black | ";
            }
            else if (colour_grid[ant_position[0]][ant_position[1]] == 1) {
                // Black square
                ant_direction = (ant_direction + 1) % directions.size();
                colour_grid[ant_position[0]][ant_position[1]] = 2;
                grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::Green);
                texture.draw(grid[ant_position[0]][ant_position[1]]);
                read_out += "to White | ";
            }
            else if (colour_grid[ant_position[0]][ant_position[1]] == 2) {
                // Green square
                ant_direction = (ant_direction - 1 + directions.size()) % directions.size();
                colour_grid[ant_position[0]][ant_position[1]] = 3;
                grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::Magenta);
                texture.draw(grid[ant_position[0]][ant_position[1]]);
                read_out += "to Green | ";
            }
            else if (colour_grid[ant_position[0]][ant_position[1]] == 3) {
                // Magnenta square
                ant_direction = (ant_direction - 1 + directions.size()) % directions.size();
                colour_grid[ant_position[0]][ant_position[1]] = 0;
                grid[ant_position[0]][ant_position[1]].setFillColor(sf::Color::Black);
                texture.draw(grid[ant_position[0]][ant_position[1]]);
                read_out += "to Magenta | ";
            }
            else {
                cout << "Bool grid error!\n";
            }

            read_out += "Ant position row: " + std::to_string(ant_position[0]) + " | column: " + std::to_string(ant_position[1]);

            // Calculate next ant position and loop across edges - LLRR, 0123
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
            cout << "| Interval: " << inter_duration.count() << " seconds" << endl;
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
                    cout << "Paused\n";
                    paused = !paused;
                }
                if (key_pressed->scancode == sf::Keyboard::Scancode::S) {
                    if (speed == 100) speed = 500;
                    else speed = 100;
                }
            }
        }

        // Rendering
        // window.clear();
        texture.display(); //finished rendering to texture

        window.draw(sprite); //draw texture to window

        window.display();

        interval = std::chrono::high_resolution_clock::now();
    }

}