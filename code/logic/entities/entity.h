//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_ENTITY_H
#define PACKMAN_ENTITY_H
#include <memory>
#include "../Observer.h"
#include "../notifications.h"

// Forward declarations
namespace view {
    class wallView;
}

namespace logic {
    /**
     * @class entity
     * @brief Een abstracte klasse voor alle objecten in de game.
     */
    class entity {
    protected:
        std::shared_ptr<Observer<notifications>> observer;  /// De observer van de movableEntity.
        double x; /// Positie op de x as.
        double y; /// Positie op de y as.
    public:
        // constructor
        /**
         * @param x De positie van het object op de x-as (relatief tussen -1 en 1).
         * @param y De positie van het object op de y-as (relatief tussen -1 en 1).
         */
        entity(double x, double y);

        // methodes

        /**
         * @return De positie van het object op de x-as.
         */
        [[nodiscard]] double getX() const;

        /**
         * @return De positie van het object op de y-as.
         */
        [[nodiscard]] double getY() const;

        /**
         * @return De positie van het object als een pair {x,y}.
         */
        [[nodiscard]] std::pair<double,double> getPosition() const;

        /**
        * @brief Default destructor.
        */
        virtual ~entity() = default;
    };

    /**
     * @class wall
     * @brief Concrete klasse die een muur representeert, positie x,y is de linkerbovenhoek.
     */
    class wall final : public entity {
    public:
        // constructor
        /**
         * @param x De positie van het object op de x-as (relatief tussen -1 en 1).
         * @param y De positie van het object op de y-as (relatief tussen -1 en 1).
         */
        wall(double x,double y);


        /**
        * @brief Default destructor.
        */
        ~wall() override = default;
    };

    /**
    * @class invisibleWall
    * @brief Concrete klasse die een invisible muur representeert, ja kan het niet zien op de window, maar de objecten kunnen er niet door gaan (enkel de ghosts om uit hun cage te gaan).
    * @brief Positie x,y is de linkerbovenhoek.
    */
    class invisibleWall final : public entity {
    public:
        /**
         *
         * @param x De positie van het object op de x-as (relatief tussen -1 en 1).
         * @param y De positie van het object op de y-as (relatief tussen -1 en 1).
         */
        invisibleWall(double x,double y);

        /**
        * @brief Default destructor.
        */
        ~invisibleWall() override = default;
    };
}



#endif //PACKMAN_ENTITY_H