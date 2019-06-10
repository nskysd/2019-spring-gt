/* 
    Your main program goes here
*/


#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <queue>

#include "network_manager.h"
#include "gplot.h"
#include "path.h"


using namespace std;


void Euler_Path_Searching(NetworkManager* nm , vector<Vertex*> node_list);
int Accessible_Vertex_Identification(NetworkManager* nm , vector<Vertex*> node_list , string vertex);
int Vertex_Number_Getting(vector<Vertex*> node_list , string vertex);
void Graph_Eulerizing( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , vector<Vertex*> Odd_Degree_Vertex , int Number_Of_Odd_Degree_Vertex );
int Breadth_First_Search( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Odd_Degree_Vertex );

// create NetworkManager first
NetworkManager *nm = new NetworkManager();


int main(int argc, char** argv){

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
        //cout<<"Degree["<<i<<"]="<<degree[i]<<endl;
        cout<<"Degree of Vertex \""<<node_list[i]->name<<"\" is "<<degree[i]<<"."<<endl;

//////////////////////////////////////////////////////////////////////////////////////////////////////    
    

    //Eulerize Graph (If Graph is not Eulerian)
//////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    vector<Vertex*> Odd_Degree_Vertex;
    
    int Number_Of_Odd_Degree_Vertex = 0;
    for(int i = 0 ; i < Number_Of_Vertex ; i++)
        if(degree[i]%2 != 0){
            Odd_Degree_Vertex.push_back(node_list[i]) ;
            Number_Of_Odd_Degree_Vertex++;
        }
    for(int i = 0 ; i < Number_Of_Odd_Degree_Vertex ; i++)
        cout<<"Vertex \""<<Odd_Degree_Vertex[i]->name<<"\" is odd degree Vertex."<<endl;
        
    /*
    if(Number_Of_Odd_Degree_Vertex = 2)
        nm->connect(Odd_Degree_Vertex[0]->name,Odd_Degree_Vertex[1]->name);
    //else if(Number_Of_Odd_Degree_Vertex > 2)
        //Graph_Eulerizing( nm , Number_Of_Vertex , Odd_Degree_Vertex , Number_Of_Odd_Degree_Vertex );
    */    
        
    Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name );    
        
    
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    
    //Search Euler Path
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    //Euler_Path_Searching(nm , node_list);
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    
    return 0;

}


