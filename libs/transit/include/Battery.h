#ifndef BATTERY_H_
#define BATTERY_H_

#include "IEntity.h"

/**
 * @class Battery
 * @brief Represents a battery entity. Extends IEntity.
 */
class Battery : public IEntity {
 public:
    /**
     * @brief A new battery is created
     * @param obj JSON object containing the drone's information
     */
    Battery(JsonObject& obj);

    /**
     * @brief Battery destructor
     */
    ~Battery();

    /**
     * @brief Update the battery in the model
     * @param dt The time step
     */
    void update(double dt);

    /**
     * @brief Get the battery level
     * @return The battery level
     */
    double getBattery();

    /**
     * @brief Set the battery level
     * @param newBattery The new battery level
     */
    void setBattery(double newBattery);

    /**
     * @brief Get the isCharging boolean
     * @return The isCharging boolean
     */
    bool getIsCharging();

    /**
     * @brief Set the isCharging boolean
     * @param newIsCharging The new isCharging boolean
     */
    void setIsCharging(bool newIsCharging);

 protected:
    // The actual battery level percentage
    double batteryLevel = 100;
    // Represents whether battery is currently charging or not
    bool isCharging = false;
};

#endif
