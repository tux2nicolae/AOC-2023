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

vector<long long> SolveVertical(const vector<string> & pattern)
{
  vector<long long> results;

  // vertical
  for (int x = 0; x < pattern[0].size() - 1; x++)
  {
    bool allGood = true;
    for (int i = 0; i < pattern.size(); i++)
    {
      for (int a = x, b = x + 1; a >= 0 && b < pattern[0].size(); a--, b++)
      {
        if (pattern[i][a] != pattern[i][b])
        {
          allGood = false;
          break;
        }
      }

      if (!allGood)
        break;
    }

    if (allGood)
    {
      results.push_back(x + 1);
    }
  }

  return results;
}

vector<long long> SolveHorisontal(const vector<string> & pattern)
{
  vector<long long> results;

  // horisontal
  for (int x = 0; x < pattern.size() - 1; x++)
  {
    bool allGood = true;
    for (int j = 0; j < pattern[0].size(); j++)
    {
      for (int a = x, b = x + 1; a >= 0 && b < pattern.size(); a--, b++)
      {
        if (pattern[a][j] != pattern[b][j])
        {
          allGood = false;
          break;
        }
      }

      if (!allGood)
        break;
    }

    if (allGood)
    {
      results.push_back(x + 1);
    }
  }

  return results;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  vector<vector<string>> patterns;

  vector<string> currentPattern;
  for (auto line : lines)
  {
    if (line.empty())
    {
      patterns.push_back(currentPattern);
      currentPattern.clear();
    }
    else
    {
      currentPattern.push_back(line);
    }
  }

  patterns.push_back(currentPattern);

  auto inverse = [](char c) -> char
  {
    if (c == '.')
      return '#';
    else
      return '.';
  };

  auto useNext = [](vector<long long> current, vector<long long> next) -> std::optional<long long>
  {
    if (current.size())
      next.erase(remove(next.begin(), next.end(), current[0]), next.end());

    if (!next.size())
      return nullopt;

    return next[0];
  };

  long long sumVertical   = 0;
  long long sumHorisontal = 0;
  for (const auto & pattern : patterns)
  {
    vector<long long> verticals   = SolveVertical(pattern);
    vector<long long> horisontals = SolveHorisontal(pattern);

    // part 2
    long long nextVertical   = 0;
    long long nextHorisontal = 0;

    vector<long long> nextVerticals;
    vector<long long> nextHorisontals;
    auto              nextPattern = pattern;

    bool found = false;
    for (size_t i = 0; i < nextPattern.size(); i++)
    {
      for (size_t j = 0; j < nextPattern[i].size(); j++)
      {
        nextPattern[i][j] = inverse(nextPattern[i][j]);

        nextVertical   = useNext(verticals, SolveVertical(nextPattern)).value_or(0);
        nextHorisontal = useNext(horisontals, SolveHorisontal(nextPattern)).value_or(0);

        if (nextVertical || nextHorisontal)
        {
          assert(nextVertical == 0 || nextHorisontal == 0);
          found = true;
          break;
        }

        // inverse back
        nextPattern[i][j] = inverse(nextPattern[i][j]);
      }

      if (found)
        break;
    }

    if (!found)
    {
      for (auto line : pattern)
        out << line << endl;
    }

    assert(found);
    assert(nextVertical == 0 || nextHorisontal == 0);

    // part 1
    // sumVertical += vertical;
    // sumHorisontal += horisontal;

    // part 2
    sumVertical += nextVertical;
    sumHorisontal += nextHorisontal;
  }

  std::cout << sumVertical + 100 * sumHorisontal;

  return 0;
}
