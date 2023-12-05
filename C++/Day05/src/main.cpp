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

  bool operator<(const MapEntry aOther) { return this->sourceStart < aOther.sourceStart; }
};

long long Convert(vector<MapEntry> & aMap, long long from)
{
  for (auto & entry : aMap)
  {
    if (entry.sourceStart <= from && from <= entry.sourceStart + entry.lenght)
    {
      auto diff = from - entry.sourceStart;
      return entry.destinationStart + diff;
    }
  }

  return from;
}

vector<pair<long long, long long>> ConvertRange(vector<MapEntry> &         aMap,
                                                pair<long long, long long> range)
{
  long long from   = range.first;
  long long lenght = range.second;

  vector<pair<long long, long long>> newRanges;

  // inside range
  for (auto & entry : aMap)
  {
    if (entry.sourceStart <= from && from < entry.sourceStart + entry.lenght)
    {
      auto diff        = from - entry.sourceStart;
      auto destination = entry.destinationStart + diff;

      // full inside
      if (destination + lenght < entry.destinationStart + entry.lenght)
      {
        newRanges.push_back({ destination, lenght });
      }
      // starting inside range but overflow
      else
      {
        long long lenghtDiff = (entry.destinationStart + entry.lenght) - destination;
        newRanges.push_back({ destination, lenghtDiff });

        assert(lenght - lenghtDiff >= 0);

        auto childRanges = ConvertRange(aMap, { from + lenghtDiff, lenght - lenghtDiff });
        copy(begin(childRanges), end(childRanges), back_inserter(newRanges));
      }

      return newRanges;
    }
  }

  for (auto & entry : aMap)
  {
    // starting outside
    if (from < entry.sourceStart && entry.sourceStart < from + lenght)
    {
      long long lenghtDiff = entry.sourceStart - from;
      newRanges.push_back({ from, lenghtDiff });

      assert(lenght - lenghtDiff >= 0);

      auto childRanges = ConvertRange(aMap, { from + lenghtDiff, lenght - lenghtDiff });
      copy(begin(childRanges), end(childRanges), back_inserter(newRanges));

      return newRanges;
    }
  }

  newRanges.push_back({ from, lenght });
  return newRanges;
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

  vector<pair<long long, long long>> seedsRanges;
  for (int i = 0; i < seeds.size(); i += 2)
  {
    seedsRanges.push_back({ seeds[i], seeds[i + 1] });
  }

  //
  vector<MapEntry> seedToSoil;
  vector<MapEntry> soilToFertilizer;
  vector<MapEntry> fertilizerToWater;
  vector<MapEntry> waterToLight;
  vector<MapEntry> lightToTemperature;
  vector<MapEntry> temperatureToHumidity;
  vector<MapEntry> humidityToLocation;

  sort(begin(seedToSoil), end(seedToSoil));
  sort(begin(soilToFertilizer), end(soilToFertilizer));
  sort(begin(fertilizerToWater), end(fertilizerToWater));
  sort(begin(waterToLight), end(waterToLight));
  sort(begin(lightToTemperature), end(lightToTemperature));
  sort(begin(temperatureToHumidity), end(temperatureToHumidity));
  sort(begin(humidityToLocation), end(humidityToLocation));

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

  // part 1
  auto runAllConversions = [&](long long initialSeed) -> long long
  {
    auto seed = Convert(seedToSoil, initialSeed);
    seed      = Convert(soilToFertilizer, seed);
    seed      = Convert(fertilizerToWater, seed);
    seed      = Convert(waterToLight, seed);
    seed      = Convert(lightToTemperature, seed);
    seed      = Convert(temperatureToHumidity, seed);
    seed      = Convert(humidityToLocation, seed);

    return seed;
  };

  long long minSeed = numeric_limits<long long>::max();
  for (auto seed : seeds)
  {
    seed    = runAllConversions(seed);
    minSeed = min(minSeed, seed);
  }

  cout << minSeed << endl;

  // part 2
  auto runOneRangeConversion =
    [&](vector<MapEntry> & map, vector<pair<long long, long long>> & initialRanges)
  {
    vector<pair<long long, long long>> ranges;

    for (auto & seedRange : initialRanges)
    {
      auto resultRanges = ConvertRange(map, seedRange);
      copy(resultRanges.begin(), resultRanges.end(), back_inserter(ranges));
    }

    return ranges;
  };

  auto runAllRangeConversions = [&](vector<pair<long long, long long>> initialRanges)
  {
    auto seed = runOneRangeConversion(seedToSoil, initialRanges);
    seed      = runOneRangeConversion(soilToFertilizer, seed);
    seed      = runOneRangeConversion(fertilizerToWater, seed);
    seed      = runOneRangeConversion(waterToLight, seed);
    seed      = runOneRangeConversion(lightToTemperature, seed);
    seed      = runOneRangeConversion(temperatureToHumidity, seed);
    seed      = runOneRangeConversion(humidityToLocation, seed);

    return seed;
  };

  long long minSeed2 = numeric_limits<long long>::max();

  auto ranges = runAllRangeConversions(seedsRanges);
  for (auto range : ranges)
    minSeed2 = min(minSeed2, range.first);

  cout << minSeed2 << endl;

  return 0;
}
