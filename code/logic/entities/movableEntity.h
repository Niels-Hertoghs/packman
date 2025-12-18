//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_MOVABLEENTITY_H
#define PACKMAN_MOVABLEENTITY_H
#include <vector>
#include "../notifications.h"
#include "entity.h"


namespace logic {
// forward declaration
class Ghost;

/**
 * @class movableEntity
 * @brief Een abstracte klasse voor alle beweegbare objecten in de game (x, y coo zijn in het midden van de sprite).
 */
class movableEntity : public entity {
protected:
    directions direction;               /// Richting dat het object gaat.
    const directions originalDirection; /// Originele richting van object bij het inladen, voor het respawn.
    double speed;                       /// De snelheid van het object.
    double prevX, prevY;
    /// Vorige posities van de objecten (voor de update, als het op een muur gaat staan kan het terug naar de oude positie gaan).
    const double spawnLocatieX, spawnLocatieY;
    /// Begin locatie van het object, voor als het dood gaat dat het er terug kan spawnen.

    /**
     * @brief Zet de positie van de movable terug naar de vorige locatie (voor als die op een muur is beland).
     */
    void prevLocation();
public:
    // constructor
    /**
     * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
     * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
     * @param direction De richting van de ghost.
     * @param speed De snelheid van de ghost.
     */
    movableEntity(double x, double y, double speed, directions direction);

    // pure virtual methodes
    /**
     * @brief Update de movable entity, laat die bewegen en checkt voor botsingen met muren.
     * @param deltaTime De tijd dat er verstreken is sinds de laatste update.
     * @param walls De muren in de wereld, om te zien dat de movable er niet door kan bewegen.
     */
    virtual void update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) = 0;

    /**
     * @brief Reset alles van de movable toen het was ingeladen (positie, richting, ...).
     */
    virtual void died() = 0;

    // methodes
    /**
     * @brief Kijkt of de movable en het andere entity object zouden botsen als de movable naar de gegeven coordinaten zou gaan.
     * @param other Pointer naar het andere entity object.
     * @param newX De x coordinate van de movable.
     * @param newY De y coordinate van de movable.
     * @return Of dat other en de gegeven coordinaten zouden botsen (in elkar liggen).
     */
    [[nodiscard]] static bool wouldCollide(const std::shared_ptr<entity>& other, double newX, double newY);

    /**
     * @brief Kijkt of de movable (daarvan moet het opgeroepen worden) en het andere entity object zouden botsen als de movable naar de gegeven coordinaten zou gaan.
     * @brief Gebruikt de huidige x en y van de movable.
     * @param other Pointer naar het andere entity object.
     * @return Of dat other en de gegeven coordinaten zouden botsen (in elkar liggen).
     */
    [[nodiscard]] bool standsOn(const std::shared_ptr<entity>& other);


    /**
     * @brief Laat de movable effectief bewegen in de huidige direction.
     * @param delta De tijd dat er verstreken is sinds de laatste update.
     */
    void move(double delta);

    /**
     * @brief Berekent de volgende positie van de movable als die in de gegeven direction zou bewegen (voor de manhattanGhosts).
     * @param delta De tijd dat er verstreken is sinds de laatste update.
     * @param dir De richting waarin de movable zou bewegen.
     * @param _x De huidige x positie van de movable.
     * @param _y De huidige y positie van de movable.
     * @return Pair van de x en y coordinaat van de volgende positie.
     */
    [[nodiscard]] std::pair<double, double> calculateNextPos(double delta, directions dir, double _x, double _y) const;

    /**
     * @brief Verplaats de movable terug naar zijn spawn locatie, en de richting naar de originele richting.
     */
    void toSpawnLocation();

    /**
     * @return Pair van de x en y coopackman_logicrdinaat van de voorkant van de movable, afhankelijk van zijn direction.
     */
    std::pair<double, double> getFront();

    /**
     * @return Pair van de x en y coordinaat van de achterkant van de movable, afhankelijk van zijn direction.
     */
    std::pair<double, double> getBack();

    /**
     * @brief Geeft de coordinaten van de richting van de movable.
     * @param dir De richting waarvan je de coordinaten wilt hebben.
     * @return Pair van de x en y coordinaat van de kant van de movable, afhankelijk van zijn direction.
     */
    std::pair<double, double> getCoSide(directions dir);

    /**
     * @brief Geeft de tegenovergestelde richting van de gegeven richting.
     * @param dir De richting waarvan je de tegenovergestelde wilt hebben.
     * @return De tegenovergestelde richting van de gegeven richting.
     */
    static directions oppositeDirection(directions dir);

    /**
     * @brief Laat de observer weten dat de movable van positie is veranderd.
     */
    void notifyPos();

    /**
     * @brief Laat de observer weten dat de movable van richting is veranderd, met de correcte richting.
     */
    void notifyDir();

    // getter
    /**
     * @return De direction van de movable entity.
     */
    [[nodiscard]] directions get_direction() const;

    /**
     * @brief default destructor.
     */
    ~movableEntity() override = default;
};

/**
 * @class Pacman
 * @brief De concrete klasse voor pacman.
 */
class Pacman final : public movableEntity {
private:
    directions nextDirection; /// Volgende richting zodra mogelijk.
public:
    // constructor
    /**
    * @param x De positie van de Ghost op de x-as (relatief tussen -1 en 1).
    * @param y De positie van de Ghost op de y-as (relatief tussen -1 en 1).
    * @param speed De snelheid van de ghost.
    */
    Pacman(double x, double y, double speed);

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    void update(double deltaTime, std::vector<std::shared_ptr<entity>>& walls) override;

    void died() override;

    // methodes
    /**
     * @param other De pointer naar de coin om te checken of pacman erop staat.
     * @return Bool, of dat pacman op de coin staat.
     */
    [[nodiscard]] bool standsOnCoin(const std::shared_ptr<entity>& other);

    /**
     * @brief Update de volgende richting van pacman.
     * @param direction De nieuwe richting waar pacman naartoe moet gaan zodra mogelijk.
     */
    void updateDir(enum directions direction);

    /**
     * @param ghost De pionter naar de ghost om te checken of pacman erop staat.
     * @return Bool, of dat pacman op de ghost staat.
     */
    [[nodiscard]] bool standsOnGhost(const std::shared_ptr<Ghost>& ghost);

    /**
     * @brief Default destructor.
     */
    ~Pacman() override = default;
};

}


#endif //PACKMAN_MOVABLEENTITY_H