void Euler_Path_Searching( NetworkManager* nm , vector<Vertex*> node_list ) {
    
    std::stack<std::string> Euler_Path ;
    std::stack<std::string> Temp_Euler_Path ;
    
    nm->print_all_e();
    nm->print_all_v();

    Temp_Euler_Path.push(node_list[0]->name);
   
   
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
    while(!Temp_Euler_Path.empty()) {
        
        Start_Vertex_Number = Vertex_Number_Getting( node_list , Temp_Euler_Path.top() );
        
        if( Accessible_Vertex_Identification( nm , node_list , node_list[Start_Vertex_Number]->name ) ) {
            
            Euler_Path.push(Temp_Euler_Path.top());
            Temp_Euler_Path.pop();
        
        }
        else
            for( int i = 0 ; i < Number_Of_Vertex ; i++ )
                if( ! ( nm->connected_d( node_list[Start_Vertex_Number]->name , node_list[i]->name ) ) ) {
                  
                    nm->disconnect( node_list[Start_Vertex_Number]->name , node_list[i]->name );
                    cout << "Vertex \""<<node_list[Start_Vertex_Number]->name<<"\" and Vertex \" "<<node_list[i]->name<<"\" is disconnected"<<endl;
                    nm->print_all_e();
                    Temp_Euler_Path.push( node_list[i]->name ) ;
                    break;
                }    

                else if( ! ( nm->connected_d( node_list[i]->name , node_list[Start_Vertex_Number]->name ) ) ) {
                    
                    nm->disconnect( node_list[i]->name , node_list[Start_Vertex_Number]->name );
                    cout << "Vertex \""<<node_list[Start_Vertex_Number]->name<<"\" and Vertex \" "<<node_list[i]->name<<"\" is disconnected"<<endl;
                    nm->print_all_e();
                    Temp_Euler_Path.push( node_list[i]->name ) ;
                    break;
                }
    }
    
    
    
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();
    
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


/*
void Graph_Eulerizing( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , vector<Vertex*> Odd_Degree_Vertex , int Number_Of_Odd_Degree_Vertex ){
    
    std::queue<std::string> Breadth_First_Search_Path ;
    
    int distance [Number_Of_Vertex] ;
    int color[Number_Of_Vertex] ; //0 is white, 1 is gray, and 2 is black.
    for(int i = 0 ; i < Number_Of_Vertex ; i++) {
    
        color[i] = 0 ;
        distance [i] = 9999 ;
    
    }
    
    string parent[Number_Of_Vertex] ;
    
    Breadth_First_Search_Path.push(Odd_Degree_Vertex[0]);
    
    while( ! Breadth_First_Search_Path.empty() ) {
    
        for(int i = 0 ; i < Number_Of_Vertex ; i++ ) {
            
            if( ! ( nm->connected( Breadth_First_Search_Path.front() , node_list[i]->name ) ) ) {
                
                color[i] = 1 ;
                distance [i] = distance [0] + 1 ;
                parent[i] = Breadth_First_Search_Path.front() ;
                Breadth_First_Search_Path.push(node_list[i]->name) ;
                
            }
        }  
        
        color[i] = 2 ;
    
    }
    
    if( Number_Of_Odd_Degree_Vertex = 2 )
        if( ! ( nm->connected( Odd_Degree_Vertex[Number_Of_Odd_Degree_Vertex-2]->name , Odd_Degree_Vertex[Number_Of_Odd_Degree_Vertex-1]->name ) ) )
            nm -> connect( Odd_Degree_Vertex[Number_Of_Odd_Degree_Vertex-2]->name , Odd_Degree_Vertex[Number_Of_Odd_Degree_Vertex-1]->name ) ;
        else if()
    else

}
*/

int Breadth_First_Search( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Odd_Degree_Vertex ) {

    std::queue<std::string> Breadth_First_Search_Path ;
    
    int distance [Number_Of_Vertex] ;
    int color[Number_Of_Vertex] ; //0 is white, 1 is gray, and 2 is black.
    for(int i = 0 ; i < Number_Of_Vertex ; i++) {
    
        color[i] = 0 ;
        distance [i] = 9999 ;
    
    }
    
    
    
    
    
    for(int i = 0 ; i < Number_Of_Vertex ; i++ ){
        cout<<i<<endl;
        cout<<"color is "<<color[i]<<endl;
    }
    
    
    string parent[Number_Of_Vertex] ;
    string aaa ;
    
    distance [1] = 0;
    Breadth_First_Search_Path.push(Odd_Degree_Vertex);
    
    //cout<<Breadth_First_Search_Path.front()<<endl;
    //cout<<node_list[0]->name<<endl;
    
    while( ! Breadth_First_Search_Path.empty() ) {
    
        aaa=Breadth_First_Search_Path.front();
        Breadth_First_Search_Path.pop();
        cout<<aaa<<endl;
        
        for(int i = 0 ; i < Number_Of_Vertex ; i++ ) {
            
            
            //cout<<i<<endl;
            cout<<nm->connected( aaa , node_list[i]->name )<<endl;
            cout<<color[i]<<endl;
            
            if( ( ! ( nm->connected( aaa , node_list[i]->name ) ) ) && ( color[i] == 0 ) ) {
                cout<<i<<" yes"<<endl;
                color[i] = 1 ;
                distance [i] = distance [1] + 1 ;
                cout<<"distance is "<<distance [i]<<endl;
                parent[i] = Breadth_First_Search_Path.front() ;
                Breadth_First_Search_Path.push(node_list[i]->name) ;
                //cout<<node_list[i]->name<<endl;
            }
            else{
                cout<<i<<endl;
                cout<<"no"<<endl;
            }
        }  
        
        /*
        
        if(aaa=="b")
            color[1] = 2 ;
        
        
        switch (aaa) { 
            case 'a': 
                color[0] = 2 ; 
                break; 
            case 'b': 
                color[1] = 2 ; 
                break; 
            case 'c': 
                color[2] = 2 ; 
                break; 
            case 'd': 
                color[3] = 2 ; 
                break;
            case 'e': 
                color[4] = 2 ; 
                break; 
            case 'f': 
                color[5] = 2 ; 
                break; 
            case 'g': 
                color[6] = 2 ; 
                break; 
            //default: 
                //; 
        }
        
        
        
        */
        
        
        
        
        /*
        cout<<Breadth_First_Search_Path.front()<<endl;
        Breadth_First_Search_Path.pop();
        cout<<Breadth_First_Search_Path.front()<<endl;
        Breadth_First_Search_Path.pop();
        cout<<Breadth_First_Search_Path.front()<<endl;
        Breadth_First_Search_Path.pop();
        cout<<Breadth_First_Search_Path.front()<<endl;
        Breadth_First_Search_Path.pop();
        cout<<Breadth_First_Search_Path.front()<<endl;
        Breadth_First_Search_Path.pop();
        cout<<Breadth_First_Search_Path.front()<<endl;
        Breadth_First_Search_Path.pop();
        */
   
    }
    
    /*
    for(int i = 0 ; i < Number_Of_Vertex ; i++ ){
        cout<<i<<endl;
        cout<<distance[i]<<endl;
    }
    */

    return 0 ;

}




















