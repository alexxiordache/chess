#pragma once

#include <bits/stdc++.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Piece.h"

const float WINDOW_W = 1200.0f;
const float WINDOW_H = 1200.0f;
const float PADDING = 10.0f;
const float SQUARE_SIZE = 100.0f;

sf::Texture WhitePawn::texture;
sf::Texture BlackPawn::texture;
using namespace std;

class ButtonData {
    protected:
        sf::RectangleShape shape;
        string name;
        bool pressed = false;
    public:
        ButtonData() = default;
        void setShape(sf::RectangleShape &s) {
            shape = s;
        }
        void setName(std::string s) {
            name = s;
        }
        void toggle() {
            pressed ^= 1;
        }
        sf::RectangleShape& getShape() {
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
        Piece* piece;
    public:
        BoardSquare() {
            piece = nullptr;
        }
        void init(sf::RectangleShape s, bool c) {
            shape = s; 
            color = c;
        }
        void setPiece(Piece* p) {
            piece = p;
            if (piece) {
                float pieceWidth = piece->getSprite().getGlobalBounds().size.x;
                float pieceHeight = piece->getSprite().getGlobalBounds().size.y;

                float x = shape.getPosition().x + (SQUARE_SIZE - pieceWidth) / 2.0f;
                float y = shape.getPosition().y + (SQUARE_SIZE - pieceHeight) / 2.0f;

                piece->setPosition(x, y);
            }
        }

        Piece* getPiece() {
            return piece;
        }
};

BoardSquare board[9][9];

sf::RectangleShape CreateRect(float size_x, float size_y, float pos_x, float pos_y, 
    sf::Color color, float outline_thickness = 0.0f, sf::Color outline_color = sf::Color::Transparent) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(size_x, size_y));
    rect.setPosition(sf::Vector2f(pos_x, pos_y)); 
    rect.setFillColor(color); 
    rect.setOutlineThickness(outline_thickness);
    rect.setOutlineColor(outline_color);
    return rect;
}

void InitTextures() {
    WhitePawn::loadTexture();
    BlackPawn::loadTexture();
}

void InitBoard(sf::RenderWindow& window) {
    InitTextures();
    float x;
    float y = (WINDOW_H - 8 * SQUARE_SIZE) / 2;
    bool current_color = 0;
    
    for(int i = 8; i >= 1; i--) {
        x = (WINDOW_W - 8 * SQUARE_SIZE) / 2;
        current_color ^= 1;
        
        for(int j = 1; j <= 8; j++) {
            if(!current_color)
                board[i][j].init(CreateRect(SQUARE_SIZE, SQUARE_SIZE, x, y, sf::Color::White), false);
            else 
                board[i][j].init(CreateRect(SQUARE_SIZE, SQUARE_SIZE, x, y, sf::Color::Black), true);
            current_color ^= 1;
            x += SQUARE_SIZE;
        }
        y += SQUARE_SIZE;
    }
    for(int j = 1; j <= 8; j++) {
        float x = (WINDOW_W - 8 * SQUARE_SIZE) / 2 + (j-1) * SQUARE_SIZE, y = (WINDOW_H - 8 * SQUARE_SIZE) / 2 + SQUARE_SIZE;
        WhitePawn* p = new WhitePawn();
        // p -> setPosition(x, y);
        board[2][j].setPiece(p);
    }
}

void DrawBoard(sf::RenderWindow& window) {
    for(int i = 1; i <= 8; i++) 
        for(int j = 1; j <= 8; j++) 
            window.draw(board[i][j].getShape());
    for(int i = 1; i <= 8; i++) 
        for(int j = 1; j <= 8; j++)
            if (board[i][j].getPiece()) 
                window.draw(board[i][j].getPiece()->getSprite());
}