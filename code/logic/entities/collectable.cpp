//
// Created by niels on 11/6/25.
//

#include "collectable.h"


namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class collectable
    /// ---------------------------------------------------------------------------------------------------------------
    ///
    collectable::collectable(double x, double y,double Points) : entity(x,y ), points(Points) {}

    double collectable::getPoints() {
        return points;
    }

    void collectable::setPoints(double newPoints) {
        points = newPoints;
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class coin
    /// ---------------------------------------------------------------------------------------------------------------

    coin::coin(double x, double y,double points) : collectable(x,y,points){}


    void coin::coinSubscribe(std::shared_ptr<view::coinView> CoinObserver) {
        coinObserver = CoinObserver;
    }

    void coin::collected() {
        coinObserver->notify(notifications::COLLECTED);
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// @class fruit
    /// ---------------------------------------------------------------------------------------------------------------

    fruit::fruit(double x, double y,double points) : collectable(x,y,points){}


    void fruit::fruitSubscribe(std::shared_ptr<view::fruitView> FruitObserver) {
        fruitObserver = FruitObserver;
    }

    void fruit::collected() {
        fruitObserver->notify(notifications::COLLECTED);
    }


}
