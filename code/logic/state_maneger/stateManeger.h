//
// Created by niels on 10/30/25.
//

#ifndef PACKMAN_STATEMANEGER_H
#define PACKMAN_STATEMANEGER_H
#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include "../../camera.h"
#include "../../Stopwatch.h"
#include "../../render/worldView.h"
#include "state.h"

namespace logic {
    class world;
}
class state;

/**
 * class stateManeger
 * brief Manages the different states of the game (menu, level, pause, etc.).
 */
class stateManeger {
private:
    std::stack<std::unique_ptr<view::state>> stack;

public:
    stateManeger();
    void pushState(std::unique_ptr<view::state> newState);
    void prevState();
    std::unique_ptr<view::state> getCurrentState();

    void runTop(sf::RenderWindow& window, sf::Event& event, camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime);
};




#endif //PACKMAN_STATEMANEGER_H