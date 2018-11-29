#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "state_t.hpp"

class DFA {
private:
  set<state_t> states_; //conjunto de estados
  int all_states_; //cantidad de estados totales
  unsigned init_; //id del estado inicial
  set<char> alphabet; //alfabeto sobre el que el automata trabaja
public:
  DFA (void);
  DFA (const set<state_t>& states);
  ~DFA (void);

  const unsigned init (void);

  void create_dfa (const char* nombreFichero, bool& errorApertura);
  void show_chain_result (void);
  void show_dead_states (void);
  void show_alphabet (void);

  ostream& dbg_write (void) const;
  ostream& write (void) const;
  void clear (void);

private:
  bool chain_test (const string& chain) const;
  set<state_t> dead_states (void);
  const state_t find_by_id (const unsigned id) const;
};
