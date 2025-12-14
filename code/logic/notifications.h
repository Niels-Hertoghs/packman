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
    UPDATE_SCORE,
    UPDATE_LIVES,
    UPDATE_LEVEL,
    TO_CHASING_MODE,
    TO_FEAR_MODE,
    END_GAME
};

class notifications {
public:
    explicit notifications(const notificationTypes notification) : type(notification) {}
    notifications(notificationTypes notification,double x, double y) : type(notification), x(x), y(y) {}
    notificationTypes type;
    double x{}, y{};
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