//
// Created by niels on 11/6/25.
//

#include "collectable.h"
#include <utility>


namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class collectable
    /// ---------------------------------------------------------------------------------------------------------------

    collectable::collectable(double x, double y, int Points) : entity(x, y), points(Points) {
    }

    int collectable::getPoints() const {
        return points;
    }

    void collectable::collected() {
        notifyObservers(notifications(notificationTypes::COLLECTED));
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// @class coin
    /// ---------------------------------------------------------------------------------------------------------------

    coin::coin(const double x, const double y, const int points) : collectable(x, y, points) {
    }


    bool coin::isFruit() const {
        return false;
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// @class fruit
    /// ---------------------------------------------------------------------------------------------------------------

    fruit::fruit(const double x, const double y, const int points)
        : collectable(x, y, points) {
    }

    bool fruit::isFruit() const {
        return true;
    }
}