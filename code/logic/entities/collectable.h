//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_COLLECTABLE_H
#define PACKMAN_COLLECTABLE_H
#include "entity.h"

namespace view {
     class coinView;
     class fruitView;
}

namespace render {
     class Render;
}

namespace logic {

     /**
      * @class collectable
      * @brief Een abstracte klasse voor collectables.
      */
     class collectable : public entity {
     private:
          double points; /// Hoeveel punten er bij de score worden toegevoegd als het object na 1 seconde wordt opgegeten.
     public:
          // constructor
          collectable(double x, double y,double points);

          // pure virtual
          virtual void render(std::shared_ptr<render::Render> render) override = 0;

          // methods
          double getPoints();
          void setPoints(double newPoints);
     };

     /**
      * @class coin
      * @brief Een concrete klasse voor de coins.
      */
     class coin : public collectable {
     private:
          std::shared_ptr<view::coinView> coinObserver;

     public:
          coin(double x, double y, double points);
          void render(std::shared_ptr<render::Render> render) override;
          void coinSubscribe(std::shared_ptr<view::coinView> coinObserver);

          void collected();
     };

     class fruit : public collectable {
     private:
          std::shared_ptr<view::fruitView> fruitObserver;

     public:
          fruit(double x, double y, double points);
          void render(std::shared_ptr<render::Render> render) override;
          void fruitSubscribe(std::shared_ptr<view::fruitView> fruitObserver);
          void collected();

     };
}
#endif //PACKMAN_COLLECTABLE_H