//
// Created by niels on 11/5/25.
//

#include "world.h"
#include <fstream>
#include <iostream>
#include "Stopwatch.h"

namespace logic {


world::world(const std::string& inputFile2) {
    try {
        std::ifstream file(inputFile2);
        if (!file.is_open()) {
            throw std::runtime_error("Bestand bestaat niet: " + inputFile2);
        }
        inputFile = inputFile2;
    } catch (const std::exception& e) {
        std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
        throw;
    }
}

void world::startWorld(int level) {
    std::ifstream file(inputFile); // bestand openen

    // bij level 1 is het eten van een ghost 100 punten waart, daarna 50 punten er bij voor elk level
    int ghostPoints = 90 + (50 * level);
    // speed = 1 en plus 0.25 voor elke hoger level
                // speed is iets trager dan pacman, elke hoger level wordt er 0.5 bij de speed gedaan
    const float ghostSpeed = 0.75f + level * 0.25f;
    const float pacmanSpeed = 1.f + level * 0.25f;
    const int coinPoints = 30 + (10 * level);
    const int fruitPoints = 40 + (10 * level);


    std::unique_ptr<ConcreteLogicFactory> factory = std::make_unique<ConcreteLogicFactory>();

    std::string line;
    double y = 1.0 - 2.0 / 7.0;
    while (std::getline(file, line)) {
        double x = -1.0;
        for (char c : line) {
            switch (c) {
            case '#':
                walls.push_back(factory->createWall(x, y));
                break;
            case '-':
                // points staat op 40 om te beginnen, daarna 10 extra per level
                collectables.push_back(factory->createCollectable(collectableTypes::COIN,x,y,coinPoints));
                break;
            case '_':
                invisibleWalls.push_back(factory->createInvisibleWall(x,y));
                break;
            case 'f':
                // points staan op 50 om te beginne, is meer dan coins, daarna 10 extra per level
                collectables.push_back(factory->createCollectable(collectableTypes::FRUIT,x,y,fruitPoints));
                break;
            case 'p':
                //pacman aanmaken, origin = midpunt
                pacman = factory->createPacman(x,y,pacmanSpeed);
                break;
            case 'r':
                ghosts.push_back(factory->createGhost(ghostTypes::RED,x,y,ghostSpeed,ghostPoints));
                break;
            case 'g':
                ghosts.push_back(factory->createGhost(ghostTypes::GREEN,x,y,ghostSpeed,ghostPoints));
                break;
            case 'b':
                ghosts.push_back(factory->createGhost(ghostTypes::BLUE,x,y,ghostSpeed,ghostPoints));
                break;
            case 'a':
                ghosts.push_back(factory->createGhost(ghostTypes::ORANGE,x,y,ghostSpeed,ghostPoints));
                break;
            default:
                break;
            }
            x += 0.1;
        }
        y -= 1.0 / 7.0;
    }

    for (const std::shared_ptr<Ghost>& ghost : ghosts) {
        ghost->givePacman(pacman);
    }

    for (const std::shared_ptr<collectable>& collectable : collectables) {
        collectable->subscribeScore(score);
    }
}

void world::update(float deltaTime) {
    // pacman updaten, oa de locatie
    std::vector<std::shared_ptr<entity> > allWalls;
    allWalls.insert(allWalls.end(), walls.begin(), walls.end());
    allWalls.insert(allWalls.end(), invisibleWalls.begin(), invisibleWalls.end());

    pacman->update(deltaTime, allWalls);


    for (std::shared_ptr<Ghost>& ghost : ghosts) {
        if (ghost->hadFirstCollision()) {
            ghost->update(deltaTime, allWalls);
        } else {
            std::vector<std::shared_ptr<entity> > w;
            w.insert(w.end(), walls.begin(), walls.end());
            ghost->update(deltaTime, w);
        }
    }

    // zien of pacman niet op een collectable staat
    for (auto it = collectables.begin(); it != collectables.end();) {
        if (pacman->standsOnCoin(*it)) {
            if (it->get()->collected()) {
                startFearMode();
            }
            it = collectables.erase(it); // erase retourneert de volgende iterator
        } else {
            ++it;
        }
    }

    for (std::shared_ptr<Ghost>& ghost : ghosts) {
        if (pacman->standsOnGhost(ghost)) {
            if (ghost->get_mode() == modes::CHASING_MODE) {
                died();
            } else if (ghost->get_mode() == modes::FEAR_MODE) {
                ghost->died();
                score->GhostEaten(ghost->getGhostPoints());
            }
        }
    }

    if (collectables.empty()) {
        score->nextLevel();
        return;
    }

    for (const std::shared_ptr<Ghost>& ghost : ghosts) {
        if (ghost->get_mode() == modes::FEAR_MODE && Stopwatch::getInstance()->isFearDone(score->getLevel())) {
            // kan eender welke ghost zijn
            ghost->startChaseMode();
        }
    }
}

void world::died() const {
    score->liveLost();
    for (const std::shared_ptr<Ghost>& ghost : ghosts) {
        ghost->died();
    }
    pacman->died();
    Stopwatch::getInstance()->reset();
}


void world::updatePacmanDir(directions dir) const {
    pacman->updateDir(dir);
}

void world::subscribeScore(const std::shared_ptr<logic::Score>& _score) {
    score = _score;
    for (const std::shared_ptr<collectable>& collectable : collectables) {
        collectable->subscribeScore(_score);
    }
}

std::vector<std::shared_ptr<wall> > world::get_walls() const {
    return walls;
}

std::vector<std::shared_ptr<collectable> > world::get_collectables() const {
    return collectables;
}

std::shared_ptr<Pacman> world::get_pacman() const {
    return pacman;
}

std::shared_ptr<Score> world::get_score() const {
    return score;
}

std::vector<std::shared_ptr<Ghost>> world::get_ghosts() const {
    return ghosts;
}

void world::clear() {
    walls.clear();
    collectables.clear();
    invisibleWalls.clear();
}

void world::startFearMode() const {

    for (const std::shared_ptr<Ghost>& ghost : ghosts) {
        ghost->startFearMode();
    }
    Stopwatch::getInstance()->startFearMode();
}


}
