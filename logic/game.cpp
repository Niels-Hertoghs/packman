//
// Created by niels on 10/30/25.
//

#include "game.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "state_maneger/stateManeger.h"

game::game() {

}

void game::playGame() {
    stateManeger manager;
    manager.start();
    manager.levelState();
}