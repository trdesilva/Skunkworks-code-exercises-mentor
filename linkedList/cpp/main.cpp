#include "LinkedList.h"
#include <iostream>

int main(int argc, char** argv)
{
    // Test your LinkedList here
    int a[4] = {1,2,3,4};
    LinkedList* list = new LinkedList(a, 4);
    if(list->get(0) != 1 || list->get(1) != 2
    || list->get(2) != 3 || list->get(3) != 4)
    {
        std::cout << "uh oh: " << list->get(0) << "," << list->get(1) << "," << list->get(2) << "," << list->get(3);
    }
    
    return 0;
}
