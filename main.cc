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
void Graph_Eulerizing( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , vector<Vertex*> Odd_Degree_Vertex , int Number_Of_Odd_Degree_Vertex );

int Accessible_Vertex_Identification(NetworkManager* nm , vector<Vertex*> node_list , string Identified_Vertex);
int Vertex_Number_Getting(vector<Vertex*> node_list , string vertex);
int Distance_Getting_By_Breadth_First_Search( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex , string End_Vertex ) ;

queue<std::string> Breadth_First_Search_Path_Getting ( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex ) ;
queue<std::string> Shortest_Path_Getting ( NetworkManager* nm , vector<Vertex*> node_list , int Number_Of_Vertex , string Start_Vertex , string End_Vertex ) ;


// create NetworkManager first
NetworkManager *nm = new NetworkManager () ;


int main ( int argc , char** argv ) {

    //Read Graph
//////////////////////////////////////////////////////////////////////////////////////////////////////
    
    nm -> interpret ( "Graph.txt" ) ;
    //nm -> print_all_e () ;
    //nm -> print_all_v () ;

//////////////////////////////////////////////////////////////////////////////////////////////////////

    //Identify Odd Degree Vertex
//////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Vertex* node = nm -> get_all_nodes () ;
    vector<Vertex*> node_list;
    while( node != 0 ) {

       node_list.push_back( node ) ;
       node = node -> next ;

    }

    int Number_Of_Vertex;
    Number_Of_Vertex = node_list.size();

    int degree[Number_Of_Vertex-1];
    for( int i = 0 ; i < Number_Of_Vertex ; i++ )
        
        degree[i]=0;


    for( int i = 0 ; i < Number_Of_Vertex ; i++ )
        
        for(int j = 0 ; j < Number_Of_Vertex ; j++ )
            
            if( ! ( nm -> connected( node_list[i] -> name , node_list[j] -> name ) ) )
                
                degree[i] = degree[i] + 1 ;
            
            else
                
                degree[i] = degree[i] ;

            
    vector<Vertex*> Odd_Degree_Vertex;    
    int Number_Of_Odd_Degree_Vertex = 0;
    for( int i = 0 ; i < Number_Of_Vertex ; i++ )

        if( degree[i]%2 != 0 ) {
            
            Odd_Degree_Vertex.push_back( node_list[i] ) ;
            Number_Of_Odd_Degree_Vertex++ ;
        
        }


    /*
    for(int i = 0 ; i < Number_Of_Odd_Degree_Vertex ; i++)
        
        cout<<"Vertex \""<<Odd_Degree_Vertex[i]->name<<"\" is odd degree Vertex."<<endl;
        
    */

    /*
    for(int i = 0 ; i < Number_Of_Vertex ; i++)
        
        cout<<"Degree of Vertex \""<<node_list[i]->name<<"\" is "<<degree[i]<<"."<<endl;
    
    */

//////////////////////////////////////////////////////////////////////////////////////////////////////    
    

    //Eulerize Graph ( If Graph is not Eulerian )
//////////////////////////////////////////////////////////////////////////////////////////////////////

    queue<std::string> Shortest_Path_queue ;
    vector<std::string> Shortest_Path_vector ;
    if ( Number_Of_Odd_Degree_Vertex == 2 )
        
        if ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[1]->name ) == 1 )

            nm -> connect( Odd_Degree_Vertex[0] -> name , Odd_Degree_Vertex[1] -> name ) ;
         
        else {
            
            Shortest_Path_queue = Shortest_Path_Getting( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0] -> name , Odd_Degree_Vertex[1] -> name ) ;
            
            for ( int i = 0 ; i < Shortest_Path_queue.size() ; i++ ) {
                
                Shortest_Path_vector.push_back(Shortest_Path_queue.front());
                Shortest_Path_queue.push(Shortest_Path_queue.front());
                Shortest_Path_queue.pop();
            } 
            
            for ( int i = 0 ; i < Shortest_Path_vector.size() - 1 ; i++ )
            
                nm -> connect( Shortest_Path_vector[i] , Shortest_Path_vector[i+1] ) ;
            
        }
    
    else if ( Number_Of_Odd_Degree_Vertex == 4 ) {
   
        if ( ( ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[1]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[2]->name , Odd_Degree_Vertex[3]->name ) ) <= ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[2]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[1]->name , Odd_Degree_Vertex[3]->name ) ) ) && ( ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[2]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[1]->name , Odd_Degree_Vertex[3]->name ) ) <= ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[3]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[1]->name , Odd_Degree_Vertex[2]->name ) ) ) ) {
        
            Shortest_Path_queue = Shortest_Path_Getting( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0] -> name , Odd_Degree_Vertex[1] -> name ) ;

            for ( int i = 0 ; i < Shortest_Path_queue.size() ; i++ ) {
                
                Shortest_Path_vector.push_back(Shortest_Path_queue.front());
                Shortest_Path_queue.push(Shortest_Path_queue.front());
                Shortest_Path_queue.pop();
            }

            
            for ( int i = 0 ; i < Shortest_Path_vector.size() - 1 ; i++ )

                nm -> connect( Shortest_Path_vector[i] , Shortest_Path_vector[i+1] ) ;
            
            Shortest_Path_vector.clear();

            Shortest_Path_queue = Shortest_Path_Getting( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[2] -> name , Odd_Degree_Vertex[3] -> name ) ;

            for ( int i = 0 ; i < Shortest_Path_queue.size() ; i++ ) {
                
                Shortest_Path_vector.push_back(Shortest_Path_queue.front());
                Shortest_Path_queue.push(Shortest_Path_queue.front());
                Shortest_Path_queue.pop();
            }

            for ( int i = 0 ; i < Shortest_Path_vector.size() - 1 ; i++ )

                nm -> connect( Shortest_Path_vector[i] , Shortest_Path_vector[i+1] ) ;
        
        
        }

        else if ( ( ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[2]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[1]->name , Odd_Degree_Vertex[3]->name ) ) <= ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[1]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[2]->name , Odd_Degree_Vertex[3]->name ) ) ) && ( ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[1]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[2]->name , Odd_Degree_Vertex[3]->name ) ) < ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[3]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[1]->name , Odd_Degree_Vertex[2]->name ) ) ) ) {

            Shortest_Path_queue = Shortest_Path_Getting( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0] -> name , Odd_Degree_Vertex[2] -> name ) ;

            for ( int i = 0 ; i < Shortest_Path_queue.size() ; i++ ) {
                
                Shortest_Path_vector.push_back(Shortest_Path_queue.front());
                Shortest_Path_queue.push(Shortest_Path_queue.front());
                Shortest_Path_queue.pop();
            } 
            
            for ( int i = 0 ; i < Shortest_Path_vector.size() - 1 ; i++ )
               
                nm -> connect( Shortest_Path_vector[i] , Shortest_Path_vector[i+1] ) ;
            

            Shortest_Path_vector.clear();
            
            Shortest_Path_queue = Shortest_Path_Getting( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[1] -> name , Odd_Degree_Vertex[3] -> name ) ;
 
            for ( int i = 0 ; i < Shortest_Path_queue.size() ; i++ ) {
                
                Shortest_Path_vector.push_back(Shortest_Path_queue.front());
                Shortest_Path_queue.push(Shortest_Path_queue.front());
                Shortest_Path_queue.pop();

            }     

            for ( int i = 0 ; i < Shortest_Path_vector.size() - 1 ; i++ )

                nm -> connect( Shortest_Path_vector[i] , Shortest_Path_vector[i+1] ) ;

        
        }
        
        else if ( ( ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[3]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[1]->name , Odd_Degree_Vertex[2]->name ) ) <= ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[1]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[2]->name , Odd_Degree_Vertex[3]->name ) ) ) && ( ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[1]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[2]->name , Odd_Degree_Vertex[3]->name ) ) < ( Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0]->name , Odd_Degree_Vertex[2]->name ) + Distance_Getting_By_Breadth_First_Search( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[1]->name , Odd_Degree_Vertex[3]->name ) ) ) ) {

            Shortest_Path_queue = Shortest_Path_Getting( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[0] -> name , Odd_Degree_Vertex[3] -> name ) ;
            
            for ( int i = 0 ; i < Shortest_Path_queue.size() ; i++ ) {
                
                Shortest_Path_vector.push_back(Shortest_Path_queue.front());
                Shortest_Path_queue.push(Shortest_Path_queue.front());
                Shortest_Path_queue.pop();
            }

            for ( int i = 0 ; i < Shortest_Path_vector.size() - 1 ; i++ )
                
                nm -> connect( Shortest_Path_vector[i] , Shortest_Path_vector[i+1] ) ;
            

            Shortest_Path_vector.clear();
            
            Shortest_Path_queue = Shortest_Path_Getting( nm , node_list , Number_Of_Vertex , Odd_Degree_Vertex[1] -> name , Odd_Degree_Vertex[2] -> name ) ;
            
            for ( int i = 0 ; i < Shortest_Path_queue.size() ; i++ ) {
                
                Shortest_Path_vector.push_back(Shortest_Path_queue.front());
                Shortest_Path_queue.push(Shortest_Path_queue.front());
                Shortest_Path_queue.pop();
            }
            
            for ( int i = 0 ; i < Shortest_Path_vector.size() - 1 ; i++ )
                
                nm -> connect( Shortest_Path_vector[i] , Shortest_Path_vector[i+1] ) ;
            

        }

    }

    else if(Number_Of_Odd_Degree_Vertex == 6) {
        
        cout<<"/////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
        cout<<"///                                                                                                   ///"<<endl;
        cout<<"///                                 Please read the file \"README.md\".                                 ///"<<endl;
        cout<<"///The number of vertex with odd degree is graeter than 4 so this program cna not find the Euler Path.///"<<endl;
        cout<<"///                                                                                                   ///"<<endl;
        cout<<"/////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;        
        return 0 ;

    }

   
    
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    //Search Euler Path
//////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    Euler_Path_Searching(nm , node_list);
    
