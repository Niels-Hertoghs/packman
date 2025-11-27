//
// Created by niels on 11/5/25.
//

#include "world.h"
#include <fstream>
#include <iostream>
#include <sstream>

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

        std::string line;
        double y = 1.0 - 2.0/7.0;
        while (std::getline(file, line)) {
            double x = -1.0;
            for (char c : line) {
                switch (c) {
                case '#':
                    walls.push_back(std::make_shared<wall>(x, y));
                    break;
                case '-':
                    // points staat op 40 om te beginnen, daarna 10 extra per level
                    collectables.push_back(std::make_shared<coin>(x + 1.f/20.f, y - 1.f/14.f, 40 + (level * 10)));
                    break;
                case '_' :
                    invisibleWalls.push_back(std::make_shared<invisibleWall>(x, y));
                    break;
                case 'f':
                    // points staan op 50 om te beginne, is meer dan coins, daarna 10 extra per level
                    collectables.push_back(std::make_shared<fruit>(x + 1.f/20.f, y - 1.f/14.f,50+ (level * 10)));
                    break;
                case 'p':
                    //pacman aanmaken, origin = midpunt
                        // speed = 1 en plus 0.5 voor elke hoger level
                    pacman = std::make_shared<Packman>(x + 1.f/20.f, y - 1.f/14.f, 1.f + (static_cast<float>(level) * 0.5f));
                    break;
                case 'r':
                        // speed is iets trager dan pacman, elke hoger level wordt er 0.5 bij de speed gedaan
                    _redGhost = std::make_shared<redGhost>(x + 1.f/20.f, y - 1.f/14.f,0.95f + (static_cast<float>(level) * 0.5f));
                    break;
                case 'g':
                        // speed is iets trager dan pacman, elke hoger level wordt er 0.5 bij de speed gedaan
                    _greenGhost = std::make_shared<greenGhost>(x + 1.f/20.f, y - 1.f/14.f,0.95f + (static_cast<float>(level) * 0.5f));
                    break;
                case 'b':
                        // speed is iets trager dan pacman, elke hoger level wordt er 0.5 bij de speed gedaan
                    _blueGhost = std::make_shared<blueGhost>(x + 1.f/20.f, y - 1.f/14.f,0.95f + (static_cast<float>(level) * 0.5f));
                    break;
                case 'a' :
                        // speed is iets trager dan pacman, elke hoger level wordt er 0.5 bij de speed gedaan
                    _orangeGhost = std::make_shared<orangeGhost>(x + 1.f/20.f, y - 1.f/14.f,0.95f + (static_cast<float>(level) * 0.5f));
                    break;
                default:
                    break;
                }
                x += 0.1;
            }
            y -= 1.0/7.0;
        }

        _blueGhost->givePacman(pacman);
        _greenGhost->givePacman(pacman);
        _orangeGhost->givePacman(pacman);
    }

    void world::update(float deltaTime) {
        // pacman updaten, oa de locatie
        std::vector<std::shared_ptr<entity>> allWalls;
        allWalls.insert(allWalls.end(),walls.begin(),walls.end());
        allWalls.insert(allWalls.end(),invisibleWalls.begin(),invisibleWalls.end());

        pacman->update(deltaTime,allWalls);


        std::vector<std::shared_ptr<Ghost>> ghosts = {
            _redGhost,
            _blueGhost,
            _greenGhost,
            _orangeGhost
        };

        for (std::shared_ptr<Ghost>& ghost : ghosts) {
            if (ghost->hadFirstCollision()) {
                ghost->update(deltaTime,allWalls);
            } else {
                std::vector<std::shared_ptr<entity>> w;
                w.insert(w.end(),walls.begin(),walls.end());
                ghost->update(deltaTime,w);
            }
        }

        // zien of pacman niet op een collectable staat
        for (auto it = collectables.begin(); it != collectables.end(); ) {
            if (pacman->standsOnCoin(*it)) {
                if (it->get()->collected()) {
                    startFearMode();
                }
                it = collectables.erase(it); // erase retourneert de volgende iterator
            } else {
                ++it;
            }
        }

        for (std::shared_ptr<Ghost>& ghost:ghosts) {
            if (pacman->standsOnGhost(ghost)) {
                died();
            }
        }

        if (collectables.empty()) {
            score->nextLevel();
        }
    }

    void world::died() const {
        score->liveLost();
        _redGhost->died();
        _blueGhost->died();
        _greenGhost->died();
        _orangeGhost->died();
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

    std::vector<std::shared_ptr<wall>> world::get_walls() const {
        return walls;
    }

    std::vector<std::shared_ptr<collectable>> world::get_collectables() const {
        return collectables;
    }

    std::shared_ptr<redGhost> world::get_red_ghost() const {
        return _redGhost;
    }

    std::shared_ptr<Packman> world::get_pacman() const {
        return pacman;
    }

    std::shared_ptr<Score> world::get_score() const {
        return score;
    }

    std::shared_ptr<blueGhost> world::get_blue_ghost() const {
        return _blueGhost;
    }

    std::shared_ptr<orangeGhost> world::get_orange_ghost() const {
        return _orangeGhost;
    }

    std::shared_ptr<greenGhost> world::get_green_ghost() const {
        return _greenGhost;
    }

    void world::clear() {
        walls.clear();
        collectables.clear();
        invisibleWalls.clear();
    }

    void world::startFearMode() {
        std::vector<std::shared_ptr<Ghost>> ghosts = {
            _redGhost,
            _blueGhost,
            _greenGhost,
            _orangeGhost
        };

        for (const std::shared_ptr<Ghost>& ghost : ghosts) {
            ghost->startFearMode();
        }
    }

}
