#ifndef BUG_H
#define BUG_H

#include <iostream>

template <typename T>
void bug(T msg) {
    std::cerr << "> " << msg << std::endl;
}

#endif // BUG_H

