//
// Implementation file for the "DiscardTray" class 
//

/******************************************************************************************/
/*										Imports											  */
/******************************************************************************************/
#include "DiscardTray.h"

/******************************************************************************************/
/*									Method definitions									  */
/******************************************************************************************/

//
// Initialize the instance to 0, since this is a singleton class and it will be created on
// demand 
//
DiscardTray* DiscardTray::_instance = 0;

//
// Static implementation
//
DiscardTray* DiscardTray::get_instance() {
	
    //
    // Check whether a prior instance of this class already exists if not, then go ahead and 
    // create a new single instance 
    //
	if (_instance == 0) {
		_instance = new DiscardTray();
	}

    //
	// Return the new instance (or the one that's already been created)
    //
	return _instance;
}

//
// Collect the players and dealers cards 
//
void DiscardTray::collect_participants_cards(vector<Card> cards) {
    
    //
	// Append the passed vector to the end of the current tray 
    //
	CardTray.insert(CardTray.end(), cards.begin(), cards.end());
}

//
// Move the contents of the deque back to the "Shoe" where it will be reshuffled, 
// the Cut Card will be positioned and a new session can be played
//
void DiscardTray::empty_Tray(Shoe* GameShoe) {

    //
    // Local variables
    //
    CardTrayIterator start = CardTray.begin();
    CardTrayIterator end = CardTray.end();

    //
    // Move all items inside the "DiscardTray" object to the end of the container in the 
    // "Shoe" class. Since the "DiscardTray" will still be used by the game, do not de-
    // lete any space, as that would require to have them allocated again once the tray
    // is being used 
    //
    std::move(start, end, std::back_inserter(GameShoe->GameDeck));
    this->clear_tray();
}

//
// Reset the tray for another game session 
//
void DiscardTray::clear_tray() {
	CardTray.clear();
}