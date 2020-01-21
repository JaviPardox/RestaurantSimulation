/*
 * @file restaurant.cc
 *
 * @brief Source file for the restaurant class and where the simulation takes place
 *
 * @author Javier Pardo
 *
 * @date 2/15/2017
 */

#include<iostream>
#include<string>
#include"restaurant.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

/*
 * @brief Starts the simulation by calling a restaurant object and its functions.
 * @param None.
 * @return 0
 */

int main()
{
  Restaurant simulation;
  simulation.getInput();
  simulation.serveParties();
  return 0;
}

/*
 * @brief Gets input from standart input and creates a table or a party depeinding of the command inserted.
 * @param None.
 * @return Nothing.
 */

void Restaurant::getInput()
{   
   string command;
   while(cin>>command)
   {
     if(command == "table")
     {
       string tableID;
       int numSeats;
       string serverName;
       cin >> tableID;
       cin >> numSeats;
       cin >> serverName;
       Table *TableObj = new Table(tableID, numSeats, serverName);
       available.append(TableObj);
     }
     if(command == "party")
     {
       string reservationName;
       int numDiners;
       int timeRequired;
       cin >> numDiners;
       cin >> reservationName;
       cin >> timeRequired;
       Party *PartyObj = new Party(reservationName, numDiners, timeRequired);
       waiting.append(PartyObj);
     }
     if(command == "end")
     {
       break;
     }
   }
}

/*
 * @brief Where all the simulation takes place.
 * @param None.
 * @return Nothing.
 *
 * Iterates first through the available table's list and then seats the parties from the waiting list,
 * then checks the list of occupied tables to decrement their timer.
 */

void Restaurant::serveParties()
{
  bool restaurante = true;
  while(restaurante)
  {
    Table *thisTable = occupied.first();
    while(thisTable != nullptr)              // I decided to use a while loop instead a for loop so I can choose
    {                                        // when to call .next().
      bool Remove = false;                   // The variable Remove keeps track of it, if a table gets removed then
      thisTable->decrementTimer();           // the call of next() is avoided.
      if(thisTable->getTimer() == 0)
      {
        cout << *(thisTable->getParty()->getReservationName()) << " finished at " << *(thisTable->getTableID()) << endl;  
        thisTable->clearTable();
        available.append(thisTable);
        thisTable = occupied.remove();
        Remove = true;
      }
      if(Remove == false)                    // If it is false then the table was not removed so next() is called.
      {
        thisTable = occupied.next();
      }
    }
    Party *thisParty = waiting.first();
    while(thisParty != nullptr)              // Same idea, in order to know when to call next() I used a while loop
    {                                        // instead of a for loop.
      bool Removed = false;                  // So I use Removed again to keep track of it.
      Table *thisTable1 = available.first();
      while(thisTable1 != nullptr)
      {
        if(thisTable1->getNumSeats() >= thisParty->getNumDiners())
        {
          cout << *(thisParty->getReservationName()) << " seated at " << *(thisTable1->getTableID()) << endl;
          thisTable1->seatParty(thisParty);
          thisTable1->setTimer(thisParty->getTimeRequired());
          occupied.append(thisTable1);
          servers[*thisTable1->getServerName()] += thisParty->getNumDiners();  
          thisTable1 = available.remove();
          thisParty = waiting.remove();
          Removed = true;
          break;                            // Break allows me to get to the first party in the list without 
        }                                   // having to execute line 125 which messes up the final result.
        thisTable1 = available.next();
      }
      if(Removed == false)
      {
        thisParty = waiting.next();
      }
    }
    if(waiting.empty() == true && occupied.empty() == true)  // Printing each server thanks to the iterator from std::map
    {
      for(auto it = servers.cbegin(); it != servers.cend(); ++it)
      {
        cout << it->first << " served " << it->second << endl;
      }
      restaurante = false;  //close restaurant
    }
  }
}



















