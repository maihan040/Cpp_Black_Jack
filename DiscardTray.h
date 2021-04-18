//
// Class declaration file for the "DiscardTray" class. This class will simulate the tray 
// where the discarded playing cards from the "Dealer" and "Player" instances will be 
// stored 
// 
// note: class can't be further extended as of now 
// 
// Design pattern used: Singleton 
// 
// Modified on: 03/12/2021
// 

#pragma once

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include <deque>
#include <vector>
#include "Card.h"
#include "Shoe.h"

using namespace std; 

/****************************************************************************************/
/*				"Card" class declaration				*/
/****************************************************************************************/
class DiscardTray final {
private: 

	//
	// Singleton variables/constructor 
	//
	DiscardTray() = default; 
	static DiscardTray* _instance; 
	deque<Card> CardTray; 

    	//
    	// Alias to create iterators for this class
    	//
    	using CardTrayIterator = deque<Card>::iterator;

public: 

	//
	// Singleton member method 
	//
	static DiscardTray* get_instance();
	
	//
	// Delete copy constructor as well as assignment operator 
	//
	DiscardTray(const DiscardTray&) = delete; 
	DiscardTray& operator=(const DiscardTray&) = delete; 

	//
	// Default methods
	//
	~DiscardTray() = default; 
	
	//
	// Remaining member methods 
	//

	/* Collect player and dealers cards */
	void collect_participants_cards(vector<Card> cards);

	/* Move the contents of the tray back to the shoe */
	void empty_Tray(Shoe* GameShoe);

	/* Empty the tray */
	void clear_tray(); 
};