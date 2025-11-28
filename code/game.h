//
// Created by niels on 10/30/25.
//

#ifndef PACKMAN_GAME_H
#define PACKMAN_GAME_H
#include <SFML/Graphics.hpp>
#include "camera.h"
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

#include "observer.h"
#include "logic/state_maneger/stateManeger.h"
#include "world.h"
#include "Stopwatch.h"
#include "view/worldView.h"


class game {
public:
    game();
    void playGame();

};


#endif //PACKMAN_GAME_H