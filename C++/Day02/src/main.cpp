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

  FStreamReader  reader(in);
  vector<string> v = reader.ReadLines();

  int s        = 0;
  int sumPower = 0;

  // part 2
  for (auto & line : v)
  {
    int maxRed   = 0;
    int maxGreen = 0;
    int maxBlue  = 0;

    auto game = AOC::Explode(line, ": ");

    assert(game.size() == 2);
    int  gameID  = AOC::ExtractInt(game[0], "Game (.*)");
    bool posible = true;

    auto subsets = AOC::Explode(game[1], "; ");
    for (auto subset : subsets)
    {
      auto extractions = AOC::Explode(subset, ", ");

      for (auto extraction : extractions)
      {
        auto extractionMatches = AOC::ExtractMatches(extraction, "(.*) (.*)");
        assert(extractionMatches.size() == 2);

        int    number = stoi(extractionMatches[0]);
        string color  = extractionMatches[1];

        if (color == "red")
        {
          maxRed = max(maxRed, number);

          if (number > 12)
            posible = false;
        }
        else if (color == "green")
        {
          maxGreen = max(maxGreen, number);

          if (number > 13)
            posible = false;
        }
        else if (color == "blue")
        {
          maxBlue = max(maxBlue, number);

          if (number > 14)
            posible = false;
        }
      }
    }

    if (posible)
    {
      s += gameID;
    }

    int power = maxRed * maxGreen * maxBlue;
    sumPower += power;
  }

  cout << s << endl;
  cout << sumPower;

  return 0;
}
