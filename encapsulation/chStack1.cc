// Filename: chStack1.cc
#include <iostream>
#include "chStack1.h"

int countChar(char c, ChStack s) {
    int  count = 0;
    while (!s.isEmpty())
        count += (c == s.pop());
    return count;
}