//////////////////////////////////////////////////////////////////////////////////////////////////////    

    return 0;

}

// Search and print the Euler Path, in addition, generate related file.
void Euler_Path_Searching( NetworkManager* nm , vector<Vertex*> node_list ) {
    
    vector<string> Euler_Path ;
    vector<string> Temp_Euler_Path ;

    Temp_Euler_Path.push_back ( node_list[0] -> name ) ;
    
    // Search the Euler Path.
    int Number_Of_Vertex;
    int Start_Vertex_Number;
    Number_Of_Vertex = node_list.size() ;
    while ( ! Temp_Euler_Path.empty() ) {
        
        Start_Vertex_Number = Vertex_Number_Getting ( node_list , Temp_Euler_Path.back() ) ;
        
        if ( Accessible_Vertex_Identification( nm , node_list , node_list[Start_Vertex_Number] -> name ) ) {
            
            Euler_Path.push_back ( Temp_Euler_Path.back() ) ;
            Temp_Euler_Path.pop_back() ;
        
        }

        else
            
            for ( int i = 0 ; i < Number_Of_Vertex ; i++ )
                if ( ! ( nm->connected_d( node_list[Start_Vertex_Number] -> name , node_list[i] -> name ) ) ) {
                  
                    nm -> disconnect ( node_list[Start_Vertex_Number] -> name , node_list[i] -> name );
                    Temp_Euler_Path.push_back ( node_list[i]->name ) ;
                    break;
                }    

                else if( ! ( nm->connected_d( node_list[i]->name , node_list[Start_Vertex_Number]->name ) ) ) {
                    
                    nm->disconnect( node_list[i]->name , node_list[Start_Vertex_Number]->name );
                    Temp_Euler_Path.push_back( node_list[i]->name ) ;
                    break;
                }


    }
    
    // Connect each vertex in Euler_Path. ( If neglect this action, the file "Euler_Path.dot" will only contain the vertex. )
    for(int i = 0 ; i < Euler_Path.size() - 1 ; i++ ) {

        nm -> connect ( Euler_Path[i] , Euler_Path[i+1] ) ;
    }
    
    // Print the Euler Path and generate the file "Euler_Path.txt".
    string writeFileName = "Euler_Path.txt" ;
    ofstream out ( writeFileName.c_str() ) ;
    for ( int i = 0 ; i < Euler_Path.size() ; i++ ) {
        
        cout << Euler_Path[i] <<endl;
        out << Euler_Path[i] << endl;

    }
    out.close();

    // generate the file "Euler_Path.dot".
    Gplot *gp = new Gplot();
    gp -> gp_add ( nm -> elist ) ;
    gp -> gp_dump ( true ) ;
    gp -> gp_export ( "Euler_Path" ) ;
 
}

