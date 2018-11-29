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
  state_t (const unsigned id, const bool accept = false);
  ~state_t (void);

  const unsigned id (void) const;
  set<pair<char, unsigned> > getNext (void) const;
  const bool is_accept (void) const;

  //Devuelve el puntero par que contiene dicha letra. Usado para transitar entre los estados
  unsigned find_by_letter (const char c);
  void insert_pair (const char symbol, const unsigned id);

  ostream& dbg_write (void) const;

  const bool operator< (const state_t state) const;
};
