#include "IEntityDecorator.h"
#include "IController.h"

IEntityDecorator::IEntityDecorator(IEntity* entity) {
  this->entity = entity;
}

IEntityDecorator::~IEntityDecorator() {
  // Delete dynamically allocated variables
  if (entity) delete entity;
}

void IEntityDecorator::update(double dt) {}

IEntity* IEntityDecorator::getEntity() {
  return entity;
}
