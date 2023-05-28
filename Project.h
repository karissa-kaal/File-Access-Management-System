#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<list>
using namespace std;

//PROJECT'2021

class userNode;
template<class T> class pQueue;

void swap(userNode* X, userNode* Y) {
	//swapping 
	userNode* temp = X;
	X = Y;
	Y = temp;
}

//This is the class user storing ID, access and priority counter
class userNode {
private:
	int userID;
	int priority;
	char access;	//'R' = reading, 'W' = writing
public:
	userNode(int userID = 0, int priority = 0, char access = 'R') {
		//in case of wrong inputs userid = 0, priority = 0, access = reading
		if (userID > 0 && userID <= 10000)
			this->userID = userID;
		else
			this->userID = 0;
		if (priority > 0 && priority <= 100)
			this->priority = priority;
		else
			this->priority = 0;
		if (access == 'W')
			this->access = access;
		else
			this->access = 'R';
	}

	userNode(const userNode&rhs) {
		//copy constructor
		userID = rhs.userID;
		priority = rhs.priority;
		access = rhs.access;
	}

	userNode operator=(const userNode& rhs) {
		//assignment operator
		this->userID = rhs.userID;
		this->priority = rhs.priority;
		this->access = rhs.access;
		return *this;
	}

	void input() {
		//input
		int temp;
		cout << "\n\tEnter user ID:\t"; cin >> userID;
		cout << "\n\tEnter 0 if user is reading and 1 if writing. In case of wrong entry, reading will be set automatically:\t"; cin >> temp;

		if (temp == 1)
			access = 'W';
		else
			access = 'R';

		cout << "\n\tEnter Priority:\t"; cin >> priority;
	}

	void display() {
		cout << "User ID:\t" << userID << "\nAccess:\t" << access << "\nPriority:\t" << priority << endl;
	}
	
	char GetAccess() {
		return access;
	}

	int GetID() {
		return userID;
	}

	int getpriority() {
		return priority;
	}
	template<class U>
	friend class pQueue;
};

//A template based priority queue will be handling all the information of user in priority basis
template<class T>
class pQueue {
private:
	vector<userNode> queue;
	int pNode(int temp) {
		return (temp - 1) / 2;
	}

	int lNode(int temp) {
		return (2 * temp) + 1;
	}

	int rNode(int temp) {
		return (2 * temp) + 2;
	}

	void SortingHeap() {
		if (isEmpty())
			return;
		int SIZE = size();

		for (int i = SIZE - 1; i >= 0; i--) {
			// Move current top to end
			swap(queue[0], queue[i]);
			SIZE--;
			SortingHeap(0, SIZE);
		}
	}

	void SortingHeap(int temp, int SIZE) {
		if (isEmpty())
			return;
		int left = lNode(temp);
		int right = rNode(temp);
		int lowest = temp;

		if (left < SIZE && (queue[left].priority < queue[lowest].priority))
			lowest = left;
		if (right < SIZE && (queue[right].priority < queue[lowest].priority))
			lowest = right;

		if (lowest != temp) {
			swap(queue[lowest], queue[temp]);
			SortingHeap(lowest, SIZE);
		}

	}

	void BuildHeap() {
		if (isEmpty())
			return;
		for (int i = size() / 2 - 1; i >= 0; i--)
			SortingHeap(i, size());
	}

public:
	int size() {
		return queue.size();
	}

	void BuildQueue(vector<userNode> arr) {
		//Takes in an unsorted arrayand convert it to a priority queue
		//resizing the queue according to given array
		queue.resize(arr.size());
		for (int i = 0; i < size(); i++)
			queue[i] = arr[i];
		BuildHeap();
		SortingHeap();
	}

	userNode extractMax() {
		userNode temp = queue[0];
		queue[0] = queue[queue.size() - 1];
		queue.pop_back();
		SortingHeap();
		return temp;
	}

	void output() {
		cout << "Users waiting for access:\n";
		for (int i = 0; i < queue.size(); i++) {
			queue[i].display();
			cout << endl;
		}
	}

	void insert() {
		
		int n;
		cout << "How many users are waiting for this file?\t";
		cin >> n;
		vector<userNode> arr(n);
		for (int i = 0; i < n; i++) {
			cout << "Enter user's ID:\t";
			cin >> arr[i].userID;
			cout << "Enter user's priority:\t";
			cin >> arr[i].priority;
			cout << "Enter user's access:\t";
			cin >> arr[i].access;
			cout << endl;
		}
		BuildQueue(arr);
	}

	void insert(userNode New) {
		
		queue.push_back(New);
		BuildHeap();
		SortingHeap();
	}

