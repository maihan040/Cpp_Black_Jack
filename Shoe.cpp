//
// Implementation file for the "Shoe" class 
//

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include "Shoe.h"

/****************************************************************************************/
/*				"Shoe" class declaration				*/
/****************************************************************************************/

//
// Initialize static "RESHUFFLE" variable to false prior to start of the game
//
bool Shoe::RESHUFFLE = false;

//
// Initialize the instance to 0, since this is a singleton class and it will be created on 
// demand 
//
Shoe* Shoe::_instance = 0;

//
// Static implementation 
//
Shoe* Shoe::get_instance(int NumOfDecks) {
    	//
	// Check whether a prior instance of this class already 
	// exists if not, then go ahead and create a new single
	// instance
    	//
	if (_instance == 0) {
		_instance = new Shoe(NumOfDecks);
	}

    	//
	// Return the instance 
    	//
	return _instance;
}

//
// Constructor definition
// Default constructor will set up consisting of a minimum of six decks
//
Shoe::Shoe(int Num) {

	//
	// Validate the "NumOfDecks" variable
	//
	if (Num < Shoe::MIN_DECKS) 
		NumOfDecks = Shoe::MIN_DECKS; 
	else if (Num > Shoe::MAX_DECKS) 
		NumOfDecks = Shoe::MAX_DECKS;
	else
		NumOfDecks = Num;

	//
	// Initialize number of available cards as 
	// a default. This value will be changed 
	// once the position of the cut card has 
	// been determined 
	//
	AvailableCards = NumOfDecks * CARDS_PER_DECK;
	
	//
	// Call the build_shoe() function to populate 
	// the shoe with "Card" objects
	//
	this->build_shoe(NumOfDecks);
}

//
// Method to return the last card from the shoe 
//
Card Shoe::deal_card()
{
    	//
	// Check whether it's time to reshuffle the deck 
    	//
	if (this->get_available_cards() == 0) {
		RESHUFFLE = true;
	}

	//
	// Get the card that's at the front of "GameDeck" 
	// followed by reducing the number of available 
	// "Card" objects in the "GameDeck"
	//
	Card FrontCard = std::move(GameDeck.front());
	GameDeck.pop_front();		// Clear the spot that was occupied by the "Card" 
					// object that was just moved 
	--AvailableCards;		// Member variables that keeps track of how many 
					// cards are available in the shoe before the ca-
					// rds need to be reshuffled

	//
	// Move the "Card" 
	//
	return std::move(FrontCard); 
}

//
// Set the position of the cut card
//
// NOTE: in a standard six deck game, the last 60/75 cards 
// will not be used. This is about 20/24 percent of the 
// cards of the shoe. Since the deck can be as much as 8 
// decks the following function will ensure that this rat-
// io is kept
//
void  Shoe::set_cut_card_pos() {

	//
	// Local variables to compute the numeric range of the last 20/24% of cards
	//
	int TotalCards = CARDS_PER_DECK * NumOfDecks;
	int MaxPos = TotalCards - static_cast<int>(CUT_CARD_MIN * TotalCards);
	int MinPos = TotalCards - static_cast<int>(CUT_CARD_MAX * TotalCards);

	//
	// Set the position of the cut card
	//
	CutCardPos = generate_uniform_random_number(MinPos, MaxPos); 

	//
	// Call "set_available_cards()" to determine the final 
	// number of available cards for the game
	//
	this->set_available_cards();	
}

//
// Calculate how many cards are available in the shoe after the 
// cut card has been placed
//
inline void Shoe::set_available_cards() {

	//
	// All that's needed is to copy the position of 
	// the cut card Since the "AvailableCards" var-
	// iable will be decremented with each draw, a 
	// copy of this count will be needed in order 
	// to preserve the original
	//
	AvailableCards = CutCardPos;
}

//
// Empty the shoe once it's time to reshuffle 
// the cards, this will be done via the cont-
// ainers "clear" function 
//
void Shoe::clear_shoe() {
	GameDeck.clear();	
}

//
// Function to build the shoe with a fresh set 
// of "Card" objects
//
void Shoe::build_shoe(int NumOfDecks) {

	//
	// For an empty "GameDeck"generate "NumOfDecks" 
	// playing decks and add them to the deque obj-
	// ect that simulates the shoe 
	//
	if(GameDeck.size() == 0) {
		for (unsigned short i = 0; i < NumOfDecks; ++i) {

			//
			// Local "Deck" variable to construct a single play 
			// deck which will be added to the "Shoe"
			//
			Deck SingleDeck;
			
			//
			// Move each individual card from the above deck to the "Shoe"
			//
			for(auto it = SingleDeck.PlayDeck.begin(); it < SingleDeck.PlayDeck.end(); ++it ) {
				GameDeck.push_back(std::move(*it));
			}
		}
	}
}

//
// Function to shuffle the cards inside the shoe 
//
void Shoe::shuffle_shoe() {

	//
	// Local variables
	//
	ShoeIterator ShoeStart 	= GameDeck.begin();
   	ShoeIterator ShoeEnd 	= GameDeck.end();

	//
	// Shuffle the cards via the function from 
	// the "MiscFunction" module 
	//
   	shuffle_cards(ShoeStart, ShoeEnd);
}

/************************************************************************/
/* 			  DEBUG functions				*/
/************************************************************************/
void Shoe::print_shoe() {

	//
	// Local variables
	//
	deque<Card>::iterator start = GameDeck.begin();
	deque<Card>::iterator end = GameDeck.end();

	//
	// Use the iterator to traverse 
	// through the container's con-
	// tents
	//
	for(auto it = start; it<end; ++it) {
		it->print_card();
	}
}