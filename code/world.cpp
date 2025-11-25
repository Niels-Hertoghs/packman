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

    void world::startWorld() {
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
                    // points staat op 40 om te beginne
                    coins.push_back(std::make_shared<coin>(x + 1.f/20.f, y - 1.f/14.f, 40));
                    break;
                case '_' :
                    invisibleWalls.push_back(std::make_shared<invisibleWall>(x, y));
                    break;
                case 'f':
                    // points staan op 50 om te beginne, is meer dan coins
                    fruits.push_back(std::make_shared<fruit>(x + 1.f/20.f, y - 1.f/14.f,50));
                    break;
                case 'p':
                    //pacman aanmaken, origin = midpunt
                    pacman = std::make_shared<Packman>(x + 1.f/20.f, y - 1.f/14.f);
                    break;
                case 'r':
                    _redGhost = std::make_shared<redGhost>(x + 1.f/20.f, y - 1.f/14.f);
                    break;
                case 'g':
                    _greenGhost = std::make_shared<greenGhost>(x + 1.f/20.f, y - 1.f/14.f);
                    break;
                case 'b':
                    _blueGhost = std::make_shared<blueGhost>(x + 1.f/20.f, y - 1.f/14.f);
                    break;
                case 'a' :
                    _purpleGhost = std::make_shared<purpleGhost>(x + 1.f/20.f, y - 1.f/14.f);
                    break;
                default:
                    continue;
                }
                x += 0.1;
            }
            y -= 1.0/7.0;
        }

        _blueGhost->givePacman(pacman);
        _greenGhost->givePacman(pacman);
        _purpleGhost->givePacman(pacman);
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
            _purpleGhost
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
        for (auto it = coins.begin(); it != coins.end(); ) {
            if (pacman->standsOnCoin(*it)) {
                it->get()->collected();
                score->coinEaten(it->get()->getPoints());
                it = coins.erase(it); // erase retourneert de volgende iterator
            } else {
                ++it;
            }
        }
        for (auto it = fruits.begin(); it != fruits.end(); ) {
            if (pacman->standsOnCoin(*it)) {
                it->get()->collected();
                score->coinEaten(it->get()->getPoints());
                it = fruits.erase(it); // erase retourneert de volgende iterator
            } else {
                ++it;
            }
        }
        std::shared_ptr<Ghost> r = _redGhost;
        if (pacman->standsOnGhost(_redGhost)) {
            died();
        }
        if (fruits.empty() && coins.empty()) {
            score->nextLevel();
            // nextLevel();
        }
    }

    void world::died() {
        score->liveLost();
        _redGhost->died();
        pacman->died();
    }


    void world::updatePacmanDir(directions dir) {
        pacman->updateDir(dir);
    }

    void world::subscribeScore(std::shared_ptr<logic::Score> _score) {
        score = _score;
    }

    std::vector<std::shared_ptr<wall>> world::get_walls() const {
        return walls;
    }

    std::vector<std::shared_ptr<fruit>> world::get_fruits() const {
        return fruits;
    }

    std::vector<std::shared_ptr<coin>> world::get_coins() const {
        return coins;
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

    std::shared_ptr<purpleGhost> world::get_purple_ghost() const {
        return _purpleGhost;
    }

    std::shared_ptr<greenGhost> world::get_green_ghost() const {
        return _greenGhost;
    }

    void world::clear() {
        walls.clear();
        fruits.clear();
        coins.clear();
        invisibleWalls.clear();
    }


}
