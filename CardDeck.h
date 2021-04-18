// 
// Class declaration file for the "Deck" class this class will simulate a standard 52 card 
// deck which can be used for any card game
// 
// Design pattern used: None 
// 

#pragma once

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include <algorithm>
#include <vector>
#include <iostream>
#include <random> 
#include <limits.h>
#include "Card.h"
#include "MiscFunctions.h"

using namespace std; 

/****************************************************************************************/
/*				"Deck" class declaration				*/
/****************************************************************************************/
class Deck final{
public:

	//
	// Member and friend declarations
	//
	vector<Card> PlayDeck; 
	friend class Shoe;

	//
	// Alias definitions
	//
	using PlayDeckIterator = vector<Card>::iterator;
	using MapIterator = map<string, short>::const_iterator;

	//
	// Constructors and destructors
	//
	Deck();	
	~Deck() = default;

    	//
	// Special member methods 
 	//

	/* copy constructor */
    	Deck(const Deck&) = default;
	
	/* copy assignment operator */
	Deck& operator=(const Deck&) = default;

	/* move constructor */
    	Deck(Deck&&) = default; 

	/* move assignment operator */
    	Deck& operator=(Deck&&) = default; 

	//
	// Remining class methods 
	//
	Card draw_card();	// Returns a card from the deck 
	void clear_deck();	// Clears the vector	

	//
	// Debug methods
	//
	void print_deck();
};