#pragma once

#include <stdio.h>
#include <SFML/Graphics.hpp>

const float WINDOW_W = 1200.0f;
const float WINDOW_H = 1200.0f;
const float PADDING = 10.0f;
const float SQUARE_SIZE = 100.0f;
using namespace std;

class ButtonData {
    protected:
        sf::RectangleShape shape;
        string name;
        bool pressed = false;
    public:
        void setShape(sf::RectangleShape &s) {
            shape = s;
        }
        void setName(std::string s) {
            name = s;
        }
        void toggle() {
            pressed ^= 1;
        }
        sf::RectangleShape getShape() const {
            return shape;
        }
        string GetName() const {
            return name;
        }
        bool isPressed() const {
            return pressed;
        }
        bool Update(const sf::Vector2f& mousePos) {
            bool actionTriggered = false; 
            if (shape.getGlobalBounds().contains(mousePos)) 
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    if (!isPressed()) 
                        actionTriggered = true;  
                    toggle();
                }
            return actionTriggered; 
        }
        virtual ~ButtonData() {};
};

class BoardSquare: public ButtonData {
    private:
        bool color; // 0 - white, 1 - black
        // Piece piece;
    public:
        void init(sf::RectangleShape s, bool c) {
            shape = s; 
            color = c;
        }
};

BoardSquare board[8][8];

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
                board[i][j].init(DrawRectangle(window, SQUARE_SIZE, SQUARE_SIZE, x, y, sf::Color::White), false);
            else 
                board[i][j].init(DrawRectangle(window, SQUARE_SIZE, SQUARE_SIZE, x, y, sf::Color::Black), true);
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