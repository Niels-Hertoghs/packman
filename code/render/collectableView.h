//
// Created by niels_hertoghs on 11/16/25.
//

#ifndef PACKMAN_COLLECTABLEVIEW_H
#define PACKMAN_COLLECTABLEVIEW_H
#include <SFML/Graphics.hpp>

#include "entityView.h"

namespace logic {
    class fruit;
    class coin;
}

namespace view {
    /**
     * @class collectableView
     * @brief Een abstracte klasse voor alle collectables.
     */
    class collectableView : public entityView {
    protected:
        bool collected;
    public:
        /**
         * @brief Constructor voor de collectable observer.
         * @param stopwatch De stopwatch klasse.
         * @param window De window waar de collectable afgebeeld met worden.
         * @param cam Camera klasse
         */
        collectableView(Stopwatch& stopwatch,sf::RenderWindow& window,camera cam);

        /**
         * @brief Pure virtual methodes
         */
        void draw() override = 0;
        void notify(enum notifications message) override = 0;
    };

    /**
     * @class coinView
     * @brief De concrete klasse van een coin observer.
     */
    class coinView : public collectableView {
    private:
        sf::CircleShape _coin; /// De representatie van de coin.
        std::weak_ptr<logic::coin> coinModel; /// Smart pointer naar de logica van coin.
    public:
        /**
        * @brief Constructor voor de coin observer.
        * @param stopwatch De stopwatch klasse.
        * @param window De window waar de collectable afgebeeld met worden.
        * @param cam Camera klasse
        */
        coinView(Stopwatch& stopwatch,sf::RenderWindow& window,camera cam,std::shared_ptr<logic::coin>& coinModel);

        /**
         * @brief Wanneer opgeroepen wordt coin weergegeven in de window.
         */
        void draw() override;

        /**
         * @param message De verandering van het object.
         */
        void notify(enum notifications message) override;
    };

    class fruitView : public collectableView {
    private:
        sf::Texture texture; /// De texture van de fruit.
        sf::RectangleShape _fruit; /// De representatie van de fruit.
        std::weak_ptr<logic::fruit> fruitModel; /// Smart pointer naar de logica van fruit.
    public:
        /**
        * @brief Constructor voor de coin observer.
        * @param stopwatch De stopwatch klasse.
        * @param window De window waar de collectable afgebeeld met worden.
        * @param cam Camera klasse
        */
        fruitView(Stopwatch& stopwatch,sf::RenderWindow& window,camera cam,std::shared_ptr<logic::fruit>& fruitModel);

        /**
        * @brief Wanneer opgeroepen wordt coin weergegeven in de window.
        */
        void draw() override;

        /**
        * @param message De verandering van het object.
        */
        void notify(enum notifications message) override;
    };
}

#endif //PACKMAN_COLLECTABLEVIEW_H