#include <iostream>
#include <climits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Edge {
    int data;
    int weight;
    Edge* next;
};

struct Node {
    int data;
    Edge* head;
    Node* next;
    int days;
    bool visited;
    int predecessor;
};

Node* head = NULL;
Node* tail = NULL;
Node* lstVertices[50];

string vertexNames[] = {
    "Mystic Cavern", "Whispering Falls", "Enchanted Grove", "Serenity Summit", "Emerald Oasis",
    "Luminous Lagoon", "Tranquil Vale", "Hidden Haven", "Velvet Vista", "Secret Spire",
    "Ethereal Echo", "Celestial Citadel", "Blissful Bluff", "Harmony Highlands", "Starlight Sanctuary",
    "Radiant Ravine", "Fantasy Foothills", "Pinnacle Paradise", "Dreamy Dell", "Twilight Terrace",
    "Mystic Grotto", "Whispering Cascade", "Enchanted Glade", "Serene Peak", "Emerald Oasis",
    "Lustrous Lagoon", "Tranquil Meadow", "Secret Retreat", "Velvet Overlook", "Hidden Spire",
    "Ethereal Resonance", "Celestial Stronghold", "Blissful Plateau", "Harmony Plateau", "Starlit Grove",
    "Radiant Canyon", "Fantasy Plateau", "Pinnacle Valley", "Dreamy Hollow", "Twilight Plateau",
    "Moonlit Valley", "Dazzling Dale", "Silver Stream", "Ivory Isle", "Crimson Crest", "Sapphire Springs",
    "Golden Gaze", "Vibrant Vista", "Misty Mirage", "Azure Abyss"
};

void insertVertex(int data) {
    Node* temp = new Node;
    temp->data = data;
    temp->next = NULL;
    temp->head = NULL;
    temp->days = INT_MAX;
    temp->visited = false;
    temp->predecessor = -1;

    if (head == NULL) {
        head = tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }

    lstVertices[data - 1] = temp;
}

void addEdge(int vname, int uname, int weight) {
    Node* vtemp = lstVertices[vname - 1];
    Node* utemp = lstVertices[uname - 1];

    if (vname < 1 || vname > 50 || uname < 1 || uname > 50) {
        cout << "Invalid vertices in edge" << endl;
        return;
    }

    if (lstVertices[vname - 1] == NULL || lstVertices[uname - 1] == NULL) {
        cout << "Vertices not yet inserted" << endl;
        return;
    }

    Edge* etemp = new Edge;
    etemp->data = uname;
    etemp->weight = weight;
    etemp->next = NULL;

    if (vtemp->head == NULL) {
        vtemp->head = etemp;
    } else {
        Edge* lastEdge = vtemp->head;
        while (lastEdge->next != NULL) {
            lastEdge = lastEdge->next;
        }
        lastEdge->next = etemp;
    }
}

void enqueue(int item, int queue[], int& front, int& rear) {
    if (rear == 50) {
        cout << "Queue is full";
    } else {
    	if(lstVertices[item-1]->visited==true){
    		return;
		}
        int i = rear;
        while (i >= front && item < queue[i]) {
            queue[i + 1] = queue[i];
            i--;
        }
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = item;
    }
}


int dequeue(int queue[], int& front, int& rear) {
    int item = queue[front];
    if (front == rear) {
        front = rear = -1;
    } else {
        front++;
    }
    return item;
}

void displayGraph() {
    cout << "Graph Structure:" << endl;
    for (int i = 0; i < 50; ++i) {
        Node* temp = lstVertices[i];
        cout << vertexNames[i] << " -> ";
        Edge* etem = temp->head;
        if (etem == NULL) {
            cout << "NULL";
        } else {
            while (etem != NULL) {
                cout << vertexNames[etem->data - 1] << "(";
                if (etem->weight == INT_MAX) {
                    cout << "Infinity) ";
                } else {
                    cout << etem->weight << ") ";
                }
                etem = etem->next;
                if (etem != NULL) {
                    cout << "-> ";
                }
            }
        }
        cout << endl;
    }
}

