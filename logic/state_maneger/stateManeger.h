//
// Created by niels on 10/30/25.
//

#ifndef PACKMAN_STATEMANEGER_H
#define PACKMAN_STATEMANEGER_H
#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include "../camera.h"

class world;
class state;

/**
 * class stateManeger
 * brief Manages the different states of the game (menu, level, pause, etc.).
 */
class stateManeger {
private:
    std::stack<std::unique_ptr<state>> stack;

public:
    stateManeger();
    void pushState(std::unique_ptr<state> newState);
    void prevState();
    std::unique_ptr<state> getCurrentState();

    void runTop(sf::RenderWindow& window, sf::Event& event,const camera& cam,world& wereld);
};

/**
 * class state
 * brief Abstract base class for different game states.
 */
class state {
public:

    state() = default;
    virtual ~state() = default;

    virtual void run(sf::RenderWindow& window, sf::Event& event,stateManeger& manager,const camera& cam, world& wereld) = 0;
};

/**
 * class menuState
 * brief Represents the menu state of the game.
 */
class menuState : public state {
public:
    menuState() = default;
    void run(sf::RenderWindow& window, sf::Event& event,stateManeger& manager,const camera& cam, world& wereld) override;
};

/**
 * class LevelState
 * brief Represents the level state of the game.
 */
class LevelState : public state {

public:
    LevelState(world& wereld);
    void run(sf::RenderWindow &window, sf::Event &event, stateManeger &manager,const camera& cam,world& wereld) override;
};


#endif //PACKMAN_STATEMANEGER_H