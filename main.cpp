//****************************************************************************
// Ricky Romero
// DESCRIPTION:  This is a program that adds node then addes edges to the nodes connecting them together.
//
//****************************************************************************

#include <iostream>
#include <vector>
#include <list>
#include <fstream>

using namespace std;


struct NodeData{
    
    int dist;
    string name;
    vector <list<string> > adjList;
    
};


//MARK: Node Class
class Node{
private:
    vector <list<string> > adjList;
    
    struct NodeData* adjNode;
public:
    Node();
    void addNode(string);
    void removeNode(string);
    void addEdge(string,string);
    void removeEdge(string, string);
    void print();
    void printMatrix();
    void search(string);
    void file();
    
};
Node::Node(){
}

//MARK: ADD
void Node::addNode(string node){ //,string name,int dist){
    /*
     checks to see if node already exist
     */
    for (int i = 0; i < adjList.size(); i++){
        if(adjList[i].front() == node){
            cout << " **Node already exist** \n";
            return;
        }
    }
    /*
     end of checks
     */
    list<string> newlist;
    newlist.push_back(node);
    /*
     node is saved to the list and then is pushed by the 
     adjList that will store everything.
     */
    adjList.push_back(newlist);
    cout << "added node: " << node << endl;
    return;
}

void Node::addEdge(string nodeA, string nodeB){
    bool foundA = false, foundB = false,aExist = false, bExist = false;
/*
     check to see if node is the head and then checks to see if node alread has the edge
*/
    for (int i = 0; i < adjList.size(); i++){
        /*
         first block checks the first node
         makes sure that it is in front
         then loops throught the list to see if
         nodeB(the node being added) already exist
         */
        if(adjList[i].front() == nodeA){ //<--checks node is head
            for (list<string>::iterator it = adjList[i].begin(); it != adjList[i].end(); ++it){
                if (*it == nodeB){ //<--if nodeA already has NodeB
                    cout << "already has edge \n:";
                    bExist = true;
                    break;
                }
            }
            if(!bExist) {
                cout << " **Node exist to add edge ** \n";
                foundA = true;
            }

        }
        /*
         does the samething for the 2nd node
         */
        if(adjList[i].front() == nodeB){
            for (list<string>::iterator it = adjList[i].begin(); it != adjList[i].end(); ++it){
                if (*it == nodeA){ //<--if nodeB already has NodeA
                    cout << "already has edge \n:";
                    aExist = true;
                    break;
                }
            }
            if(!aExist) {
                cout << " **Node exist to add edge ** \n";
                foundB = true;
            }
        }
    }
    /*
     end if checks
     if both nodes pass, the edges get added to eachother
     */
    if(foundA && foundB){

        for (int i = 0; i < adjList.size(); i++){
            /*
             first checks is the node will be adding itself.
             if not it will just add the edges to eachother
             */
            if(adjList[i].front() == nodeA && adjList[i].front() == nodeB){
                adjList[i].push_front(nodeA);
                cout << " added:" << nodeA << " to " << nodeB << endl;
                return;
            }else{
                
                if (adjList[i].front() == nodeA){
                    adjList[i].push_back(nodeB);
                }else if (adjList[i].front() == nodeB){
                    adjList[i].push_back(nodeA);
                }
            }
        }
        cout << "added Edge: "<< nodeA << " : " << nodeB << "\n";
        return;
    }else{
        cout << " **did not add edge** \n";
    }
    
    return;
}
//MARK: REMOVE
void Node::removeNode(string node){
    cout << endl;
    cout << "Removing: "<< node << endl;
    /*
     first it will remove the nodes anywhere in the list. 
     checks to see is its the beginning, if so it skips that one and moves to the next
     line to remove itself
     */
    for (int i = 0; i < adjList.size(); i++){
        for (list<string>::iterator it = adjList[i].begin(); it != adjList[i].end(); ++it){
            if (*it == node && it == adjList[i].begin())
                break;
            else if (*it == node)
                adjList[i].erase(it);
            break; // this is why it quits the program
        }
    }
    /*
     after it removes itself from everywhere 
     it will go to the nodes head and clear it out
     */
    for (int i = 0; i < adjList.size(); i++){
        if (adjList[i].front() == node){
            adjList[i].clear();
            adjList.erase(adjList.begin() + i);
        }
    }
//    size--;
    return;
}
void Node::removeEdge(string nodeA, string nodeB){
    cout << "removeing edge: " << nodeA << " : " << nodeB << "\n\n";
    
    for (int i = 0; i < adjList.size(); i++){
        for (list<string>::iterator it = adjList[i].begin(); it != adjList[i].end(); ++it){
            if (adjList[i].front() == nodeA){

                if (*it == nodeB && it == adjList[i].begin())
                    break;
                else if (*it == nodeB){
                    adjList[i].erase(it);
                    break;
                }
            }
            if (adjList[i].front() == nodeB){
                
                if (*it == nodeA && it == adjList[i].begin())
                    break;
                else if (*it == nodeA){
                    adjList[i].erase(it);
                    break;
                }
            }
        }
        
    }


    
}

