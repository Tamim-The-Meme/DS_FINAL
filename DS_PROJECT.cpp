#include <iostream>
#include <cstdlib>
#include <cmath>
#include <conio.h>

using namespace std;








//=====================================================GLOBAL VARIABLES===================================================//
int carnode = 0;
bool gamestarted = false;
bool displayshortestpath = false;
int G_number;
int G_total;
int G_START;
int G_END;
int MOVEMENTSMADE = 0;
int GAMEENDED = 0;

bool lastnode = false;
int SCORE = 0;
string GAMESTATUS = "";
//======================================================DEFAULT NODE BLOCK=========================================//
struct Node {
    int data;
    Node* next;
    int level = 0;
    Node* top;
    Node* bottom;
    Node* left;
    Node* right;
    char charact;
    int weight;
    bool isshortestpath;

    int QUEUENODE;
    char QUEUECHARACT;

    Node(int value) : data(value), next(nullptr) {
        charact = '_';
        level = 0;
        top = bottom = left = right = nullptr;
        weight = 1;
        isshortestpath = false;

    }
};




//SECOND NODE CLASS FOR HOLDING VALUES OTHER THEN NODES
//USED TO MAKE CODE EASIER

//=============================== CREATING A SECOND STRUCT TO RETURN MULTIPLE VALUES (PAIRS AND TRIOS ====================================//

struct structure
{
    int value1;
    char value2;
    string value3;
};



//========================================================STACK DATA STRUCTURE========================================================//
class Stack {
public:
   
    Node* topNode;


    Stack() : topNode(nullptr) {}

   /* ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }*/

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop() {
        if (!isEmpty()) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    int top() const {
        if (!isEmpty()) {
            return topNode->data;
        }
        // Handle error, throw an exception, or return a special value
        return -1; // Placeholder for an empty stack
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }
};




//=================================================QUEUE DATA STRUCTURE========================================================//




class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

  

    Node* frontnode()
    {
        return front;
    }

    Node* rearnode()
    {
        return rear;
    }
    bool isEmpty() {
        return front == nullptr;
    }

  
    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void enqueue(char charact, int nodevalue)
    {
        Node* newNode = new Node(nodevalue);
        newNode->QUEUENODE = nodevalue;
        newNode->QUEUECHARACT = charact;
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

  



    int dequeue() {
        if (isEmpty()) {
            std::cerr << "Error: Queue is empty." << std::endl;
            return -1; 
        }

        int value = front->data;
        Node* temp = front;

        if (front == rear) {
            front = rear = nullptr;
        }
        else {
            front = front->next;
        }

        delete temp;
        return value;
    }


    structure dequeue2() {
        if (isEmpty()) {
            std::cerr << "Error: Queue is empty." << std::endl;
            structure temp;
            temp.value1 = -100;
            return temp;
        }
        structure ret;
        ret.value1 = front->QUEUENODE;
        ret.value2 = front->QUEUECHARACT;
        Node* temp = front;

        if (front == rear) {
            front = rear = nullptr;
        }
        else {
            front = front->next;
        }

        delete temp;
        return ret;
    }


   /* ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }*/
};


//======================================================PRIORITY QUEEUEUE DATA STRCUTRUE====================================================//
class PriorityQueue {
private:
    int* distances;
    int* vertices;
    int size;
    int capacity;

public:
    PriorityQueue(int capacity) : size(0), capacity(capacity) {
        distances = new int[capacity];
        vertices = new int[capacity];
    }

    ~PriorityQueue() {
        delete[] distances;
        delete[] vertices;
    }

    void push(int distance, int vertex) {
        int i = size;
        while (i > 0 && distances[(i - 1) / 2] > distance) {
            distances[i] = distances[(i - 1) / 2];
            vertices[i] = vertices[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        distances[i] = distance;
        vertices[i] = vertex;
        size++;
    }

    pair<int, int> top() {
        return { distances[0], vertices[0] };
    }

    void pop() {
        size--;
        distances[0] = distances[size];
        vertices[0] = vertices[size];
        heapify(0);
    }

    bool empty() {
        return size == 0;
    }

private:
    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && distances[left] < distances[smallest]) {
            smallest = left;
        }

        if (right < size && distances[right] < distances[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            swap(distances[i], distances[smallest]);
            swap(vertices[i], vertices[smallest]);
            heapify(smallest);
        }
    }
};


//====================================================SIMPLE ARRAY WALI LINKED LIST==========================================================//




class LinkedList {
private:
 
public:
    Node* head;
    int num;
    LinkedList() : head(nullptr) {
        num = 0;
    }
    void addNode(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        num = num + 1;
    }


    void addNode(int value, char destination) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;   
    }

    void displayList() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
    }


    bool search(int val)
    {
        bool found = false;
        Node* curr = head;
        while (curr)
        {
            if (curr->data == val) 
            {
                found = true;
                break;
            }
            curr = curr->next;
        }

        return found;
    }


