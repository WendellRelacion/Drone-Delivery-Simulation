#ifndef RECHARGE_STATION_FACTORY_H_
#define RECHARGE_STATION_FACTORY_H_

#include <vector>
#include "IEntityFactory.h"
#include "RechargeStation.h"

/**
 * @class RechargeStationFactory
 * @brief Recharge Station Factory to produce RechargeStation class.
 */
class RechargeStationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for RechargeStationFactory class.
   */
  virtual ~RechargeStationFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity JsonObject to be used to create the new entity.
   * @return RechargeStation that was created if it was created successfully, or a
   *    nullpointer if creation failed.
   */
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
