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
    TestAtom atom1(sf::Vector2f(100.0f, 100.0f), sf::Color::Red);
    TestAtom atom2(sf::Vector2f(110.0f, 110.0f), sf::Color::Red);

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
        atoms.push_back(TestAtom(sf::Vector2f(posX, posY), sf::Color::Red));
    }
}

void Sim::drawTestAtoms()
{
    for (const auto &at : atoms)
    {
        sf::CircleShape circle(at.radius);
        circle.setPosition(at.position);
        circle.setFillColor(at.color);

        window.draw(circle);
    }
}

void Sim::updateTestAtoms()
{
    // update velocities

    for (auto &at1 : atoms)
    {
        float totalForceX = 0;
        float totalForceY = 0;
        for (auto &at2 : atoms)
        {
            if (&at1 == &at2)
                continue;
            const float rx = at2.position.x - at1.position.x;
            const float ry = at2.position.y - at1.position.y;
            const float r = hypot(rx, ry);
            if (r > 0 && r < rMax)
            {
                // std::cout << "calc force" << std::endl;
                const float f = force(r / rMax, matrix[at1.colorIndex][at2.colorIndex]);
                totalForceX += rx / r * f;
                totalForceY += ry / r * f;
                // std::cout << "total Force1 calculated: (" << totalForceX << "; " << totalForceY << ")" << std::endl;
            }
        }
        // std::cout << "total Force1 after if: (" << totalForceX << "; " << totalForceY << ")" << std::endl;
        // std::cout << "rMax and forceFactor: (" << rMax << "; " << forceFactor << ")" << std::endl;
        totalForceX *= rMax * forceFactor;
        totalForceY *= rMax * forceFactor;
        // std::cout << "total Force2 calculated: (" << totalForceX << "; " << totalForceY << ")" << std::endl;

        at1.velocity.x *= frictionFactor;
        at1.velocity.y *= frictionFactor;

        at1.velocity.x += totalForceX * dt;
        at1.velocity.y += totalForceY * dt;
        // std::cout << "velocity calculated: (" << at1.velocity.x << "; " << at1.velocity.y << ")" << std::endl;
    }

    // update positions
    for (auto &at : atoms)
    {
        // std::cout << "velocity: (" << at.velocity.x << "; " << at.velocity.y << ") " << std::endl;
        // std::cout << "position before: (" << at.position.x << "; " << at.position.y << ") ";
        at.position.x += at.velocity.x * dt;
        at.position.y += at.velocity.y * dt;
        // std::cout << "position after: (" << at.position.x << "; " << at.position.y << ")" << std::endl;
    }
}
