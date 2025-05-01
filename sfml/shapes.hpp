#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::cout; using std::cin; using std::endl; using std::string;
using std::vector;

// Window dimensions
extern float win_width;
extern float win_height;
extern int win_width_int;
extern int win_height_int;

// Text
extern float txt_x;
extern float txt_y;
extern float txt_x_vel;
extern float txt_y_vel;

// Circle
extern sf::CircleShape circle;
extern float c_x;
extern float c_y;
extern float c_x_vel;
extern float c_y_vel;

// Triangle
extern sf::VertexArray triangle;
extern vector <float> triangle_x;
extern vector <float> triangle_y;
extern vector <float> triangle_x_vec;
extern vector <float> triangle_y_vec;

// Lines
extern float line_speed;
extern float line_x;
extern float line_x_vel;
extern sf::RectangleShape line_vert;

extern float line_y;
extern float line_y_vel;
extern sf::RectangleShape line_horz;

// Polyonal strip
extern int polyg_count;
extern vector <float> polygonal_x;
extern vector <float> polygonal_y;
extern vector <float> polygonal_x_vec;
extern vector <float> polygonal_y_vec;
extern sf::VertexArray polygonal;

// Rectangles tunnel
extern int rect_grid_size;
extern int rect_verts;
extern float rect_margin; //starting margin iffset
extern int rect_vrt_i;
extern float rect_min;
extern float rect_speed;
extern float rect_life_diminish;
extern float rect_lifetime;
extern vector <float> rect_x;
extern vector <float> rect_y;
extern vector <float> rect_life;
extern vector <float> rect_speed_list;
extern vector <sf::VertexArray> rect_grid;
extern bool rect_white_colour; //keep track of rect grid current colour
extern bool rect_colour_change; //change colour this frame?
extern sf::Color rect_colour; //change rect grid to this colour

// Particles
extern int p_count;
extern sf::VertexArray particles;
extern vector <sf::Vector2f> particle_position;
extern vector <sf::Vector2f> particle_velocity;
extern vector <float> particle_life_left;
extern bool particles_white;
extern bool p_reset;

int initShapes();
float getRandom(int min, int max);


#endif