bool isQueueEmpty(int front) {
    return front == -1;
}

void dijkstra(int startVertex, int endVertex, int numVertices) {
	for (int i = 0; i < numVertices; ++i) {
    lstVertices[i]->visited = false;
    lstVertices[i]->predecessor = -1;
    }

    int days[50];
    for (int i = 0; i < numVertices; i++) {
        days[i] = INT_MAX;
    }
    days[startVertex - 1] = 0;

    int queue[50];
    int front = -1;
    int rear = -1;

    enqueue(startVertex, queue, front, rear);

    while (!isQueueEmpty(front)) {
        int currentVertex = dequeue(queue, front, rear);
		lstVertices[currentVertex - 1]->visited = true;
        for (Edge* e = lstVertices[currentVertex - 1]->head; e != NULL; e = e->next) {
            int neighbor = e->data - 1;
            int day = days[currentVertex - 1] + e->weight;
            if (day < days[neighbor]) {
                days[neighbor] = day;
                
                enqueue(neighbor + 1, queue, front, rear);
                lstVertices[neighbor]->predecessor = currentVertex - 1;
            }
        }
    }

    vector<string> path;
    int current = endVertex - 1;
    while (current != -1) {
        path.push_back(vertexNames[current]);
        current = lstVertices[current]->predecessor;
    }

    cout << "Shortest path from " << vertexNames[startVertex - 1] << " to " << vertexNames[endVertex - 1] << ": ";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i != 0) cout << " -> ";
    }
    cout << endl;

    if (days[endVertex - 1] == INT_MAX) {
		cout << "Path to the destination is blocked from here on! " << endl;
	}
     else {
        cout << "Shortest days: " << days[endVertex - 1] << endl;
    }
}

void printMenu() {
    cout << "\n**************Mystic Odyssey******************" << endl;
    cout << "**************************************************" << endl;
    cout << "1. Display Graph" << endl;
    cout << "2. Find Shortest Path" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    for (int i = 0; i < 50; ++i) {
        insertVertex(i + 1);
    }

    ifstream fin;
    fin.open("pathedges.csv");
    if (!fin.is_open()) {
        cout << "File not found" << endl;
        return -1;
    }

    string line;
    int vertex1, vertex2, DAYSS;

    while (getline(fin, line)) {
        stringstream data_row(line);
        string vertex1_str, vertex2_str, DAYSS_str;

        getline(data_row, vertex1_str, ',');
        getline(data_row, vertex2_str, ',');
        getline(data_row, DAYSS_str, ',');

        
        stringstream(vertex1_str) >> vertex1;
		stringstream(vertex2_str) >> vertex2;
		stringstream(DAYSS_str) >> DAYSS;


        addEdge(vertex1, vertex2, DAYSS);
    }

    fin.close();

    int choice;
    do {
        printMenu();
        cin >> choice;
        cout << "_______________________________________________________________________" << endl;

        switch (choice) {
            case 1:
                displayGraph();
                break;
            case 2: {
                cout << "\nLocations:\n";
                for (int i = 0; i < 50; ++i) {
                    cout << i + 1 << " : " << vertexNames[i] << endl;
                }
                int initialNode, goalNode;
                cout << "Enter the initial node (1-50): ";
                cin >> initialNode;

                if (initialNode < 1 || initialNode > 50) {
                    cout << "Invalid initial node. Please try again.\n";
                    continue;
                }

                cout << "Enter the goal node (1-50): ";
                cin >> goalNode;

                if (goalNode < 1 || goalNode > 50) {
                    cout << "Invalid goal node. Please try again.\n";
                    continue;
                }

                dijkstra(initialNode, goalNode, 50);
                break;
            }
            case 3:
                cout << "\nExiting... Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}

