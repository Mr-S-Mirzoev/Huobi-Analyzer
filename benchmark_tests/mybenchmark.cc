#include <benchmark/benchmark.h>
#include <fstream>
#include <set>
#include <array>
#include <ctime>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>

double fRand(double fMin, double fMax)
{
    double f = (double)std::rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

std::vector <std::pair<double, unsigned long>> generateRandomUpdate(double min, double max, bool noNulls, std::vector <double> &cvalues) {
	std::array<double,20> values;
	for (int i = 0; i < 20; ++i) {
		values[i] = fRand(min, max);
	} 
	srand(time(NULL));
	std::vector <std::pair<double, unsigned long>> v;
	for (int i = 0; i < (std::rand() % 10); ++i)
		if (noNulls || values.empty()) {
			v.push_back(std::make_pair(values[rand() % 20], 1 + (rand() % 100)));
		} else {
			if ((rand() % 3 > 0)) {
				v.push_back(std::make_pair(values[rand() % 20], 1 + (rand() % 100)));
			} else {
				auto it = cvalues.begin();
				std::advance(it, rand() % cvalues.size());
				v.push_back(std::make_pair((*it), 0));
			}
		}
	return v;
}

static void BM_Insert_On_Maps(benchmark::State& state) {
	std::map <double, unsigned long> asks, bids;
	bool flag;
	double bb_price, bb_amount, ba_price, ba_amount;
	unsigned max = 0;
	std::vector <std::pair<double, unsigned long>> a, b;
	for (auto _ : state) {
		state.PauseTiming ();
		if (asks.size() > max)
			max = asks.size();
		if (bids.size() > max)
			max = bids.size();
		std::vector <double> vals;
		for (auto it = asks.begin(); it != asks.end(); ++it)
			vals.push_back(it->first);
		a = generateRandomUpdate(10000.0, 11000.0, flag, vals);
		vals.clear();
		for (auto it = bids.begin(); it != bids.end(); ++it)
			vals.push_back(it->first);
		b = generateRandomUpdate(11000.0, 12000.0, flag, vals);
		vals.clear();
		state.ResumeTiming();
		if (flag) {
			if (!a.empty())
				for (auto it = a.begin(); it != a.end(); ++it) 
					asks.insert({(*it).first, (*it).second});
			if (!b.empty())
				for (auto it = b.begin(); it != b.end(); ++it)
					bids.insert({(*it).first, (*it).second});
			flag = false;
		} else {
			if (!(a.empty())) {
				for (auto it = a.begin(); it != a.end(); ++it) {
					//std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
					if (it->second != 0)
						asks.insert({it->first, it->second});
					else
						asks.erase(it->first);
				}
			}
			if (!(b.empty())) {
				for (auto it = b.begin(); it != b.end(); ++it) {
					//std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
					if (it->second != 0)
						bids.insert({it->first, it->second});
					else
						bids.erase(it->first);
				}
			}
		}
		state.PauseTiming ();
		ba_price = (*(asks.rbegin())).first;
		ba_amount = (*(asks.rbegin())).second;
		bb_price = (*(bids.begin())).first;
		bb_amount = (*(bids.begin())).second;
		state.ResumeTiming();
	}
	//std::cout << max << std::endl;
}
// Register the function as a benchmark
BENCHMARK(BM_Insert_On_Maps)->Iterations(100000);

// Define another benchmark
static void BM_Insert_On_UnorderedMaps(benchmark::State& state) {
	std::unordered_map <double, unsigned long> asks, bids;
	bool flag;
	double asks_max, bids_min;
	unsigned max = 0;
	unsigned long asks_amount, bids_amount;
	bool ask_max_invalidated = false, bid_min_invalidated = false;
	std::vector <std::pair<double, unsigned long>> a, b;
	for (auto _ : state) {
		state.PauseTiming ();
		if (asks.size() > max)
			max = asks.size();
		if (bids.size() > max)
			max = bids.size();
		std::vector <double> vals;
		for (auto it = asks.begin(); it != asks.end(); ++it)
			vals.push_back(it->first);
		a = generateRandomUpdate(10000.0, 11000.0, flag, vals);
		vals.clear();
		for (auto it = bids.begin(); it != bids.end(); ++it)
			vals.push_back(it->first);
		b = generateRandomUpdate(11000.0, 12000.0, flag, vals);
		vals.clear();
		state.ResumeTiming();
		if (flag) {
			if (!a.empty())
				for (auto it = a.begin(); it != a.end(); ++it) {
					if (!ask_max_invalidated && ((*it).first > asks_max)) {
						asks_max = (*it).first;
						asks_amount = (*it).second;
					}
					asks.insert({(*it).first, (*it).second});
				}
			if (!b.empty())
				for (auto it = b.begin(); it != b.end(); ++it) {
					if (!bid_min_invalidated && ((*it).first < bids_min)) {
						bids_min = (*it).first;
						bids_amount = (*it).second;
					}
					bids.insert({(*it).first, (*it).second});
				}
			flag = false;
		} else {
			if (!(a.empty())) {
				for (auto it = a.begin(); it != a.end(); ++it) {
					//std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
					if (it->second != 0) {
						if (!ask_max_invalidated && ((*it).first > asks_max)) {
							asks_max = (*it).first;
							asks_amount = (*it).second;
						}
						asks.insert({(*it).first, (*it).second});
					} else {
						asks.erase(it->first);
						if (it->first == asks_max)
							ask_max_invalidated = true;
					}
				}
			}
			if (!(b.empty())) {
				for (auto it = b.begin(); it != b.end(); ++it) {
					//std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
					if (it->second != 0) {
						if (!bid_min_invalidated && ((*it).first < bids_min)) {
							bids_min = (*it).first;
							bids_amount = (*it).second;
						}
						bids.insert({(*it).first, (*it).second});
					} else {
						bids.erase(it->first);
						if (it->first == bids_min)
							bid_min_invalidated = true;
					}
				}
			}
		}
		state.PauseTiming ();
		if (bid_min_invalidated) {
			bool not_set = true;

			for (auto val : bids) {
				if (not_set) {
					not_set = false;
					bids_min = val.first;
					bids_amount = val.second;
				}
				if (val.first < bids_min) {
					bids_min = val.first;
					bids_amount = val.second;
				}
			}
			bid_min_invalidated = false;
		}

		if (ask_max_invalidated) {
			bool not_set = true;

			for (auto val : asks) {
				if (not_set) {
					not_set = false;
					asks_max = val.first;
					asks_amount = val.second;
				}
				if (val.first > asks_max) {
					asks_max = val.first;
					asks_amount = val.second;
				}
			}
			ask_max_invalidated = false;
		}

		state.ResumeTiming();
	}
	//std::cout << max << std::endl;
}
// Register the function as a benchmark
BENCHMARK(BM_Insert_On_UnorderedMaps)->Iterations(100000);



BENCHMARK_MAIN();
