/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    if(n == 0){return 0;}
    if(n ==1){return 1;}
    return memoized_fib(n-2) + memoized_fib(n-1);
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */
    static map<unsigned long, unsigned long> fib_map = {{0, 0}, {1, 1}, {2, 1}};
    map<unsigned long, unsigned long>::iterator lookup = fib_map.find(n);
    if(lookup == fib_map.end()){fib_map[n] = memoized_fib(n-1) + memoized_fib(n-2);}
    return fib_map[n];
}
