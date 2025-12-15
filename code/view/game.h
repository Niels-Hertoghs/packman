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
#include "state_maneger/stateManeger.h"
#include "../logic/world.h"
#include "../logic/Stopwatch.h"
#include "worldView.h"

namespace view {
/**
 * @class game
 * @brief De hoofdklasse voor het spel, start alles op, heeft de main loop.
 */
class game {
public:
    /**
     * @brief Constructor
     */
    game() = default;

    /**
     * @brief Start de main game loop, en blijft lopen tot het geeindigd wordt.
     */
    static void playGame();

};
}


#endif //PACKMAN_GAME_H