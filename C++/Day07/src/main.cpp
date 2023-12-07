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

bool part2 = false;

unordered_map<char, char> CardPoints{ { 'A', 14 }, { 'K', 13 }, { 'Q', 12 }, { 'J', 11 },
                                      { 'T', 10 }, { '9', 9 },  { '8', 8 },  { '7', 7 },
                                      { '6', 6 },  { '5', 5 },  { '4', 4 },  { '3', 3 },
                                      { '2', 2 } };

std::vector<int> GetFrequency(string str)
{
  std::vector<int> frequency(15, 0);

  for (auto c : str)
    frequency[c]++;

  return frequency;
}

bool IsFullHouese(vector<int> frequency)
{
  sort(frequency.begin(), frequency.end(), greater<int>());
  return (frequency[0] == 3 && frequency[1] == 2);
}

bool IsTwoPairs(vector<int> frequency)
{
  sort(frequency.begin(), frequency.end(), greater<int>());
  return frequency[0] == 2 && frequency[1] == 2;
}

struct Hand
{
  string hand;
  int    bid{ 0 };

  bool operator<(Hand & aOther)
  {
    auto frequency      = GetFrequency(hand);
    auto otherFrequency = GetFrequency(aOther.hand);

    // part 2
    auto jokerfrequency      = frequency[CardPoints['J']];
    auto otherJokerFrequency = otherFrequency[CardPoints['J']];

    if (part2)
    {
      frequency[CardPoints['J']] -= jokerfrequency;
      otherFrequency[CardPoints['J']] -= otherJokerFrequency;
    }

    auto & left  = *max_element(begin(frequency), end(frequency));
    auto & right = *max_element(begin(otherFrequency), end(otherFrequency));

    // part 2
    if (part2)
    {
      left += jokerfrequency;
      right += otherJokerFrequency;
    }

    // Full house
    if (IsFullHouese(frequency) && IsFullHouese(otherFrequency))
      return hand < aOther.hand;
    else if (IsFullHouese(frequency) && right < 4)
      return false;
    else if (IsFullHouese(otherFrequency) && left < 4)
      return true;

    // X of a kind
    if (left < right)
      return true;
    else if (left > right)
      return false;
    else if (left == right)
    {
      // Two pairs
      if (!IsTwoPairs(frequency) && IsTwoPairs(otherFrequency))
        return true;
      else if (IsTwoPairs(frequency) && !IsTwoPairs(otherFrequency))
        return false;

      return hand < aOther.hand;
    }

    assert(false);
    return false;
  }
};

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader  reader(in);
  vector<string> v = reader.ReadLines();

  vector<Hand> hands;

  // part 1
  for (auto line : v)
  {
    auto matches = AOC::ExtractMatches(line, "(.*) (.*)");
    assert(matches.size() == 2);

    // transform to points
    string hand = matches[0];
    for (auto & c : hand)
      c = CardPoints[c];

    hands.push_back(Hand{ hand, atoi(matches[1].c_str()) });
  }

  sort(hands.begin(), hands.end());

  long long sumPart1 = 0;
  for (int i = 0; i < hands.size(); i++)
    sumPart1 += hands[i].bid * (i + 1ll);

  cout << sumPart1 << endl;

  // part 2
  part2 = true;

  hands.clear();
  CardPoints['J'] = 1;

  for (auto line : v)
  {
    auto matches = AOC::ExtractMatches(line, "(.*) (.*)");
    assert(matches.size() == 2);

    // transform to points
    string hand = matches[0];
    for (auto & c : hand)
      c = CardPoints[c];

    hands.push_back(Hand{ hand, atoi(matches[1].c_str()) });
  }

  sort(hands.begin(), hands.end());

  long long sumPart2 = 0;
  for (int i = 0; i < hands.size(); i++)
    sumPart2 += hands[i].bid * (i + 1ll);

  cout << sumPart2;

  return 0;
}
