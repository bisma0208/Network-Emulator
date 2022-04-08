#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <cmath>
#include <time.h>
#include <iomanip>
#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using namespace std::chrono_literals;
using namespace std;

template <typename t>
struct LNode
{
	t data;
	LNode* next;

	LNode()
	{
		next = NULL;
	}
};

template<typename t>
class LinkedList
{
	LNode<t>* head;

public:
	LinkedList()
	{
		head = NULL;
	}

	bool is_Empty()
	{
		return head == NULL;
	}

	void insert(t d1)
	{
		if (is_Empty())
		{
			head = new LNode<t>;
			head->data = d1;

		}
		else
		{
			LNode<t>* temp = head;
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = new LNode<t>;
			temp->next->data = d1;
		}
	}

	LNode<t>& searchNode(t d1)
	{
		LNode<t>* temp = head;
		while (temp->next && temp->next->data != d1)
		{
			temp = temp->next;
		}
		return temp->next;
	}

	t getNodeatIdx(int index)
	{
		LNode<t>* temp = head;

		while (temp && index)
		{
			temp = temp->next;
			index--;
		}

		return temp->data;
	}


	void deleteNode(t d1)
	{
		if (is_Empty())
			return;

		if (head->data == d1)
		{
			LNode<t>* temp = head;
			head = head->next;
			delete temp;
			return;
		}

		LNode<t>* temp = head;
		while (temp->next && temp->next->data != d1)
		{
			temp = temp->next;
		}

		LNode<t>* delnode = temp->next;
		temp->next = temp->next->next;
		delete delnode;
	}

	void display()
	{
		LNode<t>* temp = head;
		while (temp)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	~LinkedList() {
		LNode<t>* trav;
		while (!is_Empty()) {
			trav = head;
			head = head->next;
			delete trav;
			trav = NULL;
		}
	}

};

template<typename t>
class Stack
{
	LNode<t>* top;

public:
	Stack()
	{
		top = NULL;
	}

	bool isEmpty() { return top == NULL; }

	void push(t data)
	{
		if (top == NULL)
		{
			top = new LNode<t>;
			top->data = data;
		}
		else
		{
			LNode<t>* new_top = new LNode<t>;
			new_top->data = data;
			new_top->next = top;
			top = new_top;
		}
	}

	t pop()
	{
		if (top != NULL)
		{
			LNode<t>* temp = top;
			top = top->next;
			t data = temp->data;
			delete temp;
			return data;
		}
	}
};

template<typename t>
struct Queue
{
	LNode<t>* front;
	LNode<t>* rear;
	Queue() {
		front = rear = NULL;
	}
	bool is_Empty() { return front == NULL; }
	void Enqueue(t d1) {
		if (is_Empty()) {
			front = new LNode<t>;
			front->data = d1;
			rear = front;
		}
		else if (front->next == NULL)
		{
			front->next = new LNode<t>;
			rear = front->next;
			rear->data = d1;
		}
		else
		{
			rear->next = new LNode<t>;
			rear = rear->next;
			rear->data = d1;
		}
	}

	t dequeue() {
		if (!is_Empty()) {
			LNode<t>* temp = front;
			front = front->next;
			t temp_data = temp->data;
			delete temp;
			return temp_data;
		}
		else
		{
			//return NULL;
		}
	}

	void display()
	{
		LNode<t>* temp = front;
		while (temp)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	~Queue()
	{
		while (!is_Empty())
			dequeue();
	}
};

struct MSG
{
	string ID;
	string Priority;
	string Payload;
	string src;
	string dest;
	string Trace;

	MSG()
	{
		Priority = Payload = src = dest = Trace = ID = "";
	}

	MSG(string msg)
	{
		int idx = 0;
		Priority = Payload = src = dest = Trace = ID = "";

		while (msg[idx] != ',')
		{
			ID += msg[idx];
			idx++;
		}
		idx++;
		while (msg[idx] != ',')
		{
			Priority += msg[idx];
			idx++;
		}
		idx++;
		while (msg[idx] != ',')
		{
			src += msg[idx];
			idx++;
		}
		idx++;
		while (msg[idx] != ',')
		{
			dest += msg[idx];
			idx++;
		}
		idx++;
		while (msg[idx] != ',')
		{
			Payload += msg[idx];
			idx++;
		}
		idx++;
		while (msg[idx] != '\0')
		{
			Trace += msg[idx];
			idx++;
		}
	}

