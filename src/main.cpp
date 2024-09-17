// #include <SFML/Graphics.hpp>
#include "Simulation.hpp"
#include "config.hpp"
#include <iostream>

using namespace Screen_Config;

int main()
{
    Sim sim;
    // sim.intializeMultipleTestAtoms(n);
    sim.intializeMultipleColoredTestAtoms(300, 5);
    std::cout << "atoms empty?" << (sim.atoms.empty() ? "yes" : "no") << std::endl;
    std::cout << "atom size: " << sim.atoms.size() << std::endl;
    sim.createWindow(screen_width, screen_height, "Test");

    while (sim.isWindowOpen())
    {
        for (auto event = sf::Event{}; sim.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                sim.closeWindow();
            }
        }

        sim.clearWindow();

        sim.drawTestAtoms();
        sim.updateAtoms();

        sim.displayWindow();
    }
}
