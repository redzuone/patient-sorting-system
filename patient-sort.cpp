#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Linked list node
struct dataNode
{
	int age;
	dataNode * link;
};

// Binary tree node
struct TreeNode
{
	int value;	// The value in the node
	TreeNode * left;	// Pointer to left child node
	TreeNode * right;	// Pointer to right child node
};
TreeNode * root;	// Root pointer
int dataSize = 0;

void readFile(int ageArray[]);

// Functions for the linked list
void arrayToLL(int ageArray[], dataNode* &tail, dataNode* &head);
void initNode(dataNode* &head, int n);
void addNode(dataNode* &head, dataNode* &tail, int n);
void modifyLL(dataNode* &head, dataNode* &tail);
char menu();
void remove(dataNode* &head, int index);
dataNode* searchNodeLL(dataNode* &head, int index);
void display(dataNode* &head);

// Functions for the binary tree
void createTree(dataNode* &head);
void insertNode(int);
void insert(TreeNode *&, TreeNode *&);
bool searchNode(int num);
void displayPostOrder(TreeNode *nodePtr);
void searchTree();
void swap(int *a, int *b);
void quickSort(int ageArray[], int low, int high);
void printArray(int ageArray[], int size);
int partition(int ageArray[], int low, int high);

int main()
{
	int ageArray[500];

	// Read text file, insert the values into linked list
	readFile(ageArray);

	dataNode *head = NULL;
	dataNode *tail = NULL;
	arrayToLL(ageArray, tail, head);

	modifyLL(head, tail);

	createTree(head);

	// Display traversal
	cout << "Would you like to display postorder traversal?";
	cout << "\n 1. Yes";
	cout << "\n 2. No";
	cout << "\nEnter choice (1-2):\n";
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		cout << "Postorder traversal:" << endl;
		displayPostOrder(root);
	}

	// Searching the binary tree
	searchTree();

	// Create new updated array
	int ageArrayUpdated[dataSize];
	dataNode * temp;
	temp = head;
	for (int i = 0; i < dataSize; i++)
	{
		ageArrayUpdated[i] = temp->age;
		//cout<<temp->age;
		temp = temp->link;
	}

	// sorting function
	quickSort(ageArrayUpdated, 0, dataSize - 1);
	cout << "\nList of Vaccine Recipient Sorted by Age: \n";
	printArray(ageArrayUpdated, dataSize);

	// Save sorted list to file
	remove("sortedAge.txt");	// remove file
	ofstream sortedAgeFile("sortedAge.txt", ios::app);
	for (int i = 0; i < dataSize; i++)
		sortedAgeFile << ageArrayUpdated[i] << endl;
	cout << endl << "Sorted list of recipient saved into sortedAge.txt";

}

void readFile(int ageArray[])
{
	cout << "Reading data file...";
	ifstream MyFile("data.txt");	// input stream MyFile test.txt
	string myText;
	int age, index = 0;
	stringstream convertToInt;	// convertToInt - to convert string to text
	while (getline(MyFile, myText))
	{
		convertToInt.clear();	// clear stream
		convertToInt << myText;	// insert string
		convertToInt >> age;	// extract converted string
		ageArray[index] = age;
		index++;
	}
	MyFile.close();	// close file
	cout << "\nDone!";
}

void arrayToLL(int ageArray[], dataNode* &tail, dataNode* &head)
{
	int age;
	for (int i = 0; i < 500; i++)
	{
		age = ageArray[i];
		if (head == NULL)
		{
			// if no node in linked list, initialize first node
			head = new dataNode;
			initNode(head, age);
		}
		else
		{
			// use addNode() for the rest of the items
			addNode(head, tail, age);
		}
	}
}

void initNode(dataNode* &head, int n)
{
	head->age = n;
	head->link = NULL;
	dataSize++;
}

void addNode(dataNode* &head, dataNode* &tail, int n)
{
	dataNode *newNode = new dataNode;
	newNode->age = n;
	newNode->link = NULL;

	dataNode *cur = head;
	while (cur != NULL)
	{
		if (cur->link == NULL)
		{
			cur->link = newNode;
			tail = cur->link;
			dataSize++;
			return;
		}
		cur = cur->link;
	}
}

void display(dataNode* &head)
{
	int counter = 1;
	dataNode *list = head;
	while (list)
	{
		cout << counter << ". " << list->age << " | ";
		list = list->link;
		counter++;
	}
	cout << endl;
	cout << endl;
}

