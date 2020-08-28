#include <benchmark/benchmark.h>
#include <fstream>
#include <array>
#include <ctime>

#include <map>
#include <unordered_map>
#include <list>
#include "avl.hpp"

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
		if (noNulls || cvalues.empty()) {
			v.push_back(std::make_pair(values[rand() % 20], 1 + (rand() % 100)));
		} else {
			if ((rand() % 3 > 0) && cvalues.size() < 20) {
				v.push_back(std::make_pair(values[rand() % 20], 1 + (rand() % 100)));
			} else {
				auto it = cvalues.begin();
				std::advance(it, rand() % cvalues.size());
				v.push_back(std::make_pair((*it), 0));
			}
		}
	return v;
}

static void BM_Insert_On_Lists(benchmark::State& state) {
	std::list <std::pair<double, unsigned long>> asks, bids;
	bool flag;
	double bb_price, bb_amount, ba_price, ba_amount; /*
	unsigned max = 0;
	unsigned long long sumqa = 0, sumqb = 0;
	unsigned q; */
	std::vector <std::pair<double, unsigned long>> a, b;
	for (auto _ : state) {

state.PauseTiming ();
/*
		if (asks.size() > max)
			max = asks.size();
		if (bids.size() > max)
			max = bids.size();

		sumqa += asks.size();
		sumqb += bids.size();
		++q;
*/
		std::vector <double> vals;
		if (!asks.empty())
			for (auto it = asks.begin(); it != asks.end(); ++it)
				vals.push_back(it->first);
		a = generateRandomUpdate(1000.0, 1100.0, flag, vals);
		if (!vals.empty())
			vals.clear();
		if (!bids.empty())
			for (auto it = bids.begin(); it != bids.end(); ++it)
				vals.push_back(it->first);
		b = generateRandomUpdate(1100.0, 1200.0, flag, vals);
		if (!vals.empty())
			vals.clear();
state.ResumeTiming();

		if (flag) { // If first
			if (!a.empty())
				for (auto it = a.begin(); it != a.end(); ++it) 
					asks.insert(asks.begin(), {(*it).first, (*it).second});
			if (!b.empty())
				for (auto it = b.begin(); it != b.end(); ++it)
					bids.insert(bids.begin(), {(*it).first, (*it).second});
			flag = false;
		} else {
			if (!(a.empty())) {
				for (auto it = a.begin(); it != a.end(); ++it) {
					if (it->second != 0 || asks.empty()) {
						asks.insert(asks.begin(), {it->first, it->second});
					} else {
						for (auto it2 = asks.begin(); it2 != asks.end(); ++it2) {
							if (it2->first == it->first) {
								asks.erase(it2);
								break;
							}
						}
					}
				}
			}
			if (!(b.empty())) {
				for (auto it = b.begin(); it != b.end(); ++it) {
					if (it->second != 0 || bids.empty())
						bids.insert(bids.begin(), {it->first, it->second});
					else
						for (auto it2 = bids.begin(); it2 != bids.end(); ++it2)
							if (it2->first == it->first) {
								bids.erase(it2);
								break;
							}
				}
			}
		}

state.PauseTiming ();
		std::pair <double, unsigned long> mina;
		for (auto x : asks)
			if (x.first < mina.first)
				mina = x;
		ba_price = mina.first;
		ba_amount = mina.second;
		std::pair <double, unsigned long> maxb;
		for (auto x : bids)
			if (x.first > maxb.first)
				maxb = x;
		bb_price = maxb.first;
		bb_amount = maxb.second;
state.ResumeTiming();
	}
/*
	std::cout << max << std::endl;
	std::cout << sumqa / q << std::endl;
	std::cout << sumqb / q << std::endl;
*/
}
// Register the function as a benchmark
BENCHMARK(BM_Insert_On_Lists)->Iterations(1000000);


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
		a = generateRandomUpdate(1000.0, 1100.0, flag, vals);
		vals.clear();

		for (auto it = bids.begin(); it != bids.end(); ++it)
			vals.push_back(it->first);
		b = generateRandomUpdate(1100.0, 1200.0, flag, vals);
		vals.clear();
state.ResumeTiming();

		if (flag) { // If first
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
}
// Register the function as a benchmark
BENCHMARK(BM_Insert_On_Maps)->Iterations(1000000);

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
		a = generateRandomUpdate(1000.0, 1100.0, flag, vals);
		vals.clear();

		for (auto it = bids.begin(); it != bids.end(); ++it)
			vals.push_back(it->first);
		b = generateRandomUpdate(1100.0, 1200.0, flag, vals);
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
BENCHMARK(BM_Insert_On_UnorderedMaps)->Iterations(1000000);

