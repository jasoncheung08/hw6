#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <string>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        int strLength = k.length();
        int group = 4;

        for (int i = strLength; i > 0 && group >= 0; i -= 6, --group) {
            unsigned long long value = 0;
            int power = 0;
            for (int j = std::max(0, i - 6); j < i; ++j) {
                value = value * 36 + letterDigitToNumber(k[j]);
            }
            w[group] = value;
        }


        unsigned long long hash = 0;
        for(int i = 0; i < 5; ++i) {
            hash += rValues[i] * w[i];
        }

        // debuging + print w[i] vals
        for (int i = 0; i < 5; ++i) {
            std::cout << "w[" << i << "] = " << w[i] << std::endl;
        }

        return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = std::tolower(letter);
        if(letter >= 'a' && letter <= 'z') {
            return letter - 'a';
        }
        else if (letter >= '0' && letter <= '9') {
            return 26 + (letter - '0');
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