	string stringfy()
	{
		string to_ret = "";

		to_ret += ID;
		to_ret += ',' + Priority;
		to_ret += ',' + src;
		to_ret += ',' + dest;
		to_ret += ',' + Payload;
		to_ret += ',' + Trace;

		return to_ret;
	}

	void addTrace(string router)
	{
		if (Trace != "")
			Trace += "->";
		Trace += router;
	}
};
struct binary_heap {
	MSG* arr;
	int size;//size of array
	int counter;

	binary_heap(int x) {
		arr = new MSG[x];
		size = x;
		counter = 1;
	}

	bool is_Full() { return counter == size; }

	int parent(int i) { return (i) / 2; }

	int left(int i) { return (2 * i); }

	int right(int i) { return (2 * i + 1); }

	void insert(MSG msg) {
		if (!is_Full())
		{
			arr[counter] = msg;
			if (counter == 1)
			{
				counter++;
			}
			else
			{
				int counter_parent = parent(counter);
				int i = counter;

				while (i != 1 && arr[(parent(i))].Priority < arr[i].Priority)
				{
					MSG temp = arr[i];
					arr[i] = arr[(parent(i))];
					arr[(parent(i))] = temp;
					i = parent(i);
				}
				counter++;
			}
		}
		else
		{
			cout << "THE HEAP IS FULL\n";
		}
	}

	void display()
	{
		for (int i = 1; i < counter; i++)
		{
			cout << arr[i].stringfy() << " ";
		}
		cout << endl;
	}
};


struct AdjLst
{
	int weight;				// holds the weight of the edge
	string nodeId;
	AdjLst* next;			// next element in the adjacent list

	AdjLst()
	{
		weight = 0;
		nodeId = "";
		next = NULL;
	}

	AdjLst(int weight, string nodeId)
	{
		next = NULL;
		this->weight = weight;
		this->nodeId = nodeId;
	}
};


struct GraphNode
{
	string nodeId;
	GraphNode* next;		// this will point to the next node
	AdjLst* adjList;		// this will point towards the nodes which are adjacent to the current node
	int n_neighbours;

	GraphNode()
	{
		nodeId = "";
		next = NULL;
		adjList = NULL;
		n_neighbours = 0;
	}

	GraphNode(string nodeId)
	{
		this->nodeId = nodeId;
		next = NULL;
		adjList = NULL;
		n_neighbours = 0;
	}
};
class Graph
{
	GraphNode* start;			// this will store the starting node of the Graph

public:
	Graph()
	{
		start = NULL;
	}

	bool insertNode(string nodeId)
	{
		if (start == NULL)
		{
			start = new GraphNode(nodeId);
			return true;
		}
		else
		{
			GraphNode* temp = start;

			while (temp->next != NULL)
			{
				temp = temp->next;

				if (temp)
				{
					// check for the same IDs
					if (temp->nodeId == nodeId)
					{
						cout << "ERROR: GIVEN ID IS ALREADY IN USE\n";
						return false;
					}
				}
			}

			temp->next = new GraphNode(nodeId);
			return true;
		}
	}

	bool isValidNode(string nodeId)
	{
		GraphNode* temp = start;

		while (temp != NULL)
		{
			if (temp->nodeId == nodeId)
			{
				return true;
			}

			temp = temp->next;
		}

		return false;
	}

	int getNodeIndex(string nodeID)
	{
		GraphNode* temp = start;

		int idx = 0;

		while (temp != NULL)
		{
			if (temp->nodeId == nodeID)
			{
				return idx;
			}
			temp = temp->next;
			idx++;
		}

		return -1;		// -1 means that the node is not in the graph
	}

	int** getAdjacencyMatrix()
	{
		int v = getnumNode();
		// make a num_node * num_nodes matrix
		int** m = new int* [v];

		for (int i = 0; i < v; i++) 
		{
			m[i] = new int[v];
		}

		// initialize all the vertices with -1 which shows no edge
		for (int i = 0; i < v; i++)
		{
			for (int j = 0; j < v; j++)
			{
				m[i][j] = 0;
			}
		}

		// now traverse over the whole array and add the number of nodes
		GraphNode* temp = start;

		int idx = 0;
		while (temp)
		{
			AdjLst* trav = temp->adjList;

			while (trav != NULL)
			{
				int yidx = getNodeIndex(trav->nodeId);
				m[idx][yidx] = trav->weight;
				trav = trav->next;
			}

			temp = temp->next;
			idx++;
		}

		return m;
	}

