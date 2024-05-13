#ifndef ENTITY_DECORATOR_H_
#define ENTITY_DECORATOR_H_

#include "IEntity.h"
#include "SimulationModel.h"
#include "IController.h"

/**
 * @class IEntityDecorator
 * @brief Represents a decorator for an entity with another entity. Allows us to wrap
 *   an entity with functionality of another entity.
 */
class IEntityDecorator : public IEntity {
 public:
        /**
         * @brief IEntityDecorator constructor
         * @param entity The entity to decorate
         */
        IEntityDecorator(IEntity* entity);

        /**
         * @brief IEntityDecorator destructor - clean up dynamically allocated memory for entity's
         */
        virtual ~IEntityDecorator();

        /**
         * @brief Update the entity in the model (inherited from IEntity)
         * @param dt The time step
         */
        virtual void update(double dt);

        /**
         * @brief Get the entity that this decorator decorates
         * @return The entity that this decorator decorates
         */
        virtual IEntity* getEntity();

 protected:
        // The entity that this decorator decorates
        IEntity* entity = nullptr;
};

#endif
