#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Return a force proportional to the proximity of the boids with the bounds, and opposed to it
  Vector2f force = Vector2f::zero();  // zero

  auto winSize = this->world->engine->window->size();

  //Checks the location of the boid and if it is too close to a side of the screen, applies a force in the opposite direction
  //Right side
  if(boid->getPosition().x > winSize.x - desiredDistance) {
    force.x = desiredDistance/(boid->getPosition().x-this->world->engine->window->size().x);
  }
//Left side
  if(boid->getPosition().x < desiredDistance) {
    force.x = desiredDistance/boid->getPosition().x;
  }
  //Top Side
  if(boid->getPosition().y > winSize.y - desiredDistance) {
    force.y = desiredDistance/(boid->getPosition().y-this->world->engine->window->size().y);
  }
  //bottom side
  if(boid->getPosition().y < desiredDistance) {
    force.y = desiredDistance/boid->getPosition().y;
  }
  //Multiplies returned force by 2.5 to ensure no boids can speed past the repelling force
  return force * 2.5f;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}