void modifyLL(dataNode* &head, dataNode* &tail)
{
	char choice;
	cout << "\nWould you like to add or remove vaccine recipients?\n";
	cout << " 1. Yes\n";
	cout << " 2. No\n";
	cin >> choice;
	if (choice == '1')
	{
		int age, number;
		do { 	choice = menu();
			switch (choice)
			{
				case '1':
					cout << "Please enter recipient age:\n";
					cin >> age;
					addNode(head, tail, age);
					cout << "Recipient added.\n";
					break;
				case '2':
					display(head);
					cout << "Please enter which recipient to remove:\n";
					cin >> number;
					remove(head, number);
					break;
				case '3':
					display(head);
					break;
				default:
					cout << "Exiting..\n";
			}
		}
		while (choice != '4');
	}
}

char menu()
{
	char choice;
	cout << "\nMenu\n";
	cout << "1. Add New Vaccine Recipient.\n";
	cout << "2. Remove Vaccine Recipient.\n";
	cout << "3. List Vaccine Recipient's Age.\n";
	cout << "4. Exit\n";
	cout << "Enter choice(1-4):\n";

	cin >> choice;
	return choice;
}

void remove(dataNode* &head, int index)
{
	dataNode * temp;
	dataNode *ptrNode = searchNodeLL(head, index);
	temp = head;

	while (temp)
	{
		// if head, remove head node then point head pointer to the next node
		if (ptrNode == head)
		{
			head = head->link;
			delete ptrNode;
			dataSize--;
			return;
		}
		// if  the node is in the middle, remove the node
		// and link previous node and the next node
		else if (temp->link == ptrNode && ptrNode->link != NULL)
		{
			temp->link = temp->link->link;
			delete ptrNode;
			dataSize--;
			return;
		}
		// if it is the tail node, remove tail node and point tail to the previous node
		else if (temp->link == ptrNode && ptrNode->link == NULL)
		{
			temp->link = NULL;
			delete ptrNode;
			dataSize--;
			return;
		}
		temp = temp->link;
	}
}

dataNode* searchNodeLL(dataNode* &head, int index)
{
	dataNode *cur = head;
	int counter = 1;
	while (cur)
	{
		if (counter == index)
		{
			return cur;
		}
		cur = cur->link;
		counter++;
	}
}

void createTree(dataNode* &head)
{
	dataNode * temp;
	temp = head;
	while (temp)
	{
		insertNode(temp->age);	// insert age from linked list into tree
		temp = temp->link;
	}
}

void insertNode(int num)
{
	TreeNode *newNode = NULL;	// Pointer to a new node.

	// Create a new node and store num in it.
	newNode = new TreeNode;
	newNode->value = num;
	newNode->left = newNode->right = NULL;

	// Insert the node.
	insert(root, newNode);
}

void insert(TreeNode* &nodePtr, TreeNode* &newNode)
{
	if (nodePtr == NULL)
		nodePtr = newNode;	// Insert the node.
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode);	// Search the left branch
	else
		insert(nodePtr->right, newNode);	// Search the right branch
}

void displayPostOrder(TreeNode *nodePtr)
{
	if (nodePtr)
	{
		displayPostOrder(nodePtr->left);
		displayPostOrder(nodePtr->right);
		cout << nodePtr->value << " ";
	}
}

void searchTree()
{
	int choice;
	cout << "\nWould you like to search the binary tree?";
	cout << "\n 1. Yes";
	cout << "\n 2. No";
	cout << "\nEnter your choice (1-2):\n";
	cin >> choice;
	if (choice == 1)
	{
		int key;
		cout << "\nPlease enter age to find:\n";
		cin >> key;
		if (searchNode(key) == true)
			cout << "Recipient found.";
		else
			cout << "Recipient not found.";
	}
}

bool searchNode(int num)
{
	TreeNode *nodePtr = root;
	while (nodePtr)
	{
		if (nodePtr->value == num)
			return true;
		else if (num < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return false;
}

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int ageArray[], int low, int high)
{
	int pivot = ageArray[high];	// pivot
	int i = (low - 1);	// Index of smaller element and indicates the right position of pivot found so far

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (ageArray[j] < pivot)
		{
			i++;	// increment index of smaller element
			swap(&ageArray[i], &ageArray[j]);
		}
	}
	swap(&ageArray[i + 1], &ageArray[high]);
	return (i + 1);
}

void quickSort(int ageArray[], int low, int high)
{
	if (low < high)
	{
		/*pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(ageArray, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(ageArray, low, pi - 1);
		quickSort(ageArray, pi + 1, high);
	}
}

/*Function to print an array */
void printArray(int ageArray[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << ageArray[i] << " ";
	cout << endl;
}
