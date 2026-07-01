#pragma once
#include "utils.h"

class Piece {
private:
    bool isWhite;
    sf::Sprite sprite;
public:
    Piece(bool white, const sf::Texture& texture) : isWhite(white), sprite(texture) {}

    virtual void setPosition(float x, float y) {
        sprite.setPosition({x, y});
    }

    sf::Sprite& getSprite() {
        return sprite;
    }
    
    bool getColor() const {
        return isWhite;
    }
    virtual ~Piece() {}
};

class Pawn : public Piece {
public:
    Pawn(bool white, const sf::Texture& texture) : Piece(white, texture) {
    }
};

class WhitePawn : public Pawn {
private:
    static sf::Texture texture; 

public:
    WhitePawn() : Pawn(true, texture) {}
    static void loadTexture() {
        if (!texture.loadFromFile("pieces/pawn_white.png")) {
            printf("Eroare la incarcare pawn_white.png\n");
        }
    }
};

class BlackPawn : public Pawn {
private:
    static sf::Texture texture;
public:
    BlackPawn() : Pawn(false, texture) {}

    static void loadTexture() {
        if (!texture.loadFromFile("pieces/pawn_black.png")) {
            printf("Eroare la incarcare pawn_black.png\n");
        }
    }
};
