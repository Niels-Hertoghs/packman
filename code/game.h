//
// Created by niels on 10/30/25.
//

#ifndef PACKMAN_GAME_H
#define PACKMAN_GAME_H
#include <SFML/Graphics.hpp>
#include "view/camera.h"
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

#include "observer.h"
#include "view/state_maneger/stateManeger.h"
#include "logic/world.h"
#include "logic/Stopwatch.h"
#include "view/worldView.h"


class game {
public:
    game();
    void playGame();

};


#endif //PACKMAN_GAME_H