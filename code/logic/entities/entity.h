//
// Created by niels on 11/5/25.
//

#ifndef PACKMAN_ENTITY_H
#define PACKMAN_ENTITY_H
#include <memory>

#include "../../render/entityView.h"


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
        double x; /// Positie op de x as.
        double y; /// Positie op de y as.
    public:
        // constructor
        entity(double x, double y);

        // methodes
        [[nodiscard]] double getX() const;
        [[nodiscard]] double getY() const;

        virtual ~entity() = default;
    };



    /**
     * @class wall
     * @brief Concrete klasse die een muur representeert.
     */
    class wall : public entity {
    private:
        std::shared_ptr<view::wallView> _wallObserver;
    public:
        wall(double x,double y);
        [[nodiscard]] std::pair<double,double> getPosition() const;

        void wallSubscribe(std::shared_ptr<view::wallView> wallObserver);
    };
}



#endif //PACKMAN_ENTITY_H