static void BM_FindMax_On_Lists(benchmark::State& state) {
	std::list <std::pair<double, unsigned long>> asks, bids;
	bool flag;
	double bb_price, bb_amount, ba_price, ba_amount;
//	unsigned max = 0;
	std::vector <std::pair<double, unsigned long>> a, b;
	for (auto _ : state) {

state.PauseTiming (); /*
		if (asks.size() > max)
			max = asks.size();
		if (bids.size() > max)
			max = bids.size(); */

		std::vector <double> vals;
		for (auto it = asks.begin(); it != asks.end(); ++it)
			vals.push_back(it->first);
		a = generateRandomUpdate(1000.0, 1100.0, flag, vals);
		vals.clear();

		for (auto it = bids.begin(); it != bids.end(); ++it)
			vals.push_back(it->first);
		b = generateRandomUpdate(1100.0, 1200.0, flag, vals);
		vals.clear();

		if (flag) { // If first
			if (!a.empty())
				for (auto it = a.begin(); it != a.end(); ++it) 
					asks.insert(asks.begin(), {(*it).first, (*it).second});
			if (!b.empty())
				for (auto it = b.begin(); it != b.end(); ++it)
					bids.insert(bids.begin(), {(*it).first, (*it).second});
			flag = false;
		} else {
			if (!(a.empty())) {
				for (auto it = a.begin(); it != a.end(); ++it) {
					//std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
					if (it->second != 0)
						asks.insert(asks.begin(), {it->first, it->second});
					else
						for (auto it2 = asks.begin(); it2 != asks.end(); ++it2)
							if (it2->first == it->first) {
								asks.erase(it2);
								break;
							}
				}
			}
			if (!(b.empty())) {
				for (auto it = b.begin(); it != b.end(); ++it) {
					//std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
					if (it->second != 0)
						bids.insert(bids.begin(), {it->first, it->second});
					else
						for (auto it2 = bids.begin(); it2 != bids.end(); ++it2)
							if (it2->first == it->first) {
								bids.erase(it2);
								break;
							}
				}
			}
		}

state.ResumeTiming ();
		std::pair <double, unsigned long> mina;
		for (auto x : asks)
			if (x.first < mina.first)
				mina = x;
		ba_price = mina.first;
		ba_amount = mina.second;
		std::pair <double, unsigned long> maxb;
		for (auto x : bids)
			if (x.first > maxb.first)
				maxb = x;
		bb_price = maxb.first;
		bb_amount = maxb.second;
state.PauseTiming();
	}
//	std::cout << max << std::endl;
}
// Register the function as a benchmark
BENCHMARK(BM_FindMax_On_Lists)->Iterations(1000000);

static void BM_FindMax_On_Maps(benchmark::State& state) {
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
		a = generateRandomUpdate(1000.0, 1100.0, flag, vals);
		vals.clear();

		for (auto it = bids.begin(); it != bids.end(); ++it)
			vals.push_back(it->first);
		b = generateRandomUpdate(1100.0, 1200.0, flag, vals);
		vals.clear();

		if (flag) { // If first
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
state.ResumeTiming();
		ba_price = (*(asks.rbegin())).first;
		ba_amount = (*(asks.rbegin())).second;
		bb_price = (*(bids.begin())).first;
		bb_amount = (*(bids.begin())).second;
	}
}
// Register the function as a benchmark
BENCHMARK(BM_FindMax_On_Maps)->Iterations(1000000);

static void BM_FindMax_On_UnorderedMaps(benchmark::State& state) {
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
		a = generateRandomUpdate(1000.0, 1100.0, flag, vals);
		vals.clear();

		for (auto it = bids.begin(); it != bids.end(); ++it)
			vals.push_back(it->first);
		b = generateRandomUpdate(1100.0, 1200.0, flag, vals);
		vals.clear();

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
state.ResumeTiming();
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
state.PauseTiming();
	}
	//std::cout << max << std::endl;
}
// Register the function as a benchmark
BENCHMARK(BM_FindMax_On_UnorderedMaps)->Iterations(1000000);
/*
static void BM_FindMax_On_AVL_Tree(benchmark::State& state) {
	AVL asks, bids;
	bool flag;
	double bb_price, bb_amount, ba_price, ba_amount;
//	unsigned max = 0;
	std::vector <std::pair<double, unsigned long>> a, b;
	for (auto _ : state) {

state.PauseTiming ();

		std::vector <double> vals;
		for (AVL::iterator it = asks.root; it.isEnd() ; it.next())
			vals.push_back(it.curr()->key.first);
		a = generateRandomUpdate(1000.0, 1100.0, flag, vals);
		vals.clear();

		for (AVL::iterator it = asks.root; it.isEnd() ; it.next())
			vals.push_back(it.curr()->key.first);
		b = generateRandomUpdate(1100.0, 1200.0, flag, vals);
		vals.clear();

		if (flag) { // If first
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
						for (AVL::iterator it2 = asks.root; it2.isEnd() ; it2.next())
							if (it2.curr()->key.first == it->first)
								asks.remove(it2.curr()->key.first);
				}
			}
			if (!(b.empty())) {
				for (auto it = b.begin(); it != b.end(); ++it) {
					//std::cout << (*it)[0] << ' ' << (*it)[1] << std::endl;
					if (it->second != 0)
						bids.insert({it->first, it->second});
					else
						for (AVL::iterator it2 = asks.root; it2.isEnd() ; it2.next())
							if (it2.curr()->key.first == it->first)
								asks.remove(it2.curr()->key.first);
				}
			}
		}

state.ResumeTiming ();
		auto mina = std::min(asks.begin(), 
							asks.end(), 
							[] (const std::__1::__list_iterator<std::__1::pair<double, unsigned long>, void *> &a, const std::__1::__list_iterator<std::__1::pair<double, unsigned long>, void *> &b) {
			return a->first < b->first;
		});
		ba_price = mina->first;
		ba_amount = mina->second;
		auto maxb = std::max(bids.begin(), 
							bids.end(), 
							[] (const std::__1::__list_iterator<std::__1::pair<double, unsigned long>, void *> &a, const std::__1::__list_iterator<std::__1::pair<double, unsigned long>, void *> &b) {
			return a->first < b->first;
		});
		bb_price = maxb->first;
		bb_amount = maxb->second;
state.PauseTiming();
	}
//	std::cout << max << std::endl;
}
// Register the function as a benchmark
BENCHMARK(BM_FindMax_On_AVL_Tree)->Iterations(1000000);
*/
BENCHMARK_MAIN();
