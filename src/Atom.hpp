#pragma once

#include <SFML/Graphics.hpp>

struct Atom
{
    sf::Vector2f position;
    float radius = 5.0f;
    sf::Vector2f velocity = {0.0f, 0.0f};
    sf::Color color;

    Atom(sf::Vector2f pos, sf::Color col) 
        : position(pos), color(col) {}
};


