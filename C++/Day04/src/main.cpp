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

struct ScratchCard
{
  int      id{};
  int      instances{ 1 };
  int      matchingNumbers{ 0 };
  set<int> winningNumbers;
  set<int> numbersYouHave;
};

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader  reader(in);
  vector<string> v = reader.ReadLines();

  long long sum = 0;

  vector<ScratchCard> cards;

  for (auto line : v)
  {
    auto matches = AOC::ExtractMatches(line, "Card (.*): (.*)");
    assert(matches.size() == 2);

    auto cardId = matches[0];

    auto _numbers = AOC::Explode(matches[1], " \\| ");
    assert(_numbers.size() == 2);

    set<int> winningNumbers;
    set<int> numbersYouHave;

    std::istringstream ss(_numbers[0]);

    int n = 0;
    while (ss >> n)
      winningNumbers.insert(n);

    std::istringstream ss2(_numbers[1]);

    int n2 = 0;
    while (ss2 >> n2)
      numbersYouHave.insert(n2);

    vector<int> intersection;
    set_intersection(winningNumbers.begin(), winningNumbers.end(), numbersYouHave.begin(),
                     numbersYouHave.end(), back_inserter(intersection));

    if (intersection.size())
    {
      int points = pow(2, intersection.size() - 1);
      sum += points;
    }

    cards.push_back(ScratchCard{ stoi(cardId.c_str()), 1, (int)intersection.size(), winningNumbers,
                                 numbersYouHave });
  };

  std::cout << sum << endl;

  int sum2 = 0;
  for (int i = 0; i < cards.size(); i++)
  {
    auto & currentCard = cards[i];
    sum2 += currentCard.instances;

    for (int j = 0; j < currentCard.matchingNumbers; j++)
    {
      assert(i + j + 1 < cards.size());
      cards[i + j + 1].instances += currentCard.instances;
    }
  }

  cout << sum2;

  return 0;
}