    int iterate(int index)
    {
        Node* curr = head;
        int i = 0;
        while (curr)
        {
            if ( i == index) break;
            curr = curr->next;
            i++;
        }
        if (curr)
            return  curr->data;

        else return 4;
    }

   
  
};


//===================================================GRAPH DATA STRUCTURE=============================================================//



class Graph {
private:
    int numVertices;
    LinkedList* adjacencyList;
    LinkedList gnodes;

    Queue obstacles;

public:


    Graph()
    {
        adjacencyList = nullptr;
        numVertices = 0;

    }
    Graph(int vertices) : numVertices(vertices) {
        adjacencyList = new LinkedList[numVertices];
        for (int i = 0 ; i < numVertices ;i++)
        {
            gnodes.addNode(i);
        }
    }


    void setup(int vertices)
    {
        numVertices = vertices;
        adjacencyList = new LinkedList[vertices];
        for (int i = 0; i < numVertices; i++)
        {
            gnodes.addNode(i);

            
        }

    }






    bool validatemovement(int move)
    {

        Node* currnode = gnodes.head;
        while (currnode)
        {
            if (currnode->data == carnode)
            {
                break;
            }
            currnode = currnode->next;
        }
        if (move == 0)  //above
        {

            /*
             carnode = carnode - G_number; top
             carnode = carnode + G_number; below
             carnode = carnode + 1 left 
             carnode = carnode + 1 right
            */
            if (currnode->top)
            {
                if (currnode->top->charact == '#' || currnode->top->charact == '&' || currnode->top->charact == '+' || currnode->top->charact == 'P' || currnode->top->charact == 'O')
                {
                    carnode = carnode - G_number;
                    SCORE--;
                    MOVEMENTSMADE++;
                     
                    if (MOVEMENTSMADE % 2 == 0 && !obstacles.isEmpty() )
                    {
                        structure temp = obstacles.dequeue2();
                        updataobstacles(temp.value1, temp.value2);
                    }
                    return true;
                }
                else return false;
            }
            else return false;
        }


        if (move == 1)  //below
        {
            if (currnode->bottom)
            {
                if (currnode->bottom->charact == '#' || currnode->bottom->charact == '&'||currnode->bottom->charact == '+' || currnode->bottom->charact == 'O' || currnode->bottom->charact == 'P')
                {
                    carnode = carnode + G_number;
                    SCORE--;
                    MOVEMENTSMADE++;
                    if (MOVEMENTSMADE % 3 == 0 && obstacles.isEmpty() == false)
                    {
                        structure temp = obstacles.dequeue2();
                        updataobstacles(temp.value1, temp.value2);
                    }
                    return true;
                }
                else 
                {
                  
                    return false;
                }
            }
            else 
            {
                
                return false;
            }
        }

        if (move == 2)  //left
        {
            if (currnode->left)
            {
                if (currnode->left->charact == '#' || currnode->left->charact == '&' || currnode->left->charact == '+' || currnode->left->charact == 'O' || currnode->left->charact == 'P')
                {
                    carnode = carnode - 1;
                    SCORE--;
                    MOVEMENTSMADE++;
                    if (MOVEMENTSMADE % 3 == 0 && obstacles.isEmpty() == false)
                    {
                        structure temp = obstacles.dequeue2();
                        updataobstacles(temp.value1, temp.value2);
                    }
                    return true;
                }
                else return false;
            }
            else return false;
        }

        if (move == 3)  //right
        {
            if (currnode->right)
            {
                if (currnode->right->charact == '#' || currnode->right->charact == '&' || currnode->right->charact == '+' || currnode->right->charact == 'O' || currnode->right->charact == 'P')
                {
                    carnode = carnode + 1;
                    SCORE--;
                    MOVEMENTSMADE++;
                    if (MOVEMENTSMADE % 3 == 0 && obstacles.isEmpty() == false)
                    {
                        structure temp = obstacles.dequeue2();
                        updataobstacles(temp.value1, temp.value2);
                    }
                    return true;
                }
                else return false;
            }
            else return false;
        }


    }








    void addEdge(int source, int destination, char direction) {
        adjacencyList[source].addNode(destination);
        adjacencyList[destination].addNode(source);
        Node* currnode = gnodes.head;   //source node
        while (currnode)
        {
            if (currnode->data == source) break;
            currnode = currnode->next;
        }

        Node* currnode2 = gnodes.head; //destination node
        while (currnode2)
        {
            if (currnode2->data == destination) break;
            currnode2 = currnode2->next;
        }


        if (direction == 't')
        {
            currnode->top = currnode2;
        }
        else if (direction == 'b')
        {
            currnode->bottom = currnode2;
        }
        else if (direction == 'l')
        {
            currnode->left = currnode2;
        }
        else if (direction == 'r')
        {
            currnode->right = currnode2;
        }
    }


