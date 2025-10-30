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
    std::stack<std::unique_ptr<state>> states;

public:
    stateManeger();
    void pushState(std::unique_ptr<state> newState);
    void popState();
    state* getCurrentState();

    void start();
    void levelState();
};

class state {
public:

    state() = default;
    virtual ~state() = default; // virtuele destructor is cruciaal
};

class menuState : public state {
private:
    std::shared_ptr<state> currentState;
    public:
    menuState();
};

class LevelState : public state {

public:
    LevelState();
};


#endif //PACKMAN_STATEMANEGER_H