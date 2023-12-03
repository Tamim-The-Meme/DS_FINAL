#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;








//=====================================================GLOBAL VARIABLES===================================================//
int carnode = 0;
bool gamestarted = false;
bool displayshortestpath = false;
int G_number;
int G_total;
int G_START;
int G_END;
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

    Node(int value) : data(value), next(nullptr) {
        charact = '_';
        level = 0;
        top = bottom = left = right = nullptr;
        weight = 1;

    }
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

  
};


//===================================================GRAPH DATA STRUCTURE=============================================================//



class Graph {
private:
    int numVertices;
    LinkedList* adjacencyList;
    LinkedList gnodes;

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
            if (currnode->top)
            {
                if (currnode->top->charact == '#' || currnode->top->charact == '&')
                {
                    carnode = carnode - G_number;
                    cout << "[TESTING] MOVE A" << endl;
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
                if (currnode->bottom->charact == '#' || currnode->bottom->charact == '&')
                {
                    carnode = carnode + G_number;
                    cout << "[TESTING] MOVE D" << endl;
                    return true;
                }
                else 
                {
                    cout << " [TESTING] THERE IS NO PATH." << endl;
                    cout << "currnodes bottom is: " << currnode->bottom << " characted: " << currnode->bottom->charact << endl;
                    return false;
                }
            }
            else 
            {
                cout << " [TESTING] THERE IS NO BOTTOM." << endl;
                return false;
            }
        }

        if (move == 2)  //left
        {
            if (currnode->left)
            {
                if (currnode->left->charact == '#' || currnode->left->charact == '&')
                {
                    carnode = carnode - 1;
                    cout << "[TESTING] MOVE DL" << endl;
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
                if (currnode->right->charact == '#' || currnode->right->charact == '&')
                {
                    carnode = carnode + 1;
                    cout << "[TESTING] MOVE RIGHT" << endl;
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






    void displaymap(int startVertex)
    {

        cout << "FUNCTIONS TARTED WITH TOTAL VERTICES: " << numVertices << endl;
        int skip = 0;

        for (int i = 0; i < sqrt(numVertices); i++)
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
                            else if (currnode->charact == '&' && displayshortestpath == true) cout << '$';
                            else if (currnode->charact == '&' && displayshortestpath == false) cout << '.';
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

           cout << endl;
        }

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
                        if ( currnode->next) currnode->next->charact = '#';
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

            currnode->charact = '&';

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

        currnode->charact = '&';

    }

    void printPath(int startVertex, int endVertex, int* predecessors) {
        if (endVertex == startVertex) {
          //cout << startVertex << " ";
            return;
        }
        printPath(startVertex, predecessors[endVertex], predecessors);
        //cout << endVertex << " ";
    }




   
   ~Graph() {
       cout << "NOTHING DELETED FUCK U" << endl;
      
    }
};

int main() {


   /* cout << "Enter the dimension of the grid you want: " << endl;
    int number;
   

    int total = number * number;*/
    int number;
    cin >> number;
    Graph graph;
    int total = number * number;
    graph.setup(total + 1);

    G_number = number;
    G_total = total;

    
    
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
    graph.displaymap(0);





    //=========================================GAMEPLAY===================================================//
    cout << "GAME GENERATED." << endl;

    cout << "||---------------------------------------||" << endl;
    cout << "               1. START GAME" << endl;
    cout << "               2. EXIT" << endl;
    cout << "||---------------------------------------||" << endl;

    int choice;
    cin >> choice;
    int exit = 0;
    if (choice == 1)
    {
        while( exit == 0)
        {
            //cout << "\n\n\n\n\n\n\n";
            system("cls");

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
            
            char movement_option;
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
            }


        }

    }
    //====================================================================================================//


    
    return 0;
}



