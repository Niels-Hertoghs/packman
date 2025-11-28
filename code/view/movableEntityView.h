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
        int aantalSprites;  /// Hoeveel verschillende sprites er zijn van dat object per richting (ghost == 2, pacman == 4)
        int counter;
        int id; /// De unieke id van deze movableEntityView, (voor het veranderen van de sprite).
        inline static int nextId; /// Statische variabele voor unieke id's, zodat elke movableEntityView een eigen id heeft.
        std::weak_ptr<logic::movableEntity> Model;
    protected:
        std::vector<std::vector<std::pair<int,int>>> allSprites;  /// Alle sprites van dit object, in de volgorde down, up, right, left.
        std::vector<std::pair<int,int>> spriteCo;  /// Alle sprites van het object in een bepaalde richting
        sf::Texture texture;
        sf::RectangleShape _movable;
    public:
        movableEntityView(sf::RenderWindow &window, camera &cam, std::shared_ptr<logic::movableEntity> &model,
                          const std::vector<std::pair<int, int> > &spriteCo, int aantalSprites,
                          const std::vector<std::vector<std::pair<int, int> > > &allSprites);
        void draw() override;
        void notify(enum notifications message) override ;

        virtual bool isGhost() = 0;
    };

    class packmanView : public movableEntityView {
    private:
    public:
        packmanView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::movableEntity> pacmanModel);
        bool isGhost() override;
    };
}


#endif //PACKMAN_MOVABLEENTITYVIEW_H