#ifndef BATTERY_FACTORY_H_
#define BATTERY_FACTORY_H_

#include <vector>
#include "IEntityFactory.h"
#include "Battery.h"

/**
 * @class BatteryFactory
 * @brief Battery Factory to produce Battery class.
 */
class BatteryFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for BatteryFactory class.
   */
  virtual ~BatteryFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity JsonObject to be used to create the new entity.
   * @return Battery that was created if it was created successfully, or a
   *    nullpointer if creation failed.
   */
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
