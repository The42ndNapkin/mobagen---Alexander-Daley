#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();
  int totalForces = 0;
  //iterate over neighborhood to get the average velocity of said neighborhood
  for(Boid* b : neighborhood) {
    if(b->getPosition() == boid->getPosition()) {
      continue;
    }
    totalForces++;
    averageVelocity += b->getVelocity();
  }

  //Returns a zero vector if the neighborhood is empty, as there are no boids to align with
  if(totalForces == 0) {
    return Vector2f::zero();
  }

  //calculates the average velocity of the neighborhood, capping the weight of the force.
  averageVelocity /= totalForces;
  if (averageVelocity.getMagnitude() > 0.6f) {
    averageVelocity *= 0.6f;
  }
  //Returns a normalized vector to just get the direction of alignment
  return Vector2f::normalized(averageVelocity);
}