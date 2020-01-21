/*
 * @file table.cc
 *
 * @brief Source file for the table class
 *
 * @author Javier Pardo
 *
 * @date 2/15/2017
 */

#include"table.h"
#include<string>

using std::string;

/**
 * @brief Table default constructor.
 */

Table::Table()
{
  this->tableID = new string("noId");
  this->numSeats = -1;
  this->serverName = new string("noName");
  this->timer = -1;
  this->party = nullptr;
}

/**
 * @brief Table constructor.
 */

Table::Table(const string& tableID, int numSeats, const string& serverName)
{
  this->tableID = new string(tableID);
  this->numSeats = numSeats;
  this->serverName = new string(serverName);
}

/**
 * @brief Table destructor.
 */

Table::~Table()
{
  delete tableID;
  delete serverName;
}

/**
 * @brief Alocates a new party object and set it equal to the party pointer.
 * @param newParty A pointer of the party being seated in the table.
 * @return Nothing.
 *
 * Makes a copy of the party being seated and attaches it to the table.
 */

void Table::seatParty(const Party* newParty)
{
  party = new Party(*(newParty->getReservationName()), newParty->getNumDiners(), newParty->getTimeRequired());
}



