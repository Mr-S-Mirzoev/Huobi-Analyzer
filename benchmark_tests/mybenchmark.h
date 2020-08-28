#define InsertVectorsonLists(vector1, vector2, list1, list2, flag) if (flag) { \
			if (!vector1.empty()) \
				for (auto it = vector1.begin(); it != vector1.end(); ++it) \
					list1.insert(list1.begin(), {(*it).first, (*it).second}); \
			if (!vector2.empty())  \
				for (auto it = vector2.begin(); it != vector2.end(); ++it) \
					list2.insert(list2.begin(), {(*it).first, (*it).second}); \
			flag = false; \
		} else { \
			if (!(vector1.empty())) { \
				for (auto it = vector1.begin(); it != vector1.end(); ++it) { \
					if (it->second != 0 || list1.empty()) { \
						list1.insert(list1.begin(), {it->first, it->second}); \
					} else { \
						for (auto it2 = list1.begin(); it2 != list1.end(); ++it2) { \
							if (it2->first == it->first) { \
								list1.erase(it2); \
								break; \
							} \
						} \
					} \
				} \
			} \
			if (!(vector2.empty())) { \
				for (auto it = vector2.begin(); it != vector2.end(); ++it) { \
					if (it->second != 0 || list2.empty()) \
						list2.insert(list2.begin(), {it->first, it->second}); \
					else \
						for (auto it2 = list2.begin(); it2 != list2.end(); ++it2) \
							if (it2->first == it->first) { \
								list2.erase(it2); \
								break; \
							} \
				} \
			} \
		} 

#define FindMaxonLists(ba_price, ba_amount, bb_price, bb_amount, list1, list2) std::pair <double, unsigned long> mina; \
		for (auto x : list1) \
			if (x.first < mina.first) \
				mina = x; \
		ba_price = mina.first; \
		ba_amount = mina.second; \
		std::pair <double, unsigned long> maxb; \
		for (auto x : list2) \
			if (x.first > maxb.first) \
				maxb = x; \
		bb_price = maxb.first; \
		bb_amount = maxb.second;

#define InsertVectorsonMaps(vector1, vector2, map1, map2, flag) if (flag) { \
			if (!vector1.empty()) \
				for (auto it = vector1.begin(); it != vector1.end(); ++it) \
					map1.insert({(*it).first, (*it).second}); \
			if (!vector2.empty()) \
				for (auto it = vector2.begin(); it != vector2.end(); ++it) \
					map2.insert({(*it).first, (*it).second}); \
			flag = false; \
		} else { \
			if (!(vector1.empty())) { \
				for (auto it = vector1.begin(); it != vector1.end(); ++it) { \
					if (it->second != 0) \
						map1.insert({it->first, it->second}); \
					else \
						map1.erase(it->first); \
				} \
			} \
			if (!(vector2.empty())) { \
				for (auto it = vector2.begin(); it != vector2.end(); ++it) { \
					if (it->second != 0) \
						map2.insert({it->first, it->second}); \
					else \
						map2.erase(it->first); \
				} \
			} \
		} 

#define FindMaxonMaps(ba_price, ba_amount, bb_price, bb_amount, map1, map2) ba_price = (*(map1.rbegin())).first; \
		ba_amount = (*(map1.rbegin())).second; \
		bb_price = (*(map2.begin())).first; \
		bb_amount = (*(map2.begin())).second; 

#define InsertVectorsonUnorderedMaps(vector1, vector2, map1, map2, flag, bidinv, askinv, bids_min, bids_amount, asks_max, asks_amount) if (flag) { \
			if (!vector1.empty()) \
				for (auto it = vector1.begin(); it != vector1.end(); ++it) { \
					if (!askinv && ((*it).first > asks_max)) { \
						asks_max = (*it).first; \
						asks_amount = (*it).second; \
					} \
					map1.insert({(*it).first, (*it).second}); \
				} \
			if (!vector2.empty()) \
				for (auto it = vector2.begin(); it != vector2.end(); ++it) { \
					if (!bidinv && ((*it).first < bids_min)) { \
						bids_min = (*it).first; \
						bids_amount = (*it).second; \
					} \
					map2.insert({(*it).first, (*it).second}); \
				} \
			flag = false; \
		} else { \
			if (!(vector1.empty())) { \
				for (auto it = vector1.begin(); it != vector1.end(); ++it) { \
					if (it->second != 0) { \
						if (!askinv && ((*it).first > asks_max)) { \
							asks_max = (*it).first; \
							asks_amount = (*it).second; \
						} \
						map1.insert({(*it).first, (*it).second}); \
					} else { \
						map1.erase(it->first); \
						if (it->first == asks_max) \
							askinv = true; \
					} \
				} \
			} \
			if (!(vector2.empty())) { \
				for (auto it = vector2.begin(); it != vector2.end(); ++it) { \
					if (it->second != 0) { \
						if (!bidinv && ((*it).first < bids_min)) { \
							bids_min = (*it).first; \
							bids_amount = (*it).second; \
						} \
						map2.insert({(*it).first, (*it).second}); \
					} else { \
						map2.erase(it->first); \
						if (it->first == bids_min) \
							bidinv = true; \
					} \
				} \
			} \
		}

#define FindMaxonUnorderedMaps(bids_min, bids_amount, asks_max, asks_amount, map1, map2, bidinv, askinv) if (bidinv) { \
			bool not_set = true; \
			for (auto val : map2) { \
				if (not_set) { \
					not_set = false; \
					bids_min = val.first; \
					bids_amount = val.second; \
				} \
				if (val.first < bids_min) { \
					bids_min = val.first; \
					bids_amount = val.second; \
				} \
			} \
			bidinv = false; \
		} \
\
		if (askinv) { \
			bool not_set = true; \
\
			for (auto val : map1) { \
				if (not_set) { \
					not_set = false; \
					asks_max = val.first; \
					asks_amount = val.second; \
				} \
				if (val.first > asks_max) { \
					asks_max = val.first; \
					asks_amount = val.second; \
				} \
			} \
			askinv = false; \
		}

#define InsertVectorsonAVL(vector1, vector2, avl1, avl2, flag) if (flag) { \
			if (!vector1.empty()) \
				for (auto it = vector1.begin(); it != vector1.end(); ++it) \
					avl1.insert((*it).first, (*it).second); \
			if (!vector2.empty()) \
				for (auto it = vector2.begin(); it != vector2.end(); ++it) \
					avl2.insert((*it).first, (*it).second); \
			flag = false; \
		} else { \
			if (!(vector1.empty())) { \
				for (auto it = vector1.begin(); it != vector1.end(); ++it) { \
					if (it->second != 0) \
						avl1.insert(it->first, it->second); \
					else \
						avl1.remove(it->first); \
				} \
			} \
			if (!(vector2.empty())) { \
				for (auto it = vector2.begin(); it != vector2.end(); ++it) { \
					if (it->second != 0) \
						avl2.insert(it->first, it->second); \
					else \
						avl2.remove(it->first); \
				} \
			} \
		} 

#define FindMaxonAVL(ba_price, ba_amount, bb_price, bb_amount, avl1, avl2) AVL<double, unsigned long>::node *min = avl1.min(); \
			ba_price = min->key; \
			ba_amount = min->value; \
		AVL<double, unsigned long>::node *max = avl2.max(); \
			bb_price = max->key; \
			bb_amount = max->value; 
