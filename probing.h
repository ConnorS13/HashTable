#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>
#include <algorithm>

#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion

    int sizeOf;
    // enumeration for entry state
    std::vector<std::pair<int, int>> table;
    int bucketCount;

public:
    ProbingHash(int n = 11) 
    {
        sizeOf = 0;
        bucketCount = n;
    }

    ~ProbingHash() 
    {
        this->clear();
    }

    int size() 
    {
        return sizeOf;
    }

    V operator[](const K& key) 
    {
        std::cout << "";
        return key;
    }

    bool insert(const std::pair<K, V>& pair) 
    {
        std::vector<EntryState> enumCheck;
       /* int x = pair.first;
        // std::vector<std::pair<int,int>>::iterator it;
        auto it = (table.begin() + x);

        if (table.find(table.begin(), table.end(), pair) != table.end())
        {
           table.insert(it, pair); 
        }

        else
        {
            return false;
        }
*/
        EntryState enumVal;
        int x = pair.first, y = pair.second;
        // std::vector<std::pair<int,int>>::iterator it;
        auto it = (table.begin() + x);
        //auto he = (enumCheck.begin() + x);
        table.insert(it, std::make_pair(x, y));
        enumVal = VALID;
        //enumCheck.insert(he, VALID);
        
        if (enumVal == VALID)
        {

            //std::cout << sizeOf;
            ++sizeOf;

            if (load_factor() > 0.45)
            {
                bucket_count();
            }
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
        // std::cout << ((sizeOf * 1.0) / bucketCount);
        return ((sizeOf * 1.0) / bucketCount);
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

    int hash(const K& key) {
    // take the modulo of tablesize and the key value!    
        int x = key;

        x = x % bucketCount;

        return x;         
    }
    
};

#endif //__PROBING_HASH_H
