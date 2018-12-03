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

  void create_dfa (const char* nombreFichero, bool& errorApertura);

  void show_chain_result (void);
  void show_dead_states (void);
  void show_important_states (void);
  void show_alphabet (void);

  void is_dfa (void);
  
  ostream& dbg_write (void) const;
  ostream& write (void) const;

  void clear (void);

private:
  bool find (const vector<char> v, const char c);
  bool chain_test (const string& chain) const;
  void chain_test (const string& chain, const state_t& state, const char c, const unsigned i, vector<int>& states, vector<int>& next, vector<char>& vc, bool& accepted) const;
  void display_posibilities (const vector<int>& states, const vector<int>& next, const vector<char>& c) const;
  set<state_t> dead_states (void);
  set<state_t> important_states (void);
  const state_t find_by_id (const unsigned id) const;
};
