# Cpp_Black_Jack

## Purpose:

This is an implementation of a black game build using C++. Goal of this project was to utilize as many C++ concepts in order to build the game that would
simulate a real game that's being played in a casino, by creating objects such as: 
  player
  dealer 
  shoe
  deck of cards
  discard tray

## Motivation:

Motivation for this project was twofold: 
  
  * Learn to become proficient with git/github
  * Break down a real world problem into C++ modules to model those
  * Use proven/solid methods such as reuse/modular design to build a real world scenario
  * Utilize multiple C++ paradigms 
 
## Following C++ concepts were used: 

  * OOP
  * Inheritance
  * STL containers
  * Exception handling 
  * Iterators
  * Use of unicode characters
  * File processing
  * Move semantics 
  * Design patterns (predominantly singleton)
  * Splitting of declaration and implementation 

## Tech/framework used:

  * C++
  * Make
  * Figlet (used to generate special ascii fonts)
 
## Features:

  Code will have heavy documentation throughout, which serves to clearly show the operation of each function.

## Contents:
  
  Following cpp files were built (most of them have a corresponding header file)
  * Card.cpp -> Class to model a single playing card
  * Deck.cpp -> Class to model a deck of 52 playing cards
  * Shoe.cpp -> Class to model a shoe to hold as many as 8 decks 
  * DiscardTray.cpp -> Class to model the discard tray to collect the play cards
  * BlackJackParticipant.cpp -> Parent class to model a participant who is part of the game 
  * Player.cpp -> derived class to model a player 
  * Dealer.cpp -> derived class to model the dealer 
  * BlackJackGame.cpp -> Class to model a black jack game 
  * MiscFunctions.cpp -> Module containing functions that are shared by multiple objects 
  * BlackJack_Driver.cpp -> Class to orchestrate the game 
  
  Following text files are used by the game: 
  * BlackJack.txt -> BlackJack banner 
  * GameMenu.txt -> Start menu to get choice from player 
  * PlayerWon.txt -> Message to indicate the player has won 
  * PlayerLost.txt -> Message to indicate the player has lost 
  * TieMessage.txt -> Message to indiccate no one has won the round 
  * Card.txt -> Ascii image of two cards which are used by the start menu 
  * ReshufflingText.txt -> Message to indicate that the shoe is being reshuffled
  * Menu.txt -> Menu to ask player whether to continue the game or not 
 
