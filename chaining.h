/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    int sizeOf;
    int bucketCount;
    vector <list<pair<K,V>>> table;
public:
    ChainingHash(int n = 11) 
    {
        sizeOf = 0;
        bucketCount = n;
    }

    ~ChainingHash() 
    {
        this->clear();
    }

    int size() 
    {
        return sizeOf;
    }

    V operator[](const K& key) 
    {
        //std::vector<std::pair<int, int>> it;
        std::cout << "";
        return key; //find(table.begin(), table.end(), ).second;
    }

    bool insert(const std::pair<K, V>& pair) 
    {
        /*int x = pair.first, y = pair.second;
        // std::vector<std::pair<int,int>>::iterator it;
        auto it = (table.begin() + x);

        table.insert(it, std::make_pair(x, y));

        ++sizeOf;
*/
        list<std::pair<int, int>> mylist;
        int x = pair.first, y = pair.second;
        // std::vector<std::pair<int,int>>::iterator it;
        auto it = (table.begin() + x);

        mylist.push_back(std::make_pair(x, y));

        table.insert(it, mylist);
        //std::cout << sizeOf;
        ++sizeOf;

        if (load_factor() > 0.45)
        {
            bucket_count();
        }

        return true;
    }

    void erase(const K& key) 
    {
        auto it = (table.begin() + key);
        --sizeOf;
        table.erase(it);
    }

    void clear() 
    {
        table.clear();
    }

    int bucket_count() 
    {
        // std::cout << findNextPrime(bucketCount + 1) << " " << std::endl;
        //if (bucketCount != 101)
        //{
        bucketCount = findNextPrime(bucketCount);
        //}

        return bucketCount;
    }

    float load_factor() 
    {
        return ((1.0 * sizeOf) / bucketCount);
    }

private:
    int findNextPrime(int n)
    {
        n = n + 1;
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) 
    {
        // hash is modding corresponding to the key that is submitted. 
        // take the modulo of tablesize and the key value!
        
        int x = key;

        x = x % bucketCount;

        return x;       
    }

};

#endif //__CHAINING_HASH_H
