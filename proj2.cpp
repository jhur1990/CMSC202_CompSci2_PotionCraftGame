/**********************************************
 ** File: proj2.cpp
 ** Project: CMSC 202 Project 2, Spring 2023
 ** Author: Joshua Hur
 ** Date: 3/14/23
 ** E-mail: jhur1@umbc.edu
 **
 ** This is a potion craft game in which a player combines discovered ingredients and crafted potions to get a new potion.
 ** The player's inventory records the number of potions and ingredients.
 ** The main goal is to create the highest degree potion, and the player wins.
 ************************************************************************/

#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {
  srand(time(NULL));
  Game newGame;
  newGame.StartGame();
  return 0;
}