    void printnodesonly()
    {
        Node* currnode = gnodes.head;

        while (currnode)
        {
            cout << currnode->data << " LEVEL : " << currnode->level << endl;
            if (currnode->top) cout << "[ TOP ]" << currnode->top->data << endl;
            if (currnode->bottom) cout << "[ BOTTOM ]" << currnode->bottom->data << endl;
            if (currnode->left) cout << "[ LEFT ]" << currnode->left->data << endl;
            if (currnode->right) cout << "[ RIGHT ]" << currnode->right->data << endl;
            currnode = currnode->next;
            cout << endl;
        }
    }


    void printadjacencylist()
    {
        for (int i = 0; i < numVertices; i++)
        {
            cout << "[ADJACENCY LIST] Node number: " << i << endl;
            Node* currnode = adjacencyList[i].head;
            while (currnode)
            {
                cout << currnode->data << " ";
                currnode = currnode->next;
            }
            cout << endl;
        }
    }








    void addspacing(int startVertex) {
        bool* visited = new bool[numVertices]();


        Queue bfsQueue;
        visited[startVertex] = true;
        bfsQueue.enqueue(startVertex);

  

        while (!bfsQueue.isEmpty()) {

            int currentVertex = bfsQueue.frontnode()->data;
          
            Node* currnodes = gnodes.head;
            while (currnodes)
            {
                if (currnodes->data == startVertex) break;
                currnodes = currnodes->next;
            }

            if (!currnodes->right)
            {
                Node* newnode = new Node(-1);
                newnode->level = currnodes->level;
                currnodes->right = newnode;
            }


            bfsQueue.dequeue();
            for (Node* neighbor = adjacencyList[currentVertex].head; neighbor != nullptr; neighbor = neighbor->next) {
                int neighborVertex = neighbor->data;
                if (!visited[neighborVertex]) {
                    Node* currnode = gnodes.head;
                    while (currnode)
                    {
                        if (currnode->data == neighborVertex) break;
                        currnode = currnode->next;
                    }
                   

                    if (!currnode->right)
                    {
                        Node* newnode = new Node(-1);
                        newnode->level = currnodes->level;
                        currnode->right = newnode;
                    }

                    visited[neighborVertex] = true;
                    bfsQueue.enqueue(neighborVertex);
                }
            }
        }

       // delete[] visited;
        cout << std::endl;
    }








  

   
    void BFS(int startVertex) {
        bool* visited = new bool[numVertices]();

      
       Queue bfsQueue;
        visited[startVertex] = true;
        bfsQueue.enqueue(startVertex);

       

        while (!bfsQueue.isEmpty()) {
           
            int currentVertex = bfsQueue.frontnode()->data;
            
            Node* currnodes = gnodes.head;
            while (currnodes)
            {
                if (currnodes->data == startVertex) break;
                currnodes = currnodes->next;
            }

            if (currnodes->bottom)
            {
                Node* currnodeb = gnodes.head;
                while (currnodeb)
                {
                    if (currnodeb->data == currnodes->bottom->data) break;
                    currnodeb = currnodeb->next;
                }

                currnodeb->level = currnodes->level + 1;
            }



            if (currnodes->right)
            {
                Node* currnoder = gnodes.head;
                while (currnoder)
                {
                    if (currnoder->data == currnodes->right->data) break;
                    currnoder = currnoder->next;
                }

                currnoder->level = currnodes->level;
            }
            if (currnodes->left)
            {
                Node* currnodel = gnodes.head;
                while (currnodel)
                {
                    if (currnodel->data == currnodes->left->data) break;
                    currnodel = currnodel->next;
                }

                currnodel->level = currnodes->level;
            }

            if (currnodes->top)
            {
                Node* currnodet = gnodes.head;
                while (currnodet)
                {
                    if (currnodet->data == currnodes->top->data) break;
                    currnodet = currnodet->next;
                }

                currnodet->level = currnodes->level - 1;
            }


            bfsQueue.dequeue();
            for (Node* neighbor = adjacencyList[currentVertex].head; neighbor != nullptr; neighbor = neighbor->next) {
                int neighborVertex = neighbor->data;
                if (!visited[neighborVertex]) {
                    Node* currnode = gnodes.head;
                    while (currnode)
                    {
                        if (currnode->data == neighborVertex) break;
                        currnode = currnode->next;
                    }
                    if (currnode->bottom)
                    {
                        Node* currnodeb = gnodes.head;
                        while (currnodeb)
                        {
                            if (currnodeb->data == currnode->bottom->data) break;
                            currnodeb = currnodeb->next;
                        }

                        currnodeb->level = currnode->level + 1;
                    }




                    if (currnode->top)
                    {
                        Node* currnodet = gnodes.head;
                        while (currnodet)
                        {
                            if (currnodet->data == currnode->top->data) break;
                            currnodet = currnodet->next;
                        }

                        currnodet->level = currnode->level - 1;
                    }

                    if (currnode->right)
                    {
                        Node* currnoder = gnodes.head;
                        while (currnoder)
                        {
                            if (currnoder->data == currnode->right->data) break;
                            currnoder = currnoder->next;
                        }

                        currnoder->level = currnode->level;
                    }
                    if (currnode->left)
                    {
                        Node* currnodel = gnodes.head;
                        while (currnodel)
                        {
                            if (currnodel->data == currnode->left->data) break;
                            currnodel = currnodel->next;
                        }

                        currnodel->level = currnode->level;
                    }


                    visited[neighborVertex] = true;
                    bfsQueue.enqueue(neighborVertex);
                }
            }
        }

        //delete[] visited;
        cout << std::endl;
    }



