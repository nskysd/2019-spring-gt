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
int Distance_Getting_By_Breadth_First_Search( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex , string End_Vertex ) ;

//int Breadth_First_Search_Path_Getting( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex ) ;
queue<std::string> Breadth_First_Search_Path_Getting ( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex ) ;
queue<std::string> Shortest_Path_Getting ( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex , string End_Vertex ) ;



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
    
    cout<<"Test Point1"<<endl;
    cout<<Number_Of_Odd_Degree_Vertex<<endl;

    
    queue<std::string> Shortest_Path_queue ;
    vector<std::string> Shortest_Path_vector ;
    if ( Number_Of_Odd_Degree_Vertex == 2 ){
        cout<<"Test Point111111111"<<endl;
        if ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[1]->name ) == 1 )
        //if ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , "b" , "d" ) == 1 )
            nm -> connect( Odd_Degree_Vertex[0] -> name , Odd_Degree_Vertex[1] -> name ) ;
        else {
            cout<<"Test Point1"<<endl;
            Shortest_Path_queue = Shortest_Path_Getting( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0] -> name , Odd_Degree_Vertex[1] -> name ) ;
            //Shortest_Path_queue = Shortest_Path_Getting( nm , node_list , Number_Of_Vertex , "b" , "d" ) ;
            int rrrr ;
            rrrr = Shortest_Path_queue.size() ;
            for ( int i = 0 ; i < rrrr ; i++ ) {
                
                Shortest_Path_vector.push_back(Shortest_Path_queue.front());
                Shortest_Path_queue.pop();
            }
        
            cout<<"eeeeeeeeeeeeeee"<<Shortest_Path_vector.size()<<endl;
            cout<<Shortest_Path_vector[2]<<endl;
            
        
            for ( int i = 0 ; i < Shortest_Path_vector.size() - 1 ; i++ ){
                cout<<i<<endl;
                cout<<Shortest_Path_vector[i]<<endl;
                cout<<Shortest_Path_vector[i+1]<<endl;
                nm -> connect( Shortest_Path_vector[i] , Shortest_Path_vector[i+1] ) ;
            }
        }
    }
    else
        cout<<"Test Point"<<endl;
    //else if(Number_Of_Odd_Degree_Vertex > 2)
        //Graph_Eulerizing( nm , Number_Of_Vertex , Odd_Degree_Vertex , Number_Of_Odd_Degree_Vertex );
    
        
   

    cout<<"Test Point"<<endl;




   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    
    //Search Euler Path
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    Euler_Path_Searching(nm , node_list);
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
    
    int Number_Of_Vertex_In_Euler_Path ;
    Number_Of_Vertex_In_Euler_Path = Euler_Path.size() ;
    for( int i = 0 ; i < Number_Of_Vertex_In_Euler_Path ; i++ ) {

        cout << Euler_Path.top()<<endl;
        Euler_Path.pop();

    }
    
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

int Vertex_Number_Getting ( vector<Vertex*> node_list , string vertex){
    
    int Vertex_Number = 0 ;
    while(vertex != node_list[Vertex_Number]->name)
        Vertex_Number++ ;

    return Vertex_Number;
}


/*
void Graph_Eulerizing( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , vector<Vertex*> Odd_Degree_Vertex , int Number_Of_Odd_Degree_Vertex ){
    
    std::queue<std::string> Distance_Getting_By_Breadth_First_Search_Path ;
    
    int Distance_From_Start_Vertex [Number_Of_Vertex] ;
    int Visit_Condition[Number_Of_Vertex] ; //0 is white, 1 is gray, and 2 is black.
    for(int i = 0 ; i < Number_Of_Vertex ; i++) {
    
        Visit_Condition[i] = 0 ;
        Distance_From_Start_Vertex [i] = 9999 ;
    
    }
    
    string parent[Number_Of_Vertex] ;
    
    Distance_Getting_By_Breadth_First_Search_Path.push(Odd_Degree_Vertex[0]);
    
    while( ! Distance_Getting_By_Breadth_First_Search_Path.empty() ) {
    
        for(int i = 0 ; i < Number_Of_Vertex ; i++ ) {
            
            if( ! ( nm->connected( Distance_Getting_By_Breadth_First_Search_Path.front() , node_list[i]->name ) ) ) {
                
                Visit_Condition[i] = 1 ;
                Distance_From_Start_Vertex [i] = Distance_From_Start_Vertex [0] + 1 ;
                parent[i] = Distance_Getting_By_Breadth_First_Search_Path.front() ;
                Distance_Getting_By_Breadth_First_Search_Path.push(node_list[i]->name) ;
                
            }
        }  
        
        Visit_Condition[i] = 2 ;
    
    }
    
    if( Number_Of_Odd_Degree_Vertex = 2 )
        if( ! ( nm->connected( Odd_Degree_Vertex[Number_Of_Odd_Degree_Vertex-2]->name , Odd_Degree_Vertex[Number_Of_Odd_Degree_Vertex-1]->name ) ) )
            nm -> connect( Odd_Degree_Vertex[Number_Of_Odd_Degree_Vertex-2]->name , Odd_Degree_Vertex[Number_Of_Odd_Degree_Vertex-1]->name ) ;
        else if()
    else
}
*/

