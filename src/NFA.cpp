#include "../include/NFA.hpp"

using namespace std;
NFA::NFA (void) : states_(), all_states_(0), init_(-1) {}

NFA::NFA (const set<state_t>& states) : states_ (states), all_states_(0), init_(-1){
  all_states_ = states_.size();
}

NFA::~NFA (void) { clear(); }

const unsigned NFA::init (void) {
  return init_;
}

void NFA::create_dfa (const char* nombreFichero, bool& errorApertura) {
  states_.clear();
  ifstream fich;
  fich.open(nombreFichero);

  if (!fich.is_open()) {
    cerr << "Error. El fichero no se ha podido abrir con exito.\n";
    errorApertura = 1;
    return;
  }

  //Empezamos leyendo el valor de estados totales
  fich >> (int &)all_states_;

  //Leemos el estado de arranque del NFA
  fich >> (unsigned &)init_;

  //Leemos, para cada estado, sus diferentes valores
  unsigned id, accepted, transition;
  char symbol;
  for (int i = 0; i < all_states_; i++) {
    if (fich.eof()) { cerr << "Se ha llegado al final del fichero.\n"; return; } //Si se llega antes de leer todos los estados, hay un error
    //Primero el ID y si es de aceptacion
    fich >> (unsigned &)id >> (unsigned &)accepted;

    //Obtenemos el estado e indicamos si es de aceptacion
    state_t state(id,accepted);

    //Recogemos el numero de transiciones de cada estado
    fich >> (unsigned &)transition;

    //Procedemos a leer los estados sucesores para cada estado
    for (int j = 0; j < transition; j++) {
      fich >> (char &)symbol;
      if (symbol != '&') alphabet.insert(symbol);

      fich >> (unsigned &)id;
      state.insert_pair(symbol, id);
    }
    states_.insert(state);
  }
  fich.close();
}

void NFA::show_chain_result (void) {
  string s;
  bool result;
  cout << "Inserta la cadena a analizar: ";
  cin >> s;
  cout << "\x1b[1J\x1b[H"; //Limpio pantalla
  result = chain_test(s);
  cout << "Cadena de entrada " << (result ? "" : "NO ") << "ACEPTADA\n";
}

void NFA::show_dead_states (void) {
  set<state_t> states = dead_states();

  cout << "\x1b[1J\x1b[H"; //Limpio pantalla
  if (states.empty()) cout << "\tNo hay estados de muerte."; else {
    cout << "\tHay " << states.size() << " estado" << (states.size() > 1 ? "s" : "") << " de muerte, " << (states.size() > 1 ? "los cuales son" : "el cual es") << ": ";
    cout << "{";
    int cont = 0;
    for (set<state_t>::iterator it = states.begin(); it != states.end(); it++) {
      cout << it->id() << (cont++ != states.size()-1 ? "," : "");
    }
    cout << "}";
  }
  cout << "\n";
}

void NFA::show_important_states (void) {
  set<state_t> states = important_states();

  cout << "\x1b[1J\x1b[H"; //Limpio pantalla
  if (states.empty()) cout << "\tNo hay estados importantes."; else {
    cout << "\tHay " << states.size() << " estado" << (states.size() > 1 ? "s" : "") << " importante, " << (states.size() > 1 ? "los cuales son" : "el cual es") << ": ";
    cout << "{";
    int cont = 0;
    for (set<state_t>::iterator it = states.begin(); it != states.end(); it++) {
      cout << it->id() << (cont++ != states.size()-1 ? "," : "");
    }
    cout << "}";
  }
  cout << "\n";
}

void NFA::is_dfa (void) {
  set<char> symbols_read;
  bool dfa;
  for (set<state_t>::iterator i = states_.begin(); i != states_.end(); i++) {
    symbols_read.clear();
    dfa = true;
    for (set<pair<char,unsigned> >::iterator j = i->getNext().begin(); j != i->getNext().end(); j++) {
      char symbol = get<1>(*j);
      if (symbols_read.find(symbol) != symbols_read.end() || symbol == '&') {
        dfa = false;
        break;
      }
      symbols_read.insert(symbol);
    }
    if (!dfa) {
      cout << "El automata no es un DFA.\n";
    } else {
      cout << "El automata es un DFA.\n";
    }
  }
}

void NFA::show_alphabet (void) {
  cout << "Alfabeto utilizado por el automata: ";
  cout << "{";
  int cont = 0;
  for (set<char>::iterator it = alphabet.begin(); it != alphabet.end(); it++) {
    cout << *it << (cont++ != alphabet.size()-1 ? "," : "");
  }
  cout << "}\n";
}

ostream& NFA::dbg_write (void) const {
  cout << "Estado totales: " << all_states_ << "\n";
  cout << "ID del estado inicial: " << init_ << "\n";
  for (set<state_t>::iterator it = states_.begin(); it != states_.end(); it++) {
    it->dbg_write();
  }
  return cout;
}

ostream& NFA::write (void) const {
  cout << all_states_ << "\n";
  cout << init_ << "\n";
  for (set<state_t>::iterator it = states_.begin(); it != states_.end(); it++) {
    cout << it->id() << " ";
    cout << (it->is_accept() ? 1 : 0);
    cout << " " << it->getNext().size();
    for (set<pair<char, unsigned> >::iterator k = it->getNext().begin(); k != it->getNext().end(); k++) {
      cout << " " << get<0>(*k) << " " << get<1>(*k);
    }
    cout << "\n";
  }
  return cout;
}

void NFA::clear (void) {
  states_.clear();
  alphabet.clear();
}

//METODOS PRIVADOS////////////////////////////////////////

bool NFA::chain_test (const string& chain) const {
  cout << "Cadena de entrada: " << chain << "\n";
  cout << "ESTADO ACTUAL\tENTRADA\t\tSIGUIENTE ESTADO\n";
  state_t aux = find_by_id(init_);
  unsigned cid;
  for (int i = 0; i < chain.length(); i++) {
    cout << aux.id() << "\t\t" << chain[i] << "\t\t";
    cid = aux.find_by_letter(chain[i]);
    if (cid != -1) {
      aux = find_by_id(cid);
      cout << aux.id() << "\n";
    } else {
      cout << "NONE\n";
      return false;
    }
  }
  if (aux.is_accept()) return true; else return false;
}

set<state_t> NFA::dead_states (void) {
  set<state_t> deadStates;
  for (set<state_t>::iterator i = states_.begin(); i != states_.end(); i++) {
    bool is_dead = true;
    for (set<pair<char,unsigned> >::iterator j = i->getNext().begin(); j != i->getNext().end(); j++) {
      if (i->id() != get<1>(*j)) { is_dead = false; break; }
    }
    if (is_dead) deadStates.insert(*i);
  }
  return deadStates;
}

set<state_t> NFA::important_states (void) {
  set<state_t> result;
  bool is_important;
  for (set<state_t>::iterator i = states_.begin(); i != states_.end(); i++) {
    if (i->is_accept()) { result.insert(*i); continue; } else { is_important = false; }
    for (set<pair<char,unsigned> >::iterator j = i->getNext().begin(); j != i->getNext().end(); j++) {
      if (get<1>(*j) != '&') { is_important = true; break; }
    }
    if (is_important) { result.insert(*i); }
  }
  return result;
}

const state_t NFA::find_by_id (const unsigned id) const {
  for (set<state_t>::iterator it = states_.begin(); it != states_.end(); it++) {
    if (it->id() == id) { return *it; }
  }
  return *(new state_t (-1));
}