    void updateturns(int startVertex) {
        bool* visited = new bool[numVertices]();


        Queue bfsQueue;
        visited[startVertex] = true;
        bfsQueue.enqueue(startVertex);



        while (!bfsQueue.isEmpty()) {

            int currentVertex = bfsQueue.frontnode()->data;

            Node* currnodes = gnodes.head;
            while (currnodes)
            {
                if (currnodes->data == startVertex) break;
                currnodes = currnodes->next;
            }


            if (currnodes->right)

            {
                if (currnodes->right->charact == '_' && currnodes->charact == '_')
                {
                    currnodes->charact = '+';
                }
                if (currnodes->right->charact == '+' && currnodes->charact != '_')
                {
                    currnodes->charact = '#';
                }

            }

            if (currnodes->left)

            {
                if ( currnodes->left->charact == '_' && currnodes->charact != '_' )
                {
                    currnodes->charact = '+';

                }
                if (currnodes->left->charact == '+' && currnodes->charact != '_')
                {
                    currnodes->charact = '#';
                }
            }

            if (currnodes->top)
            {
                if (currnodes->top->charact == '+' && currnodes->charact != '_')
                {
                    currnodes->charact = '#';
                }
            }

            if (currnodes->bottom)
            {
                if (currnodes->bottom->charact == '+' && currnodes->charact != '_')
                {
                    currnodes->charact = '#';
                }
            }




            bfsQueue.dequeue();
            for (Node* neighbor = adjacencyList[currentVertex].head; neighbor != nullptr; neighbor = neighbor->next) {
                int neighborVertex = neighbor->data;
                if (!visited[neighborVertex]) {
                    Node* currnode = gnodes.head;
                    while (currnode)
                    {
                        if (currnode->data == neighborVertex) break;
                        currnode = currnode->next;
                    }
         
                    if (currnode->right)

                    {
                        if (currnode->right->charact == '_' && currnode->charact != '_')
                        {
                            currnode->charact = '+';
                        }

                        if (currnode->right->charact == '+' && currnode->charact != '_')
                        {
                            currnode->charact = '#';
                        }
                    }

                    if (currnode->left)

                    {
                        if (currnode->left->charact == '_' && currnode->charact != '_')
                        {
                            currnode->charact = '+';
                        }

                        if (currnode->left->charact == '+' && currnode->charact != '_')
                        {
                            currnode->charact = '#';
                        }
                    }


                    if (currnode->top)
                    {
                        if (currnode->top->charact == '+' && currnode->charact != '_')
                        {
                            currnode->charact = '#';
                        }
                    }

                    if (currnode->bottom)
                    {
                        if (currnode->bottom->charact == '+' && currnode->charact != '_')
                        {
                            currnode->charact = '#';
                        }
                    }




                    visited[neighborVertex] = true;
                    bfsQueue.enqueue(neighborVertex);
                }
            }
        }

        //delete[] visited;
        cout << std::endl;
    }


    void displaymap(int startVertex)
    {

        cout << "FUNCTION STARTED WITH TOTAL VERTICES: " << numVertices << endl;
        int skip = 0;

        cout << "      ";
        for (int i = 0; i < G_number*2 + 2; i++)
        {
            cout << "_";
        }
        cout << endl;

        cout << "      |";
        int ski = 0;
        for (int i = 0; i < sqrt(numVertices) - 1; i++)
        {
           
            Node* currnode = gnodes.head;
            
            while (currnode)
            {
               
                    /*if (currnode->right != nullptr)
                        if (currnode->right->data == -1 && currnode->level == i) cout << " ";*/
                    if ( skip > 0)
                    {
                        if (currnode->level == i) 
                        {
                            if (currnode->data == carnode && gamestarted == true) cout << 'C';
                            else if (currnode->data == G_START) cout << 'S';
                            else if (currnode->data == G_END) cout << 'E';
                            else if (currnode->isshortestpath == true && displayshortestpath == true) cout << '$';
                            else if (currnode->charact == 'O') cout << 'O';
                            else if (currnode->charact == 'P') cout << 'P';
                            else if (currnode->charact == '+') cout << '+';
                            else if (currnode->isshortestpath == true && displayshortestpath == false) cout << '.';
                            else if (currnode->charact == '#') cout << '.';
                            else if (i % 2 == 0 && currnode->charact != '_')  cout << '.';
                            else if  (i % 2 != 0 && currnode->charact != '_')cout << ".";
                            else cout << " ";


                            cout << " ";
                           // cout << currnode->charact;
                        }
                    }

                    currnode = currnode->next;

                    skip++;
               
            }
           
                cout << "|";
                cout << endl;
                cout << "      |";
            

           

        }
        for (int i2 = 0; i2 < G_number * 2 ; i2++)
        {
            cout << "_";
        }
        cout << '|';
        cout << endl;

        cout << "FUNCTION EXITED" << endl;

    }


