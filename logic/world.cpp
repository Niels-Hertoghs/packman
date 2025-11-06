//
// Created by niels on 11/5/25.
//

#include "world.h"
#include "render.h"

world::world() {
    // linker en rechter muur maken
    double y = 1.f - 2.f/7.f;
    for (int i = 0; i<11;i++) {
        std::unique_ptr<wall> Lmuur = std::make_unique<wall>(-1.f,y); // voor de linker muur
        walls.push_back(std::move(Lmuur));

        std::unique_ptr<wall> Rmuur = std::make_unique<wall>(1.f - 1.f/7.f,y); // voor de linker muur
        walls.push_back(std::move(Rmuur));
        y -= 1.f/7.f;
    }

    // boven en onder muur maken
    double x = -1.f + 1.f/10.f;
    for (int i = 0; i<18;i++) {
        std::unique_ptr<wall> Bmuur = std::make_unique<wall>(x,1.f - 2.f/7.f); // voor de boven muur
        walls.push_back(std::move(Bmuur));

        std::unique_ptr<wall> Omuur = std::make_unique<wall>(x,-1.f + 2.f/7.f); // voor de onder muur
        walls.push_back(std::move(Omuur));
        x += 1.f/10.f;
    }
}

Render* world::render(const camera& cam,const sf::Font& pacmanFont) {
    Render* render = new Render(cam);
    render->loadMap(cam,pacmanFont);

    for (const std::shared_ptr<wall>& muur:walls) {
        muur->render(render);
    }

    return render;
}
