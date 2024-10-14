#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<AStarNode> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  AStarNode start = AStarNode(w->getCat());
  start.heuristic = start.calcHeuristic(start.position, w->getWorldSideSize() / 2);
  Point2D goal = nearestExit(w, start.position);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    AStarNode current = frontier.top();
    if (frontierSet.contains(current.position))
    {
        // remove the current from frontierset
        frontierSet.erase(current.position);
        frontier.pop();
    }
    
    // mark current as visited
    visited[current.position] = true;

    if (current.position.x == w->getWorldSideSize() / 2 || current.position.x == w->getWorldSideSize() / -2
        || current.position.y == w->getWorldSideSize() / 2 || current.position.y == w->getWorldSideSize() / -2)
    {
      borderExit = current.position;
      break;
    }
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> neighbors = getVisitableNeighbors(w, current.position, visited,frontierSet);
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    for (Point2D neighbor: neighbors) {
      if (visited[neighbor] == false) {
        AStarNode neigh = AStarNode(neighbor);
        neigh.accCost = current.accCost + 1;
        neigh.heuristic = neigh.calcHeuristic(neigh.position, w->getWorldSideSize() / 2);
        cameFrom[neighbor] = current.position;
        frontier.push(neigh);
        frontierSet.insert(neighbor);
      }
    }
    
  }
  //Build the path vector backwards using the camefrom array
  //  if the border is not infinity, build the path from border to the cat using the camefrom map
  //  if there isnt a reachable border, just return empty vector
  //  if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat moves
  vector<Point2D> path = {};
  if (borderExit != Point2D::INFINITE)
  {
    Point2D newCurr = cameFrom[borderExit];
    while (newCurr != start.position)
    {
      path.push_back(newCurr);
      newCurr = cameFrom[newCurr];
    }
  }
  
  return path;
}

//Function to get the nearest wall from a point
Point2D Agent::nearestExit(World* w, Point2D p)
{ 
  int halfSize = w->getWorldSideSize() / 2;
  int yToWall = halfSize - abs(p.y);
  int xToWall = halfSize - abs(p.x);
  if (yToWall > xToWall && p.x > 0)
  {
    return Point2D(halfSize, p.y);
  }
  else if (yToWall > xToWall && p.x < 0)
  {
    return Point2D(-halfSize, p.y);
  } 
  else if (yToWall < xToWall && p.y > 0)
  {
    return Point2D(p.x, halfSize);
  }
  else if (yToWall < xToWall && p.y < 0)
  {
    return Point2D(p.x, -halfSize);
  }

  return Point2D(p.x, p.y);

}

//Returns visitable neighbors
std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D p, unordered_map<Point2D, bool> visited, unordered_set<Point2D> frontierSet) { 
    auto sideOver2 = w->getWorldSideSize() / 2;
    std::vector<Point2D> neighbors;
    int start = p.y;

    //Edit x offset based on the hexogonal row
    if (start % 2 == 0)
    {
      start = -1;
    } else {
      start = 0;
    }
    //Check neighbors that are visitable
    //Top neighbors
    for (int i = p.x + start; i < p.x + start + 2; i++)
    {
      Point2D temp = Point2D(i, p.y - 1);
      if (!w->getContent(temp) && w->getCat() != temp && !visited[temp] && !frontierSet.contains(temp))
      {
        neighbors.push_back(temp);
      }
    }
    //Middle neighbors
    for (int i = p.x - 1; i < p.x + 2; i++) {
      Point2D temp = Point2D(i, p.y);
      if (!w->getContent(temp) && w->getCat() != temp && !visited[temp] && !frontierSet.contains(temp) && temp != p) {
        neighbors.push_back(temp);
      }
    }
    //Bottom neighbors
    for (int i = p.x + start; i < p.x + start + 2; i++) {
      Point2D temp = Point2D(i, p.y + 1);
      if (!w->getContent(temp) && w->getCat() != temp && !visited[temp] && !frontierSet.contains(temp)) {
        neighbors.push_back(temp);
      }
    }
    return neighbors;
}
