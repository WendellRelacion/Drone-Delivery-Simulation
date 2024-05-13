#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

// Import dependencies
#include "IEntityDecorator.h"
#include "SimulationModel.h"
#include "IStrategy.h"
#include "BeelineStrategy.h"
#include "Battery.h"
#include "DataCollectorSingleton.h"

/**
 * @class BatteryDecorator
 * @brief Represents a battery entity decorator. Extends battery functionality to an entity.
 */
class BatteryDecorator : public IEntityDecorator {
 public:
        /**
         * @brief BatteryDecorator constructor
         * @param entity The entity to decorate
         */
        BatteryDecorator(IEntity* entity);

        /**
         * @brief BatteryDecorator destructor
         */
        ~BatteryDecorator();

        /**
         * @brief Update the battery wrapped entity in the model
         * @param dt The time step
         */
        virtual void update(double dt);

        /**
         * @brief Get the battery wrapped entity
         * @return The battery wrapped entity
         */
        virtual IEntity* getEntity();

        /**
         * @brief Get the recharge route strategy
         * @return The recharge route strategy
         */
        IStrategy* getRechargeRoute();

        /**
         * @brief Set the recharge route strategy
         * @param newRechargeRoute The new recharge route strategy
         */
        void setRechargeRoute(IStrategy* newRechargeRoute);

 private:
        // The associated battery entity: must be spawned in from "umn.json"
        Battery* battery = nullptr;
        // The strategy used to route to the closest recharge station
        IStrategy* rechargeRoute = nullptr;
        // Tick count threshold for logging data
        int tickCount = 0;
};

#endif
