#include"Project.h"

void main() {

	repositoryOfFiles<fileNode> obj;

	int n;
	bool check = false;

	while (!check) {
		cout << "\t\t\t---$$$---MENU---$$$---\n\n";

		cout << "Press 1 to load the data from file.\n";
		cout << "Press 2 to print the hash table.\n";
		cout << "Press 3 to request a file access.\n";
		cout << "Press 4 to release access of a file.\n";
		cout << "Press 5 to insert a file.\n";
		cout << "Press 6 to delete a file.\n";
		cout << "Press 0 to exit pprogram.\n";

		cout << "Enter you choice here:\t";
		cin >> n;

		switch (n) {
		case 1:
			obj.loadData();
			break;
		case 2:
			obj.printTable();
			break;
		case 3:
			obj.RequestFileAccess();
			break;
		case 4:
			obj.ReleaseFile();
			break;
		case 5:
			obj.insertFile();
			break;
		case 6:
			obj.deleteFile();
			break;
		case 0:
			check = true;
			break;
		default:
			cout << "\nInvalid entry\n";
			check = false;
			break;
		}
	
	}
}