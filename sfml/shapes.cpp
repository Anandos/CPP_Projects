#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "shapes.hpp"
#include <random>

using std::cout; using std::cin; using std::endl; using std::string;

float win_width = 1600;
float win_height = 800;
int win_width_int = static_cast <int> (win_width);
int win_height_int = static_cast <int> (win_height);

// Random engine
float getRandom(int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <int> dist(min * 100, max * 100);
    return static_cast <float> (dist(gen)) / 100;
}

// Text
float txt_x = 0;
float txt_y = 15;
float txt_x_vel = 1;
float txt_y_vel = 1;

// Circle
sf::CircleShape circle(20.f);
float c_x = win_width / 2;
float c_y = win_height / 2;
float c_x_vel = -1;
float c_y_vel = -1;

// Triangle
sf::VertexArray triangle(sf::PrimitiveType::Triangles, 3);
vector <float> triangle_x = {120, 200, 340};
vector <float> triangle_y = {100, 320, 140};
vector <float> triangle_x_vec = {1, 1, 1};
vector <float> triangle_y_vec = {1, 1, 1};

// Lines
float line_speed = 2;
float line_x = 0;
float line_x_vel = line_speed;
sf::RectangleShape line_vert({win_height, 2.f});

float line_y = 0;
float line_y_vel = line_speed;
sf::RectangleShape line_horz({win_width, 2.f});
bool horizontal = true;

// Polyonal strip
int polyg_count = 64;
vector <float> polygonal_x(polyg_count);
vector <float> polygonal_y(polyg_count);
vector <float> polygonal_x_vec(polyg_count, 1);
vector <float> polygonal_y_vec(polyg_count, 1);
sf::VertexArray polygonal(sf::PrimitiveType::TriangleStrip, polyg_count);

// Rectangles tunnel
int rect_grid_size = 20;
int rect_verts = 5;
float rect_margin = 0; //starting margin offset
// float rect_offset = win_height / 9; //offset the offset for each line
// float rect_offset_diminish = 0.77; //70% shrink offset each line strip in grid
int rect_vrt_i = 0;
float rect_min = 200;
float rect_speed = 0.1;
float rect_life_diminish = 0;
float rect_lifetime = 30;
vector <float> rect_x(rect_grid_size * rect_verts);
vector <float> rect_y(rect_grid_size * rect_verts);
vector <float> rect_life(rect_grid_size);
vector <float> rect_speed_list(rect_grid_size);
vector <sf::VertexArray> rect_grid(rect_grid_size);
bool rect_white_colour = true; //keep track of rect grid current colour
bool rect_colour_change = false; //change colour this frame?
sf::Color rect_colour = sf::Color::White; //change rect grid to this colour

// Fan shape
int fan_size = 8;
sf::VertexArray fan(sf::PrimitiveType::TriangleFan, fan_size);
vector <float> fan_x(fan_size);
vector <float> fan_y(fan_size);
vector <float> fan_x_vec(fan_size);
vector <float> fan_y_vec(fan_size);


// Particles
int p_count = 400;
float p_lifetime = 20;
sf::VertexArray particles(sf::PrimitiveType::Points, p_count);
vector <sf::Vector2f> particle_position(p_count);
vector <sf::Vector2f> particle_velocity(p_count);
vector <float> particle_life_left(p_count);
bool particles_white = true;
bool p_reset = false;


int initShapes(){

    // Circle
    circle.setFillColor(sf::Color::Black);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(40.f);
    circle.setOrigin({0, 0});
    circle.setPosition({c_x, c_y});
    cout << "Eye initialised" << endl;

    // Free triangle
    for(int i{}; i < 3; i++){
        triangle[i].position = sf::Vector2f({triangle_x[i], triangle_y[i]});
    }
    triangle[0].color = sf::Color(255, 0, 0, 125);
    triangle[1].color = sf::Color(0, 255, 0, 125);
    triangle[2].color = sf::Color(0, 0, 255, 125);
    cout << "Triangle initialised" << endl;

    // Rectangle line
    line_vert.setFillColor(sf::Color(255, 155, 0));
    line_vert.setRotation(sf::degrees(90));
    line_vert.setPosition({line_x, 0.f});
    line_horz.setFillColor(sf::Color(255, 155, 0));
    line_horz.setPosition({0.f, line_y});
    cout << "Scan lines initialised" << endl;

    // Polygonal strip
    for(int i{}; i < polyg_count; i++){
        // {20, 0, 220, 200, 420, 400};
        polygonal_x[i] = (win_width / 2) + i * 10;
        // {0, 150, 20, 170, 40, 190};
        polygonal_y[i] = (i % 2 == 0) ? 0 : 10;
        polygonal_y[i] += i * 10;
        polygonal[i].position = sf::Vector2f({polygonal_x[i], polygonal_y[i]});
        polygonal[i].color = sf::Color(255, 0, 255);
    }
    cout << "Snake initialised" << endl;

    // Rect tunnel
    for(int i{}; i < rect_grid.size(); i++){ //setup tunnel effect
        sf::VertexArray rect_next(sf::PrimitiveType::LineStrip, rect_verts);
        rect_grid[i] = rect_next;
        rect_life_diminish += 2;
        rect_life[i] = rect_lifetime - rect_life_diminish;
        rect_x[rect_vrt_i] = win_width / 2; //1
        rect_y[rect_vrt_i] = win_height / 2;
        rect_grid[i][0].position = sf::Vector2f(
            {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
        rect_vrt_i ++;
        rect_grid[i][0].color = sf::Color(255, 255, 255, 0);

        rect_x[rect_vrt_i] = win_width / 2; //2
        rect_y[rect_vrt_i] = win_height / 2;
        rect_grid[i][1].position = sf::Vector2f(
            {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
        rect_vrt_i ++;
        rect_grid[i][1].color = sf::Color(255, 255, 255, 0);

        rect_x[rect_vrt_i] = win_width / 2; //3
        rect_y[rect_vrt_i] = win_height / 2;
        rect_grid[i][2].position = sf::Vector2f(
            {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
        rect_vrt_i ++;
        rect_grid[i][2].color = sf::Color(255, 255, 255, 0);

        rect_x[rect_vrt_i] = win_width / 2; //4
        rect_y[rect_vrt_i] = win_height / 2;
        rect_grid[i][3].position = sf::Vector2f(
            {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
        rect_vrt_i ++;
        rect_grid[i][3].color = sf::Color(255, 255, 255, 0);

        rect_x[rect_vrt_i] = win_width / 2; //5
        rect_y[rect_vrt_i] = win_height / 2;
        rect_grid[i][4].position = sf::Vector2f(
            {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
        rect_vrt_i ++;
        rect_grid[i][4].color = sf::Color(255, 255, 255, 0);
    }
    cout << "Tunnel initialised" << endl;

    // Particles
    for(int i{}; i < p_count; i++){
        particle_position[i] = sf::Vector2f({getRandom(0, win_width), getRandom(0, win_height)});
        particles[i].position = particle_position[i];
        particle_velocity[i] = sf::Vector2f({(getRandom(-1, 1) / 10), (getRandom(-1, 1) / 10)});
        particles[i].color = sf::Color::White;

    }
    cout << "Particles initialised" << endl;

    return 0;
}


// clang++ -Wall -std=c++17 -g window.cpp shapes.cpp -o window -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
