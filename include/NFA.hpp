
/**
* @file NFA.hpp
* @Author Himar Manuel
* @date 1/12/2018
* @brief NFA implementation
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

#include "state_t.hpp"

class NFA {
private:
  set<state_t> states_; //conjunto de estados
  int all_states_; //cantidad de estados totales
  unsigned init_; //id del estado inicial
  set<char> alphabet; //alfabeto sobre el que el automata trabaja
public:
  NFA (void);
  NFA (const set<state_t>& states);
  ~NFA (void);

  const unsigned init (void);

  /**
  * @brief Creates a NFA read from file
  * @param nombreFichero The name of the file
  * @param errorApertura Boolean showing if there was an error or not
  */

  void create_nfa (const char* nombreFichero, bool& errorApertura);

  void show_chain_result (void);
  void show_dead_states (void);
  void show_important_states (void);
  void show_alphabet (void);

  void is_dfa (void);

  ostream& dbg_write (void) const;
  ostream& write (void) const;

  /**
  * @brief Reset the automaton
  */

  void clear (void);

private:

  /**
  * @brief Check wether c exist on v or not
  * @param c constant char testing if exist on v
  * @param v constant char's vector where to check if c exist
  * @return true if found, false in another case
  */

  bool find (const vector<char> v, const char c);

  /**
* @brief Test if chain is recognize by the automaton
* @param chain String to evaluate
* @return 0 if is recognized, 0 in another case
*/

  bool chain_test (const string& chain) const;
  void chain_test (const string& chain, const state_t& state, const char c, const unsigned i, vector<int>& states, vector<int>& next, vector<char>& vc, bool& accepted) const;

  /**
  * @brief Show a posibility of way
  * @param states Set of all actual states during the way
  * @param next Set of next states
  * @param c Set of character evaluated
  */

  void display_posibilities (const vector<int>& states, const vector<int>& next, const vector<char>& c) const;

  /**
  * @brief Check dead states
  * @return Set with all dead states
  */

  set<state_t> dead_states (void);

  /**
  * @brief Check important states
  * @return Set with all important states
  */

  set<state_t> important_states (void);

  /**
* @brief Look for the state with the ID indicated
* @param id constant unsigned int ID to look for
* @return State located with this ID
*/

  const state_t find_by_id (const unsigned id) const;
};
