#include "../include/DFA.hpp"

using namespace std;
DFA::DFA (void) : states_(), all_states_(0), init_(-1) {}

DFA::DFA (const set<state_t>& states) : states_ (states), all_states_(0), init_(-1){
  all_states_ = states_.size();
}

DFA::~DFA (void) { clear(); }

const unsigned DFA::init (void) {
  return init_;
}

void DFA::create_dfa (const char* nombreFichero, bool& errorApertura) {
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

  //Leemos el estado de arranque del DFA
  fich >> (unsigned &)init_;

  //Leemos, para cada estado, sus diferentes valores
  unsigned id, accepted, transition;
  char symbol;
  for (int i = 0; i < all_states_; i++) {
    if (fich.eof()) { cout << "Se ha llegado al final del fichero.\n"; return;}
    //Primero el ID y si es de aceptacion
    fich >> (unsigned &)id >> (unsigned &)accepted;

    //Obtenemos el estado e indicamos si es de aceptacion
    state_t state(id,accepted);

    //Recogemos el numero de transiciones de cada estado
    fich >> (unsigned &)transition;

    //Procedemos a leer los estados sucesores para cada estado
    set<char> symbol_read;
    symbol_read.clear();
    for (int j = 0; j < transition; j++) {
      fich >> (char &)symbol;
      if (alphabet.find(symbol) == alphabet.end()) alphabet.insert(symbol);
      if (symbol_read.find(symbol) != symbol_read.end()) {
        cerr << "Error. Letra repetida en la definicion de las aristas del estado " << state.id()+1 << ". DFA erroneo.\n";
        errorApertura = 1;
        return;
      }

      symbol_read.insert(symbol);
      fich >> (unsigned &)id;
      state.insert_pair(symbol, id);
    }
    states_.insert(state);
  }
  fich.close();
}

void DFA::show_chain_result (void) {
  string s;
  bool result;
  cout << "Inserta la cadena a analizar: ";
  cin >> s;
  cout << "\x1b[1J\x1b[H"; //Limpio pantalla
  result = chain_test(s);
  cout << "Cadena de entrada " << (result ? "" : "NO ") << "ACEPTADA\n";
}

void DFA::show_dead_states (void) {
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

void DFA::show_alphabet (void) {
  cout << "Alfabeto utilizado por el automata: ";
  cout << "{";
  int cont = 0;
  for (set<char>::iterator it = alphabet.begin(); it != alphabet.end(); it++) {
    cout << *it << (cont++ != alphabet.size()-1 ? "," : "");
  }
  cout << "}\n";
}

ostream& DFA::dbg_write (void) const {
  cout << "Estado totales: " << all_states_ << "\n";
  cout << "ID del estado inicial: " << init_ << "\n";
  for (set<state_t>::iterator it = states_.begin(); it != states_.end(); it++) {
    it->dbg_write();
  }
  return cout;
}

ostream& DFA::write (void) const {
  cout << all_states_ << "\n";
  cout << init_ << "\n";
  for (set<state_t>::iterator it = states_.begin(); it != states_.end(); it++) {
    cout << it->id() << " ";
    cout << (it->is_accept() ? 1 : 0);
    for (set<pair<char, unsigned> >::iterator k = it->getNext().begin(); k != it->getNext().end(); k++) {
      cout << " " << get<0>(*k) << " " << get<1>(*k);
    }
    cout << "\n";
  }
  return cout;
}

void DFA::clear (void) {
  states_.clear();
  alphabet.clear();
}

//METODOS PRIVADOS////////////////////////////////////////

bool DFA::chain_test (const string& chain) const {
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

set<state_t> DFA::dead_states (void) {
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

const state_t DFA::find_by_id (const unsigned id) const {
  for (set<state_t>::iterator it = states_.begin(); it != states_.end(); it++) {
    if (it->id() == id) { return *it; }
  }
  return *(new state_t (-1));
}
