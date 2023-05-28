#include"Project.h"

//PROJECT'2021

void swap(userNode* X, userNode* Y) {
	userNode* temp = X;
	X = Y;
	Y = temp;
}

userNode::userNode(int userID, int priority, char access) {
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

userNode::userNode(const userNode& rhs) {
	userID = rhs.userID;
	priority = rhs.priority;
	access = rhs.access;
}

userNode userNode::operator=(const userNode& rhs) {
	this->userID = rhs.userID;
	this->priority = rhs.priority;
	this->access = rhs.access;
	return *this;
}

void userNode::input() {
	int temp;
	cout << "\n\tEnter user ID:\t"; cin >> userID;
	cout << "\n\tEnter 0 if user is reading and 1 if writing. In case of wrong entry, reading will be set automatically:\t"; cin >> temp;

	if (temp == 1)
		access = 'W';
	else
		access = 'R';

	cout << "\n\tEnter Priority:\t"; cin >> priority;
}

void userNode::display() {
	cout << "User ID:\t" << userID << "\nAccess:\t" << access << "\nPriority:\t" << priority << endl;
}

