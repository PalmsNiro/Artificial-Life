#pragma once

#include <vector>
#include <random>
#include <ctime>
#include <math.h>
#include <SFML/Graphics.hpp>

namespace Screen_Config
{
    extern int screen_width;
    extern int screen_height;
}

std::vector<std::vector<float>> generate2DRandomArray(int m);

extern const int n;
extern const float dt;
extern const float frictionHalfLife;
extern const float rMax;
extern const int m;
extern std::vector<std::vector<float>> matrix;
extern const float forceFactor;
extern const float frictionFactor;

// Inline-Funktion kann in der Header-Datei definiert werden
inline float force(float r, float a)
{
    const float beta = 0.3f;
    if (r < beta)
        return r / beta - 1;
    else if (beta < r && r < 1)
        return a * (1 - abs(2 * r - 1 - beta) / (1 - beta));
    else
        return 0;
}

extern const std::vector<sf::Color> colorVector;