/*
****************************************************************************
     STUDENT:  Ricky Romero
 DESCRIPTION:  This is a program that adds node then addes edges to the nodes connecting them together.It will display a 
                list and matrix graph  showing the links between them. it will also try run a Kruskal’s Algorithm but does not work.


 REQUIRED SOURCE FILES:
							Main.h

****************************************************************************
*/
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

/*
 UNDIRECTED
 when an edge is removed the Kruskal’s Algorithm function and no long be used.
 */
bool UNDIRECTED = true;
/*
 NodeData will hold all of the data. 
 Name = is the name of the node
 StreetName = is the name of the edge between the two nodes
 dist = the dist between the two nodes.
 
 the Nodelist will be in a vector of list of struct(nodeData)
 vector < list<NodeData> > nodelist;

 vector holds a list inside that holds the edges and the list have all the data from the struct.
 
 */
struct NodeData{
    
    string name;
    string streetName;
    int dist;
};
/*
 struct Kruskal
 is used for the Kruskals 
 its a simple was to sort the Dist to fond later
 
 everytime we add edges together it saves to the 
 struct Kruskal.
 
 */
struct Kruskal{
    
//    NodeData *nodeData;
    
    string node1;
    string node2;
    string street;
    int nodeOne;
    int nodeTwo;
    int weight;
};


//MARK: Node Class
/*
 Node class 
 Holds all the function and data for the 
 gragh. 
 
 Mostly all of the functions are here so they can share the data
 */
class Node{
private:

    /*
     vector < list<NodeData> > nodelist;
     
     is the main vector for the graph
     
     vector< list<NodeData> > kruList;
     is for the Kruskal list.
     
     */
    vector < list<NodeData> > nodelist;
    vector< list<NodeData> > kruList;

    list<Kruskal> kru;
    struct NodeData* nodeP;
    
public:
    Node();
    void addNode(string);
    void removeNode(string);
    void addEdge(string,string, string,int);
    void removeEdge(string, string);
    void print();
    void printMatrix();
    void search(string);
    void file();
    void MST();
    void Sort(vector< list<NodeData> > &nodelist);
    void sortKru();
    bool findTwoNodes(string,string);
    void dijkstra(string,string);
    string getName() { return nodeP->name; }
    
};
Node::Node(){
}
/*
 this  sort will pass the vector of list that will be sorted
 it will sort everytime a new node to the list
 and everytime a node is removed
 */
void Node::Sort(vector< list<NodeData> > &nodelist)
{
    //does not work is just moving the node and not the other stuff with it

    
    vector< list<NodeData> > :: iterator i;
    vector< list<NodeData> > :: iterator j;
    
    for (i = nodelist.begin(); i != nodelist.end(); ++i)
    {
        for (j = nodelist.begin(); j != nodelist.end(); ++j)
        {
            list<NodeData> temp = *i;
            string strName1 = i->front().name;
            string strName2 = j->front().name;
            
            if (strName1.compare(strName2) < 0)
            {
                *i = *j;
                *j = temp;
            }
        }
    }
    
}
/*
 is is to sort the Kruskals
 
 it sorts the int (dist) from small to big
 
 loops throgh the list then it picks out the weight 
 then checks if its bigger and if so it switches them
 */
void Node::sortKru()
{
    list<Kruskal> :: iterator i;
    list<Kruskal> :: iterator j;
    
    for (i = kru.begin(); i != kru.end(); ++i)
    {
        for (j = kru.begin(); j != kru.end(); ++j)
        {
            Kruskal temp = *i;
            int strName1 = i->weight;
            int strName2 = j->weight;
            
            if (strName1 < strName2)
            {
                *i = *j;
                *j = temp;
            }
        }
    }
}
/*
 Kruskal’s Algorithm
 
 */
