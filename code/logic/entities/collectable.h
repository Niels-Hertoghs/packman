//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_COLLECTABLE_H
#define PACKMAN_COLLECTABLE_H
#include "entity.h"
#include "../Score.h"



namespace logic {

     /**
      * @class collectable
      * @brief Een abstracte klasse voor collecteerbare objecten.
      */
     class collectable : public entity {
          int points; /// Hoeveel punten er bij de score worden toegevoegd als het object na 1 seconde wordt opgegeten.
     public:

          // constructor

          /**
           * @brief Constructor voor de collectable.
           * @param x De positie van de collectable op de x-as (relatief tussen -1 en 1).
           * @param y De positie van de collectable op de y-as (relatief tussen -1 en 1).
           * @param points Het aantal punten dat er bij de score komen als de collectable wordt opgegeten.
           */
          collectable(double x, double y,int points);

          // pure virtual methodes

          /**
           * @brief Laat de observer weten dat het gegeten is + of de movables in chasing mode moeten.
           * @return True als het een fruit gegeten heeft en in chasing mode moet gaan.
           */
          [[nodiscard]] virtual bool collected() const = 0;

          /**
          * @brief Wordt gebruikt door de obser#include "../../view/entities/ghostView.h"
ver om te weten wat het moet tekenen in de window (false = coin, true = fruit).
          * @return Of de collectable en fruit is.
          */
          [[nodiscard]] virtual bool isFruit() const = 0;


          // methods

          /**
           * @return Het aantal punten dat de collectable waard is.
           */
          [[nodiscard]] int getPoints() const;



          /**
           * @brief Default destructor.
           */
          ~collectable() override = default;

     };

     /**
      * @class coin
      * @brief Een concrete klasse voor de coins, positie is het midden van de coin.
      */
     class coin final : public collectable {
     public:
          // constructor
          /**
           * @param x De positie van de collectable op de x-as (relatief tussen -1 en 1).
           * @param y De positie van de collectable op de y-as (relatief tussen -1 en 1).
           * @param points Het aantal punten dat er bij de score komen als de collectable wordt opgegeten (na 1 seconde).
           */
          coin(double x, double y, int points);

          // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
          [[nodiscard]] bool collected() const override;
          [[nodiscard]] bool isFruit() const override;

          /**
           * @brief Default destructor.
           */
          ~coin() override = default;
     };

     /**
      * @class fruit
      * @brief Een concrete klasse voor de fruit, positie is de linkerbovenhoek van de fruit.
      */
     class fruit final : public collectable {
     public:
          // constructor
          /**
           * @param x De positie van de collectable op de x-as (relatief tussen -1 en 1).
           * @param y De positie van de collectable op de y-as (relatief tussen -1 en 1).
           * @param points Het aantal punten dat er bij de score komen als de collectable wordt opgegeten (na 1 seconde).
           */
          fruit(double x, double y,int points);

          // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
          [[nodiscard]] bool collected() const override;
          [[nodiscard]] bool isFruit() const override;

          /**
           * @brief Default destructor.
           */
          ~fruit() override = default;
     };
}
#endif //PACKMAN_COLLECTABLE_H