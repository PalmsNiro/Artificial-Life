// #include <SFML/Graphics.hpp>
#include "Simulation.hpp"
#include "config.hpp"

using namespace Screen_Config; 

int main()
{
    Sim sim;
    sim.intializeMultipleTestAtoms(n);
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
        sim.updateTestAtoms();

        sim.displayWindow();
    }
}
