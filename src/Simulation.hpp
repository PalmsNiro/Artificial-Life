#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Atom.hpp"

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
    void intializeTestAtoms();
    void drawTestAtoms();
    void updateAtoms();

    // variables
    sf::RenderWindow window;
    std::vector<Atom> atoms;
};