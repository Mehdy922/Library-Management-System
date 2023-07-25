#include <iostream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

class ListofAuthors
{
public:
	ListofAuthors()
	{
		Authhead = NULL;
		Authtail = NULL;
	}
	ListofAuthors(string n)
	{
		if (Authhead == NULL) {
			Authhead = Authtail = new Authors(n, NULL);
		}
		else {
			Authors* newnode = new Authors(n, Authhead);
			Authhead = newnode;
			Authtail = Authtail;
		}
	}
	void addauthor(string n)
	{
		if (Authhead == NULL) {
			Authhead = Authtail = new Authors(n, NULL);
		}
		else {
			Authors* newnode = new Authors(n, Authhead);
			Authhead = newnode;
		}
	}
	void authorPrint()
	{
		Authors* tmp;
		int i = 1;
		for (tmp = Authhead; tmp != NULL; tmp = tmp->next)
		{
			cout << "Author " << i << " = " << tmp->Name;
			i++;
			cout << endl;

		}
	}
	void deleteAuthor(int key)
	{
		Authors* temp;
		int count = 2;
		if (key == 1)
		{
			Authors* store = Authhead;
			Authhead = Authhead->next;
			delete store;
		}
		else
		{
			for (temp = Authhead; temp->next != NULL; temp = temp->next)
			{
				if (count == key)
				{
					Authors* store = temp->next;
					temp->next = temp->next->next;
					delete store;
					break;
				}
				count++;
			}
		}

	}
	void updateexistingAuthor(int key)
	{
		bool changeflag = false;
		char newname[100];
		Authors* temp;
		int count = 1;

		for (temp = Authhead; temp != NULL; temp = temp->next)
		{
			if (count == key)
			{
				cin.ignore();
				cout << "\nEnter New name = ";
				cin.getline(newname, 100);
				temp->Name = newname;
				changeflag = true;
				break;
			}
			count++;
		}
		if (!changeflag)
		{
			cout << "\nAuthor Index Not Found\n\n";
		}

	}
private:
	struct Authors
	{
		Authors()
		{
			next = NULL;
			Name = "\0";
		}
		Authors(string n, Authors* nxt)
		{
			Name = n;
			next = nxt;
		}

