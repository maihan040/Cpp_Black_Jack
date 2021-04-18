//
// Implementation file for the "Player" class 
//

/******************************************************************************************/
/*					Imports						  */
/******************************************************************************************/
#include "Player.h"

/******************************************************************************************/
/*				    Method definitions					  */
/******************************************************************************************/

//
// Implementation for the "Player" member 
//
void Player::hit(Card new_card, bool deal_round) {

	//
	// Add the new card to the "Hand" 
	//
	this->append_card(new_card);

	//
	// Add the current card value to the total in the current "hand"  
	//
	this->add_new_card_val(new_card.CardMap.at(new_card.FaceValue));

	//
	// Check whether the hand contains an ACE
	//	
	if (this->get_TotalCardValues() == 21) {
		
		/* Check whether 21 was hit during the deal round */
		if (deal_round == true)
			this->set_HitBlackJack(true);

		/* Mark that 21 has been reached */
		this->set_Hit21(true);
	}
}