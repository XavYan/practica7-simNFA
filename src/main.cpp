#include "../include/DFA.hpp"

unsigned set_format (void) { //Indica el formato de muestreo. Si es 0 el DFA lo muestra como en el fichero.
  char opt;
  cout << "Idique el formato:\n";
  cout << "f. Formato [f]ichero (lo muestra igual que en el fichero).\n";
  cout << "l. Formato [l]ectura (lo muestra en un formato mas legible).\n";
  cout << "Formato >> ";
  cin >> opt;
  cout << "\x1b[1J\x1b[H"; //Limpio pantalla
  cout << "Formato de escritura cambiado a modo " << (opt == 'l' ? "lectura" : "fichero") << "\n";
  return (opt == 'f' ? 0 : 1);
}

int main (void) {

  DFA dfa;

  int opt;
  unsigned format = 0;
  bool errorApertura = 1;

  cout << "\x1b[2J\x1b[H"; //Limpia la terminal
  do {
    cout << "Practica 6 de COMPUTABILIDAD Y ALGORITMIA - SIMULADOR DE AUTOMATAS FINITOS DETERMINISTAS\n";
    cout << "----------------------------------------------------------------------------------------------------\n";
    cout << "Estado del fichero: " << (errorApertura ? "CERRADO" : "ABIERTO") << "\n";
    cout << "----------------------------------------------------------------------------------------------------\n";
    cout << "1. LEER DFA DESDE FICHERO\n";
    cout << "2. CAMBIAR FORMATO DE MUESTREO\n";
    cout << "3. MOSTRAR DFA\n";
    cout << "4. INDICAR ESTADOS DE MUERTE DEL AUTOMATA\n";
    cout << "5. ANALIZAR CADENA\n";
    cout << "6. MOSTRAR ALFABETO\n";
    cout << "7. SALIR DEL PROGRAMA\n";

    cout << "\nIndique una de las acciones (numero) >> ";
    cin >> opt;

    cout << "----------------------------------------------------------------------------------------------------\n";

    switch (opt) {
      case 1: {
        dfa.clear();
        errorApertura = false;
        string nombreFichero;
        cout << "Indica el nombre del fichero a cargar: ";
        cin >> nombreFichero;
        nombreFichero = "../examples/"+nombreFichero;
        cout << "\x1b[1J\x1b[H"; //Limpio pantalla
        dfa.create_dfa(nombreFichero.data(), errorApertura);
        if (errorApertura) {
          cerr << "Error de apertura. No se ha podido cargar el fichero correctamente.\n";
        } else {
          cout << "Fichero cargado correctamente.\n";
        }
      }
        break;
      case 2: {
        format = set_format();
        break;
      }
      case 3: {
        cout << "\x1b[2J\x1b[H"; //Limpio pantalla
        if (!errorApertura) {
          if (format == 0) { dfa.write(); } else { dfa.dbg_write(); }
        } else {
          cerr << "El fichero no esta cargado o no se ha cargado correctamente. Por favor, seleccione la opcion 1 (LEER DFA DESDE FICHERO) para cargar el fichero en memoria.\n";
        }
      }
        break;
      case 4: {
        if (!errorApertura) {
          dfa.show_dead_states();
        } else {
          cout << "\x1b[1J\x1b[H"; //Limpio pantalla
          cerr << "El fichero no esta cargado o no se ha cargado correctamente. Por favor, seleccione la opcion 1 (LEER DFA DESDE FICHERO) para cargar el fichero en memoria.\n";
        }
      }
        break;
      case 5: {
        if (!errorApertura) {
          dfa.show_chain_result();
        } else {
          cout << "\x1b[1J\x1b[H"; //Limpio pantalla
          cerr << "El fichero no esta cargado o no se ha cargado correctamente. Por favor, seleccione la opcion 1 (LEER DFA DESDE FICHERO) para cargar el fichero en memoria.\n";
        }
      }
        break;
      case 6: {
        cout << "\x1b[1J\x1b[H"; //Limpio pantalla
        if (!errorApertura) {
          dfa.show_alphabet();
        } else {
          cerr << "El fichero no esta cargado o no se ha cargado correctamente. Por favor, seleccione la opcion 1 (LEER DFA DESDE FICHERO) para cargar el fichero en memoria.\n";
        }
      }
        break;
      case 7: {
        cout << "Ha seleccionado salir del programa.\n";
      }
        break;
      default: {
        cout << "No ha seleccionado una opcion valida. Por favor, indique un numero de los indicados arriba para realizar una accion.\n";
      }
    }
    cout << "----------------------------------------------------------------------------------------------------\n";
  } while (opt != 7);

  return 0;
}
