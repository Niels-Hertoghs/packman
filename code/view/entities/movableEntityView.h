//
// Created by niels_hertoghs on 11/16/25.
//

#ifndef PACKMAN_MOVABLEENTITYVIEW_H
#define PACKMAN_MOVABLEENTITYVIEW_H
#include "entityView.h"
#include "../../logic/notifications.h"

namespace view {
/**
* @class movableEntityView
* @brief Abstracte klasse voor alle movableEntity observers.
*/
class movableEntityView : public entityView {
    int aantalSprites;
    /// Hoeveel verschillende sprites er zijn van dat object per richting (ghost == 2, pacman == 4)
    int counter; /// Hoeveelste sprite van de huidige richting er getoond moet worden.
    int id;      /// De unieke id van deze movableEntityView, (voor het veranderen van de sprite).
    inline static int nextId;
    /// Statische variabele voor unieke id's, zodat elke movableEntityView een eigen id heeft.
    std::vector<std::vector<std::pair<int, int>>> allSprites;
    /// Alle sprites van dit object, in de volgorde down, up, right, left.
    std::vector<std::vector<std::pair<int, int>>> originalAllSprites;
    /// Alle sprites van dit object, in de volgorde down, up, right, left (voor als het terug naar chasing mode moet).
protected:
    std::vector<std::pair<int, int>> spriteCo; /// Alle sprites van het object in een bepaalde richting
    sf::Texture texture; /// Texture voor de sprite sheet.
    sf::RectangleShape _movable; /// Representatie van de movable entity. (als een rectangle met een texture erop).
public:
    /**
     * @brief Constructor voor de movableEntity observer.
     * @param window Waar het op moet worden afgebeeld.
     * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
     * @param spriteCo De coordinaten van de sprites voor deze movableEntity in de gegeven richting.
     * @param aantalSprites Het aantal verschillende sprites per richting.
     * @param allSprites Alle coordinaten van de sprites voor deze movableEntity in alle richtingen (volgorde: down, up, right, left).
     * @param x De x coo van de start locatie van de movable. (relatief tussen -1, en 1)
     * @param y De y coo van de start locatie van de movable. (relatief tussen -1, en 1)
     */
    movableEntityView(sf::RenderWindow& window, camera& cam, double x, double y,
                      const std::vector<std::pair<int, int>>& spriteCo, int aantalSprites,
                      const std::vector<std::vector<std::pair<int, int>>>& allSprites);

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    void draw() override;

    void notify(const logic::notifications& message) override;


    // Pure virtual methodes
    /**
     * @return Bool, of dat deze movableEntityView een ghost is.
     */
    [[nodiscard]] virtual bool isGhost() = 0;

    /**
     * @brief Default destructor.
     */
    ~movableEntityView() override = default;
};

/**
* @class packmanView
* @brief Concrete klasse voor de pacman observer.
*/
class packmanView final : public movableEntityView {
public:
    /**
     * @brief Constructor
     * @param window Waar het op moet worden afgebeeld.
     * @param cam Camera klasse voor het omzetten naar pixel coordinaten.
     * @param x De x coo van de start locatie van de pacman. (relatief tussen -1, en 1)
     * @param y De y coo van de start locatie van de pacman. (relatief tussen -1, en 1)
     */
    packmanView(sf::RenderWindow& window, camera& cam, double x, double y);

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    bool isGhost() override;

    /**
     * @brief Default destructor.
     */
    ~packmanView() override = default;
};
}


#endif //PACKMAN_MOVABLEENTITYVIEW_H
