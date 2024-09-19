#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Atom.hpp"
#include "Space_Partitioning.hpp"

class Sim
{
public:
    Sim();
    ~Sim();

    // window related functions
    void createWindow(int width, int height, const std::string &title);
    void clearWindow();
    void displayWindow();
    bool isWindowOpen() const;
    void closeWindow();
    bool pollEvent(sf::Event &event);

    // Test Atom functions
    void intializeTwoTestAtoms();
    void intializeMultipleTestAtoms(int n);
    void intializeMultipleColoredTestAtoms(int n, int c);
    void drawTestAtoms();
    void updateVelocity();
    void updateAtoms();

    sf::Vector2f calculatePeriodicDistance(const sf::Vector2f &pos1, const sf::Vector2f &pos2, const sf::Vector2f &bounds);
    void applyPeriodicBoundaryConditions(sf::Vector2f &position, const sf::Vector2f &bounds);
    void randomizeParticles();
    // variables
    sf::RenderWindow window;

    std::vector<TestAtom> atoms;

    void drawGrid()
    {
        grid.draw(window);
    }

private:
    UniformGrid grid;

    void updateGrid()
    {
        grid.clear();
        for (size_t i = 0; i < atoms.size(); ++i)
        {
            grid.insertParticle(i, atoms[i].position);
        }
    }
};