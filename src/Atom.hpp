#pragma once

#include <SFML/Graphics.hpp>

struct TestAtom
{
    sf::Vector2f position;
    float radius = 2.0f;
    sf::Vector2f velocity = {0.0f, 0.0f};
    sf::Color color;
    int colorIndex; 

    TestAtom(sf::Vector2f pos, sf::Color col, int colInd) 
        : position(pos), color(col), colorIndex(colInd) {}
};