int Distance_Getting_By_Breadth_First_Search( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex , string End_Vertex ) {

    std::queue<std::string> Temp_Breadth_First_Search_Path ;
    
    int Distance_From_Start_Vertex [Number_Of_Vertex] ;
    int Visit_Condition[Number_Of_Vertex] ; // 0 is nonvisited. ; 1 is visited and has someone can visit. ; 2 is visited and has none can visit.
    for(int i = 0 ; i < Number_Of_Vertex ; i++) {
    
        Distance_From_Start_Vertex [i] = 0 ;
        Visit_Condition[i] = 0 ;
    
    }
    
    int Start_Vertex_Number;
    Start_Vertex_Number = Vertex_Number_Getting( node_list , Start_Vertex ) ;   
    
    //string parent[Number_Of_Vertex] ;
    string Temp_Start_Vertex ;
    
    Distance_From_Start_Vertex [Start_Vertex_Number] = 0;
    Temp_Breadth_First_Search_Path.push(Start_Vertex);
    
    int Temp_Vertex_Number;
    while( ! Temp_Breadth_First_Search_Path.empty() ) {

        Temp_Start_Vertex=Temp_Breadth_First_Search_Path.front() ;
        Temp_Vertex_Number=Vertex_Number_Getting( node_list , Temp_Start_Vertex ) ;
        Temp_Breadth_First_Search_Path.pop() ;
        
        for(int i = 0 ; i < Number_Of_Vertex ; i++ )

            if( ( ! ( nm->connected( Temp_Start_Vertex , node_list[i]->name ) ) ) && ( Visit_Condition[i] == 0 ) ) {

                Visit_Condition[i] = 1 ;
                Distance_From_Start_Vertex[i] = Distance_From_Start_Vertex [Temp_Vertex_Number] + 1 ;
                //parent[i] = Temp_Breadth_First_Search_Path.front() ;
                Temp_Breadth_First_Search_Path.push(node_list[i]->name) ;

            }

        Visit_Condition[Temp_Vertex_Number] = 2 ;

    }
    
    /*
    for(int i = 0 ; i < Number_Of_Vertex ; i++ )
        cout<<"Distance betweem Vertex \""<<Start_Vertex<<"\" and Vertex \""<<node_list[i]->name<<"\" is "<<Distance_From_Start_Vertex[i]<<endl;
    */
    
    
    
    
    int End_Vertex_Number ;
    End_Vertex_Number = Vertex_Number_Getting( node_list , End_Vertex ) ;
    return Distance_From_Start_Vertex[End_Vertex_Number] ;
    

    
    
}



















