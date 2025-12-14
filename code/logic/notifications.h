//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_NOTIFIES_H
#define PACKMAN_NOTIFIES_H

/**
 * @brief Alle mogelijke notificaties die een observer kan ontvangen van zijn subject.
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

template <typename notifications>
class NotificationsBase {
public:
    explicit NotificationsBase(notifications notif)
        : type(notif) {

    }

    notifications type;
};

class notifications : public NotificationsBase<notificationTypes> {
public:
    explicit notifications(const notificationTypes notification)
        : NotificationsBase(notification) {
    }

    notifications(notificationTypes notification, double x, double y)
        : NotificationsBase(notification), x(x), y(y) {
    }

    double x{}, y{};
};

enum class scoreViewTypes {
    UPDATE_SCORE,
    UPDATE_LIVES,
    UPDATE_LEVEL,
    END_GAME,
    EMPTY
};

class scoreViewNotifications : public NotificationsBase<scoreViewTypes> {
public:
    scoreViewNotifications()
        : NotificationsBase(scoreViewTypes::EMPTY) {
    };

    explicit scoreViewNotifications(const scoreViewTypes notification)
        : NotificationsBase(notification) {
    }

    int lives{}, level{}, score{};

};


enum class scoreNotificationsType {
    ENTITY_EATEN,
    LIVE_LOST,
    NEXT_lEVEL

};

class scoreNotifications : public NotificationsBase<scoreNotificationsType> {
public:
    explicit scoreNotifications(scoreNotificationsType type)
        : NotificationsBase(type) {
    }

    scoreNotifications(scoreNotificationsType type, int points, bool isGhost)
        : NotificationsBase(type), points(points), isGhost(isGhost) {
    }

    scoreNotifications(scoreNotificationsType type, int points)
    : NotificationsBase(type), points(points) {
    }

    int points{};
    bool isGhost = false;
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


#endif //PACKMAN_NOTIFIES_H