// Identify if there is any vertex accessible for Identified_Vertex. ( If there is, return 0, otherwise, return 1. )
int Accessible_Vertex_Identification ( NetworkManager* nm , vector<Vertex*> node_list , string Identified_Vertex ) {
    
    int Number_Of_Vertex;
    Number_Of_Vertex = node_list.size();
    
    int Degree_Of_Identified_Vertex = 0 ; 
    for ( int i = 0 ; i < Number_Of_Vertex ; i++ )
        
        if ( ! ( nm -> connected ( Identified_Vertex , node_list[i] -> name ) ) )
            
            Degree_Of_Identified_Vertex = Degree_Of_Identified_Vertex + 1 ;
        
        else
            
            Degree_Of_Identified_Vertex = Degree_Of_Identified_Vertex ;

    
    if ( Degree_Of_Identified_Vertex )
        
        return 0 ;
    
    else
        
        return 1 ;


}

// Get vertex number of Getted_Vertex in container ( ie. stack, queue, etc. ) and return the vertex number.
int Vertex_Number_Getting ( vector<Vertex*> node_list , string Getted_Vertex ) {
    
    int Vertex_Number = 0 ;
    while ( Getted_Vertex != node_list[Vertex_Number] -> name )
        
        Vertex_Number++ ;


    return Vertex_Number;

}


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
    
    Breadth_First_Search_Path = Breadth_First_Search_Path_Getting( nm , node_list , Number_Of_Vertex , Start_Vertex ) ;
    
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

    return Shortest_Path;

}




