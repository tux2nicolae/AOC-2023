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

struct Boat
{
  int speed{ 0 };
};

long long RunRace(long long time, long long speed, long long distance)
{
  long long sum = 0;
  for (int i = 0; i <= time; i++)
  {
    long long newTime  = time - i;
    long long newSpeed = speed + i;

    if (newTime * newSpeed > distance)
      sum++;
  }

  return sum;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader  reader(in);
  vector<string> v = reader.ReadLines();

  auto time     = AOC::ExtractMatches(v[0], "Time: (.*) (.*) (.*) (.*)");
  auto distance = AOC::ExtractMatches(v[1], "Distance: (.*) (.*) (.*) (.*)");

  int race1 = RunRace(53, 0, 250);
  int race2 = RunRace(91, 0, 1330);
  int race3 = RunRace(67, 0, 1081);
  int race4 = RunRace(68, 0, 1025);

  // int race1 = RunRace(7, 0, 9);
  // int race2 = RunRace(15, 0, 40);
  // int race3 = RunRace(30, 0, 200);
  // int race4 = 1;

  cout << race1 * race2 * race3 * race4 << endl;

  long long racePart2 = RunRace(53916768, 0, 250133010811025);
  cout << racePart2;

  return 0;
}
