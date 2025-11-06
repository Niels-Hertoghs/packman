//
// Created by niels on 11/5/25.
//

#include "world.h"
#include "render.h"

world::world() {
    for (int i = 0; i<11;i++) {

    }
    float y = -1.f + 2.f/14.f;
    std::unique_ptr<wall> muur = std::make_unique<wall>(-1.f,-1.f);
    walls.push_back(std::move(muur));
}

std::unique_ptr<Render> world::render(const camera& cam,const sf::Font& pacmanFont) {
    auto render = std::make_unique<Render>(cam);
    render->loadMap(cam,pacmanFont);

    for (const std::shared_ptr<wall>& muur:walls) {
        muur->render(render.get());
    }

    return render;
}