queue<std::string> Breadth_First_Search_Path_Getting( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex ) {

    std::queue<std::string> Temp_Breadth_First_Search_Path ;
    std::queue<std::string> Breadth_First_Search_Path ;
    
    int Distance_From_Start_Vertex [Number_Of_Vertex] ;
    int Visit_Condition[Number_Of_Vertex] ; // 0 is nonvisited. ; 1 is visited and has someone can visit. ; 2 is visited and has none can visit.
    for(int i = 0 ; i < Number_Of_Vertex ; i++) {
    
        Distance_From_Start_Vertex [i] = 0 ;
        Visit_Condition[i] = 0 ;
    
    }
    
    int Start_Vertex_Number;
    Start_Vertex_Number = Vertex_Number_Getting( node_list , Start_Vertex ) ;   
    
    //string parent[Number_Of_Vertex] ;
    string Temp_Start_Vertex ;
    
    Distance_From_Start_Vertex [Start_Vertex_Number] = 0;
    Temp_Breadth_First_Search_Path.push(Start_Vertex);
    
    Breadth_First_Search_Path.push ( Start_Vertex ) ;
    
    
    int Temp_Vertex_Number;
    while( ! Temp_Breadth_First_Search_Path.empty() ) {

        Temp_Start_Vertex=Temp_Breadth_First_Search_Path.front() ;
        Temp_Vertex_Number=Vertex_Number_Getting( node_list , Temp_Start_Vertex ) ;
        Temp_Breadth_First_Search_Path.pop() ;
        
        for(int i = 0 ; i < Number_Of_Vertex ; i++ )

            if( ( ! ( nm->connected( Temp_Start_Vertex , node_list[i]->name ) ) ) && ( Visit_Condition[i] == 0 ) ) {

                Visit_Condition[i] = 1 ;
                Distance_From_Start_Vertex[i] = Distance_From_Start_Vertex [Temp_Vertex_Number] + 1 ;
                //parent[i] = Temp_Breadth_First_Search_Path.front() ;
                Temp_Breadth_First_Search_Path.push(node_list[i]->name) ;
                Breadth_First_Search_Path.push(node_list[i]->name) ;
            }

        Visit_Condition[Temp_Vertex_Number] = 2 ;

    }
    
    
    /*
    for(int i = 0 ; i < Number_Of_Vertex ; i++ )
        cout<<"Distance betweem Vertex \""<<Start_Vertex<<"\" and Vertex \""<<node_list[i]->name<<"\" is "<<Distance_From_Start_Vertex[i]<<endl;
    */
    

    /*
    for(int i = 0 ; i < Number_Of_Vertex ; i++ ) {
        cout<<"eeeeeeeeeeeeeeeeeeee"<<Breadth_First_Search_Path.front()<<endl;
        Breadth_First_Search_Path.pop() ;
    }
    
    */
    
    
    
    
    
    
    return Breadth_First_Search_Path ;
    

    
    
}










queue<std::string> Shortest_Path_Getting( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex , string End_Vertex ) {

    
    queue<std::string> Breadth_First_Search_Path ;
    queue<std::string> Shortest_Path ;
    
    int Distance_Between_Start_Vertex_And_End_Vertex ;
    Distance_Between_Start_Vertex_And_End_Vertex = Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Start_Vertex , End_Vertex ) ;
    
    /*
    cout<<"Test Point"<<endl;
    cout<<Start_Vertex<<endl;
    cout<<"Test Point"<<endl;
    */
    
    Breadth_First_Search_Path = Breadth_First_Search_Path_Getting( nm , node_list , Number_Of_Vertex , Start_Vertex ) ;
    
    
    //cout<<Breadth_First_Search_Path.front()<<endl;
    Shortest_Path.push( Breadth_First_Search_Path.front() );
    Breadth_First_Search_Path.pop();
    
    
    
    //cout<<Shortest_Path.size()<<endl;
    //cout<<Shortest_Path.front()<<endl;

    
    int j = 1 ;
    int ssss = Breadth_First_Search_Path.size() ;
    for ( int i = 0 ; i < ssss ; i++ ) {
        
        /*
        cout<<"Test Point4"<<endl;
        cout<<i<<endl;
        cout<<Breadth_First_Search_Path.size()<<endl;
        cout<<Shortest_Path.front()<<endl;
        cout<<Breadth_First_Search_Path.front()<<endl;
        
        cout<<Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Shortest_Path.front() , Breadth_First_Search_Path.front() )<<endl;
        cout<<Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Breadth_First_Search_Path.front() , End_Vertex )<<endl;
        */
        
        
        
        if ( ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Shortest_Path.front() , Breadth_First_Search_Path.front() ) == j ) && (( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Breadth_First_Search_Path.front() , End_Vertex ) == (Distance_Between_Start_Vertex_And_End_Vertex - j) ) ) ) {
            
            Shortest_Path.push( Breadth_First_Search_Path.front() );
            //cout<<Shortest_Path.size()<<endl;
            //cout<<"Test Point4"<<endl;
            Breadth_First_Search_Path.pop();
            j++;
        }
        else
            Breadth_First_Search_Path.pop();
        
    }    
    
    
    //Shortest_Path.push( Breadth_First_Search_Path.front() );
    
    
    
    //cout<<"Test Point3"<<endl;
    
    
    /*
    for ( int i = 0 ; i < Distance_Between_Start_Vertex_And_End_Vertex + 1 ; i++ ) {
    
        cout<<Shortest_Path.front()<<endl;
        Shortest_Path.pop();

    }
    */
    
    return Shortest_Path;

}




