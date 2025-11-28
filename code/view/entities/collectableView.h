//
// Created by niels_hertoghs on 11/16/25.
//

#ifndef PACKMAN_COLLECTABLEVIEW_H
#define PACKMAN_COLLECTABLEVIEW_H
#include <SFML/Graphics.hpp>

#include "entityView.h"

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
        bool collected;
        std::weak_ptr<logic::collectable> Model; /// Weak pointer naar de logica van collectable.
    public:
        /**
         * @brief Constructor voor de collectable observer.
         * @param window De window waar de collectable afgebeeld met worden.
         * @param cam Camera klasse
         */
        collectableView(sf::RenderWindow& window,camera& cam, std::shared_ptr<logic::collectable>& model);

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
    public:
        /**
        * @brief Constructor voor de coin observer.
        * @param window De window waar de collectable afgebeeld met worden.
        * @param cam Camera klasse
        */
        coinView(sf::RenderWindow& window,camera& cam,std::shared_ptr<logic::collectable>& coinModel);

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
    public:
        /**
        * @brief Constructor voor de coin observer.
        * @param window De window waar de collectable afgebeeld met worden.
        * @param cam Camera klasse
        */
        fruitView(sf::RenderWindow& window,camera& cam,std::shared_ptr<logic::collectable>& fruitModel);

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