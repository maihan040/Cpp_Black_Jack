//
// Implementation file for the "Card" class 
// 
// Modified on: 03/23/2021
//

/******************************************************************************************/
/*					Imports						  */
/******************************************************************************************/
#include <iostream>
#include "Card.h"

using namespace std; 

/******************************************************************************************/
/*				Const member attributes					  */
/******************************************************************************************/

//
// Map data structure to convert a given cards string value to the corresponding int
//
const map<string, short> Card::CardMap = {
	{"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, 
	{"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, 
	{"10", 10}, {"J", 10}, {"Q", 10}, {"K", 10}, {"A", 11}};

//
// Map data structure to identify the four possible  suits a card can take. Use unicode values 
// to print the actual suit for each output 
//
const map<short, string> Card::CardSuit = {
	{0, "\xe2\x99\xa3"}, 
	{1, "\xe2\x99\xa6"}, 
	{2, "\xe2\x99\xa0"}, 
	{3, "\xe2\x99\xa5"}

};

//
// String array to hold all the possible values a card can take
//
const string Card::CardFaceValues[MAX_CARDS_PER_SUIT] = 
{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

/******************************************************************************************/
/*				Method/constructor definitions	   			  */
/******************************************************************************************/

//
// Constructor method definition 
//
Card::Card(string face_val, string suit) : FaceValue{ face_val }, Suit{ suit } {}

//
// Functions for debugging purposes
//
void Card::print_card() {
	cout << this->FaceValue << " " << this->Suit << endl;
}