//MARK: search
void Node::search(string node){
    for (int i = 0; i < adjList.size(); i++)
    {
            if (adjList[i].front() == node){
                cout << "Found node: " << node;
                cout << endl;
                return;
            }
            
    }
    cout << "Node was not found. \n";
    return;
    
    
    
}
//MARK: Print
void Node::print(){
    for (int i = 0; i < adjList.size(); i++){
        for (list<string>::iterator it = adjList[i].begin(); it != adjList[i].end(); ++it){
            if (it == adjList[i].begin())
                cout << " |" << *it << "|-> ";
            else
                cout << *it << " -> ";
        }
        cout << endl;
    }
    return;
}
//MATRIX
void Node::printMatrix(){

    cout << "\t";
    //output column headers
    for (int i = 0; i < adjList.size(); i++)
        cout << adjList[i].front() << "\t";
        cout << std::endl;
    for (int i = 0; i < adjList.size(); i++){
        //output row header
        cout << adjList[i].front() << "\t";
        for (int j = 0; j < adjList.size(); j++){
            int y = 0;
             list<string>::iterator it;
            //check for edge
            for (it = adjList[j].begin(); it != adjList[j].end(); ++it){
                if (*it == adjList[i].front() && it != adjList[j].begin()){
                    y = 1;
                    break;
                }
            }
            if (y)
                cout << "1\t";//if edge output 1
            else
                cout << "0\t";//else output 0
        }
        cout << std::endl;
    }
    cout << std::endl;
    //my code
    for (int i = 0; i < adjList.size(); i++){
        for (int j = 0; j < adjList.size(); j++){
            
            int y = 0;
            
            for (list<string>::iterator it = adjList[j].begin(); it != adjList[j].end(); ++it){
                if (*it == adjList[i].front() && it != adjList[j].begin()){
                    y = 1;
                    break;
                }
                
            }
            if(y)
                cout<< "1\t";
            else
                cout <<"0\t";
            
        }
        cout << endl;
    }

    return;

}
//removes the \n from the string
void remove_carriage_return(string& line)
{
    if (*line.rbegin() == '\r')
    {
        line.erase(line.length() - 1);
    }
}
//MARK: File
void Node::file(){
    string filename;
    string command,input,nodeA,nodeB;
    cout << "Ex: /Users/RickyRomero/cose/nodelist.csv \nWhere is the file Located? ";
//    getline(cin, filename);
    cin >> filename;
    ifstream myfile(filename.c_str());
    if (myfile.is_open()){
        cout << "file opean\n ";
        
        while (!myfile.eof()){
            getline(myfile, command,',');
            getline(myfile, input, ',');
            getline(myfile, nodeA, ',');
            getline(myfile, nodeB, '\n');
            remove_carriage_return(nodeB);

//            cout << "-------file--------->" <<command << "--" << input << "--" << nodeA << "--" << nodeB << "--\n";
            
                        if(command == "node"){
            
                            if(input == "add"){
                                addNode(nodeA);
                            }
                            else if(input == "delete"){
                                removeNode(nodeA);
                            }
                            else if(input == "search"){
                                search(nodeA);
                            }
            
                        }
                        else if(command == "edge"){
                            if(input == "add"){
                                addEdge(nodeA, nodeB);
                            }
                            else if(input == "delete"){
                                removeEdge(nodeA, nodeB);
                            }
            
                        }
                        else if(command == "print"){
                            if(input == "list"){
                                print();
                            }
                            else if(input == "matrix"){
                                printMatrix();
                            }
                            
                        }
        }
    }
}

//MARK: MAIN
void menuInterface()
{
    Node n;

    bool on = true;
    while(on){
        string input;
        cout << "+---------------------------------------+" << endl;
        cout << "|                                       |" << endl;
        cout << "| (1): Add Node       (2): Remove Node  |" << endl;
        cout << "| (3): Add Edge       (4): Remove Edge  |" << endl;
        cout << "| (5): Print List     (6): Print Matrix |" << endl;
        cout << "| (7): Search Node    (8): csv file     |" << endl;
        cout << "|             (9): Quit                 |" << endl;
        cout << "+--------------------------------------+" << endl;
        
        cout << "cmd> ";
        cin >> input;
    //    getline(cin, input);
        
        string nodeA , nodeB;
        if(input == "1"){ //<--add Node
            cout<< "node add <name> ";
            cin >> nodeA;
            n.addNode(nodeA);
        }else if(input == "2"){//<--remove Node
            cout<< "node delete <name> ";
            cin >> nodeA;
            n.removeNode(nodeA);
        }else if(input == "3"){//<--add edge
            cout<< "edge add \nNODE1: ";
            cin >> nodeA;
            cout <<"NODE2: ";
            cin >> nodeB;
            n.addEdge(nodeA, nodeB);
        }else if(input == "4"){//<--remove edge
            cout<< "edge delete \nNODE1: ";
            cin >> nodeA;
            cout <<"NODE2: ";
            cin >> nodeB;
            n.removeEdge(nodeA, nodeB);
        }else if(input == "5"){//--print list
            cout << " print list\n";
            n.print();
            
        }else if(input == "6"){//--print matrix
            cout << " print matrix\n";
            n.printMatrix();
            
        }else if(input == "7"){//<--search
            cout << "node search <name>";
            cin >> nodeA;
            n.search(nodeA);
            
        }else if(input == "8"){//<--search
            cout << " search\n";
            n.file();
            
        }else if(input == "9"){//<--quit
            cout << " quit\n";
            on = false;
        }else{
            cout << "ERROR: Invalid input" << endl;
        }

    }
    cout << "PROGRAM CLOSED." << endl << endl;

    return;
}

//MARK: MAIN
int main() {
    
    menuInterface();
    return 0;

}


















