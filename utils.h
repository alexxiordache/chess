#pragma once

#include <stdio.h>
#include <SFML/Graphics.hpp>

const float WINDOW_W = 1200.0f;
const float WINDOW_H = 1200.0f;
const float PADDING = 10.0f;
const float SQUARE_SIZE = 100.0f;

sf::RectangleShape DrawRectangle(sf::RenderWindow& window, float size_x, float size_y, float pos_x, float pos_y, 
    sf::Color color, float outline_thickness = 0.0f, sf::Color outline_color = sf::Color::Transparent) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(size_x, size_y));
    rect.setPosition(sf::Vector2f(pos_x, pos_y)); 
    rect.setFillColor(color); 
    rect.setOutlineThickness(outline_thickness);
    rect.setOutlineColor(outline_color);
    window.draw(rect);
    return rect;
}

void DrawBoard(sf::RenderWindow& window) {
    float x, y = (WINDOW_H - 8*SQUARE_SIZE) / 2;
    bool current_color = 0;
    for(int i = 0; i < 8; i++) {
        x = (WINDOW_W - 8*SQUARE_SIZE) / 2;
        current_color ^= 1;
        for(int j = 0; j < 8; j++) {
            if(!current_color)
                DrawRectangle(window, SQUARE_SIZE, SQUARE_SIZE, x, y, sf::Color::White);
            else 
                DrawRectangle(window, SQUARE_SIZE, SQUARE_SIZE, x, y, sf::Color::Black);
            current_color ^= 1;
            x += SQUARE_SIZE;
        }
        y += SQUARE_SIZE;

    }
    

    // sf::Text path_text(font, path_display, FONT_SIZE);
    // path_text.setPosition(sf::Vector2f(x + 5.0f, y + 5.0f));
    // path_text.setFillColor(sf::Color::Black); 
    // window.draw(path_text);

}