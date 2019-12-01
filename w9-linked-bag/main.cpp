
#include <iostream>
#include "lbag.h"

using namespace std;


int main() {
    LBag<int> a;
    a.append(1);
    a.append(2);
    a.append(3);
    a.append(4);
    a.find_replace(4, 5);
    a.print();
    
    LBag<int> b;
    b = a;
    b.append(8);
    
    cout << endl;

    // iterating over the elements of the linked list
    // printing elements of b
    for (LBag<int>::iterator it = b.begin(); it != b.end(); ++it) {
        std::cout << "Node has item: " << *it << std::endl;
    }

    return 0;
}

