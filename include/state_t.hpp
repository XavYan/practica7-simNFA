/**
* @file state_t.hpp
* @Author Himar Manuel
* @date 1/12/2018
* @brief State implementation
*/

#pragma once

#include <iostream>
#include <set>
#include <utility>

using namespace std;

class state_t {
private:
  unsigned id_; //identificador del estado
  bool accept_; //indica si es un nodo de aceptacion
  set<pair<char, unsigned> > next_; //Conjunto de estados siguientes a la arista

public:

  /**
  * @brief Constructor of a state
  * @param id identifier of the state
  * @param accept set if the state is a acceptation one. By default is false
  */

  state_t (const unsigned id, const bool accept = false);

  /**
  * @brief Destruct a state
  */

  ~state_t (void);

  /**
  * @brief Get ID of the state
  * @return ID of the state
  */

  const unsigned id (void) const;

  /**
  * @brief Get all the next states connected to the actual state
  * @return return a copy of the attribute "next_"
  */

  set<pair<char, unsigned> > getNext (void) const;

  /**
* @brief Check if the state is an acceptation one
* @return 0 if the state is accept, 0 if not
*/

  const bool is_accept (void) const;

  /**
* @brief Find the state connected to this by the character
* @param c const char
* @return An unsigned int corresponding to the state
*/

  //Devuelve el puntero par que contiene dicha letra. Usado para transitar entre los estados
  unsigned find_by_letter (const char c);

  /**
* @brief Insert a pair (in this case, a pair char, unsigned) to add a new connection to the state
* @param symbol A const char with the character who connects it
* @param id A constant unsigned int
*/

  void insert_pair (const char symbol, const unsigned id);

  /**
  * @brief Write on console a friendly information about the state
  */

  ostream& dbg_write (void) const;

  /**
* @brief A operator
*/

  const bool operator< (const state_t state) const;
};