    void DFS(int startVertex) {

        srand(static_cast<unsigned int>(time(0)));



        bool* visited = new bool[numVertices]();
        Stack dfsStack;

        visited[startVertex] = true;
        dfsStack.push(startVertex);

        while (!dfsStack.isEmpty()) {
            int currentVertex = dfsStack.topNode->data;
            dfsStack.pop();
            int tempdiv = adjacencyList[currentVertex].num;
           
           /* cout << adjacencyList[currentVertex].head->data << " - > " << tempdiv << endl;*/
            if (tempdiv == 0)
            {
                tempdiv = 1;
            }




            int randomNumber = rand() % tempdiv;
           
            int i = 0;
            for (Node* neighbor = adjacencyList[currentVertex].head; neighbor != nullptr; neighbor = neighbor->next) {
                int neighborVertex = neighbor->data;

                
                if (!visited[neighborVertex]) {
                    visited[neighborVertex] = true;


                    Node* currnode = gnodes.head;
                    while (currnode)
                    {
                        if (currnode->data == neighbor->data)
                        {
                            break;
                        }

                        currnode = currnode->next;
                    }

                    if (i == randomNumber || i == randomNumber + 1 || i == randomNumber - 1 || i == randomNumber + 2)
                    {
                        currnode->charact = '#';
                        //if ( currnode->next) currnode->next->charact = '#';
                    }

                    dfsStack.push(neighborVertex);

                    
                    


                }

                i++;

            }
        }

        //delete[] visited;
       
    }


    //=============================================================DJISKIRTIS ALGORITHM===============================================================//

    void dijkstra(int startVertex, int max, int  number, int total) {
        int* distances = new int[numVertices];
        int* predecessors = new int[numVertices];
        bool* visited = new bool[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            distances[i] = max;
            predecessors[i] = -1;  // Initialize predecessors to -1
            visited[i] = false;
        }

        distances[startVertex] = 0;

        PriorityQueue pq(numVertices);
        pq.push(0, startVertex);

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) {
                continue;
            }

            visited[u] = true;

