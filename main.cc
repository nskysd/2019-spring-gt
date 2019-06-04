/* 
    Your main program goes here
*/
#include <iostream>
#include <vector>

#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();


int main(int argc, char** argv){

    /* start your program */


    //Read Graph
//////////////////////////////////////////////////////////////////////////////////////////////////////
    nm->interpret("Graph.txt");
    nm->print_all_e();
    nm->print_all_v();
//////////////////////////////////////////////////////////////////////////////////////////////////////




    Vertex* node = nm->get_all_nodes();
    vector<Vertex*> node_list;

    while(node != 0 ){
       node_list.push_back(node);
       node=node->next;
    }

    /*
    for(int i = 0 ; i < 10 ; i++)
        cout<<node_list[i]->name<<endl;
    */

    int Number_Of_Vertex;
    Number_Of_Vertex=node_list.size();

    
    int degree[Number_Of_Vertex-1];
    for(int i = 0 ; i < Number_Of_Vertex ; i++)
        degree[i]=0;
    
    for(int i = 0 ; i < Number_Of_Vertex ; i++)
        for(int j = 0 ; j < Number_Of_Vertex ; j++)
            if(!(nm->connected(node_list[i]->name , node_list[j]->name)))
                degree[i]=degree[i]+1;
            else
                degree[i]=degree[i];

    /*
    for(int i = 0 ; i < Number_Of_Vertex ; i++)
        cout<<"Degree["<<i<<"]="<<degree[i]<<endl;
    */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    
    Degree_a=(nm->connected("a" , "b"))+(nm->connected("a" , "c"));
    
    cout<<nm->connected("a" , "d");
    
    
    
    cout<<"Degree_a="<<Degree_a<<endl;

    */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    nm->print_all_e();
    nm->print_all_v();
    */
    
    
    
    
    

    

    return 0;
}