#include "WindRule.h"
#include <imgui.h>
#include <iostream>
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f WindRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Converts windAngle to radians for calculations
  Vector2f windForce = Vector2f(sin((windAngle * (M_PI / 180))), cos((windAngle * (M_PI / 180))));
  //returns force multiplied by the weight of the wind
  windForce = windForce.normalized();
  //Not sure why but the force isn't working properly.  For some reason the updated wind angle doesn't update force direction and the calcs aren't proper?
    return (windForce*weight);
}

bool WindRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valueHasChanged = false;

  if (ImGui::SliderAngle("Wind Direction", &windAngle, 0)) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}