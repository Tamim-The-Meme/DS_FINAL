#include <iostream>
using namespace std;


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

    Node(int value) : data(value), next(nullptr) {
        charact = '.';
        level = 0;
        top = bottom = left = right = nullptr;

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

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};





//====================================================SIMPLE ARRAY WALI LINKED LIST==========================================================//




class LinkedList {
private:
 
public:
    Node* head;
    LinkedList() : head(nullptr) {}
    void addNode(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
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

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
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
    Graph(int vertices) : numVertices(vertices) {
        adjacencyList = new LinkedList[numVertices];
        for (int i = 0 ; i < numVertices ;i++)
        {
            gnodes.addNode(i);
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

        delete[] visited;
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

        delete[] visited;
        cout << std::endl;
    }






    void displaymap(int startVertex)
    {

       

        for (int i = 0; i < numVertices; i++)
        {
            Node* currnode = gnodes.head;
            while (currnode)
            {
                if (currnode->right->data == -1 && currnode->level == i) cout << " ";
                if( currnode->level == i ) cout << currnode->data;
               
                currnode = currnode->next;
            }

            cout << endl;
        }


    }








   
    ~Graph() {
        delete[] adjacencyList;
    }
};

int main() {
    Graph graph(8);
    graph.addEdge(0, 1, 'b');
    graph.addEdge(1, 2, 'r');
    graph.addEdge(2, 3, 'r');
    graph.addEdge(3, 4, 't');
    graph.addEdge(4, 5, 'r');
    graph.addEdge(5, 6, 'r');
    graph.addEdge(6, 7, 'b');
    
    graph.BFS(0);
  

    graph.addspacing(0);
    graph.printnodesonly();

    graph.displaymap(0);
    return 0;
}



