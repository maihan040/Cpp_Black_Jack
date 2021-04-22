//
// Class declaration file for the "Player" class this class will simulate the play-
// er object of the game 
// 
// currently the "Game" is set up to only have one player and one "Dealer" object
// 
// Design pattern used: None 
//
// Modified on: 03/12/2021
//

#pragma once

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include <sstream>
#include <iomanip>
#include "Card.h"
#include "BlackJackParticipant.h"

/****************************************************************************************/
/*				"Player" class declaration				*/
/****************************************************************************************/
class Player final : public BlackJackParticipant { 
public:

	/****************************************/
	/* Special member methods		*/
	/****************************************/

	//
	// Default special member functions
	//
	Player() = default;
	Player(const Player&) = default; 
	Player& operator=(Player &) = default;

	Player(Player&& ) = default;
	Player& operator=(Player&&) = default;
	
	~Player() = default; 

	//
	// Virtual functions 
	//
	virtual void hit(Card new_card, bool deal_round) override;

	//
	// Delete assignment operator 
	//
	Player& operator=(const Player&) = delete;

};