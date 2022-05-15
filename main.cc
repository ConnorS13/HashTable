#include <map>
#include <string>
#include <chrono>
#include <cassert>
#include "chaining.h"
#include "probing.h"
#include <iostream>
#include <fstream>

/*
    Connor Strom
    PA3 - Hash Table using Chaining and Probing
    Fall 2021
    CPTS 223
*/

// implementation was displaying wrong bucket count because of order function called, -2 fixed. 

void testHash(Hash<int, int> *hash, std::ofstream &myfile)
{
    int x = hash->size(), y = hash->bucket_count() - 2; 
    float z = hash->load_factor();


    myfile << "current size: " << x << " bucket count: " << y
           << " load factor: " << z << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; ++i)
    {
        assert(hash->insert(std::make_pair(i, i)));
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    assert((*hash)[97] == 97);
    end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    hash->erase(97);
    end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    assert((*hash)[10000] == 10000);
    end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    x = hash->size(), y = hash->bucket_count(), z = hash->load_factor();

    myfile << "current size: " << x << " bucket count: " << y
           << " load factor: " << z << std::endl;
    hash->clear();
}

int main(int argc, char *argv[])
{
    std::ofstream myfile;
    myfile.open("output.txt");
    ChainingHash<int, int> cHash(101);
    ProbingHash<int, int> pHash(101);
    testHash(&cHash, myfile);
    testHash(&pHash, myfile);
    myfile.close();
}