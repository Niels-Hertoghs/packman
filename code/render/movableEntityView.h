//
// Created by niels_hertoghs on 11/16/25.
//

#ifndef PACKMAN_MOVABLEENTITYVIEW_H
#define PACKMAN_MOVABLEENTITYVIEW_H
#include "entityView.h"
#include "notifications.h"

namespace logic {
    class Packman;
}

namespace view {
    class movableEntityView : public entityView {
    private:
        int aantalSprites;
        int counter;
        int id; /// de unieke id van deze movableEntityView, (voor het veranderen van de sprite).
        inline static int nextId; /// statische variabele voor unieke id's, zodat elke movableEntityView een eigen id heeft.
    protected:
        std::vector<std::pair<int,int>> spriteCo;
        sf::Texture texture;
        sf::RectangleShape _movable;
    public:
        movableEntityView(sf::RenderWindow& window,camera& cam,const std::vector<std::pair<int,int>>& spriteCo,int aantalSprites);
        void draw() override;
        void notify(enum notifications message) override = 0;
    };

    class packmanView : public movableEntityView {
    private:
        std::weak_ptr<logic::Packman> pacmanModel;
    public:
        packmanView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::Packman>& pacmanModel);
        void notify(enum notifications message) override;
    };
}


#endif //PACKMAN_MOVABLEENTITYVIEW_H