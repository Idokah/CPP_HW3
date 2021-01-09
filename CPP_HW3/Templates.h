#ifndef CPP_HW3_SERIALIZATIONHELPER_H
#define CPP_HW3_SERIALIZATIONHELPER_H

#include <iostream>
#include <map>
#include "consts.h"
#include <algorithm>
#include <vector>

using namespace std;

template<class K, class V>
map<K, V> loadMap(istream &in, map<K, V> map)
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
    return map;
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

template<class K>
static void saveVector(ostream& out, vector<K> vec)
{
    int size = vec.size();
    out.write(rcastcc(&size), sizeof(size));
    for (auto const& item : vec)
    {
        item->save(out);
    }
}

template <class T>
void printVector(vector<T> vec)
{
    for (auto item: vec) {
        cout << *item << endl;
    }
}

template <class K, class V>
vector<pair<K, V>> getMapSortByValue(map<K, V> map)
{
    vector<pair<K, V>> sortedMapVector;
    for (auto const& pair : map)
    {
        sortedMapVector.push_back(pair);
    }
    sort(sortedMapVector.begin(), sortedMapVector.end(), [](const pair<int, int>& a, const pair<int, int>& b) -> bool {return a.second > b.second; });
    return sortedMapVector;
}

#endif //CPP_HW3_SERIALIZATIONHELPER_H
