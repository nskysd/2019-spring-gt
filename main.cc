/* 
    Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();

int main(int argc, char** argv){

    /* start your program */
    
    nm->interpret("Graph.txt");
    
    nm->print_all_e();
    
    nm->print_all_v();
    

    return 0;
}