void Node::MST(){
    /*
     strating node and an ending node. find the shortest path to the end.
     test:
     */
    cout << "\n\tKruskal’s Algorithm \n" << endl;
    list<NodeData> nodeA;
//    kruList = nodelist;
    NodeData nod;
    
    list<Kruskal> kruNod;
    Kruskal Kru;
    Kru.nodeOne = 0;
    Kru.nodeTwo = 0;
    
    if(UNDIRECTED == true){

        cout << endl;
        for (int i = 0; i < kruList.size(); i++){

        for (list<Kruskal>::iterator iter = kru.begin(); iter != kru.end(); ++iter){

                if(iter->nodeOne <= 2 && iter->nodeTwo <= 2){
                    if(iter->nodeOne + 1 <= 2 && iter->nodeTwo + 1 <= 2){
                        iter->nodeOne++;
                        iter->nodeTwo++;
                        
//                        for (int i = 0; i < kruList.size(); i++){
                        
                            if (kruList[i].front().name == iter->node1){
                                nod.name = iter->node2;
                                nod.streetName = iter->street;
                                nod.dist = iter->weight;
                                kruList[i].push_back(nod);
                                //                    cout << "added: " << nod.name << endl;;
                            }else if (kruList[i].front().name == iter->node2){
                                nod.name = iter->node1;
                                nod.streetName = iter->street;
                                nod.dist = iter->weight;
                                kruList[i].push_back(nod);
                                //                    cout << "added: " << nod.name << endl;;
                            }
//                        }

                        
                        
                    }
                }
            
                }
            }

        cout << "\n     PRINT Kruskal LIST   \n\n";
        
        for (int i = 0; i < kruList.size(); i++){
            
            for (list<NodeData>::iterator it = kruList[i].begin(); it != kruList[i].end(); ++it){
                if (it == kruList[i].begin()){
                    cout << " |" << it->name << "|-> ";
                }else
                    cout << it->name << "(" << it->streetName << "," << it->dist << ")-> ";
            }
            cout << endl;
        }
        
        cout << " \nprint List from low to high" << endl;
        for (list<Kruskal>::iterator iter = kru.begin(); iter != kru.end(); ++iter){
            
            cout << iter->node1 << iter->node2 << " " << iter->weight << " " << iter->nodeOne << " " << iter->nodeTwo << endl;
            
        }
        
        
        
        
    }else if(UNDIRECTED == false){
        
        cout << "ERROR: Kruskal’s Algorithm available only for UNDIRECTED graphs" << endl;
    }
    
    
    
}
/*
 This is to make sure that both Nodes are in the list
 this function is set apart from the add edge function were it was at fist so if i need to use it 
 somewhere else i can call is function to see if both node are in the list.
 
 did not work with the removeedge function b/c it a little diffrent.
 */
