cmake_minimum_required(VERSION 3.31)
project(conways_upgrade)

set(CMAKE_CXX_STANDARD 20)

include_directories(SYSTEM /opt/homebrew/include)

set(SFML_ROOT "/opt/homebrew")
#set(CMAKE_EXE_LINKER_FLAGS "-L${SFML_ROOT}/lib")
set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.0_1/lib/cmake/SFML/SFMLConfig.cmake")


find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_executable(conways_upgrade main.cpp)

#target_link_libraries(conways_upgrade sfml-graphics sfml-window sfml-system)
target_link_libraries(conways_upgrade
        "/opt/homebrew/lib/libsfml-graphics.dylib"
        "/opt/homebrew/lib/libsfml-window.dylib"
        "/opt/homebrew/lib/libsfml-system.dylib"
)

# Allow uninitialized sf::Event (SFML expects this)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-uninitialized -Wno-missing-field-initializers")

#clang++ -Wall -std=c++11 -g main.cpp -o main -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system