	bool insertEdge(string nodeId1, int weight, string nodeId2)
	{
		if (isValidNode(nodeId1) && isValidNode(nodeId2) && nodeId1 != nodeId2)
		{
			// find nodeId1 and add it to the adjacency list of nodeId1

			GraphNode* temp = start;

			while (temp->nodeId != nodeId1)
			{
				temp = temp->next;
			}
			temp->n_neighbours++;

			AdjLst* trav = temp->adjList;

			if (trav == NULL)
			{
				temp->adjList = new AdjLst(weight, nodeId2);
			}
			else
			{
				while (trav->next != NULL)
					trav = trav->next;

				trav->next = new AdjLst(weight, nodeId2);
			}
			return true;
		}
		else
		{
			cout << "ERROR: INVALID EDGE\n";
			return false;
		}
	}
	void printGraph()
	{
		GraphNode* temp = start;
		while (temp != NULL)
		{
			cout << temp->nodeId << "->";
			AdjLst* trav = temp->adjList;
			while (trav != NULL)
			{
				cout << trav->nodeId << "(" << trav->weight << ")";
				trav = trav->next;

				if (trav)
					cout << ",";
			}

			temp = temp->next;
			cout << endl;
		}
		cout << endl;
	}
	string getNodeIdAt(int index)
	{
		GraphNode* temp = start;

		for (int i = 0; i < index && temp; i++)
			temp = temp->next;

		if (temp == NULL)
			return "";
		else
			return temp->nodeId;
	}

	int minDistance(int dist[], bool sptSet[])
	{
		int min = INT_MAX, min_index = 0;
		int vertices = getnumNode();

		for (int v = 0; v < vertices; v++)
			if (sptSet[v] == false && dist[v] <= min)
				min = dist[v], min_index = v;

		return min_index;
	}

	// returns parent list for the current node shortest path.
	string* dijkstra(string nodeID)
	{
		int src = getNodeIndex(nodeID);

		int** matrix = getAdjacencyMatrix();

		// three parallel arrays to store the nodeID, its parent and total distance from the source
		int numNodes = getnumNode();
		int* dist = new int[numNodes];
		string* parent = new string[numNodes];

		bool* sptSet = new bool[numNodes];

		for (int i = 0; i < numNodes; i++)
		{
			dist[i] = INT_MAX;
			sptSet[i] = false;
		}

		// Distance of source vertex from itself is always 0
		dist[src] = 0;

		// Find shortest path for all vertices
		for (int count = 0; count < numNodes - 1; count++) 
		{
			int u = minDistance(dist, sptSet);

			sptSet[u] = true;

			for (int v = 0; v < numNodes; v++)
			{
				if (!sptSet[v] && matrix[u][v] && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v])
				{
					dist[v] = dist[u] + matrix[u][v];
					parent[v] = getNodeIdAt(u);
				}
			}
		}

		// delete the array allocated for the graph adjacency matrix
		for (int i = 0; i < numNodes; i++)
			delete[] matrix[i];

		delete[] matrix;

		return parent;
	}

	// gets the immediate next node for a specific vertix in the shortest path
	string recursive_nextNode(string arr[], string nodeID, int index, string startNode)
	{
		if (arr[index] == startNode)
			return nodeID;
		else
			return recursive_nextNode(arr, arr[index], getNodeIndex(arr[index]), startNode);
	}

	void printPath(string arr[], string nodeID, string startNode)
	{
		string par = nodeID;
		Stack<string> st;
		while (par != "")
		{
			st.push(par);
			par = arr[getNodeIndex(par)];
		}
		cout << "\n\tSHORTEST PATH FOUND: ";
		while (!st.isEmpty())
		{
			cout << st.pop();
			if (!st.isEmpty())
				cout << "->";
		}
	}

