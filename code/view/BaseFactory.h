//
// Created by niels-hertoghs on 12/12/25.
//

#ifndef PACKMAN_BASEFACTORY_H
#define PACKMAN_BASEFACTORY_H

/**
 * @class BaseFactory
 * @brief Basis abstracte klasse voor alle factories.
 */
class BaseFactory {
public:
    /**
     * @brief Default constructor.
     */
    BaseFactory() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~BaseFactory() = default;
};


#endif //PACKMAN_BASEFACTORY_H