            for (Node* neighbor = adjacencyList[u].head; neighbor != nullptr; neighbor = neighbor->next) {
                int v = neighbor->data;
                int weight = neighbor->weight;

                if (distances[v] > distances[u] + weight) {
                    distances[v] = distances[u] + weight;
                    predecessors[v] = u;  // Update predecessor
                    pq.push(distances[v], v);
                }
            }
        }

        cout << "Shortest distances from vertex " << startVertex << ":\n";
        
        srand(time(0));
       

        int evertex = (rand() % number) + (total - number);


        G_END = evertex;

      
        
        /*for (int i = 0; i < numVertices - 2; ++i) {
            cout << "To vertex " << i << ": " << distances[i] << " - Path: ";
            printPath(startVertex, i, predecessors);
            cout << endl;
        }*/

        cout << " END VERTEX: " << evertex << endl;

        printPath(startVertex, 395, predecessors);

        createPath(startVertex, evertex, predecessors);



        delete[] distances;
        delete[] predecessors;
        delete[] visited;
    }

    void createPath(int startVertex, int endVertex, int* predecessors)
    {
        if (endVertex == startVertex) {
           // cout << startVertex << " ";
            Node* currnode = gnodes.head;
            while (currnode)
            {
                if (currnode->data == startVertex) break;
                currnode = currnode->next;
            }

            currnode->isshortestpath = true;
            currnode->charact = '#';

            return;
        }

       
        createPath(startVertex, predecessors[endVertex], predecessors);
       // cout << endVertex << " ";
        Node* currnode = gnodes.head;
        while (currnode)
        {
            if (currnode->data == endVertex) break;
            currnode = currnode->next;
        }

        currnode->isshortestpath = true;
        currnode->charact = '#';

    }

    void printPath(int startVertex, int endVertex, int* predecessors) {
        //if (endVertex == startVertex) {
        //  //cout << startVertex << " ";
        //    return;
        //}
        //printPath(startVertex, predecessors[endVertex], predecessors);
        ////cout << endVertex << " ";
    }

    void counttotalpossible(int startVertex) {

        LinkedList* pathnodes = new LinkedList;
        int pathnumber = 0;
        bool* visited = new bool[numVertices]();
        Queue bfsQueue;
        visited[startVertex] = true;
        bfsQueue.enqueue(startVertex);
        while (!bfsQueue.isEmpty()) {

            int currentVertex = bfsQueue.frontnode()->data;
            Node* currnodes = gnodes.head;
            while (currnodes)
            {
                if (currnodes->data == startVertex) break;
                currnodes = currnodes->next;
            }

            if (currnodes)
            {
                if (currnodes->charact == '#' || currnodes->charact == '+' || currnodes->charact == '&')
                {
                    if ( pathnodes->search( currnodes->data) == false ) 
                    {
                        pathnodes->addNode(currnodes->data);
                        pathnumber++;
                    }
                }
            }

            bfsQueue.dequeue();
            for (Node* neighbor = adjacencyList[currentVertex].head; neighbor != nullptr; neighbor = neighbor->next) {
                int neighborVertex = neighbor->data;
                if (!visited[neighborVertex]) {
                    Node* currnode = gnodes.head;
                    while (currnode)
                    {
                        if (currnode->data == neighborVertex) break;
                        currnode = currnode->next;
                    }
                    if (currnode)
                    {
                        if (currnode->charact == '#' || currnode->charact == '+' || currnode->charact == '&')
                        {
                            if (pathnodes->search(currnode->data) == false)
                            {
                                pathnodes->addNode(currnode->data);
                                pathnumber++;
                            }
                        }
                    }

                    visited[neighborVertex] = true;
                    bfsQueue.enqueue(neighborVertex);
                }
            }
        }


    //==========================================CREATING THE RANDOM OBJECT==============================================//
        srand(time(0));

     
       for ( int  j= 0; j < G_number/2; j++)
        {
           int randnumber = (rand() % pathnodes->num - 2) + 1;
            int ran = rand() % 2;

            if (ran == 0)
            {
                int num = pathnodes->iterate(randnumber);
               
               
                obstacles.enqueue('O', num);
            }

            if (ran == 1)
            {
                int num = pathnodes->iterate(randnumber);
               
                obstacles.enqueue('P', num);
            }
            if (ran == 2)
            {
                int num = pathnodes->iterate(randnumber);
                
                obstacles.enqueue('O', num);
            }
        }
        //delete[] visited;
    }

    void updataobstacles(int randnumber, char obstacle)
    {
        Node* pnode = gnodes.head;
        int i = 1;
        while (pnode)
        {
            if (i == randnumber) break;
            pnode = pnode->next;
            i++;
        }
        if ( pnode->charact ) pnode->charact = obstacle;
    }



    void updategraphstatus()
    {
        Node* currnode = gnodes.head;
        while (currnode)
        {
            if (currnode->data == carnode) break;
            currnode = currnode->next;
        }

        if (currnode->charact == 'P')
        {
            SCORE += 5;
            GAMESTATUS = "[POWERUP COLLECTED] 5 SCORES ADDED.";
            currnode->charact = '#';
        }

        else if (currnode->charact == 'O')
        {
            SCORE -= 5;
            GAMESTATUS = "[OBSTACLE HIT] 5 SCORES REMOVED.";
            currnode->charact = '#';

        }


        else if (currnode->data == G_END)
        {
           //
            GAMEENDED = 1;
            lastnode = true;
            GAMESTATUS = "[END] GOOD JOB! GAME HAS ENDED PRESS ANY KEY TO CONTINUE";
           


        }

        else GAMESTATUS = "";


    }



    void automove()
    {

        LinkedList visted;
        

        Node* curr = gnodes.head;
        while (curr)
        {
            if (curr->data == carnode) break;
            curr = curr->next;
        }
        visted.addNode(curr->data);

        bool reachedend = false;
        while( reachedend == false)
        {
            system("cls");
            if (carnode == G_END)
            {
                reachedend = true;
                break;
            }

            curr = gnodes.head;
            while (curr)
            {
                if (curr->data == carnode) break;
                curr = curr->next;
            }


            /*   carnode = carnode - G_number; top
                   carnode = carnode + G_number; below
                   carnode = carnode - 1 left
                   carnode = carnode + 1 right*/

            if (curr->bottom)
            {
                cout << curr->bottom->isshortestpath << " [TESTING BOTTOM]" << endl;
                bool temp = visted.search(curr->bottom->data);
                if (curr->bottom->isshortestpath == true && temp == false)
                {
                    carnode = carnode + G_number;
                    cout << "[MOVED BOTTOM]" << endl;
                    visted.addNode(curr->bottom->data);
                }
            }

            if (curr->left)
            {
                cout << curr->left->isshortestpath << " [TESTING LEFT]" << endl;
                bool temp = visted.search(curr->left->data);
                if (curr->left->isshortestpath == true && temp == false)
                {
                    carnode = carnode - 1;
                    cout << "[MOVED LEFT]" << endl;
                    visted.addNode(curr->left->data);
                }
            }

            if (curr->right)
            {
                cout << curr->right->isshortestpath << " [TESTING RIGHT]" << endl;
                bool temp = visted.search(curr->right->data);
                if (curr->right->isshortestpath == true && temp == false)
                {
                    carnode = carnode + 1;
                    cout << "[MOVED RIGH]T" << endl;
                    visted.addNode(curr->right->data);
                }
            }

            if (curr->top)
            {
                cout << curr->top->isshortestpath << " [TESTING TOP]" << endl;
                bool temp = visted.search(curr->top->data);
                if (curr->top->isshortestpath == true && temp == false)
                {
                    carnode = carnode - G_number;
                    cout << "[MOVED TOP]" << endl;
                    visted.addNode(curr->top->data);
                }
            }


            updategraphstatus();
            

            displaymap(0);
            system("timeout /nobreak /t 1 >nul");
        }

    }
   
   ~Graph() {
      
      
    }
};













