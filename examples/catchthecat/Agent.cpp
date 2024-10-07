#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    Point2D current = frontier.top();
    if (frontierSet.contains(current))
    {
        // remove the current from frontierset
        frontierSet.erase(current);
        frontier.pop();
    }
    // mark current as visited
    visited[current] = true;
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> neighbors = getVisitableNeighbors(w, current);
    // iterate over the neighs:
    for (Point2D neighbor: neighbors) {
      if (visited[neighbor] == false) {
        frontier.push(neighbor);
        frontierSet.insert(neighbor);
      }
    }
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D p) { 
    auto sideOver2 = w->getWorldSideSize() / 2;
    std::vector<Point2D> neighbors;

    // Check all sides
    if (p.Up().y >= sideOver2 && w->getContent(p.Up()) == false) {
      neighbors.push_back(p.Up());
    }
    if (p.Right().x <= sideOver2 && w->getContent(p.Right()) == false) {
      neighbors.push_back(p.Right());
    }
    if (p.Down().y <= sideOver2 && w->getContent(p.Down()) == false) {
      neighbors.push_back(p.Down());
    }
    if (p.Left().x >= sideOver2 && w->getContent(p.Left()) == false) {
      neighbors.push_back(p.Left());
    }

    return neighbors;
}
