#pragma once

#include <SFML/Graphics.hpp>

struct TestAtom
{
    sf::Vector2f position;
    float radius = 4.0f;
    sf::Vector2f velocity = {0.0f, 0.0f};
    sf::Color color;
    int colorIndex =0; 

    TestAtom(sf::Vector2f pos, sf::Color col) 
        : position(pos), color(col) {}
};


