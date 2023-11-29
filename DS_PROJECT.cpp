#include <iostream>
using namespace std;


//======================================================DEFAULT NODE BLOCK=========================================//
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
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

public:
    Graph(int vertices) : numVertices(vertices) {
        adjacencyList = new LinkedList[numVertices];
    }

    void addEdge(int source, int destination) {
        adjacencyList[source].addNode(destination);
        adjacencyList[destination].addNode(source); // For an undirected graph
    }

   
    void BFS(int startVertex) {
        bool* visited = new bool[numVertices]();

      
       Queue bfsQueue;
        visited[startVertex] = true;
        bfsQueue.enqueue(startVertex);

       cout << "Breadth-First Search starting from vertex " << startVertex << ": ";

        while (!bfsQueue.isEmpty()) {
           
            int currentVertex = bfsQueue.frontnode()->data;
            std::cout << currentVertex << " ";

            bfsQueue.dequeue();
            for (Node* neighbor = adjacencyList[currentVertex].head; neighbor != nullptr; neighbor = neighbor->next) {
                int neighborVertex = neighbor->data;
                if (!visited[neighborVertex]) {
                    visited[neighborVertex] = true;
                    bfsQueue.enqueue(neighborVertex);
                }
            }
        }

        delete[] visited;
        std::cout << std::endl;
    }

   
    ~Graph() {
        delete[] adjacencyList;
    }
};

int main() {
    Graph graph(4);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.BFS(0);
    return 0;
}



