/*
 * @file party.cc
 *
 * @brief Source file for the party class
 *
 * @author Javier Pardo
 *
 * @date 2/15/2017
 */

#include"party.h"
#include<string>

using std::string;

/**
 * @brief Party default constructor.
 */

Party::Party()
{
  this->reservationName = new string("no reservation");
  this->numDiners = -1;
  this->timeRequired = -1;
}

/**
 * @brief Party constructor.
 */

Party::Party(const string& reservationName, int numDiners, int timeRequired)
{
  this->reservationName = new string(reservationName);
  this->numDiners = numDiners;
  this->timeRequired = timeRequired;
}

/**
 * @brief Party destructor.
 */

Party::~Party()
{
  delete reservationName;
}

