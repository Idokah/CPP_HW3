#ifndef CPP_HW3_SERIALIZATIONHELPER_H
#define CPP_HW3_SERIALIZATIONHELPER_H

#include <iostream>
#include <map>
#include "consts.h"
#include <algorithm>
#include <vector>

using namespace std;

template<class K, class V>
static void loadMap(istream &in, map<K, V> map)
{
    int mapSize;
    K key;
    V value;
    pair <K,V> pair;
    in.read(rcastc(&mapSize), sizeof(mapSize));
    for (int i = 0; i < mapSize; ++i)
    {
        in.read(rcastc(&key), sizeof(key));
        in.read(rcastc(&value), sizeof(value));
        map.insert(make_pair(key, value));
    }
}


template <class K,class V>
int cmpValues(pair<K, V>& a, pair<K, V>& b)
{
    if (a.second == b.second) return 0;
    return (a.second < b.second)? -1 : 1;
}

class cmp
{
public:
    template <class K,class V>
    int operator()(const pair<K,V>& a,const pair<K,V>& b)
    {
        if (a.second == b.second) return 0;
        return (a.second < b.second)? -1 : 1;
    }
};

template <class K,class V>
vector<pair<K, V>> getMapSortByValue(map<K,V> map)
{
    vector<pair<K, V>> sortedMapVector;
    for (auto const& pair : map)
    {
        sortedMapVector.push_back(pair);
    }
    sort(sortedMapVector.begin(), sortedMapVector.end(), cmp());
    return sortedMapVector;
}

template<class K, class V>
static void saveMap(ostream &out, map<K, V> map)
    {
        int mapSize=map.size();
        out.write(rcastcc(&mapSize), sizeof(mapSize));
        for (auto const& pair : map)
            {
            auto key=pair.first;
            auto value=pair.second;
            out.write(rcastcc(&key), sizeof(key));
            out.write(rcastcc(&value), sizeof(value));
        }
    }


#endif //CPP_HW3_SERIALIZATIONHELPER_H
