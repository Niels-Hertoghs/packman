//
// Created by niels_hertoghs on 12/14/25.
//

#ifndef PACKMAN_OBSERVER_H
#define PACKMAN_OBSERVER_H

namespace logic {
/**
* @class Observer
* @brief Basis klasse voor alle observers.
* @tparam notification De notificatie set die geldt voor de observer.
*/
template <typename notification>
class Observer {
public:
    /**
     * @brief Default destructor.
     */
    virtual ~Observer() = default;

    /**
     * @brief Default constructor
     */
    Observer() = default;

    // pure virtual methodes
    /**
     * @brief Methode die wordt aangeroepen als de observer een notificatie ontvangt.
     * @param message De message die de observer ontvangt.
     */
    virtual void notify(const notification& message) = 0;
};
} // logic

#endif //PACKMAN_OBSERVER_H
