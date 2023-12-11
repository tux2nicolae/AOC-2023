/**
 * Advent of code 2023
 * @author : Nicolae Telechi
 */
#include <algorithm>
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
  vector<string> expandedUniverse;

  // expand rows
  for (auto line : universe)
  {
    auto hashes = count_if(line.begin(), line.end(),
                           [](char c)
                           {
                             return c == '#';
                           });

    if (hashes)
    {
      expandedUniverse.push_back(line);
    }
    else
    {
      expandedUniverse.push_back(string(line.size(), '$'));
    }
  }

  universe = expandedUniverse;
  expandedUniverse.clear();
  expandedUniverse.resize(universe.size(), string());

  // expand columns
  for (int j = 0; j < universe[0].size(); j++)
  {
    //
    int hashes = 0;
    for (int i = 0; i < universe.size(); i++)
    {
      if (universe[i][j] == '#')
        hashes++;
    }

    if (hashes)
    {
      for (int i = 0; i < universe.size(); i++)
      {
        expandedUniverse[i] += universe[i][j];
      }
    }
    else
    {
      for (int i = 0; i < universe.size(); i++)
      {
        expandedUniverse[i] += "$";
      }
    }
  }

  return expandedUniverse;
}

long long Distance(vector<string> & universe, AOC::Point first, AOC::Point second)
{
  long long sumVertical = 0;
  for (int i = min(first.x, second.x); i < max(first.x, second.x); i++)
  {
    if (universe[i][first.y] == '$')
      sumVertical += 1000000;
    else
      sumVertical++;
  }

  long long sumHorisontal = 0;
  for (int j = min(first.y, second.y); j < max(first.y, second.y); j++)
  {
    if (universe[first.x][j] == '$')
      sumHorisontal += 1000000;
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

  long long sum = 0;
  for (int i = 0; i < points.size() - 1; i++)
  {
    for (int j = i + 1; j < points.size(); j++)
    {
      sum += Distance(universe, points[i], points[j]);
    }
  }

  cout << sum << endl;

  return 0;
}
