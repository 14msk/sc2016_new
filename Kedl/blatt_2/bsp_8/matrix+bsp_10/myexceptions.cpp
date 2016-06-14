#include <iostream>
#include <cstdlib>            // exit
#include "myexceptions.h"

using namespace std;

void my_new_handler(void)
{
  cerr << " Nicht genuegend Speicher vorhanden" << endl;
  cerr << " Beendigung des Programmes" << endl;

  exit (-1);                                             // Fehlercode an Umgebung
}


OutOfRange :: OutOfRange(const long long int &i, const long long int &l)	// Konstruktor
 	: index(i), end_interval(l)
{
  cerr << "Index  " << i << "  is not in interval  [ 0, " << l << " ]" << endl;
  return;
}


