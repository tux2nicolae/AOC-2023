/**
 * Advent of code 2023
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <array>
#include <assert.h>
#include <deque>
#include <fstream>
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

vector<string> ExpandUniverse(vector<string> universe)
{
  // expand rows
  for (auto & line : universe)
  {
    auto galaxies = count_if(line.begin(), line.end(),
                             [](char c)
                             {
                               return c == '#';
                             });

    if (!galaxies)
    {
      line = string(line.size(), '$');
    }
  }

  // expand columns
  for (int j = 0; j < universe[0].size(); j++)
  {
    int galaxies = 0;
    for (int i = 0; i < universe.size(); i++)
    {
      if (universe[i][j] == '#')
        galaxies++;
    }

    if (!galaxies)
    {
      for (int i = 0; i < universe.size(); i++)
      {
        universe[i][j] = '$';
      }
    }
  }

  return universe;
}

long long Distance(vector<string> & universe, AOC::Point first, AOC::Point second, int step)
{
  long long sumVertical = 0;
  for (int i = min(first.x, second.x); i < max(first.x, second.x); i++)
  {
    if (universe[i][first.y] == '$')
      sumVertical += step;
    else
      sumVertical++;
  }

  long long sumHorisontal = 0;
  for (int j = min(first.y, second.y); j < max(first.y, second.y); j++)
  {
    if (universe[first.x][j] == '$')
      sumHorisontal += step;
    else
      sumHorisontal++;
  }

  return sumVertical + sumHorisontal;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          universe = reader.ReadLines();

  universe = ExpandUniverse(universe);

  vector<AOC::Point> points;

  for (int i = 0; i < universe.size(); i++)
  {
    for (int j = 0; j < universe[i].size(); j++)
    {
      if (universe[i][j] == '#')
        points.push_back({ i, j });
    }
  }

  long long part1Sum = 0;
  long long part2Sum = 0;
  for (auto [i, j] : AOC::GenerateIndexCombinations<2>(points.size()))
  {
    part1Sum += Distance(universe, points[i], points[j], 2);
    part2Sum += Distance(universe, points[i], points[j], 1000000);
  }

  cout << part1Sum << endl << part2Sum << endl;

  return 0;
}
