//
// Implementation file for the "Deck" class 
//

/******************************************************************************************/
/*					Imports						  */
/******************************************************************************************/
#include "HeaderFiles/CardDeck.h"

/******************************************************************************************/
/*				   Method definitions					  */
/******************************************************************************************/

//
// Default constructor, builds a vector of 52 card objects and shuffles them 
//
Deck::Deck() {

    //
    // Local variables
    //
    MapIterator start = Card::CardMap.begin();
    MapIterator end = Card::CardMap.end();

    //
	// Add the 52 cards to the play deck cycling through each of the possible suits via the 
    // card map data type
    //
	for (int currentSuit = 0; currentSuit < Card::MAX_SUITS; ++currentSuit) {
		for (start; start != end; ++start) {

            //
            // Create a new card object where the string face value is obtained from the above
            // iterator, and the card suit directly from the static map in the card class
            //
			PlayDeck.emplace_back(Card(start->first, Card::CardSuit.at(currentSuit)));
		}

        //
        // Reset the start iterator 
        //
        start = Card::CardMap.begin();
	}

    //
	// Shuffle the deck
    //
	PlayDeckIterator PlayDeckStart = PlayDeck.begin();
    PlayDeckIterator PlayDeckEnd   = PlayDeck.end();
    shuffle_cards(PlayDeckStart, PlayDeckEnd);

}

//
// Clear deck. 
//
void Deck::clear_deck() {
	PlayDeck.clear();
}


//
// Return a card from the deck 
//
Card Deck::draw_card() {

    /********************************************************************
    /* NOTE: given the plethora of card games available where an emtpy
    /* deck does not necesarily require the termination of the game, it's
    /* left to the caller to do the validation check of whether the deck
    /* is empty and proceed as necessary. 
    /* 
    /* CHECK FOR POSSIBLE EXCEPTIONS
    /*******************************************************************/

    //
    // Check wheter the deck has any cards remaining, and if so
    // move the "Card" object. Pop the last element from the vector
    //
    Card ReturnCard = std::move(PlayDeck.back());
    PlayDeck.pop_back();
    return ReturnCard;

}

//
// DEBUG print method 
//
void Deck::print_deck() {

    //
    // Local variables
    //
    PlayDeckIterator start = PlayDeck.begin();
    PlayDeckIterator end= PlayDeck.end();

    while(start!= end) {
        cout << start->get_face_value() << " " << start->get_card_suit() << NEW_LINE;
        ++start;
    }
}
