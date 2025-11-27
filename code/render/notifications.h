//
// Created by niels_hertoghs on 11/13/25.
//

#ifndef PACKMAN_NOTIFIES_H
#define PACKMAN_NOTIFIES_H

enum notifications {
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
};

enum directions {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    EMPTY
};

enum modes {
    CHASING_MODE,
    FEAR_MODE
};

#endif //PACKMAN_NOTIFIES_H