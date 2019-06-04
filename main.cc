/* 
    Your main program goes here
*/
#include <iostream>
#include <vector>

#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;


int Eular_Path_Searching(NetworkManager* nm);

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











    //Identify Odd Degree Vertex
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

    
    for(int i = 0 ; i < Number_Of_Vertex ; i++)
        cout<<"Degree["<<i<<"]="<<degree[i]<<endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    
    





    
    //Eular
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    nm->connect("b", "e");
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    







    
    Eular_Path_Searching(nm);
    
    
    
    

    
    

    

    return 0;
}



int Eular_Path_Searching(NetworkManager* nm){
    
    nm->print_all_e();
    nm->print_all_v();
    
    return 0;
    
}