//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_NOTIFIES_H
#define PACKMAN_NOTIFIES_H

namespace logic {

/**
 * @class NotificationsBase
 * @brief Basis klasse alle notificatie klasses, waarmee de observers worden genotified.
 * @tparam notifications De notificatie set, van de observer.
 */
template <typename notifications>
class NotificationsBase {
public:
    /**
     * @brief Constructor van de notification.
     * @param notif De notificatie/ de boodschap.
     */
    explicit NotificationsBase(notifications notif)
        : type(notif) {
    }

    notifications type; /// Het type van de notificatie (de boodschap).

    /**
     * @brief Default destructor.
     */
    ~NotificationsBase() = default;
};

/**
 * @brief Alle mogelijke notificaties (niet die van score) die een observer kan ontvangen van zijn subject.
 */
enum class notificationTypes {
    CHANGE_DIRECTION_UP,
    CHANGE_DIRECTION_DOWN,
    CHANGE_DIRECTION_LEFT,
    CHANGE_DIRECTION_RIGHT,
    CHANGE_POSITION,
    DELETE,
    COLLECTED,
    TO_CHASING_MODE,
    TO_FEAR_MODE,
    END_GAME
};

/**
 * @class notifications
 * @brief De notificatie klasse voor de entities. (alles wat er bij hun kan voorkomen).
 * @tparam notificationTypes De notificaties van een entity.
 */
class notifications : public NotificationsBase<notificationTypes> {
public:
    /**
     * @brief Explicit constructor.
     * @param notification De notificatie van een entity.
     */
    explicit notifications(const notificationTypes notification)
        : NotificationsBase(notification) {
    }

    /**
     * @brief Constructor voor als de positie veranderd.
     * @param x De nieuwe positie op de x-as.
     * @param y De nieuwe positie op de y-as.
     */
    notifications(double x, double y)
        : NotificationsBase(notificationTypes::CHANGE_POSITION), x(x), y(y) {
    }

    double x = 0, y = 0; /// Voor als de positie veranderd, is dit de nieuwe positie.

    /**
     * @brief Default destructor.
     */
    ~notifications() = default;
};


/**
 * @class scoreViewTypes
 * @brief Notificatie set voor alle notificaties die aan de scoreview obserever kunnen doorgegeven worden.
 */
enum class scoreViewTypes {
    UPDATE_SCORE,
    UPDATE_LIVES,
    UPDATE_LEVEL,
    END_GAME,
    EMPTY
};

/**
 * @class scoreViewNotifications
 * @brief De notificatie klasse voor de score View (observer van de score observer). (alles wat er bij hun kan voorkomen).
 * @tparam scoreViewTypes de notificatie set.
 */
class scoreViewNotifications : public NotificationsBase<scoreViewTypes> {
public:
    /**
     * @brief default constructor.
     */
    scoreViewNotifications()
        : NotificationsBase(scoreViewTypes::EMPTY) {
    };

    /**
     * @brief Explicit constructor.
     */
    explicit scoreViewNotifications(const scoreViewTypes notification)
        : NotificationsBase(notification) {
    }

    int lives = 0; /// Als het aantal remaining lives veranderen, dan staat hier het nieuwe level.
    int level = 0; /// Als het level veranderd, staat heir het nieuwe level.
    int score = 0; /// De aangepaste score.

    /**
     * @brief Default destructor.
     */
    ~scoreViewNotifications() = default;
};

/**
 * @brief Alle mogelijke notificaties voor de score observer.
 */
enum class scoreNotificationsType {
    ENTITY_EATEN,
    LIVE_LOST,
    NEXT_lEVEL,
    DECREASE_SCORE
};

/**
 * @brief De notificatie voor de score observer.
 * @tparam scoreNotificationsType De notificatie set van de score observer.
 */
class scoreNotifications : public NotificationsBase<scoreNotificationsType> {
public:
    /**
     * @brief Explicit constructor
     * @param type De effectieve notificate.
     */
    explicit scoreNotifications(const scoreNotificationsType type)
        : NotificationsBase(type) {
    }

    /**
     * @brief Constructor voor als er een ghost gegeten is geweest.
     * @param points Het aantal points dat een ghost waard is.
     * @param isGhost True als het een ghost is.
     */
    scoreNotifications(const int points, const bool isGhost)
        : NotificationsBase(scoreNotificationsType::ENTITY_EATEN), points(points), isGhost(isGhost) {
    }

    /**
     * @brief Constructor voor als er een entity geconsumeerd is.
     * @param points Het aantal points dat een entity waard is.
     */
    explicit scoreNotifications(const int points)
        : NotificationsBase(scoreNotificationsType::ENTITY_EATEN), points(points) {
    }


    int points = 0;       /// Het aantal points dat een object waard is.
    bool isGhost = false; /// Of het eventueel opgegeten object een ghost was.

    /**
     * @brief Default destructor.
     */
    ~scoreNotifications() = default;
};


/**
 * @brief Alle mogelijke richtingen die een movableEntity kan hebben.
 */
enum class directions {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    EMPTY
};

/**
 * @brief Alle mogelijke modes van een ghost.
 */
enum class modes {
    CHASING_MODE,
    FEAR_MODE
};

/**
 * @brief Alle mogelijke types van ghosts.
 */
enum class ghostTypes {
    RED,
    BLUE,
    GREEN,
    ORANGE
};

/**
 * @brief Alle mogelijke types van collectables.
 */
enum class collectableTypes {
    COIN,
    FRUIT
};
}
#endif //PACKMAN_NOTIFIES_H
