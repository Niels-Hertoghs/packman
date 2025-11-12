#include <iostream>
#include <memory>
#include "code/game.h"

int main() {
    std::unique_ptr<game> Game(new game);
    Game->playGame();
    return 0;
};