		string Name;
		Authors* next;
	};
	Authors* Authhead;
	Authors* Authtail;
};
class Blocks
{
public:
	Blocks()
	{
		ISSN = 0;
		title = '\0';
		copies = 0;
		cangive = 0;
		next = NULL;
		prev = NULL;

	}
	void print()
	{
		PrintBlocks();
		Blocks* ptr = next;
		while (ptr != NULL)
		{
			ptr->PrintBlocks();
			ptr = ptr->next;
		}
	}
	Blocks(int no, string n, ListofAuthors ath, int cp, int cg, Blocks* nxt = NULL, Blocks* prv = NULL)
	{
		ISSN = no;
		title = n;
		auth = ath;
		copies = cp;
		cangive = cg;
		next = nxt;
		prev = prv;
	}
	void updateinfo()
	{
		system("cls");

		cout << endl;
		bool flag = false;
		char newtitle[100];
		int newno2;
		int newno3;

		while (flag == false)
		{
			system("cls");
			PrintBlocks();
			char ans;
			cout << "ISSN found\n";
			cout << "Please select from the followng\n";
			cout << "Enter 1 to = update title\n";
			cout << "Enter 2 to = update Author\n";
			cout << "Enter 3 to = # of copies available as reference book\n";
			cout << "Enter 4 to = # of copies available as issuable book\n";
			cout << "Enter 0 to = Exit\n";
			cout << endl;
			cout << "Input =\t";
			cin >> ans;
			cout << endl;
			switch (ans)
			{
			case '1':
				cout << "Enter new title =\t";
				cin.ignore();
				cin.getline(newtitle, 100);
				cout << endl;
				title = newtitle;
				cout << "Update successful\n";
				cout << endl;
				system("pause");
				system("cls");
				break;
			case '2':
				updateAuthor();
				cout << "Update successful\n";
				system("pause");
				system("cls");
				break;
			case '3':
				cout << "Enter new # of copies available as reference book =\t";
				cin >> newno2;
				cout << endl;
				copies = newno2;
				cout << "Update successful\n";
				cout << endl;
				system("pause");
				system("cls");
				break;
			case '4':
				cout << "# of copies available as issuable book =\t";
				cin >> newno3;
				cout << endl;
				cangive = newno3;
				cout << "Update successful\n";
				cout << endl;
				system("pause");
				system("cls");
				break;
			case '0':
				flag = true;
				break;
			default:
				cout << "Invalid input\n";
				system("pause");
				system("cls");
				break;
			}
		}
	}
	void addBlocks(int no, string n, ListofAuthors ath, int cp, int cg, Blocks* nxt = NULL, Blocks* prv = NULL)
	{
		ISSN = no;
		title = n;
		auth = ath;
		copies = cp;
		cangive = cg;
		next = nxt;
		prev = prv;
	}
	void PrintBlocks()
	{
		cout << "\nISSN =\t" << ISSN << "\n" << "Book Name =\t" << title << "\n" << "# of copies available as reference book =\t" << copies << "\n" << "# of copies available as issuable book =\t" << cangive << endl;
		auth.authorPrint();
		cout << endl;
		cout << endl;

	}
	void updateAuthor()
	{
		system("cls");
		int ind;
		int ind2;
		char ans2;
		char authname[100];
		cout << "\nCurrent available authors =\n";
		auth.authorPrint();
		cout << "\nSelect one of the following\n";
		cout << "Enter 1 to add an author\n";
		cout << "Enter 2 to delete an author\n";
		cout << "Enter 3 to update an existing author\n";
		cin >> ans2;
		switch (ans2)
		{
		case '1':
			cout << "Enter author name =\t";
			cin.ignore();
			cin.getline(authname, 100);
			auth.addauthor(authname);
			break;
		case '2':
			cout << "Please Enter Author Index = ";
			cin >> ind;
			auth.deleteAuthor(ind);
			break;
		case '3':
			cout << "Please Enter Author Index = ";
			cin >> ind2;
			auth.updateexistingAuthor(ind2);
			break;
		default:
			break;

		}

	}
	int ISSN;
	string title;
	ListofAuthors auth;
	int copies;
	int cangive;
	Blocks* next;
	Blocks* prev;
};
class Hash {
private:
	int capacity;
	int primekey;
	vector<list<Blocks*>> hasharray;
	bool* status;
public:
	Hash(int cap = 0)
	{
		if (cap == 0) {
			capacity = 11;
		}
		else
		{
			capacity = cap;
		}
		if (isPrime(capacity))
		{
			primekey = capacity;
		}
		else
		{
			 int tempcap = capacity;
			 while (!isPrime(tempcap))
			 {
				if (tempcap == 1)
				{
					break;
				}
				tempcap++;
			 }
			 primekey = tempcap;
		}
		hasharray.resize(capacity);
		status = new bool[capacity];
		for (int i = 0; i < capacity; i++)
		{
			status[i] = 0;
		}
	}
	bool isPrime(int n)
	{
		bool is_prime = true;
		if (n == 0 || n == 1)
		{
			is_prime = false;
		}

		for (int i = 2; i <= n / 2; ++i)
		{
			if (n % i == 0) {
				is_prime = false;
				break;
			}
		}
		return is_prime;
	}
	int hashfunction(unsigned int issn)
	{
		srand(primekey);
		int a = rand();
		int b = rand();
		a = a * issn;
		a = a + b;
		a = a % primekey;
		a = a % capacity;
		return a;
	}
	void addRecord(int issn, string title, ListofAuthors at, int r, int i)
	{
		int index = hashfunction(issn);
		Blocks* n = new Blocks(issn, title, at, r, i);
		bool flag = false;

		list<Blocks*>::iterator itr;
		for (itr = hasharray[index].begin(); itr != hasharray[index].end(); itr++) {
			if ((**itr).ISSN == issn) {
				flag = true;
				break;
			}
		}

		if (!flag)
			hasharray[index].push_back(n);
		else
			cout << "\n\nISSN already present!!!\n" << endl;

		if (status[index] == false)
		{
			status[index] = true;
		}
	}
	void find(int issn)
	{
		bool flag = false;
		int index = hashfunction(issn);
		list<Blocks*>::iterator itr;
		for (itr = hasharray[index].begin(); itr != hasharray[index].end(); itr++) {
			if ((**itr).ISSN == issn) {
				cout << "Index = " << index<<endl;
				(**itr).PrintBlocks();
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			cout << "Record Not present\n";
		}
	}
	void deletefunc(int issn)
	{
		bool flag = false;
		int index = hashfunction(issn);
		printissn(index);
		list<Blocks*>::iterator itr;
		for (itr = hasharray[index].begin(); itr != hasharray[index].end(); itr++) {
			if ((**itr).ISSN == issn) {
				hasharray[index].remove(*itr);
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			cout << "Record Not present\n";
		}
		else 
		{
			cout << "Deletion successful\n";
		}
		if (hasharray[index].empty())
		{
			status[index] = false;
		}
	}
	void update(int issn)
	{
		bool flag = false;
		int index = hashfunction(issn);
		list<Blocks*>::iterator itr;
		for (itr = hasharray[index].begin(); itr != hasharray[index].end(); itr++) {
			if ((**itr).ISSN == issn) {
				cout << "Index = " << index<<endl;
				(**itr).updateinfo();
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			cout << "Record Not present\n";
		}
	}	
	void printall()
	{
		int index = 0;
		vector<list<Blocks*>>::iterator itr;
		for (itr = hasharray.begin(); itr != hasharray.end(); itr++) {
			if (status[index])
			{
				list<Blocks*>::iterator itr2;
				for (itr2 = hasharray[index].begin(); itr2 != hasharray[index].end(); itr2++) {
						cout << "Index = " << index << endl;
						(**itr2).PrintBlocks();		
				}
			}
			//index++;
		}
	}
	void printissn(int ind)
	{
		int index = ind;
				list<Blocks*>::iterator itr2;
				for (itr2 = hasharray[index].begin(); itr2 != hasharray[index].end(); itr2++) {
						cout << (**itr2).ISSN<< " --> ";
				}
				cout << "NULL" << endl;
	}
	~Hash()
	{
		for (int i = 0; i < capacity; i++)
		{
			hasharray[i].clear();
		}
		hasharray.clear();
	}
};
int main()
{
	int cap;
	cout << "Please enter capacity or enter 0 to set it automatically to 11 : ";
	cin >> cap;
	Hash h1(cap);
	system("cls");


	int ISSN;
	char ans3;
	bool deleteflag;
	int authNo;
	char authname[100];
	char title[100];
	int copies;
	int issue;

	
	cout << endl;
	cout << "==========================||WELCOME TO LIBRARY MANAGMENT SYSTEM||==========================";
	
	bool mainflag = false;
	char mainans;
	while (!mainflag) {
		ListofAuthors authors;
		cout << "\nPlease Select From :\n\n";
		cout << "Enter 1 to create record\nEnter 2 to review a book\nEnter 3 to update book Record\nEnter 4 to delete book record\nEnter 5 to view whole database\nEnter 0 exit\n";
		cin >> mainans;
		switch (mainans)
		{
		case '1':
			cout << "\nEnter ISSN no =\t"; cin >> ISSN;
			cout << "\nEnter title of Book =\t";
			cin.ignore();
			cin.getline(title, 100);

			cout << "\nHow many Authors do you want to add = ";
			cin >> authNo;
			cout << endl;
			cin.ignore();
			for (int i = 1; i <= authNo; i++)
			{
				cout << "Enter name of Author " << i << " =\t";
				cin.getline(authname, 100);
				authors.addauthor(authname);
				cout << endl;
			}
			cout << "\nEnter # of copies available as reference book =\t"; cin >> copies;
			cout << "\nEnter # of copies available as issuable book =\t"; cin >> issue;
			
			h1.addRecord(ISSN, title, authors, copies, issue);;
			
			system("pause");
			system("cls");
			break;
		case '2':
			ISSN = 0;
			cout << "\nPlease enter ISSN No = ";
			cin >> ISSN;
			cout << endl;
			h1.find(ISSN);
			cout << endl;
			system("pause");
			system("cls");
			break;
		case '3':
			ISSN = 0;
			cout << "\nPlease enter ISSN No = ";
			cin >> ISSN;
			cout << endl;
			h1.update(ISSN);
			system("pause");
			system("cls");
			break;
		case '4':
			deleteflag = false;
			while (!deleteflag)
			{
				ISSN = 0;
				
				cout << "\nPlease enter ISSN No = ";
				cin >> ISSN;
				
				//h1.temporary(ISSN);
				h1.deletefunc(ISSN);
				cout << "Do you wish to exit Y/N = ";
				cin >> ans3;
				switch (ans3)
				{
				case 'y':
					deleteflag = true;
					break;
				case 'Y':
					deleteflag = true;
					break;
				default:
					break;
				}
				system("cls");
			}
			system("pause");
			system("cls");
			break;
		case '5':
			h1.printall();
			system("pause");
			system("cls");
			break;
		case '0':
			mainflag = true;
			break;
		default:
			system("cls");
			break;
		}
	}
}
