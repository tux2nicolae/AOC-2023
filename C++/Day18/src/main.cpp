/**
 * Advent of code 2023
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <array>
#include <assert.h>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#include "../../AOCLib/src/Algorithm.h"
#include "../../AOCLib/src/FStreamReader.h"
#include "../../AOCLib/src/FStreamWriter.h"
#include "../../AOCLib/src/Math.h"
#include "../../AOCLib/src/Parse.h"
#include "../../AOCLib/src/Point.h"
#include "../../AOCLib/src/Ship.h"
#include "../../AOCLib/src/Time.h"
#include "../../AOCLib/src/Util.h"

bool part2 = false;

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  map<AOC::Point, string> map;

  auto maxX = numeric_limits<long long>::min();
  auto minX = numeric_limits<long long>::max();
  auto maxY = numeric_limits<long long>::min();
  auto minY = numeric_limits<long long>::max();

  AOC::Point current{ 0, 0 };

  for (auto line : lines)
  {
    auto matches = AOC::ExtractMatches(line, "(.*) (.*) \\((.*)\\)");
    assert(matches.size() == 3);

    // part 1
    string directionPart1 = matches[0];
    auto   stepsPart1     = stoll(matches[1]);

    // part 2;
    auto   stepsPart2     = std::stoll(matches[2].substr(1, 5), nullptr, 16);
    string directionPart2 = [&]()
    {
      auto direction = std::stoll(matches[2].substr(6, 1), nullptr, 16);
      switch (direction)
      {
      case 0:
        return "R";
      case 1:
        return "D";
      case 2:
        return "L";
      case 3:
        return "U";
      }

      assert(false);
      return "";
    }();

    auto steps     = stepsPart1;
    auto direction = directionPart1;

    if (part2)
    {
      steps     = stepsPart2;
      direction = directionPart2;
    }

    cout << direction << " " << steps << endl;

    while (steps--)
    {
      current      = current.GetNeighbour(direction);
      map[current] = "#";

      maxX = std::max(maxX, current.x);
      minX = std::min(minX, current.x);

      maxY = std::max(maxY, current.y);
      minY = std::min(minY, current.y);
    }
  }

  /*queue<AOC::Point>          q;
  std::map<AOC::Point, bool> visited;

  q.push({ -100, -100 });

  while (!q.empty())
  {
    auto current = q.front();
    q.pop();

    for (const auto & neighbour : current.GetDirect2DNeighbours())
    {
      if (neighbour.IsInBoundary({ -500, -500 }, { 500, 500 }) && !visited[neighbour] &&
          map[neighbour] != "#")
      {
        visited[neighbour] = true;
        map[neighbour]     = "*";
        q.push(neighbour);
      }
    }
  }*/

  for (int y = minY; y <= maxY; y++)
  {
    for (int x = minX; x <= maxX; x++)
    {
      if (map.count({ x, y }))
        out << map[{ x, y }];
      else
        out << ".";
    }
    out << endl;
  }

  cout << map.size();

  return 0;
}
