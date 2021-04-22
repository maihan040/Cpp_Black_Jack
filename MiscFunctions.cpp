
/****************************************************************************************/
/*					                    Imports	                    					*/
/****************************************************************************************/
#include "HeaderFiles/MiscFunctions.h"

/****************************************************************************************/
/*                                  Function Definitions	                    		*/
/****************************************************************************************/

//
// Function to generate a random number
//
int generate_uniform_random_number(int start, int end) {

    //
    // Validation checks
    //
    if (start < 0 or end < 0) {
        start = 1; 
        end = INT_MAX;
    }

    //
    // Local variables used to generate the random number via the "Mersenne Twister" 
    // algorithm
    //
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(start, end);
	
    //
    // Return the randomly generated number
    //
    return distr(generator);
}
