#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include "shapes.hpp"

using std::cout; using std::cin; using std::endl; using std::string;

int main(){
    std::cout << "SFML Version: " <<  SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << endl;
    if(initShapes() == 0){
        cout << "shapes.cpp loaded successfully" << endl;
    }
    else{
        cout << "shapes.cpp error loading" << endl;
        return 1;
    }

    // GPU Settings
    sf::RenderWindow window(sf::VideoMode({1600, 800}), "Hello SFML");
    cout << "Render Window initialised" << endl;

    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(120);

    // bool has_focus = window.hasFocus(); //does window have focus
    sf::Vector2u size = window.getSize(); //get size of window
    auto [width, height] = size; 
    cout << "window width & height: " << width << ' ' << height << endl;;

    // sf::Clock clock timer
    sf::Clock clock; 
    sf::Time time_elapsed = clock.getElapsedTime();
    cout << "time restrt: " << time_elapsed.asSeconds() << endl;
    clock.stop();
    clock.reset();
    clock.restart();

    // Font
    sf::Font font;
    try{
        if(!font.openFromFile("resources/font.ttf")){
            throw sf::Exception("Unable to load font file");
        }
    }
    catch(const sf::Exception &e){
        cout << "error: " << e.what() << endl;
        return -1;
    }
    sf::Text text(font);
    cout << "Font loaded successfully" << endl;
    text.setString("Hello world");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition({txt_x, txt_y});
    cout << "Text initialised" << endl;
    
    // Texture
    sf::Image image("resources/sun_texture.jpeg");

    // for(unsigned x = 0; x < image.getSize().x; x++){
    //     for(unsigned y = 0; y < image.getSize().y; y++){
    //         sf::Color c = image.getPixel({x, y});
    //         float r_pix = c.r, g_pix = c.g, b_pix = c.b;
    //         if(r_pix <= 185) r_pix = r_pix - (1 - (r_pix / 255)) * 20; //
    //         else r_pix = r_pix + (r_pix / 255) * 30;
    //         if(g_pix <= 185) g_pix = g_pix - (1 - (g_pix / 255)) * 20;
    //         else g_pix = g_pix + (g_pix / 255) * 30;
    //         if(b_pix <= 185) b_pix = b_pix - (1 - (b_pix / 255)) * 20;
    //         else b_pix = b_pix + (b_pix / 255) * 30;

    //         image.setPixel({x, y}, 
    //             sf::Color(
    //                 std::clamp(static_cast<int>(r_pix), 0, 255), 
    //                 std::clamp(static_cast<int>(g_pix), 0, 255), 
    //                 std::clamp(static_cast<int>(b_pix), 0, 255),
    //                 20
    //             ));
    //     }
    // }

    // Shader
    if(sf::Shader::isAvailable()){
        cout << "Shaders avilable on this system GPU" << endl;
    }
    sf::Shader shader;
    if(!shader.loadFromFile("shader.frag", sf::Shader::Type::Fragment)){
        return 1;
    }
    cout << "Shader loaded" << endl;



    sf::Texture texture(
        image, 
        false, 
        sf::IntRect({0, 0}, {win_width_int, win_height_int})
        );
    sf::Sprite background_sprite(texture);
    background_sprite.setColor(sf::Color(255, 255, 255, 255));

    // Audio
    sf::SoundBuffer music("resources/josefpres_piano_010.wav");
    sf::Sound audio(music);
    audio.play();

    // FPS Display
    sf::Clock fps_clock;
    float fps = 0;
    sf::Time elapsed;
    sf::Text fps_text(font);
    fps_text.setCharacterSize(20);
    fps_text.setPosition({2, -5});
    fps_text.setFillColor(sf::Color::White);
    float fps_total = 0;
    int fps_count = 0;

    int frames{0};
    // Run while window is open
    bool pause = false;
    bool additional = false;
    while(window.isOpen()){
        if(!pause){
            window.clear(sf::Color::Black);


            // FPS
            elapsed = fps_clock.restart();
            fps_total += 1.f / elapsed.asSeconds();
            fps_count ++;

            time_elapsed = clock.getElapsedTime();
            frames++;
            if(time_elapsed.asSeconds() >= 1){
                time_elapsed = clock.getElapsedTime();
                cout << frames << " frames | ";
                cout << time_elapsed.asSeconds() << " seconds" << endl;
                cout << c_x << " " << c_y << " circle coo" << endl;
                cout << c_x_vel << " " << c_y_vel << " circle vel" << endl;
                cout << line_x_vel << " " << line_y_vel << " line x y vel" << 
                endl;
                cout << c_x_vel << " " << c_y_vel << " eye velocity" << endl;
                cout << "random number: " << getRandom(-100, 100) << endl;

                cout << endl;
                frames = 0;
                clock.restart();

                fps = fps_total / fps_count;
                fps_total = 0;
                fps_count = 0;
                fps_text.setString(
                    "FPS: " + std::to_string(static_cast <int> (fps)));
            }
        
            // Eye motion
            if(c_x <= 40) c_x_vel = (getRandom(5, 20))/10;
            else if(c_x >= (win_width - 80)) 
                c_x_vel = -(getRandom(5, 20))/10;
            if(c_y <= 40) 
                c_y_vel = (getRandom(5, 20))/10;
            else if(c_y >= (win_height - 80)) c_y_vel = -(getRandom(5, 20))/10;
            c_x += c_x_vel;
            c_y += c_y_vel;
            circle.setPosition({c_x, c_y});

            // Text motion
            if(txt_x <= 0) txt_x_vel = 1;
            else if(txt_x >= (win_width - 270)) txt_x_vel = -1;
            if(txt_y <= -15) txt_y_vel = 1;
            else if(txt_y >= (win_height - 50)) txt_y_vel = -1;
            txt_x += txt_x_vel;
            txt_y += txt_y_vel;
            text.setPosition({txt_x, txt_y});

            // Triangle motion
            for(int i = 0; i < 3; i++){
                // Loop through each vertex and adjust position & momentum
                if(triangle_x[i] <= 0) 
                    triangle_x_vec[i] = (getRandom(2, 20))/10;
                else if(triangle_x[i] >= win_width) 
                    triangle_x_vec[i] = -(getRandom(2, 20))/10;
                triangle_x[i] += triangle_x_vec[i]; //update x

                if(triangle_y[i] <= 0) 
                    triangle_y_vec[i] = (getRandom(2, 20))/10;
                else if(triangle_y[i] >= win_height) 
                    triangle_y_vec[i] = -(getRandom(2, 20))/10;
                triangle_y[i] += triangle_y_vec[i]; //update y

                triangle[i].position = sf::Vector2f(triangle_x[i], triangle_y[i]); //update triangle position itself
            }

            // Rectangle shape
            if(line_x >= (win_width + 10)) line_x_vel = -line_speed;
            else if(line_x <= -10) line_x_vel = line_speed;
            line_x += line_x_vel;
            line_vert.setPosition({line_x, 0.f});

            if(line_y >= (win_height + 10)) line_y_vel = -line_speed;
            else if(line_y <= -10) line_y_vel = line_speed;
            line_y += line_y_vel;
            line_horz.setPosition({0.f, line_y});

            for(int i{}; i < polyg_count; i++){
                if(polygonal_x[i] <= 0) polygonal_x_vec[i] = 1;
                else if(polygonal_x[i] >= win_width) polygonal_x_vec[i] = -1;
                if(polygonal_y[i] <= 0) polygonal_y_vec[i] = 1;
                else if(polygonal_y[i] >= win_height) polygonal_y_vec[i] = -1;
                
                polygonal_x[i] += polygonal_x_vec[i];
                polygonal_y[i] += polygonal_y_vec[i];
                polygonal[i].position = sf::Vector2f({polygonal_x[i], polygonal_y[i]});
            }

            // Tunnel rectangles
            rect_margin = 0; //starting margin offset
            rect_vrt_i = 0;
            for(int i{}; i < rect_grid.size(); i++){ //setup tunnel effect
                rect_life[i] -= 0.01;
                // cout << "Tunnel rect " << rect_vrt_i << ": " << rect_min << endl;
                if(rect_life[i] <= 0){
                    rect_x[rect_vrt_i] = win_width / 2; //1
                    rect_y[rect_vrt_i] = win_height / 2;
                    rect_grid[i][0].color = sf::Color::Yellow;
                    rect_x[rect_vrt_i + 1] = win_width / 2; //2
                    rect_y[rect_vrt_i + 1] = win_height / 2;
                    rect_grid[i][1].color = sf::Color::Yellow;
                    rect_x[rect_vrt_i + 2] = win_width / 2; //3
                    rect_y[rect_vrt_i + 2] = win_height / 2;
                    rect_grid[i][2].color = sf::Color::Yellow;
                    rect_x[rect_vrt_i + 3] = win_width / 2; //4
                    rect_y[rect_vrt_i + 3] = win_height / 2;
                    rect_grid[i][3].color = sf::Color::Yellow;
                    rect_x[rect_vrt_i + 4] = win_width / 2; //5
                    rect_y[rect_vrt_i + 4] = win_height / 2;
                    rect_grid[i][4].color = sf::Color::Yellow;
                    rect_life[i] = rect_lifetime;
                    rect_speed_list[i] = 0.001;
                    cout << "Reset rectangle in tunnel " << rect_vrt_i << endl; 
                }

                rect_speed_list[i] *= 1.005;
                rect_x[rect_vrt_i] -= rect_speed_list[i];
                rect_y[rect_vrt_i] -= rect_speed_list[i] / 2;
                rect_grid[i][0].position = sf::Vector2f(
                    {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
                rect_vrt_i ++;

                rect_x[rect_vrt_i] += rect_speed_list[i];
                rect_y[rect_vrt_i] -= rect_speed_list[i] / 2;
                rect_grid[i][1].position = sf::Vector2f(
                    {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
                rect_vrt_i ++;

                rect_x[rect_vrt_i] += rect_speed_list[i];
                rect_y[rect_vrt_i] += rect_speed_list[i] / 2;
                rect_grid[i][2].position = sf::Vector2f(
                    {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
                rect_vrt_i ++;

                rect_x[rect_vrt_i] -= rect_speed_list[i];
                rect_y[rect_vrt_i] += rect_speed_list[i] / 2;
                rect_grid[i][3].position = sf::Vector2f(
                    {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
                rect_vrt_i ++;

                rect_x[rect_vrt_i] -= rect_speed_list[i];
                rect_y[rect_vrt_i] -= rect_speed_list[i] / 2;
                rect_grid[i][4].position = sf::Vector2f(
                    {rect_x[rect_vrt_i], rect_y[rect_vrt_i]});
                rect_vrt_i ++;

            }

            // Particles
            for(int i{}; i < p_count; i++){
                particle_velocity[i] *= 1.001f;
                particle_position[i] += particle_velocity[i];
                particles[i].position = particle_position[i];
                
                p_reset = false;
                if(particle_position[i].y <= 0 || particle_position[i].y >= win_height){
                    p_reset = true;
                }
                if(particle_position[i].x <= 0 || particle_position[i].x >= win_width){
                    p_reset = true;
                }
                if(p_reset){
                    // particle_life_left[i] = p_lifetime;
                    particle_velocity[i] = sf::Vector2f(
                        {(getRandom(-1, 1) / 100), (getRandom(-1, 1) / 100)});
                    particle_position[i] = sf::Vector2f(
                        {win_width / 2, win_height / 2});
                }
    
            }

                // background_angle += 0.1;
                // background_sprite.setRotation(sf::degrees(background_angle));
            
        }

        // Check all window events that were triggeres since last loop/frame
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                // User closes window on window close request
                window.close();

            }
            else if(const auto *key_pressed = event->getIf<sf::Event::KeyPressed>()){ //if any other key event
                // User presses Escape key
                if(key_pressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                }
                else if(key_pressed->scancode == sf::Keyboard::Scancode::Q){
                    window.close();
                }
                else if(key_pressed->scancode == sf::Keyboard::Scancode::P){
                    if(pause) pause = false;
                    else pause = true;
                }
                else if(key_pressed->scancode == sf::Keyboard::Scancode::A){
                    if(additional) additional = false;
                    else additional = true;
                }
            }
            // else if (const auto *resized = event->getIf<sf::Event::Resized>()){
            //     glViewport(0, 0, resized->size.x, resized->size.y);
            // }
        }
        

        // draw
        if(!pause){
            window.draw(background_sprite, &shader);
            window.draw(particles);

            for(auto rect : rect_grid){ //tunnel
                window.draw(rect);
            }

            window.draw(fps_text);

            window.draw(triangle);
            window.draw(text);
            window.draw(polygonal);
            window.draw(line_vert);
            window.draw(line_horz);

            // render
            // renderTexture.display(); //render renderTexture
            // sf::Sprite finalSprite(renderTexture.getTexture()); //render texture to sprite
            // window.draw(finalSprite); //draw sprite to window
            window.display();
        }
    }
}

