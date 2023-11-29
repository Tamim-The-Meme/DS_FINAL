#include <iostream>

// Node structure for the linked list representation of the queue
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Queue class
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Method to check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Method to enqueue a new element
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

    // Method to dequeue an element
    int dequeue() {
        if (isEmpty()) {
            std::cerr << "Error: Queue is empty." << std::endl;
            return -1; // Assuming -1 as an invalid value for demonstration purposes
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

    // Destructor to free allocated memory
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// Class to represent a graph using adjacency list
class Graph {
private:
    int numVertices;
    Node** adjacencyList;
    int** adjacencyMatrix;

public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int vertices) : numVertices(vertices) {
        adjacencyList = new Node * [numVertices]();
        adjacencyMatrix = new int* [numVertices]();

        for (int i = 0; i < numVertices; ++i) {
            adjacencyList[i] = nullptr;
            adjacencyMatrix[i] = new int[numVertices]();
        }
    }

    // Method to add an edge to the graph
    void addEdge(int source, int destination) {
        // Adding to adjacency list (linked list)
        Node* newNode = new Node(destination);
        newNode->next = adjacencyList[source];
        adjacencyList[source] = newNode;

       
        adjacencyMatrix[source][destination] = 1;
    }

    // Method to perform Breadth-First Search
    void BFS(int startVertex) {
        // Array to keep track of visited vertices
        bool* visited = new bool[numVertices]();

        // Create a queue for BFS
        Queue bfsQueue;

        // Mark the current node as visited and enqueue it
        visited[startVertex] = true;
        bfsQueue.enqueue(startVertex);

        std::cout << "Breadth-First Search starting from vertex " << startVertex << ": ";

        while (!bfsQueue.isEmpty()) {
            // Dequeue a vertex from the queue and print it
            int currentVertex = bfsQueue.dequeue();
            std::cout << currentVertex << " ";

            // Enqueue all adjacent vertices of the dequeued vertex that are not yet visited
            for (Node* neighbor = adjacencyList[currentVertex]; neighbor != nullptr; neighbor = neighbor->next) {
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

    // Destructor to free allocated memory
    ~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] adjacencyMatrix[i];
            Node* current = adjacencyList[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] adjacencyMatrix;
        delete[] adjacencyList;
    }
};

int main() {
    // Creating a graph with 4 vertices
    Graph graph(4);

    // Adding edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 3);

    // Perform BFS starting from vertex 2
    graph.BFS(2);

    return 0;
}