	userNode FindMax() {
		if (isEmpty())
			return NULL;

		BuildHeap();
		SortingHeap();
		return queue[0];
	}

	userNode FindMin() {
		if (isEmpty())
			return NULL;

		BuildHeap();
		SortingHeap();
		return queue[size() - 1];
	}

	bool isEmpty() {
		if (size() == 0)
			return true;
		return false;
	}

	void setInfo(int a, int b, char c) {
		userNode temp(a, b, c);
		queue.push_back(temp);
		BuildHeap();
		SortingHeap();
	}

	int SearchUser(int id) {
		for (int i = 0; i < size(); i++)
			if (queue[i].userID == id)
				return i;
		return -1;
	}
};

class fileNode {
private:
	int fileID;
	pQueue<userNode> waitingQueue;
	vector<userNode> listOfUsers;
public:
	int SearchUserinLIST(int id) {
		for (int i = 0; i < listOfUsers.size(); i++)
			if (listOfUsers[i].GetID() == id)
				return i;
		return -1;
	}

	fileNode() {
		fileID = 0;
	}

	void setData(int a, int b, int c, char d) {
		if (a > 5000 && a <= 99999)
			fileID = a;
		else
			fileID = 5001;
		waitingQueue.setInfo(b, c, d);
	}

	void printF() {
		cout << "File ID:\t" << fileID << endl;
		if (waitingQueue.isEmpty())
			cout << "No one is accessing this file.\n";
		else {
			for (int i = 0; listOfUsers.size(); i++)
				cout << "User " << listOfUsers[i].GetID() << " is " << listOfUsers[i].GetAccess() << " the file.\n";
		}
		cout << "Remaining users waiting for access:\t" << waitingQueue.size() << endl;
	}

	bool CheckCurrent() {
		if (listOfUsers[0].GetAccess() == 'R')
			return true;
		if (listOfUsers[0].GetAccess() == 'W')
			return false;
	}

	void insertF(int a) {
		if (a > 5000 && a <= 99999)
			fileID = a;
		else
			fileID = 99999;
		waitingQueue.insert();
	}

	template<class U>
	friend class repositoryOfFiles;
};

template<class T>
class repositoryOfFiles {
private:
	vector<list<fileNode>> hashTable;
	int tableSize;
	int noOfFiles;

	//Helper functions
	bool isPrime(int n) {
		if (n <= 1)  return false;
		if (n <= 3)  return true;
		if (n % 2 == 0 || n % 3 == 0) return false;
		for (int i = 5; i * i <= n; i = i + 6)
			if (n % i == 0 || n % (i + 2) == 0)
				return false;
		return true;
	}

	int nextPrime(int N) {
		if (N <= 1)
			return 2;
		int prime = N;
		bool found = false;
		while (!found) {
			prime++;
			if (isPrime(prime))
				found = true;
		}
		return prime;
	}

	int hashFunc(int key) {
		return key % tableSize;
	}

	void hashFile(fileNode obj) {
		int index = hashFunc(obj.fileID);
		hashTable[index].push_back(obj);
	}


public:
	repositoryOfFiles() {
		ifstream fin("file.txt");//Counting the total no of files
		if (!fin)
			cout << "File doesn't open!";
		string temp;
		int size = 0;
		while (getline(fin, temp))
			size++;
		//Allocating hash table
		noOfFiles = size;
		tableSize = nextPrime(size);
		hashTable.resize(tableSize);
	}

	void loadData() {
		ifstream fin("file.txt");//Counting the total no of files
		if (!fin) {
			cout << "File doesn't open!";
			return;
		}
		int fID, uID, priority;
		char access;

		for (int i = 0; i < noOfFiles; i++) {
			fileNode temp;
			fin >> fID >> uID >> priority >> access;
			temp.setData(fID, uID, priority, 'R');//Setting the data
			hashFile(temp);
			fin.clear();
		}
	}

	void printTable() {
		for (int j = 0; j < tableSize; j++)
			if (!hashTable[j].empty())
				for (auto& a : hashTable[j])
					a.printF();
	}

	bool search(int id) {
		int index = hashFunc(id);
		list<fileNode>::iterator i;
		for (i = hashTable[index].begin(); i != hashTable[index].end(); ++i) {
			if (i->fileID == id) {
				return true;
			}
		}
		return false;
	}

	void insertFile() {
		int fID, uID, priority;
		char access;
		fileNode temp;
		cout << "Enter file ID:\t";
		cin >> fID;
		while (search(fID)) {
			cout << "This file ID already exists! Enter another one:\t";
			cin >> fID;
		}
		temp.insertF(fID);
		hashFile(temp);
	}

