//
// Created by niels on 11/5/25.
//

#include "world.h"
#include <fstream>
#include <sstream>

#include "render/render.h"

namespace logic {
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

        std::string line;
        double y = 1.0 - 2.0/7.0;
        while (std::getline(file, line)) {
            double x = -1.0;
            for (char c : line) {
                if (c == '#') {
                    walls.push_back(std::make_shared<wall>(x, y));
                    // wall.subscribe(new wallView)
                    // in de main loop ook een wereldView maken samen met wereld en die laten subsriben
                    // in de main loop dan na elke tick, wereldView->render doen, die heeft als private een pointer naar window en zet daar alles op
                    // vraag: in de initializatie (hier) ook de observer van elke member maken? en die dan toevoegen aan wereldView? (coins enz) wall heeft niet echt een observer nodig
                    // for elk object in wereldView(wallView { draw{ teken}})

                    // uit elke view met getters werken naar wat ge nodig hebt.
                    // dan zou alles maar 1 keer in de window gezet moeten worden tot iets update moet dat veranderen, rest blijft staan
                    // wereld heeft ook een score observer

                    // abstract observer (entityView kijk opdracht, foto)  met pure virtual update/notify en draw rest is over erving
                    // ! voor dat je start denk eerst na over alles en als er iets niet klopt, los op voor dat je begin!
                }  else if (c == '-') {
                    // points staat op 40 om te beginne
                    collectables.push_back(std::make_shared<coin>(x + 1.f/20.f, y - 1.f/14.f, 40));
                } else if (c == 'f') {
                    // points staan op 50 om te beginne, is meer dan coins
                    collectables.push_back(std::make_shared<fruit>(x + 1.f/20.f, y - 1.f/14.f,50));
                }
                x += 0.1;
            }
            y -= 1.0/7.0;
        }

        //pacman aanmaken, origin = midpunt
        pacman = std::make_shared<Packman>(0.f, 1 - 19.f/14.f);
    }


    std::shared_ptr<render::Render> world::render(const camera& cam,const sf::Font& pacmanFont) {
        std::shared_ptr<render::Render> render = std::make_shared<render::Render>(cam,score);
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
        // pacman updaten, oa de locatie
        pacman->update(deltaTime,walls);

        // zien of pacman niet op een collectable staat
        for (auto it = collectables.begin(); it != collectables.end(); ) {
            if (pacman->standsOnCoin(*it)) {
                score->coinEaten(it->get()->getPoints());
                it = collectables.erase(it); // erase retourneert de volgende iterator
            } else {
                ++it;
            }
        }
    }

    void world::updatePacmanDir(const std::string& direction) {
        pacman->updateDir(direction);
    }
}