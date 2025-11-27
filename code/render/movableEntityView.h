//
// Created by niels_hertoghs on 11/16/25.
//

#ifndef PACKMAN_MOVABLEENTITYVIEW_H
#define PACKMAN_MOVABLEENTITYVIEW_H
#include "entityView.h"
#include "notifications.h"

namespace logic {
    class movableEntity;
}

namespace view {
    class movableEntityView : public entityView {
    private:
        int aantalSprites;
        int counter;
        int id; /// de unieke id van deze movableEntityView, (voor het veranderen van de sprite).
        inline static int nextId; /// statische variabele voor unieke id's, zodat elke movableEntityView een eigen id heeft.
        std::weak_ptr<logic::movableEntity> Model;
    protected:
        std::vector<std::vector<std::pair<int,int>>> allSprites;
        std::vector<std::pair<int,int>> spriteCo;
        sf::Texture texture;
        sf::RectangleShape _movable;
    public:
        movableEntityView(sf::RenderWindow &window, camera &cam, std::shared_ptr<logic::movableEntity> &model,
                          const std::vector<std::pair<int, int> > &spriteCo, int aantalSprites,
                          const std::vector<std::vector<std::pair<int, int> > > &allSprites);
        void draw() override;
        void notify(enum notifications message) override ;
    };

    class packmanView : public movableEntityView {
    private:
    public:
        packmanView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::movableEntity> pacmanModel);
    };
}


#endif //PACKMAN_MOVABLEENTITYVIEW_H