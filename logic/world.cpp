//
// Created by niels on 11/5/25.
//

#include "world.h"
#include <fstream>
#include <sstream>

#include "render.h"

world::world(const std::string& inputFile2,std::shared_ptr<Score> sco) : score(sco) {
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

    // Hier komt je code om het bestand te lezen
    std::string line;
    double y = 1.0 - 2.0/7.0;
    while (std::getline(file, line)) {
        double x = -1.0; // reset x per regel
        for (char c : line) {
            if (c == '#') {
                walls.push_back(std::make_shared<wall>(x, y));
            }  else if (c == '-') {
                collectables.push_back(std::make_shared<coin>(x + 1.f/20.f, y - 1.f/14.f));
            } else if (c == 'f') {
                collectables.push_back(std::make_shared<fruit>(x + 1.f/20.f, y - 1.f/14.f));
            }
            x += 0.1;
        }
        y -= 1.0/7.0;
    }

    //pacman aanmaken, origin = midpunt
    pacman = std::make_shared<Packman>(0.f, 1 - 19.f/14.f);
}


std::shared_ptr<Render> world::render(const camera& cam,const sf::Font& pacmanFont) {
    std::shared_ptr<Render> render = std::make_shared<Render>(cam,score);
    render->Leveltekst(cam,pacmanFont);

    // walls
    for (const std::shared_ptr<wall>& muur:walls) {
        muur->render(render);
    }

    // cons / fruits
    for (const std::shared_ptr<collectable>& munt:collectables) {
        munt->render(render);
    }

    //pacman
    pacman->render(render);

    return render;
}


void world::update(float deltaTime) {
    pacman->update(deltaTime,walls);
    for (auto it = collectables.begin(); it != collectables.end(); ) {
        if (pacman->standsOnCoin(*it)) {
            score->coinEaten();
            it = collectables.erase(it); // erase retourneert de volgende iterator
        } else {
            ++it;
        }
    }
}

void world::updatePacmanDir(const std::string& direction) {
    // for (auto muur : walls) {
    //     if (pacman->standsOn(muur)) {
    //         return;
    //     }
    // }
    pacman->updateDir(direction);
}

