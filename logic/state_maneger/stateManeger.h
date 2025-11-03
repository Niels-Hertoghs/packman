//
// Created by niels on 10/30/25.
//

#ifndef PACKMAN_STATEMANEGER_H
#define PACKMAN_STATEMANEGER_H
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

class state;

class stateManeger {
private:
    std::stack<std::unique_ptr<state>> stack;

public:
    stateManeger();
    void pushState(std::unique_ptr<state> newState);
    void prevState();
    std::unique_ptr<state> getCurrentState();

    void runTop(sf::RenderWindow& window, sf::Event& event);
};

class state {
public:

    state() = default;
    virtual ~state() = default;

    virtual void run(sf::RenderWindow& window, sf::Event& event,stateManeger& manager) = 0;
};

class menuState : public state {
public:
    menuState() = default;
    void run(sf::RenderWindow& window, sf::Event& event,stateManeger& manager) override;
};

class LevelState : public state {

public:
    LevelState() = default;
    void run(sf::RenderWindow &window, sf::Event &event, stateManeger &manager) override;
};


#endif //PACKMAN_STATEMANEGER_H