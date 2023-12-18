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

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  map<AOC::Point, string> map;

  std::map<long long, long long> maxX;

  AOC::Point current{ 0, 0 };

  for (auto line : lines)
  {
    auto matches = AOC::ExtractMatches(line, "(.*) (.*) \\((.*)\\)");
    assert(matches.size() == 3);

    int steps = stoi(matches[1]);
    while (steps--)
    {
      current      = current.GetNeighbour(matches[0]);
      map[current] = "#";  // matches[2];

      maxX[current.y] = std::max(maxX[current.y], current.x);
    }
  }

  queue<AOC::Point>          q;
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
  }

  for (int y = -500; y < 500; y++)
  {
    for (int x = -500; x < 500; x++)
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
