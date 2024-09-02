#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  //    float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
      if (!neighborhood.empty()) {
          Vector2f position = boid->transform.position;
        //Get info from all neighbors
        for(const Boid* b : neighborhood) {
          if(b->getPosition() == position) {
            continue;
          }
          Vector2f separationVector = boid->getPosition() - b->getPosition();
          float distance = sqrt((separationVector.x*separationVector.x) + (separationVector.y*separationVector.y));
          if(distance < desiredMinimalDistance) {
            //Add force inverse to distance to separation Force
            separatingForce = separatingForce + separationVector;
          }
        }
  //        // todo: find and apply force only on the closest mates
      }

  separatingForce = Vector2f::normalized(separatingForce);
  if(separatingForce.getMagnitude() > 0.2f) {
    separatingForce = separatingForce*0.2f;
  }
  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
