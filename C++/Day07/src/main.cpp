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

unordered_map<char, char> CardPoints{ { 'A', 14 }, { 'K', 13 }, { 'Q', 12 }, { 'J', 11 },
                                      { 'T', 10 }, { '9', 9 },  { '8', 8 },  { '7', 7 },
                                      { '6', 6 },  { '5', 5 },  { '4', 4 },  { '3', 3 },
                                      { '2', 2 } };

unordered_map<char, char> PointsCard{ { 14, 'A' }, { 13, 'K' }, { 12, 'Q' }, { 11, 'J' },
                                      { 10, 'T' }, { 9, '9' },  { 8, '8' },  { 7, '7' },
                                      { 6, '6' },  { 5, '5' },  { 4, '4' },  { 3, '3' },
                                      { 2, '2' } };

std::vector<int> GetFrequency(string str)
{
  std::vector<int> frequency(255, 0);

  for (auto c : str)
    frequency[c]++;

  return frequency;
}

bool IsFullHouese(string str)
{
  auto frequency = GetFrequency(str);
  sort(frequency.begin(), frequency.end(), greater<int>());

  return (frequency[0] == 3 && frequency[1] == 2);
}

bool IsTwoPairs(string str)
{
  auto frequency = GetFrequency(str);
  sort(frequency.begin(), frequency.end(), greater<int>());

  return frequency[0] == 2 && frequency[1] == 2;
}

struct Hand
{
  string hand;
  int    bid{ 0 };

  bool operator<(Hand & aOther)
  {
    if (hand == aOther.hand)
    {
      assert(false);
      return false;
    }

    auto frequency      = GetFrequency(hand);
    auto otherFrequency = GetFrequency(aOther.hand);

    auto left  = *max_element(begin(frequency), end(frequency));
    auto right = *max_element(begin(otherFrequency), end(otherFrequency));

    assert(left);
    assert(right);

    // Full house
    if (IsFullHouese(hand) && IsFullHouese(aOther.hand))
    {
      return hand < aOther.hand;
    }
    else if (IsFullHouese(hand) && right < 4)
    {
      return false;
    }
    else if (IsFullHouese(aOther.hand) && left < 4)
    {
      return true;
    }

    // X of a kind
    if (left < right)
    {
      return true;
    }
    else if (left > right)
    {
      return false;
    }
    else if (left == right)
    {
      // Two pairs
      if (!IsTwoPairs(hand) && IsTwoPairs(aOther.hand))
        return true;
      else if (IsTwoPairs(hand) && !IsTwoPairs(aOther.hand))
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

  // transform back
  for (auto & hand : hands)
  {
    for (auto & c : hand.hand)
      c = PointsCard[c];
  }

  long long sum = 0;
  for (int i = 0; i < hands.size(); i++)
  {
    auto & hand = hands[i];
    sum += hand.bid * (i + 1ll);

    out << hand.hand << endl;
  }

  cout << sum;

  return 0;
}
