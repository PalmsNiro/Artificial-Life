#include "Simulation.hpp"

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

void Sim::intializeTestAtoms()
{
    Atom atom1(sf::Vector2f(100.0f, 100.0f), sf::Color::Red);
    Atom atom2(sf::Vector2f(150.0f, 150.0f), sf::Color::Red);

    atoms.push_back(atom1);
    atoms.push_back(atom2);
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