//
// Created by niels_hertoghs on 11/16/25.
//

#ifndef PACKMAN_MOVABLEENTITYVIEW_H
#define PACKMAN_MOVABLEENTITYVIEW_H
#include "entityView.h"
#include "notifications.h"

namespace logic {
    class Packman;
    class Ghost;
}

namespace view {
    class movableEntityView : public entityView {
    protected:
        int counter;
        sf::Texture texture;
        std::vector<std::pair<int,int>> spriteCo;
    public:
        movableEntityView(Stopwatch& stopwatch,sf::RenderWindow& window,camera& cam,const std::vector<std::pair<int,int>>& spriteCo);
        void draw() override = 0;
        void notify(enum notifications message) override = 0;
    };

    class packmanView : public movableEntityView {
    private:
        sf::RectangleShape _pacman;
        std::weak_ptr<logic::Packman> pacmanModel;
    public:
        packmanView(Stopwatch& stopwatch,sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::Packman>& pacmanModel);
        void draw() override;
        void notify(enum notifications message) override;
    };

    class ghostView : public movableEntityView {
    private:
        sf::RectangleShape _ghost;
        std::weak_ptr<logic::Ghost> ghostModel;
    public:
        ghostView(Stopwatch& stopwatch,sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::Ghost>& ghostModel);
        void draw() override;
        void notify(enum notifications message) override;
    };
}


#endif //PACKMAN_MOVABLEENTITYVIEW_H