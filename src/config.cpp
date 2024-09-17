#include "config.hpp"
#include <cmath>

namespace Screen_Config
{
    int screen_width = 1900;
    int screen_height = 1000;
}

std::vector<std::vector<float>> generate2DRandomArray(int m)
{
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<float> dis(-3.0f, 3.0f);

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
const int m = 6;                                                         // number of colors
const std::vector<std::vector<float>> matrix = generate2DRandomArray(m); // matrix for color force relationships
const float forceFactor = 10.0f;
const float frictionFactor = std::pow(0.5f, dt / frictionHalfLife);

const std::vector<sf::Color> colorVector = {
    sf::Color(255, 0, 0),   // Rot
    sf::Color(0, 255, 0),   // Grün
    sf::Color(0, 0, 255),   // Blau
    sf::Color(255, 255, 0), // Gelb
    sf::Color(128, 0, 128)  // Lila
};