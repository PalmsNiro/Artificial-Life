#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "config.hpp"

// class SpacePar
// {
// public:
//     SpacePar();

//     void createGrid(int screen_width, int screen_height);
// };

class UniformGrid
{
private:
    float cellSize;
    int gridWidth, gridHeight;
    std::vector<std::vector<int>> grid;

    sf::Vector2i positionToCell(const sf::Vector2f &position) const
    {
        return sf::Vector2i(static_cast<int>(position.x / cellSize),
                            static_cast<int>(position.y / cellSize));
    }

public:
    UniformGrid(float cellSize)
        : cellSize(cellSize),
          gridWidth(static_cast<int>(Screen_Config::screen_width / cellSize) + 1),
          gridHeight(static_cast<int>(Screen_Config::screen_height / cellSize) + 1),
          grid(gridWidth * gridHeight) {}

    void insertParticle(int particleIndex, const sf::Vector2f &position)
    {
        sf::Vector2i cell = positionToCell(position);
        grid[cell.y * gridWidth + cell.x].push_back(particleIndex);
    }

    void clear()
    {
        for (auto &cell : grid)
        {
            cell.clear();
        }
    }

    std::vector<int> getNeighbors(const sf::Vector2f &position) const
    {
        std::vector<int> neighbors;
        sf::Vector2i cell = positionToCell(position);

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                int nx = cell.x + dx;
                int ny = cell.y + dy;

                if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight)
                {
                    const auto &cellParticles = grid[ny * gridWidth + nx];
                    neighbors.insert(neighbors.end(), cellParticles.begin(), cellParticles.end());
                }
            }
        }

        return neighbors;
    }
};