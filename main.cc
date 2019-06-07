/* 
    Your main program goes here
*/
#include <iostream>
#include <vector>
#include <stack>
#include <string>

#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;


int Eular_Path_Searching(NetworkManager* nm , vector<Vertex*> node_list);
int Accessible_Vertex_Identification(NetworkManager* nm , vector<Vertex*> node_list , string vertex);
int Vertex_Number_Getting(vector<Vertex*> node_list , string vertex);

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
            if( ! ( nm->connected( node_list[i]->name , node_list[j]->name ) ) )
                degree[i] = degree[i] + 1 ;
            else
                degree[i] = degree[i] ;

    
    for(int i = 0 ; i < Number_Of_Vertex ; i++)
        cout<<"Degree["<<i<<"]="<<degree[i]<<endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    
    





    
    //Eular
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    nm->connect("b", "e");
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    







    
    Eular_Path_Searching(nm , node_list);
    
    
    
    

    
    

    

    return 0;
}



int Eular_Path_Searching(NetworkManager* nm , vector<Vertex*> node_list){
    
    std::stack<std::string> Eular_Path;
    std::stack<std::string> Temp_Eular_Path;
    
    nm->print_all_e();
    nm->print_all_v();
    
    
    Temp_Eular_Path.push(node_list[0]->name);
   
   
    /*
    cout<<vertex.top()<<endl;
    */
  
    /*
    cout << Accessible_Vertex_Identification( nm , node_list , node_list[0]->name ) << endl ;
    cout << Vertex_Number_Getting( node_list , "a" ) << endl ;
    */
    
    
    
    
    
    
    
    int Number_Of_Vertex;
    int Start_Vertex_Number;
    Number_Of_Vertex=node_list.size();
    while(!Temp_Eular_Path.empty()) {
        
        Start_Vertex_Number = Vertex_Number_Getting( node_list , Temp_Eular_Path.top() );
        
        if( Accessible_Vertex_Identification( nm , node_list , node_list[Start_Vertex_Number]->name ) ) {
            
            Eular_Path.push(Temp_Eular_Path.top());
            Temp_Eular_Path.pop();
        
        }
        else {
            for( int i = 0 ; i < Number_Of_Vertex ; i++ ) {
                if( ! ( nm->connected_d( node_list[Start_Vertex_Number]->name , node_list[i]->name ) ) ) {
                  
                    nm->disconnect( node_list[Start_Vertex_Number]->name , node_list[i]->name );
                    cout << "Vertex \""<<node_list[Start_Vertex_Number]->name<<"\" and Vertex \" "<<node_list[i]->name<<"\" is disconnected"<<endl;
                    nm->print_all_e();
                    Temp_Eular_Path.push( node_list[i]->name ) ;
                    break;
                }    

                else if( ! ( nm->connected_d( node_list[i]->name , node_list[Start_Vertex_Number]->name ) ) ) {
                    
                    nm->disconnect( node_list[i]->name , node_list[Start_Vertex_Number]->name );
                    cout << "Vertex \""<<node_list[Start_Vertex_Number]->name<<"\" and Vertex \" "<<node_list[i]->name<<"\" is disconnected"<<endl;
                    nm->print_all_e();
                    Temp_Eular_Path.push( node_list[i]->name ) ;
                    break;
                }
                
            }
                
        }    

    }
    
    
    
        cout << Eular_Path.top()<<endl;
        Eular_Path.pop();
        cout << Eular_Path.top()<<endl;
        Eular_Path.pop();
        cout << Eular_Path.top()<<endl;
        Eular_Path.pop();
        cout << Eular_Path.top()<<endl;
        Eular_Path.pop();
        cout << Eular_Path.top()<<endl;
        Eular_Path.pop();
        cout << Eular_Path.top()<<endl;
        Eular_Path.pop();
        cout << Eular_Path.top()<<endl;
        Eular_Path.pop();
        cout << Eular_Path.top()<<endl;
        Eular_Path.pop();
        cout << Eular_Path.top()<<endl;
        Eular_Path.pop();
    
    return 0;
    
}


int Accessible_Vertex_Identification(NetworkManager* nm , vector<Vertex*> node_list , string vertex){
    
    int Number_Of_Vertex;
    Number_Of_Vertex=node_list.size();

    
    int degree = 0 ; 
    for(int i = 0 ; i < Number_Of_Vertex ; i++)
        if(!(nm->connected(vertex , node_list[i]->name)))
            degree = degree + 1 ;
        else
            degree = degree ;
    
    /*    
    cout << "Degree of Vertex\"" << vertex << "\" is " << degree << endl ;
    */
      
    if(degree)
        return 0 ;
    else
        return 1 ;

}

int Vertex_Number_Getting(vector<Vertex*> node_list , string vertex){
    
    int Vertex_Number = 0 ;
    while(vertex != node_list[Vertex_Number]->name)
        Vertex_Number++ ;

    return Vertex_Number;
}

