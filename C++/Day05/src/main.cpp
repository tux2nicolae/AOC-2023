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

struct MapEntry
{
  long long destinationStart{};
  long long sourceStart{};
  long long lenght{};
};

pair<long long, long long> Convert(vector<MapEntry> & aMap, long long from)
{
  for (auto entry : aMap)
  {
    if (entry.sourceStart <= from && from <= entry.sourceStart + entry.lenght)
    {
      auto diff = from - entry.sourceStart;
      return make_pair(entry.destinationStart + diff, entry.sourceStart + entry.lenght - from);
    }
  }

  return make_pair(from, 0);
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader  reader(in);
  vector<string> v = reader.ReadLines();

  vector<long long> seeds;

  auto matches = AOC::ExtractMatches(v[0], "seeds: (.*)");

  std::istringstream ss(matches[0]);

  long long n = 0;
  while (ss >> n)
    seeds.push_back(n);

  vector<pair<long long, long long>> seedsRange;
  for (int i = 0; i < seeds.size(); i += 2)
  {
    seedsRange.push_back({ seeds[i], seeds[i + 1] });
  }

  //
  vector<MapEntry> seedToSoil;
  vector<MapEntry> soilToFertilizer;
  vector<MapEntry> fertilizerToWater;
  vector<MapEntry> waterToLight;
  vector<MapEntry> lightToTemperature;
  vector<MapEntry> temperatureToHumidity;
  vector<MapEntry> humidityToLocation;

  string lastMap = "";
  for (int i = 1; i < v.size(); i++)
  {
    if (v[i].empty())
    {
      lastMap = v[++i];
      continue;
    }

    auto tokens = AOC::Explode(v[i], " ");
    assert(tokens.size() == 3);

    MapEntry entry{
      stoll(tokens[0]),
      stoll(tokens[1]),
      stoll(tokens[2]),
    };

    if (lastMap == "seed-to-soil map:")
      seedToSoil.push_back(entry);
    if (lastMap == "soil-to-fertilizer map:")
      soilToFertilizer.push_back(entry);
    if (lastMap == "fertilizer-to-water map:")
      fertilizerToWater.push_back(entry);
    if (lastMap == "water-to-light map:")
      waterToLight.push_back(entry);
    if (lastMap == "light-to-temperature map:")
      lightToTemperature.push_back(entry);
    if (lastMap == "temperature-to-humidity map:")
      temperatureToHumidity.push_back(entry);
    if (lastMap == "humidity-to-location map:")
      humidityToLocation.push_back(entry);
  }

  auto runAllConversions = [&](long long initialSeed) -> long long
  {
    long long minRemaining{};
    long long seed{}, remaining{};

    tie(seed, remaining) = Convert(seedToSoil, initialSeed);
    minRemaining         = min(minRemaining, remaining);

    tie(seed, remaining) = Convert(soilToFertilizer, seed);
    minRemaining         = min(minRemaining, remaining);

    tie(seed, remaining) = Convert(fertilizerToWater, seed);
    minRemaining         = min(minRemaining, remaining);

    tie(seed, remaining) = Convert(waterToLight, seed);
    minRemaining         = min(minRemaining, remaining);

    tie(seed, remaining) = Convert(lightToTemperature, seed);
    minRemaining         = min(minRemaining, remaining);

    tie(seed, remaining) = Convert(temperatureToHumidity, seed);
    minRemaining         = min(minRemaining, remaining);

    tie(seed, remaining) = Convert(humidityToLocation, seed);
    minRemaining         = min(minRemaining, remaining);

    return seed;
  };

  // part 1
  // long long minSeed = numeric_limits<long long>::max();
  // for (auto seed : seeds)
  //{
  //   seed    = runAllConversions(seed);
  //   minSeed = min(minSeed, seed);
  // }

  // cout << minSeed << endl;

  long long minSeed2 = numeric_limits<long long>::max();
  for (auto [seedStart, seedLength] : seedsRange)
  {
    for (long long seed = seedStart; seed < seedStart + seedLength; seed++)
    {
      auto result = runAllConversions(seed);

      minSeed2 = min(minSeed2, result);
    }
  }

  cout << minSeed2 << endl;

  return 0;
}