	void deleteFile() {
		int tempID;
		cout << "Enter the file ID you want to delete:\t";
		cin >> tempID;

		if (!search(tempID)) {
			cout << "File doesn't exist!\n";
			return;
		}

		list<fileNode>::iterator i;
		int index = hashFunc(tempID);
		for (i = hashTable[index].begin(); i != hashTable[index].end(); ++i) {
			if (i->fileID == tempID) {
				if (i->listOfUsers.empty()) {
					hashTable[index].erase(i);
					cout << "File deleted.\n";
					return;
				}
				else {
					cout << "Cannot delete file. User is accessing it.\n";
					return;
				}
			}
		}
	}

	bool ReturnFile(int id, fileNode& Temp) {
		int index = hashFunc(id);
		list<fileNode>::iterator i;
		for (i = hashTable[index].begin(); i != hashTable[index].end(); ++i) {
			if (i->fileID == id) {
				Temp = *i;
				return true;
			}
		}
		cout << "\n\n!!File NOT found!!\n";
		return false;
	}

	int Priority() {
		cout << "\nEnter 0 if you want to give priority in number or enter 1 if you want to gove highest or lowest priority:\t";
		int x;
		cin >> x;
		if (x == 0) {
			cout << "\nEnter priority as a number:\t";
			cin >> x;
			if (x < 0 || x > 100) {
				cout << "Priority set as 0 as wrong value was entered.";
				return 0;
			}
			return x;
		}
		else {
			cout << "\nEnter 0 if you want Highest priority else any number for lowest:\t";
			cin >> x;
			if (x == 0)
				return -1;
			else
				return -2;
		}
	}

	char Access() {
		cout << "\nEnter 0 if user wants to write else enter 1 to read";
		int x;
		cin >> x;
		if (x == 0)
			return 'W';
		else
			return 'R';
	}

	void RequestFileAccess(int User, int File) {
		if (File < 5000 || File > 99999) {
			cout << "\n\nERROR! Incorrect File ID!!\n\n";
			return;
		}

		if (User < 0 || User > 10000) {
			cout << "\n\nERROR! Incorrect User ID!!\n\n";
			return;
		}

		fileNode Temp;
		
		if (ReturnFile(File, Temp)) {
			int userPriority = Priority();

			if (userPriority == -1)
				userPriority = Temp.waitingQueue.FindMax().getpriority() + 1;
			else if (userPriority == -2)
				if (Temp.waitingQueue.FindMin().getpriority() > 1)
					userPriority = Temp.waitingQueue.FindMin().getpriority() - 1;
				else
					userPriority = Temp.waitingQueue.FindMin().getpriority();

			userNode New(User, userPriority, Access());

			if (Temp.listOfUsers.size() == 0)
				Temp.listOfUsers.push_back(New);
			else if (Temp.CheckCurrent() && New.GetAccess() == 'R')
				Temp.listOfUsers.push_back(New);
			else
				Temp.waitingQueue.insert(New);
		}
		else
			cout << "\nNO FILE FOUND WITH THAT ID\n";
	}

	void RequestFileAccess() {
		int user, file;
		cout << "\nEnter user ID:\t"; cin >> user;
		cout << "\nEnter file ID:\t"; cin >> file;
		RequestFileAccess(user, file);
	}

	void ReleaseFile(int File, int User) {
		if (File < 5000 || File > 99999) {
			cout << "\n\nERROR! Incorrect File ID!!\n\n";
			return;
		}

		if (User < 0 || User > 10000) {
			cout << "\n\nERROR! Incorrect User ID!!\n\n";
			return;
		}

		fileNode Temp;
		userNode TempUser;
		if (ReturnFile(File, Temp)) {
			int i = Temp.SearchUserinLIST(User);
			Temp.listOfUsers.erase(Temp.listOfUsers.begin() + i);
			if(Temp.listOfUsers.size() == 0)
				if (!Temp.waitingQueue.isEmpty())
					Temp.listOfUsers.push_back(Temp.waitingQueue.extractMax());
				
				else if (Temp.CheckCurrent()) {
					bool check = false;
					while (!check) {
						if (!Temp.waitingQueue.isEmpty()) {
							TempUser = Temp.waitingQueue.FindMax();
							if (TempUser.GetAccess() == 'R')
								Temp.listOfUsers.push_back(Temp.waitingQueue.extractMax());
							else
								check = true;
						}
						else
							check = true;
					}
					
				}
				
		}
		else
			cout << "\nNO FILE FOUND WITH THAT ID\n";
	}

	void ReleaseFile() {
		int user, file;
		cout << "\nEnter user ID:\t"; cin >> user;
		cout << "\nEnter file ID:\t"; cin >> file;
		ReleaseFile(user, file);
	}
};

