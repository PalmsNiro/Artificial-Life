#include <iostream>
#include "Simulation.hpp"
#include "config.hpp"

Sim::Sim() {};
Sim::~Sim() {};

void Sim::createWindow(int width, int height, const std::string &title)
{
    window.create(sf::VideoMode(width, height), title);
    window.setFramerateLimit(144);
}

void Sim::clearWindow()
{
    window.clear(sf::Color::Black);
}

void Sim::displayWindow()
{
    window.display();
}

bool Sim::isWindowOpen() const
{
    return window.isOpen();
}

void Sim::closeWindow()
{
    window.close();
}

bool Sim::pollEvent(sf::Event &event)
{
    return window.pollEvent(event);
}

void Sim::intializeTwoTestAtoms()
{
    TestAtom atom1(sf::Vector2f(100.0f, 100.0f), sf::Color::Red, 0);
    TestAtom atom2(sf::Vector2f(110.0f, 110.0f), sf::Color::Red, 0);

    atoms.push_back(atom1);
    atoms.push_back(atom2);
}

void Sim::intializeMultipleTestAtoms(int n)
{
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<float> disW(0.0f, 1900.0f);
    std::uniform_real_distribution<float> disH(0.0f, 1000.0f);
    for (int i = 0; i < n; i++)
    {
        float posX = disW(gen);
        float posY = disH(gen);
        atoms.push_back(TestAtom(sf::Vector2f(posX, posY), sf::Color::Red, 0));
    }
}

void Sim::intializeMultipleColoredTestAtoms(int n, int c)
{
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<float> disW(0.0f, 1900.0f);
    std::uniform_real_distribution<float> disH(0.0f, 1000.0f);

    for (int i = 0; i < c; i++) // colors
    {
        // std::cout << "Color index: " << i << ", Color: ("
        //           << static_cast<int>(colorVector[i].r) << ", "
        //           << static_cast<int>(colorVector[i].g) << ", "
        //           << static_cast<int>(colorVector[i].b) << ")" << std::endl;

        for (int j = 0; j < n; j++) // number of Atoms
        {
            float posX = disW(gen);
            float posY = disH(gen);
            atoms.push_back(TestAtom(sf::Vector2f(posX, posY), colorVector[i], i));

            // if (j == 0)
            // { // Print info for the first atom of each color
            //     std::cout << "  First atom position: (" << posX << ", " << posY
            //               << "), Color index: " << i << std::endl;
            // }
        }
    }
}

void Sim::drawTestAtoms()
{
    for (const auto &at : atoms)
    {
        // std::cout << "atom color: " << at.color.toInteger() << std::endl;
        sf::CircleShape circle(at.radius);
        circle.setPosition(at.position);
        circle.setFillColor(at.color);
        window.draw(circle);
    }
}

void Sim::updateVelocity()
{
    sf::Vector2f bounds(Screen_Config::screen_width, Screen_Config::screen_height);

    for (auto &at1 : atoms)
    {
        sf::Vector2f totalForce(0, 0);
        for (auto &at2 : atoms)
        {
            if (&at1 == &at2)
                continue;
            sf::Vector2f diff = calculatePeriodicDistance(at1.position, at2.position, bounds);
            float r = hypot(diff.x, diff.y);
            if (r > 0 && r < rMax)
            {
                float f = force(r / rMax, matrix[at1.colorIndex][at2.colorIndex]);
                totalForce += diff / r * f;
            }
        }

        totalForce *= rMax * forceFactor;

        at1.velocity *= frictionFactor;
        at1.velocity += totalForce * dt;
    }
}

void Sim::updateAtoms()
{
    sf::Vector2f bounds(Screen_Config::screen_width, Screen_Config::screen_height);

    // update velocities
    updateVelocity();

    // update positions
    for (auto &at : atoms)
    {
        at.position += at.velocity * dt;
        applyPeriodicBoundaryConditions(at.position, bounds);
    }
}

sf::Vector2f Sim::calculatePeriodicDistance(const sf::Vector2f &pos1, const sf::Vector2f &pos2, const sf::Vector2f &bounds)
{
    sf::Vector2f diff = pos2 - pos1;

    // X-axis
    if (diff.x > bounds.x / 2)
    {
        diff.x -= bounds.x;
    }
    else if (diff.x < -bounds.x / 2)
    {
        diff.x += bounds.x;
    }

    // Y-axis
    if (diff.y > bounds.y / 2)
    {
        diff.y -= bounds.y;
    }
    else if (diff.y < -bounds.y / 2)
    {
        diff.y += bounds.y;
    }

    return diff;
}

void Sim::applyPeriodicBoundaryConditions(sf::Vector2f &position, const sf::Vector2f &bounds)
{
    position.x = fmod(position.x + bounds.x, bounds.x);
    position.y = fmod(position.y + bounds.y, bounds.y);
}

void Sim::randomizeParticles()
{
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<float> disW(0.0f, 1900.0f);
    std::uniform_real_distribution<float> disH(0.0f, 1000.0f);
    matrix = generate2DRandomArray(m);
    for (auto &at : atoms)
    {
        at.position = {disW(gen), disH(gen)};
        at.velocity = {0, 0};
    }
}