bool Node::findTwoNodes(string nodeA, string nodeB){
    
    bool foundA = false, foundB = false,aExist = false, bExist = false;

    /*
     check to see if node is the head and then checks to see if node alread has the edge
     */
    for (int i = 0; i < nodelist.size(); i++){
        /*
         first block checks the first node
         makes sure that it is in front
         then loops throught the list to see if
         nodeB(the node being added) already exist
         */
        if(nodelist[i].front().name == nodeA){ //<--checks node is head
            for (list<NodeData>::iterator it = nodelist[i].begin(); it != nodelist[i].end(); ++it){
                if (it->name == nodeB){ //<--if nodeA already has NodeB
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
        if(nodelist[i].front().name == nodeB){
            for (list<NodeData>::iterator it = nodelist[i].begin(); it != nodelist[i].end(); ++it){
                if (it->name == nodeA){ //<--if nodeB already has NodeA
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
     
     will return true if both nodes are found
     
     else it will just return false.
     */
    if(foundA && foundB){
        
        return true;
    }
    
    return false;
}
//MARK: ADD
/*
 ADD NODE
 
added node to the list "nodelist" 
 this will go infrount of the vector.
 first checks to see if the node is already in the list if not it will
 add the node to the stuct name the it will be pushed to a list of stucts.
 
 that list of stuct will be pushed to the vector.
 
 then i pushed the same node to the Kruskal list to later use.
 
 then both are sorted.
 
 */
void Node::addNode(string node){ //,string name,int dist){
    /*
     checks to see if node already exist
     */
    list<NodeData> nodeA;
    NodeData nod;
    

    for (int i = 0; i < nodelist.size(); i++){
        if(nodelist[i].front().name == node){
            cout << " **Node already exist** \n";
            return;
        }
    }
    /*
     end of checks
     */

    
    nod.name = node;
    nodeA.push_back(nod);

    nodelist.push_back(nodeA);
    kruList.push_back(nodeA);
    
    Sort(nodelist);
    Sort(kruList);

    

    
    cout << "ADDED NODE: " << node << endl;
    return;
}

/*
 Add Edge Function
 
 if the find both node is list function returns true that both node were found it will then 
 
 push eachother to eachother to make an edge. 
 starts off by adding the data to the stuct 
 then the stuch is push to the list
 then that list is push to the right vector.
 
 after the data is saved to the Kruskal struct for later use.
 
 */
void Node::addEdge(string nodeA, string nodeB , string street , int dist){
    cout << "\n **ADDING EDGE** \n";
//    bool foundA = false, foundB = false,aExist = false, bExist = false;
    string edgeName;

    //  findTwoNodes is to check if both node are in the list
    if(findTwoNodes(nodeA, nodeB) == true){
        list<NodeData> nodeData;
        Kruskal Kru;
        NodeData nod;
        for (int i = 0; i < nodelist.size(); i++){
            /*
             first checks is the node will be adding itself.
             if not it will just add the edges to eachother
             */
            if(nodelist[i].front().name == nodeA && nodelist[i].front().name == nodeB){
                nod.name = nodeA;
                nodelist[i].push_front(nod);
                cout << " ADDED:" << nodeA << " TO " << nodeB << endl;
                return;
            }else{
                
                if (nodelist[i].front().name == nodeA){
                    nod.name = nodeB;
                    nod.streetName = street;
                    nod.dist = dist;
                    nodelist[i].push_back(nod);
//                    cout << "added: " << nod.name << endl;;
                }else if (nodelist[i].front().name == nodeB){
                    nod.name = nodeA;
                    nod.streetName = street;
                    nod.dist = dist;
                    nodelist[i].push_back(nod);
//                    cout << "added: " << nod.name << endl;;
                }
            }
        }
        Kru.node1 = nodeA;
        Kru.node2 = nodeB;
        Kru.weight = dist;
        Kru.street = street;
        kru.push_back(Kru);
        sortKru();
        
        cout << "ADDED EDGE: "<< nodeA << " : " << nodeB << " NAME: " << street << " DIST: " << dist << endl << endl;
        return;
    }else{
        cout << " **did not add edge** \n";
    }
    

    
    return;
}
//MARK: REMOVE
/*
 REMOVE NODE
 
 when removing the node you have to remove it from everywhere. from the 
 frount and from every edge. 
 
 start from removing its self then loop until you find it and removing it form everywhere.
 
 
 */
void Node::removeNode(string node){
    cout << endl;
//    cout << "\tREMOVING: "<< node << endl;
    
    /*
     after it removes itself from everywhere
     it will go to the nodes head and clear it out
     */
    for (int i = 0; i < nodelist.size(); i++){
        if (nodelist[i].front().name == node){
            nodelist[i].clear();
            nodelist.erase(nodelist.begin() + i);
            cout << "REMOVED: " << node << endl;
        }
    }
    
    /*
     first it will remove the nodes anywhere in the list.
     checks to see is its the beginning, if so it skips that one and moves to the next
     line to remove
     */
    for (int i = 0; i < nodelist.size(); i++){
        for (list<NodeData>::iterator it = nodelist[i].begin(); it != nodelist[i].end(); ++it){
            if (it->name == node && it == nodelist[i].begin())
                break;
            else if (it->name == node){
                cout << "EDGE AUTO-REMOVED BY NODE DELETION " << nodelist[i].front().name << " " << node << endl;
                nodelist[i].erase(it);
                break;
            }
        }
    }


    cout << " done removing\n";
    Sort(nodelist);

    return;
}
/*
 REMOVE EDGE
 
 First you have to check to see if both node are in the list. 
 then you have to check to see if they have an edge togther to remove it
 
 if both nodes are found and have an edge toghter.
 
 remove it by erase it from eachother.
 
 removing the edge will only be a oneway delete. to remove the full edge 
 the input will have to be entered the other way.
 
 commented below where i commeted out where it makes it a onway.
 */
void Node::removeEdge(string nodeA, string nodeB){
    cout << "removeing edge: " << nodeA << " : " << nodeB << "\n\n";
    bool foundA = false, foundB = false,aExist = false, bExist = false;

    /*
     check to see if node is the head and then checks to see if node alread has the edge
     */
    for (int i = 0; i < nodelist.size(); i++){
        /*
         first block checks the first node
         makes sure that it is in front
         then loops throught the list to see if
         nodeB(the node being added) already exist
         */
        if(nodelist[i].front().name == nodeA){ //<--checks node is head
            for (list<NodeData>::iterator it = nodelist[i].begin(); it != nodelist[i].end(); ++it){
                if (it->name == nodeB){ //<--if nodeA already has NodeB
//                    cout << "already has edge \n:";
                    bExist = true;
                    break;
                }
            }
            if(bExist) {
                cout << " **Node exist to remove edge ** \n";
                foundA = true;
            }
            
        }
        /*
         does the samething for the 2nd node
         */
        if(nodelist[i].front().name == nodeB){
            for (list<NodeData>::iterator it = nodelist[i].begin(); it != nodelist[i].end(); ++it){
                if (it->name == nodeA){ //<--if nodeB already has NodeA
//                    cout << "already has edge \n:";
                    aExist = true;
                    break;
                }
            }
            if(aExist) {
                cout << " **Node exist to remove edge ** \n";
                foundB = true;
            }
        }
    }
    /*
     end if checks
     if both nodes pass, the edges get added to eachother
     */
    if(foundA && foundB){
        UNDIRECTED = false;
        
        for (int i = 0; i < nodelist.size(); i++){
            for (list<NodeData>::iterator it = nodelist[i].begin(); it != nodelist[i].end(); ++it){
                if (nodelist[i].front().name == nodeA){

                    if (it->name == nodeB && it == nodelist[i].begin())
                        break;
                    else if (it->name == nodeB){
                        nodelist[i].erase(it);
                        break;
                    }
                }
                /*
                 by removing the code below, when removing the edge it will become a oneway
                 in order to remove the full edge you will have to remove the edge by filping the input from the command.
                 */
                
               /* if (nodelist[i].front().name == nodeB){
                    
                    if (it->name == nodeA && it == nodelist[i].begin())
                        break;
                    else if (it->name == nodeA){
                        nodelist[i].erase(it);
                        break;
                    }
                } */
            }
            
        }
        
        cout << "Deleted edge: " << nodeA << "," <<nodeB << endl;
    }else{
        
        cout << "*** ERROR *** EDGE DOES NOT EXIST FOR DELETION: "<< nodeA << " " <<  nodeB << endl;
    }

    
}

//MARK: search
/*
 SEARCH
 Loops until the node you are trying to find == with the node in the frount of the vector.
 if found prints out the message then exit the function.
 
 if not found it exit the loop and print out the message then exits the function
 
 */
void Node::search(string node){

    for (int i = 0; i < nodelist.size(); i++)
    {
        if (nodelist[i].front().name == node){
            cout << "NODE: " << node << " FOUND ";
            cout << endl;
            return;
        }
        
    }
    cout << "NODE: " << node << " NOT FOUND \n";
    return;
    
    
    
}
//MARK: Print
/*
 PRINT LIST
 Loops the list and if in frount it prints out a the head style string.
 if not in the frount it prints out a list style string.
 
 loops until the end of the list size.
 
 */
void Node::print(){
    cout << "\n     PRINT LIST   \n\n";

    for (int i = 0; i < nodelist.size(); i++){
    
        for (list<NodeData>::iterator it = nodelist[i].begin(); it != nodelist[i].end(); ++it){
            if (it == nodelist[i].begin()){
                cout << " |" << it->name << "|-> ";
            }else
                cout << it->name << "(" << it->streetName << "," << it->dist << ")-> ";
        }
        cout << endl;
    }

    
    return;
}
//MATRIX

/*
 PRINT MATRIX
 
 first print out he names out to display them on the top of the matrix
 
 then it print out the frount name followed by the edge dist. 
 if the node doesnot have an edge with the node it prints out a -1.
 
 
 
 */
void Node::printMatrix(){
    cout << "\n     PRINT MATRIX   \n";
    int miles = 0;
    string streetName;
    cout << "\t";
    //output column headers
    for (int i = 0; i < nodelist.size(); i++)
        cout << nodelist[i].front().name << "\t";
        cout << std::endl;
    
    for (int i = 0; i < nodelist.size(); i++){
        //output row header
        cout << nodelist[i].front().name << "\t";
    
        for (int j = 0; j < nodelist.size(); j++){
            int y = 0;
            //check for edge
            for (list<NodeData>::iterator it = nodelist[j].begin(); it != nodelist[j].end(); ++it){
                if (it->name == nodelist[i].front().name && it != nodelist[j].begin()){
                    y = 1;
                    miles = it->dist;
                    streetName = it->streetName;
                    break;
                }
            }
            if (y){
//                cout << "1\t";//if edge output 1
                cout << miles << "\t";
            }
            else
                cout << "-1\t";//else output 0
        }
        cout << endl;
    }
    cout << endl;

    return;

}
//removes the \n from the string
/*
 REMOVE \n \r
 
 when running the CSV file the last string has a \n and this function remove that.
 this fuction was found on
 website: Stack Over Flow
 Link: "http://stackoverflow.com/questions/8960055/getline-to-string-copies-newline-as-well"
 */
void remove_carriage_return(string& line)
{
    if (*line.rbegin() == '\r')
    {
        line.erase(line.length() - 1);
    }
}
//MARK: File
/*
 FILE
 
 RUN CSV FILE
 
 this fucntion runs a csv file. 
 
 opens the file then saves every string until the end of the line.
 
 each line has a list of command add,remove,(node/edge), search 
 then it loops until the end of the csv file.
 
 */
void Node::file(){
    string filename;
    string command,input,nodeA,nodeB,name,srtDist;
    int dist;
    
    
    cout << "Ex: /Users/RickyRomero/cose/csvFile.csv \nWhere is the file Located? ";
//    getline(cin, filename);
    cin >> filename;
    ifstream myfile(filename.c_str());
    if (myfile.is_open()){
        cout << "file opean\n ";
        
        while (!myfile.eof()){
            getline(myfile, command,',');
            getline(myfile, input, ',');
            getline(myfile, nodeA, ',');
            getline(myfile, nodeB, ',');
            getline(myfile, name, ',');
            getline(myfile, srtDist, '\n');
            
            remove_carriage_return(srtDist);
            stringstream convert(srtDist);//object from the class stringstream
            convert >> dist;  //the object has the value 12345 and stream it to the integer x

//            dist = stoi(srtDist);
            
//            cout << "-------file--------->" <<command << "--" << input << "--" << nodeA << "--" << nodeB << "--" << name << "--" << srtDist << ": " << dist << endl;
            
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
                                addEdge(nodeA, nodeB,name,dist);
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
                            
                        }else if(command == "kruskal"){
                                MST();
                        }
//            dist = NULL;

        }
    }
}

//MARK: MAIN
/*
 Interface
 
 Interface for the user to know what commands to use.
 
 this promt will diplay until the program is ended.
 
 
 loops until user quits.
 */
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
        cout << "| (9):Kruskal        (10): Quit         |" << endl;
        cout << "+--------------------------------------+" << endl;
        
        cout << "cmd> ";
        cin >> input;
    //    getline(cin, input);
        
        string nodeA , nodeB,name;
        int dist;
        
        
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
            cout << "edge name: ";
            cin >> name;
            cout << "DIST: ";
            cin >> dist;
            n.addEdge(nodeA, nodeB,name,dist);
        }else if(input == "4"){//<--remove edge
            cout<< "edge delete \nNODE1: ";
            cin >> nodeA;
            cout <<"NODE2: ";
            cin >> nodeB;
            n.removeEdge(nodeA, nodeB);
        }else if(input == "5"){//--print list
//            cout << " print list\n";
            n.print();
            
        }else if(input == "6"){//--print matrix
//            cout << " print matrix\n";
            n.printMatrix();
            
        }else if(input == "7"){//<--search
            cout << "node search <name>";
            cin >> nodeA;
            n.search(nodeA);
            
        }else if(input == "8"){//<--search
//            cout << " File\n";
            n.file();
            
        }else if(input == "9"){//<--search
//            cout << " Kruskal\n";
            n.MST();
        }else if(input == "10"){//<--quit
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
/*
 calls menuInterface(); when the user quits the menuInterface loop the program ends.
 */
int main() {
    
    menuInterface();
    return 0;

}