void waitForKeypress() {
    while (!_kbhit()) {
        // Wait for a key press
    }
    _getch();  // Clear the keypress from the buffer
}





int main() {


   /* cout << "Enter the dimension of the grid you want: " << endl;
    int number;
   

    int total = number * number;*/

    




    //======================= SELECT DIFFICULTY====================//


    cout << "                                         d88b"<< endl;
cout << "                      _______________|8888|_______________" << endl;
cout << "                     |_____________ ,~~~~~~. _____________|" << endl;
cout << "   _________         |_____________: mmmmmm :_____________|         _________" << endl;
cout << "  / _______ \   ,----|~~~~~~~~~~~,'\ _...._ /`.~~~~~~~~~~~|----,   / _______ "<< endl;
cout<<" | /       \ |  |    |       |____|,d~    ~b.|____|       |    |  | /       \ |" << endl;
cout << " ||         |-------------------\-d.-~~~~~~-.b-/-------------------|         ||" << endl;
cout << " ||         | |8888 ....... _,===~/......... \~===._         8888| |         ||" << endl;
cout << " ||         |=========_,===~~======._.=~~=._.======~~===._=========|         ||" << endl;
cout << " ||         | |888===~~ ...... //,, .`~~~~'. .,\\        ~~===888| |         ||" << endl;
cout << " ||        |===================,P'.::::::::.. `?,===================|        ||" << endl;
cout << " ||        |_________________,P'_::----------.._`?,_________________|        ||" << endl;
cout << " `|        |-------------------~~~~~~~~~~~~~~~~~~-------------------|        |'" << endl;
cout << "   \_______/                  HUZAIFA AND TAMIMS DS PROJECT          \_______/" << endl;
    cout << "||==================================================================||" << endl;
    cout << "||==================================================================||" << endl;
    
    cout << "||                     ENTER THE DIFFICULTY YOU WANT                ||" << endl;
    cout << "||==================================================================||" << endl;
    cout << "||==================================================================||" << endl;

    cout << endl;
    cout << endl;

    int dif;
    cin >> dif;

   int number;
    number = dif * 10;
    Graph graph;
    int total = number * number;
    graph.setup(total + 1);

    G_number = number;
    G_total = total;

    SCORE = total;
    
    
    int x1 = 0; 
    int x2 = 0;
    for (int i = 0; i < total; i++)
    {
       
        if (i < number)
        {
            //RIGHT MOST NODE FORMULA =; i mod number == number - 1;

            if (i == 0)     //left most node
            {
                graph.addEdge(i, i + 1, 'r');
                graph.addEdge(i, i + number, 'b');
            }
            else if (i % number == number - 1)
            {
                graph.addEdge(i, i - 1, 'l');
                graph.addEdge(i, i + number, 'b');
            }
            else
            {
                graph.addEdge(i, i + number, 'b');
                graph.addEdge(i, i + 1, 'r');
                graph.addEdge(i, i - 1, 'l');
            }
        }

        else 
        {
            if (i % number == 0)
            {
               
                graph.addEdge(i, i + 1, 'r');
                if (i < total - number)  graph.addEdge(i, i + number, 'b');


                graph.addEdge(i, i - number, 't');
            }

            else if (i % number == number - 1)
            {
               
                graph.addEdge(i, i - 1, ' l');
         
                if ( i < total - 1) graph.addEdge(i, i + number, 'b');
                graph.addEdge(i, i - number, 't');
            }
            else
            {
               
                  

                if ( i < total - number )  graph.addEdge(i, i + number, 'b');
                graph.addEdge(i, i + 1, 'r');
                graph.addEdge(i, i - 1, 'l');
                graph.addEdge(i, i - number, 't');
            }
        }
        
    }



  /*  graph.addEdge(0, 1, 'b');
    graph.addEdge(1, 2, 'r');
    graph.addEdge(2, 3, 'r');
    graph.addEdge(3, 4, 't');
    graph.addEdge(4, 5, 'r');
    graph.addEdge(5, 6, 'r');
    graph.addEdge(6, 7, 'b');*/
    

    //GENERATION OF GAME MAP KE LIE YE FUNCTIONS
    graph.BFS(0);   //SETS THE LEVEL
    graph.addspacing(0);    //SPACES MEI EMPTY NODES DALNE KE LIE
    //graph.printnodesonly();     //TESTING KE LIE NODES KI INFO
    srand(time(0));
    int randomstartnode = rand() % total;
    cout << "RANDOM START NODE IS: " << randomstartnode << endl;
    graph.DFS(randomstartnode);
    graph.displaymap(0);       //FOR LOOP SE PRINT KRANAY KE LIE
    int svertes = rand() % number;
    carnode = svertes;
    G_START = svertes;
    graph.dijkstra(svertes, total, number, total);
    
    graph.updateturns(0);
    graph.counttotalpossible(1);
    graph.displaymap(0);






    //=========================================GAMEPLAY===================================================//
   
    //TAMIM MAKE THIS MENU MORE AESTHETIC ALSO TRY TO ADD SOUNDS AND STUFF
    
    cout << "GAME GENERATED." << endl;

    cout << "||---------------------------------------||" << endl;
    cout << "               1. START GAME" << endl;

    //EDIT LAST

    cout << "               2. AUTOMATIC MOVE" << endl;
    cout << "               3. EXIT" << endl;
    cout << "||---------------------------------------||" << endl;

    gamestarted = true;

    int choice;
    cin >> choice;
    int exit = 0;
    int update = 0;
    if (choice == 1)
    {
        while( lastnode == false)
        {
            if (GAMEENDED == 1) 
            {
                system("cls");
                break;
            }


            


            //cout << "\n\n\n\n\n\n\n";
            system("cls");
            graph.updategraphstatus();

            cout << "GAME LEGEND: " << endl;
            cout << ". Moveable Path" << endl;
            cout << "$ Shortest possible path." << endl << endl << endl;
            gamestarted = true;
            graph.displaymap(0);
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "MOVE LEFT: D" << endl;
            cout << "MOVE RIGHT: A" << endl;
            cout << "MOVE ABOVE: W" << endl;
            cout << "MOVE DOWN: D" << endl;
            cout << "Show shortest path: P" << endl;
            cout << endl << GAMESTATUS << endl;
           
            cout << "\n\n\n";
            
            cout << "SCORE: " << SCORE << endl;

            
                cout << "                     __" << endl;
                cout << "               _.--""  |" << endl;
                cout << ".----.     _.-'   |/\| |.--." << endl;
                cout << "|HUZAIFA|__.-'   _________|  |_)  _______________  " << endl;
                cout << "|  .-```-.```` ___,    `----'`))   __   .-``-.````--._  " << endl;
                cout << "'-' ,--. `    |TAM|   .---.       |:.| ' ,--. `      _`." << endl;
                cout << " ( (    ) ) __|MIM|__ \\|// _..--  \/ ( (    ) )--._.-." << endl;
                cout << "  . `--' ;\__________________..--------. `--' ;--------'" << endl;
                cout << "   `-..-'                               `-..-'" << endl;

            


            //==============VALIDATE MOVEMENTS==============//
            char key;

            waitForKeypress();
            if (_kbhit()) {
                key = _getch();

                switch (key) {
                case 72: // Up arrow key
                    graph.validatemovement(0);
                    break;
                case 80: // Down arrow key
                    graph.validatemovement(1);
                    break;
                case 75: // Left arrow key
                    graph.validatemovement(3);
                    break;
                case 77: // Right arrow key
                    graph.validatemovement(2);
                    break;
               
                case 'p':
                    displayshortestpath = !displayshortestpath;
                    
                    break;

                case 'o':
                    displayshortestpath = true;
                    break;
                default:
                    cout << "";
                  
                }
            }

         

          
        }

        /* char movement_option;
           cin >> movement_option;
           if (movement_option == 'w')
           {
               graph.validatemovement(0);
           }
           if (movement_option == 'a')
           {
               graph.validatemovement(3);
           }
           if (movement_option == 's')
           {
               graph.validatemovement(1);
           }
           if (movement_option == 'd')
           {
               graph.validatemovement(2);
           }

           if (movement_option == 'p')
           {
               displayshortestpath = !displayshortestpath;
           }*/



        //==============================================WHEN GAME ENDS============================================================//

        system("cls");
        cout << "||======================================================||" << endl;
        cout << "||=====================GAME HAS ENDED===================||" << endl;
        cout << "||======================================================||" << endl;

        cout << endl;
        cout << "Your score: " << SCORE << endl;

        cout << endl << "LEADERBOARD:" << endl;


        ///TAMIM DISPLAY LEADERBOARD HERE


        //========================================================================================================================/


    }

    if (choice == 2)
    {
       
        graph.automove();


    }
    //====================================================================================================//



    
    return 0;
}



