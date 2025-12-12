//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_NOTIFIES_H
#define PACKMAN_NOTIFIES_H

/**
 * @brief Alle mogelijke notificaties die een observer kan ontvangen van zijn subject.
 */
enum class notifications {
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