	void printpath(string src, string dest)
	{
		string* parent = dijkstra(src);

		if (dest != "*")
		{
			printPath(parent, dest, src);
			cout << endl;
		}
		else
		{
			GraphNode* gn = start;
			while (gn)
			{
				if (gn->nodeId != src)
				{
					printPath(parent, gn->nodeId, src);
					cout << endl;
				}
				gn = gn->next;
			}
		}
	}
	void createRoutingTable(string nodeID)
	{

		string name_file = "rt_";
		name_file += nodeID;
		name_file += ".txt";

		ofstream file;
		file.open(name_file);

		string* parent = dijkstra(nodeID);
		int numNodes = getnumNode();

		// now get the most adjacent nodes by the recursive function
		for (int i = 0; i < numNodes; i++)
		{
			if (parent[i] == "")
			{
				//file << getNodeIdAt(i) << "," << endl;
				continue;
			}

			string next_node;

			if (parent[i] != nodeID)
				next_node = recursive_nextNode(parent, parent[i], getNodeIndex(parent[i]), nodeID);
			else
				next_node = getNodeIdAt(i);

			file << getNodeIdAt(i) << "," << next_node << endl;
		}

		file.close();
	}

	void deletegraph()
	{
		start = NULL;
	}

	void completeRoutingTable()
	{
		int nodes = getnumNode();

		for (int i = 0; i < nodes; i++)
		{
			createRoutingTable(getNodeIdAt(i));
		}
	}

	int getnumNode()
	{
		GraphNode* temp = start;
		int n_nodes = 0;
		while (temp != NULL)
		{
			temp = temp->next;
			n_nodes++;
		}
		return n_nodes;
	}

	// gives the weight between two nodes
	int getEdgeWeight(string src, string dest)
	{
		GraphNode* temp = start;

		// first fetch the graph node of the source
		while (temp && temp->nodeId != src)
		{
			temp = temp->next;
		}

		AdjLst* trav = temp->adjList;


		// now fetch the destination node and return the value of its edge
		while (trav && trav->nodeId != dest)
		{
			trav = trav->next;
		}

		if (trav)
			return trav->weight;

		return 0;		// means no such node exists
	}
	void changeEdgeWeight(string src, string dest, int weight)
	{
		GraphNode* temp = start;

		// first fetch the graph node of the source
		while (temp && temp->nodeId != src)
		{
			temp = temp->next;
		}

		AdjLst* trav = temp->adjList;

		if (!trav)
		{
			temp->adjList = new AdjLst(weight, dest);
		}

		if (trav->nodeId == dest)
		{
			trav->weight = weight;
			return;
		}

		// now fetch the destination node and return the value of its edge
		while (trav->next && trav->next->nodeId != dest)
		{
			trav = trav->next;
		}

		if (trav)
			trav->next->weight = weight;
		else
		{
			trav->next = new AdjLst(weight, dest);
		}
		//now we also create a complete routing table according to it
		completeRoutingTable();
	}

	// return a linked list of nodes
	LinkedList<string>* getNodes()
	{
		LinkedList<string>* nodes = new LinkedList<string>;

		GraphNode* temp = start;

		while (temp != NULL)
		{
			nodes->insert(temp->nodeId);
			temp = temp->next;
		}

		return nodes;
	}
};

class Router
{
	binary_heap* Incoming_Queue;
	LinkedList<Queue<MSG>> Outgoing_Queue;
	string rt_file;
	string msg_file;
	string routerID;
	LinkedList<string> routing_table;
	int size_heap;

public:
	Router(string ID)
	{
		routerID = ID;
		rt_file = "rt_";
		rt_file += ID;
		rt_file += ".txt";
		msg_file = "msg_";
		msg_file += ID;
		msg_file += ".txt";

		// now we open the file and check how much entries we have 
		// helps in deciding size of the binary heap
		ifstream file(msg_file);

		int n_msgs = 0;

		string line;
		while (!file.eof())
		{
			getline(file, line);

			if (line != "")
				n_msgs++;
		}
		size_heap = n_msgs + 1;

		// now we allocated the memory for heap
		Incoming_Queue = new binary_heap(size_heap);
	}

