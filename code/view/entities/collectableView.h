//
// Created by niels_hertoghs on 11/16/25.
//

#ifndef PACKMAN_COLLECTABLEVIEW_H
#define PACKMAN_COLLECTABLEVIEW_H
#include <SFML/Graphics.hpp>

#include "entityView.h"

// Forward declarations
namespace logic {
    class collectable;
}

namespace view {
    /**
     * @class collectableView
     * @brief Een abstracte klasse voor alle collectables.
     */
    class collectableView : public entityView {
    protected:
        bool collected; /// Of de collectable al is opgegeten.
    public:
        /**
         * @brief Constructor voor de collectable observer.
         * @param window Waar de collectable afgebeeld met worden.
         * @param cam Camera klasse
         * @param model Pointer naar de logica van collectable.
         */
        collectableView(sf::RenderWindow& window,camera& cam, double x,double y);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void draw() override = 0;
        void notify(const notifications& message) override = 0;

        /**
         * @brief Default destructor.
         */
        ~collectableView() override = default;
    };

    /**
     * @class coinView
     * @brief De concrete klasse van een coin observer.
     */
    class coinView final : public collectableView {
        sf::CircleShape _coin; /// De representatie van de coin.
    public:
        /**
        * @brief Constructor voor de coin observer.
        * @param window Waar de collectable afgebeeld met worden.
        * @param cam Camera klasse
        * @param coinModel Pointer naar de logica van de coin.
        */
        coinView(sf::RenderWindow& window,camera& cam,double x,double y);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void draw() override;
        void notify(const notifications& message) override;

        /**
         * @brief Default destructor.
         */
        ~coinView() override = default;
    };

    /**
    * @class fruitView
    * @brief De concrete klasse van een fruit observer.
    */
    class fruitView final : public collectableView {
        sf::Texture texture; /// De texture van de fruit.
        sf::RectangleShape _fruit; /// De representatie van de fruit.
    public:
        /**
        * @brief Constructor voor de coin observer.
        * @param window Waar de collectable afgebeeld met worden.
        * @param cam Camera klasse
        * @param fruitModel Pointer naar de logica van de fruit.
        */
        fruitView(sf::RenderWindow& window,camera& cam,double x,double y);

        // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
        void draw() override;
        void notify(const notifications& message) override;

        /**
        * @brief Default destructor.
        */
        ~fruitView() override = default;
    };
}

#endif //PACKMAN_COLLECTABLEVIEW_H