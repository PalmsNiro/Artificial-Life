#include "Simulation.hpp"
#include "config.hpp"
#include <iostream>

using namespace Screen_Config;

int main()
{
    Sim sim;
    // Particle creation stuff
    sim.intializeMultipleColoredTestAtoms(300, m);
    sim.createWindow(screen_width, screen_height, "Test");
    std::cout << "atoms empty?" << (sim.atoms.empty() ? "yes" : "no") << std::endl;
    std::cout << "atom size: " << sim.atoms.size() << std::endl;
    printColorForceMatrix(matrix, colorVector);

    // Create Grid here later, ig?!
    bool showGrid = false;

    // Main loop and event handeling
    while (sim.isWindowOpen())
    {
        for (auto event = sf::Event{}; sim.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                sim.closeWindow();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    sim.closeWindow();
                }
                else if (event.key.code == sf::Keyboard::R)
                {
                    sim.randomizeParticles();
                    printColorForceMatrix(matrix, colorVector);
                }
                else if (event.key.code == sf::Keyboard::G)
                {
                    showGrid = !showGrid;
                }
            }
        }

        sim.clearWindow();

        if (showGrid)
            sim.drawGrid();

        sim.drawTestAtoms();
        sim.updateAtoms();

        sim.displayWindow();
    }
}