	void forward_msg()
	{
		ifstream file(msg_file);

		// read all of the messages into Priority Incoming Queue
		while (!file.eof())
		{
			string line;
			getline(file, line);

			if (line != "")
			{
				MSG msg(line);
				Incoming_Queue->insert(msg);
			}
		}
		file.close();

		// delete all entries from the file
		ofstream outfile(msg_file);
		outfile.close();

		//Incoming_Queue->display();

		for (int i = 1; i < size_heap; i++)
		{
			Incoming_Queue->arr[i].addTrace(routerID);
		}

		// populate the routing table
		ifstream rt(rt_file);
		int rt_size = 0;
		while (!rt.eof())
		{
			string line;
			getline(rt, line);
			routing_table.insert(line);
			rt_size++;
		}
		rt.close();

		for (int i = 1; i < size_heap; i++)
		{
			if (Incoming_Queue->arr[i].stringfy() == ",,,,,")
				continue;

			MSG ms(Incoming_Queue->arr[i].stringfy());

			string dest = ms.dest;

			if (dest == routerID)
			{
				cout << "\n\tMESSAGE RECEIVED FROM " << ms.src << " to " << ms.dest << " \"" << ms.Payload << "\" " << ms.Trace;
				continue;
			}

			for (int i = 0; i < rt_size; i++)
			{
				string pair = routing_table.getNodeatIdx(i);

				string pair_dest = "";

				int j = 0;
				while (pair[j] != ',')
				{
					pair_dest += pair[j];
					j++;
				}
				j++;

				if (pair_dest == dest)
				{
					string next_router = "";

					while (pair[j] != '\0')
					{
						next_router += pair[j];
						j++;
					}

					string next_msg_file = "msg_";
					next_msg_file += next_router;
					next_msg_file += ".txt";

					ofstream ofile(next_msg_file, ios::app);

					ofile << ms.stringfy() << endl;

					ofile.close();

					break;
				}
				else
				{
					continue;
				}
			}

		}
	}

};

void readFileintoGraph(Graph& gp, string filename)
{
	ifstream file(filename);

	if (!file.is_open())	cout << "File not found\n";

	string line;

	// this is the Ids of the Graph Nodes i.e first line of the file
	getline(file, line);

	for (int i = 1; line[i] != '\0'; i++)
	{
		string nodeId = "";

		while (line[i] != ',' && line[i] != '\0')
			nodeId += line[i++];

		gp.insertNode(nodeId);

		if (line[i] == '\0')
			break;
	}

	// now inserting the edges
	while (!file.eof())
	{
		getline(file, line);

		if (line == "")
			break;

		int i = 0;

		string nodeId1 = "";

		while (line[i] != ',')
		{
			nodeId1 += line[i++];
		}
		i++;	// to move for the next id
		int index = 0;	// used to get the node 2 name
		for (; line[i] != '\0'; i++)
		{
			string weight = "";

			while (line[i] != ',' && line[i] != '\0')
				weight += line[i++];

			if (weight != "?")
			{
				gp.insertEdge(nodeId1, stoi(weight), gp.getNodeIdAt(index));
			}

			index++;
			if (line[i] == '\0')
				break;
		}
	}

	file.close();
}

// creating files for the nodes
void createFiles(Graph& gp)
{
	int num_vertices = gp.getnumNode();

	for (int i = 0; i < num_vertices; i++)
	{
		ofstream outfile;
		string filename = "msg_";
		filename += gp.getNodeIdAt(i);
		filename += ".txt";
		outfile.open(filename, ios::app);
		outfile.close();
	}
}

// forwarding all of the messages to their destination
void forwardingAllMSGs(Graph& gp)
{
	int num_vertices = gp.getnumNode();

	for (int i = 0; i < num_vertices; i++)
	{
		for (int j = 0; j < num_vertices; j++)
		{
			Router r(gp.getNodeIdAt(j));
			r.forward_msg();
		}
	}
}


void sendMsgFile(string filename)
{
	ifstream file(filename);

	while (!file.eof())
	{
		string msg = "";
		getline(file, msg);

		if (msg == "")
		{
			continue;
		}

		for (int i = 0; i < msg.length(); i++)
		{
			if (msg[i] == ':')
				msg[i] = ',';
		}
		MSG ms(msg);

		string srcfilename = "msg_";
		srcfilename += ms.src;
		srcfilename += ".txt";

		ofstream srcfile(srcfilename, ios::app);
		srcfile << ms.stringfy() << endl;
		srcfile.close();
	}
}

string command = "";
void command_line(Graph& gp, string command)
{

	while (command != "end")
	{
		// check the command
		string command_part = "";

		for (int i = 0; i < command.length() && command[i] != ' '; i++)
		{
			command_part += command[i];
		}
		if (command_part == "send")
		{
			system("cls");
			system("color 4");
			string file_name = "";

			// ignore the part of the command msg
			int idx = command_part.length() + 1;

			while (command[idx++] != ' ');

			while (command[idx] != '\0')
			{
				file_name += command[idx];
				idx++;
			}

			sendMsgFile(file_name);
			forwardingAllMSGs(gp);
		}
		else if (command_part == "print")
		{
			system("cls");
			system("color 5");
			string src = "";
			string dest = "";

			// ignore the part of the command msg
			int idx = command_part.length() + 1;

			while (command[idx++] != ' ');

			while (command[idx] != ' ')
			{
				src += command[idx];
				idx++;
			}

			idx++;
			while (command[idx++] != ' ');

			while (command[idx] != '\0')
			{
				dest += command[idx];
				idx++;
			}
			if (src != "*")
			{
				gp.printpath(src, dest);	// handles both single to single node and single to multiple nodes path
			}
			else
			{
				LinkedList<string>* nodes = gp.getNodes();
				int num_nodes = gp.getnumNode();

				for (int nt = 0; nt < num_nodes; nt++)
				{
					string src = nodes->getNodeatIdx(nt);
					if (src != dest)
						gp.printpath(src, dest);
				}
			}
		}
		else if (command_part == "change")
		{
			system("cls");
			system("color 3");
			// ignore the part of the command msg
			int idx = command_part.length() + 1;
			while (command[idx++] != ' ');
			string src = "";
			while (command[idx] != ',' && command[idx] != '\0')
			{
				src += command[idx];
				idx++;
			}

			if (command[idx] == '\0')
			{
				// means we have to change the whole graph
				gp.deletegraph();

				readFileintoGraph(gp, src);
				gp.completeRoutingTable();
				createFiles(gp);
				continue;
			}

			idx++;
			string dest = "";
			while (command[idx] != ',')
			{
				dest += command[idx];
				idx++;
			}
			idx++;
			string weight = "";
			while (command[idx] != '\0')
			{
				weight += command[idx];
				idx++;
			}
			int i_weight = stoi(weight);
			gp.changeEdgeWeight(src, dest, i_weight);
			gp.changeEdgeWeight(dest, src, i_weight);
			cout << "\n\tEDGE IS CHANGED BETWEEN " << src << " AND " << dest << "TO WEIGHT " << weight;
			cout << "\n\tPRINT PATH BETWEEN ROUTERS TO SEE THE NEW SHORTEST ROUTE" << endl;
		}
		cout << "\n\tENTER DESIRED COMMAND: ";
		getline(cin, command);
	}
}

void display()
{
	system("color 6");
	cout << "\n\n\n\n\n\n\t\t\t\t\t\t" << setw(25) << setfill('*') << "\n";
	cout << setw(49) << setfill(' ') << "" << setw(26) << setfill(' ') << "\n";
	cout << setw(49) << setfill(' ') << "" << setw(4) << setfill(' ') << " " << "NETWORK SYSTEM" << setw(11) <<
		setfill(' ') << "\n";
	cout << setw(49) << setfill(' ') << "" << setw(7) << setfill(' ') << " " << "EMULATOR" << setw(9)
		<< setfill(' ') << "\n";
	cout << setw(49) << setfill(' ') << "" << setw(26) << setfill(' ') << "\n";
	cout << "\t\t\t\t\t\t" << setw(25) << setfill('*') << "\n";
	cout << endl << endl << endl << endl;
	sleep_for(1500ms);
	system("cls");
	system("color 2");
	cout << "\n\n\n\n\n\n\t" << setw(100) << setfill('*') << "\n";
	cout << setw(49) << setfill(' ') << "" << setw(26) << setfill(' ') << "\n";
	cout << "\t <FOR SENDING MESSAGE TO MACHINE VIA MACHINE> send message (name and extension of textfile) \n";
	cout << "\t <FOR PRINTING THE SHORTEST PATH BETWEEN MACHINES> print path (source machine to destination machine) \n";
	cout << "\t <FOR CHANGING PATH BETWEEN ROUTERS OF THE MACHINES> change edge (source router,destination router,weight) \n";
	cout << "\t <FOR PROGRAM EXIT> end \n\n\n";
	cout << setw(43) << setfill(' ') << "" << setw(18) << setfill(' ') << "\n";
	cout << "\t" << setw(100) << setfill('*') << "\n";
	cout << "\n\tENTER DESIRED COMMAND: ";
	getline(cin, command);
}
int main()
{
	Graph gp;
	readFileintoGraph(gp, "network.csv");
	gp.completeRoutingTable();
	createFiles(gp);
	display();
	command_line(gp, command);
	_getch();
	return 0;
}