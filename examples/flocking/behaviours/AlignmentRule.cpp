#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();
  int totalForces = 0;
  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  for(Boid* b : neighborhood) {
    if(b->getPosition() == boid->getPosition()) {
      continue;
    }
    totalForces++;
    averageVelocity += b->getVelocity();
  }

  if(totalForces == 0) {
    return Vector2f::zero();
  }

  averageVelocity /= totalForces;
  if (averageVelocity.getMagnitude() > 0.6f) {
    averageVelocity *= 0.6f;
  }
  return Vector2f::normalized(averageVelocity);
}