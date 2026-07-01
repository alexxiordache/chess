#include "utils.h"



int main() {
    sf::VideoMode video_mode;
    video_mode.size = sf::Vector2u((unsigned int)WINDOW_W, (unsigned int)WINDOW_H);
    sf::RenderWindow window(video_mode, "Chess", sf::Style::Close);
    InitBoard(window);
     while(window.isOpen()) {
        window.clear(sf::Color(78, 140, 78)); 

        DrawBoard(window);
        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.display();
    }
}