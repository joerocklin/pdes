#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <iostream>
using namespace std;

static unsigned int debug_level = 0;

#define print_method_string if (debug_level > 2) { cout << "-- " << __FILE__ << ":" << __LINE__ << " - " << __FUNCTION__; }
#define enter_method if (debug_level > 2) { print_method_string; cout << endl; }
#define method_with_id(id) if (debug_level > 2) { print_method_string; cout << " ID: " << id << endl; }

#endif