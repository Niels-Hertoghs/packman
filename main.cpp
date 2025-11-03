#include <iostream>
#include <memory>
#include "logic/game.h"

int main() {
    std::unique_ptr<game> Game(new game);
    Game->playGame();
    tewst;
    return 0;
};
