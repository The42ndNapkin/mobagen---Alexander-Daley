#include "WindRule.h"
#include <imgui.h>
#include <iostream>
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f WindRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Converts windAngle to radians for calculations
  Vector2f windForce = Vector2f(sin((windAngle)), cos((windAngle)));
  //returns force multiplied by the weight of the wind
  windForce = windForce.normalized();
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