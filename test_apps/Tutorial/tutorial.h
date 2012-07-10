#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <iostream>
using namespace std;

#define print_method_string cout << "-- " << __FILE__ << ":" << __LINE__ << " - " << __FUNCTION__;
#define enter_method print_method_string; cout << endl;
#define method_with_id(id) print_method_string; cout << " ID: " << id << endl;

#endif