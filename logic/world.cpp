//
// Created by niels on 11/5/25.
//

#include "world.h"
#include <fstream>
#include <sstream>

#include "render.h"

world::world(const std::string& inputFile) {
    try {
        std::ifstream file(inputFile);
        if (!file.is_open()) {
            throw std::runtime_error("Bestand bestaat niet: " + inputFile);
        }

        // Hier komt je code om het bestand te lezen
        std::string line;
        double y = 1.0 - 2.0/7.0;
        while (std::getline(file, line)) {
            double x = -1.0; // reset x per regel
            for (char c : line) {
                if (c == '#') {
                    std::unique_ptr<wall> muur = std::make_unique<wall>(x, y);
                    walls.push_back(std::move(muur));
                }  else if (c == '-') {
                    std::unique_ptr<coin> munt = std::make_unique<coin>(x + 1.f/20.f, y - 1.f/14.f);
                    collectables.push_back(std::move(munt));
                }//TODO: de rest inladen
                x += 0.1;
            }
            y -= 1.0/7.0;
        }

    } catch (const std::exception& e) {
        std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
        throw;
    }
}

Render* world::render(const camera& cam,const sf::Font& pacmanFont) {
    Render* render = new Render(cam);
    render->loadMap(cam,pacmanFont);

    for (const std::shared_ptr<wall>& muur:walls) {
        muur->render(render);
    }

    for (const std::shared_ptr<collectable>& munt:collectables) {
        munt->render(render);
    }

    return render;
}
