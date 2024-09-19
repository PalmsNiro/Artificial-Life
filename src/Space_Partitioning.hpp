#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "config.hpp"

class UniformGrid
{
private:
    float cellSize;
    int gridWidth, gridHeight;
    std::vector<std::vector<int>> grid;

    sf::Vector2i positionToCell(const sf::Vector2f &position) const;

public:
    UniformGrid(float cellSize)
        : cellSize(cellSize),
          gridWidth(static_cast<int>(Screen_Config::screen_width / cellSize) + 1),
          gridHeight(static_cast<int>(Screen_Config::screen_height / cellSize) + 1),
          grid(gridWidth * gridHeight) {}

    void insertParticle(int particleIndex, const sf::Vector2f &position);

    void clear();

    std::vector<int> getNeighbors(const sf::Vector2f &position) const;

    void draw(sf::RenderWindow &window) const;
};