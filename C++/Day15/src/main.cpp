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

int HASH(string str)
{
  int currentValue = 0;
  for (auto c : str)
  {
    currentValue += c;
    currentValue *= 17;
    currentValue %= 256;
  }

  return currentValue;
}

struct Lense
{
  string label;
  int    focal = 0;
};

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();
  assert(lines.size() == 1);

  int sumPart1 = 0;

  vector<list<Lense>> boxes;
  boxes.resize(256);

  auto tokens = AOC::Explode(lines[0], ",");
  for (auto token : tokens)
  {
    sumPart1 += HASH(token);

    if (token.back() == '-')
    {
      token.pop_back();

      auto & box = boxes[HASH(token)];
      box.remove_if(
        [&](auto lense)
        {
          return lense.label == token;
        });
    }
    else
    {
      auto matches = AOC::ExtractMatches(token, "(.*)=(.*)");
      assert(matches.size() == 2);

      auto & box = boxes[HASH(matches[0])];
      auto   it  = find_if(begin(box), end(box),
                           [&](const Lense & lense)
                           {
                          return lense.label == matches[0];
                        });

      if (it != box.end())
      {
        it->focal = stoi(matches[1]);
      }
      else
      {
        box.push_back({ matches[0], stoi(matches[1]) });
      }
    }
  }

  int sumPart2 = 0;
  for (size_t i = 0; i < boxes.size(); i++)
  {
    for (size_t j = 0; j < boxes[i].size(); j++)
    {
      auto lense = boxes[i].begin();
      advance(lense, j);

      sumPart2 += (i + 1) * (j + 1) * lense->focal;
    }
  }

  cout << sumPart1 << endl;
  cout << sumPart2 << endl;

  return 0;
}
