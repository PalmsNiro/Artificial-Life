#include "config.hpp"
// #include <cmath>
#include <iostream>
#include <iomanip>

namespace Screen_Config
{
    int screen_width = 1900;
    int screen_height = 1000;
}

std::vector<std::vector<float>> generate2DRandomArray(int m)
{
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<float> dis(-5.0f, 5.0f);

    std::vector<std::vector<float>> array(m, std::vector<float>(m));

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            array[i][j] = dis(gen);
        }
    }
    // array[0][0] = 7;
    return array;
}

const int n = 400;
const float dt = 0.02f; // 1 / 144; // alternativ auch versuchen: 0.02f
const float frictionHalfLife = 0.040f;
const float rMax = 70.0f;
const int m = 5;                                                   // number of colors / should be same as sie of colorVector
std::vector<std::vector<float>> matrix = generate2DRandomArray(m); // matrix for color force relationships
const float forceFactor = 10.0f;
const float frictionFactor = std::pow(0.5f, dt / frictionHalfLife);

const std::vector<sf::Color> colorVector = {
    sf::Color(255, 0, 0),   // Rot
    sf::Color(0, 255, 0),   // Grün
    sf::Color(0, 0, 255),   // Blau
    sf::Color(255, 255, 0), // Gelb
    sf::Color(128, 0, 128)  // Lila
};

void printColorForceMatrix(const std::vector<std::vector<float>> &matrix, const std::vector<sf::Color> &colors)
{
    const int m = matrix.size();
    const int cellWidth = 10; // Width of each cell in the output

    // Print separator
    std::cout << std::string(cellWidth * (m + 1), '-') << "\n";

    // Print header
    std::cout << std::setw(cellWidth) << "Color";
    for (int i = 0; i < m; ++i)
    {
        std::cout << std::setw(cellWidth) << "Color " + std::to_string(i);
    }
    std::cout << "\n";

    // Print separator
    std::cout << std::string(cellWidth * (m + 1), '-') << "\n";

    // Print matrix rows
    for (int i = 0; i < m; ++i)
    {
        // Print row header (color name or index)
        std::cout << std::setw(cellWidth) << ("Color " + std::to_string(i));

        // Print row values
        for (int j = 0; j < m; ++j)
        {
            std::cout << std::setw(cellWidth) << std::fixed << std::setprecision(2) << matrix[i][j];
        }
        std::cout << "\n";
    }

    // Print color information
    std::cout << "\nColor Information:\n";
    for (int i = 0; i < m; ++i)
    {
        std::cout << "Color " << i << ": RGB("
                  << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << ")\n";
    }

    // Print separator
    std::cout << std::string(cellWidth * (m + 1), '-') << "\n";
}