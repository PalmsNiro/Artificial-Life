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

    void draw(sf::RenderWindow &window) const
    {
        sf::Color gridColor(100, 100, 200); // Halbtransparentes Grau

        // Vertikale Linien
        for (int x = 0; x <= gridWidth; ++x)
        {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x * cellSize, 0), gridColor),
                sf::Vertex(sf::Vector2f(x * cellSize, Screen_Config::screen_height), gridColor)};
            window.draw(line, 2, sf::Lines);
        }

        // Horizontale Linien
        for (int y = 0; y <= gridHeight; ++y)
        {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(0, y * cellSize), gridColor),
                sf::Vertex(sf::Vector2f(Screen_Config::screen_width, y * cellSize), gridColor)};
            window.draw(line, 2, sf::Lines);
        }

        // Optional: Zeichne die Anzahl der Partikel in jeder Zelle
        // sf::Font font;
        // if (font.loadFromFile("path/to/your/font.ttf"))
        // { // Stellen Sie sicher, dass Sie einen gültigen Pfad zu einer Schriftart angeben
        //     for (int y = 0; y < gridHeight; ++y)
        //     {
        //         for (int x = 0; x < gridWidth; ++x)
        //         {
        //             int index = y * gridWidth + x;
        //             int count = grid[index].size();
        //             if (count > 0)
        //             {
        //                 sf::Text text(std::to_string(count), font, 10);
        //                 text.setPosition(x * cellSize + 2, y * cellSize + 2);
        //                 text.setFillColor(sf::Color::White);
        //                 window.draw(text);
        //             }
        //         }
        //     }
        // }
    }
};