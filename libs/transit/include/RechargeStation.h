#ifndef RECHARGE_STATION_H_
#define RECHARGE_STATION_H_

#include "IEntity.h"

/**
 * @class RechargeStation
 * @brief Represents a recharge station entity. Extends IEntity.
 */
class RechargeStation : public IEntity {
 public:
  /**
   * @brief A new recharge station is created
   * @param obj JSON object containing the drone's information
   */
  RechargeStation(JsonObject& obj);

  /**
   * @brief RechargeStation destructor
   */
  ~RechargeStation();

  /**
   * @brief Update the recharge station in the model
   * @param dt The time step
   */
  void update(double dt);
};

#endif
