//
// Miscellaneous function declarations that will be used throughout the Black Jack game 
//
#pragma once

/****************************************************************************************/
/*                                      Imports                                         */
/****************************************************************************************/
#include <random> 
#include <algorithm>
#include <limits.h>

/****************************************************************************************/
/*				                         Globals		                				*/
/****************************************************************************************/
static const char NEW_LINE = '\n';
static const unsigned short STD_WAIT_TIME = 3;

/****************************************************************************************/
/*                                  Function Declarations                               */
/****************************************************************************************/

//
// Function to generate a random number
//
int generate_uniform_random_number(int start, int end);

//
// Function template to shuffle cards inside 
// a given container 
//
template <typename iterator>
extern void shuffle_cards(iterator start, iterator end) {

    //
    // Utilize the STL "shuffle" algorithm to rear-
    // range the "Card" objects stored in a given 
    // container which in this case will be either
    // a vector or a deque
    //

    //
    // Local variables
    //
    std::random_device rd;
    std::mt19937 g(rd());

    //
    // Call the function to shuffle the "Card" objects
    //
    std::shuffle(start, end, g);
}