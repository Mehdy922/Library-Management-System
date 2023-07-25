
#include <iostream>
using namespace std;

class ListofAuthors
{
public:
	ListofAuthors()
	{
		Authhead = NULL;
	}
	ListofAuthors(string n)
	{
		if (Authhead == NULL)
			Authhead = new Authors(n, NULL);
		else {
			Authors* newnode = new Authors(n, Authhead);
			Authhead = newnode;
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
	void PrintBlocks()
	{
		cout << "ISSN =\t" << ISSN << "\n" << "Book Name =\t" << title << "\n" << "# of copies available as reference book =\t" << copies << "\n" << "# of copies available as issuable book =\t" << cangive << endl;
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
template <class T>
class List
{
public:
	List()
	{
		head = NULL;
		tail = NULL;
	}
	void addrecord(int d, string s, ListofAuthors at, int r, int i, Blocks*& tmp)
	{
		Blocks* chk;

		if (head == NULL)
		{
			head = tail = new Blocks(d, s, at, r, i);
			tmp = head;
		}
		else
		{
			for (chk = head; chk != NULL; chk = chk->next)
			{
				if (chk->next == NULL)
				{
					Blocks* n = new Blocks(d, s, at, r, i, NULL, tail);
					tail->next = n;
					tail = tail->next;
					tmp = tail;
					break;
				}
				else if (chk->ISSN >= d)
				{
					if (chk->prev == NULL)
					{
						Blocks* n = new Blocks(d, s, at, r, i, head);
						head = n;
						tmp = n;
						break;
					}
					else if (chk->prev->ISSN <= d)
					{
						Blocks* n = new Blocks(d, s, at, r, i, chk->prev, chk);
						chk->prev->next = n;
						chk->prev = n;
						tmp = n;
						break;
					}
				}
			}
		}

	}
	void PrintList()
	{
		Blocks* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			tmp->PrintBlocks();
		}
	}
	void deletprint()
	{
		Blocks* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			cout << tmp->ISSN << "---> ";
		}
		cout << "NULL" << endl << endl;
	}
	~List()
	{
		Blocks* p = head;
		while (head != NULL) {
			p = head->next;
			delete head;
			head = p;
		}
		tail = NULL;
	}
	Blocks* head;
	Blocks* tail;
};
class tree
{
private:
	struct BNode
	{
	public:
		BNode()
		{
			left = NULL;
			right = NULL;
		}
		BNode(int d, BNode* l = NULL, BNode* r = NULL)
		{
			ISSN = d;
			left = l;
			right = r;

		}
		BNode* left;
		BNode* right;
		int ISSN;
		Blocks* address;
		int height;
	};
	BNode* root;
	List<Blocks> database;
public:
	tree()
	{
		root = NULL;
	}
	~tree()
	{
		Destroy(root);
	}
	void Destroy(BNode*& node)
	{
		if (node)
		{
			Destroy(node->left);
			Destroy(node->right);
			delete node;
			node = NULL;
		}
	}
	void updateRecord(int key)
	{
		updateRecord(root, key);
	}
	void updateRecord(BNode*& tmp, int key)
	{
		if (tmp) {
			if (tmp->ISSN == key)
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
					tmp->address->PrintBlocks();
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
						tmp->address->title = newtitle;
						cout << "Update successful\n";
						cout << endl;
						system("pause");
						system("cls");
						break;
					case '2':
						tmp->address->updateAuthor();
						cout << "Update successful\n";
						system("pause");
						system("cls");
						break;
					case '3':
						cout << "Enter new # of copies available as reference book =\t";
						cin >> newno2;
						cout << endl;
						tmp->address->copies = newno2;
						cout << "Update successful\n";
						cout << endl;
						system("pause");
						system("cls");
						break;
					case '4':
						cout << "# of copies available as issuable book =\t";
						cin >> newno3;
						cout << endl;
						tmp->address->cangive = newno3;
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
			else
				if (tmp->ISSN > key)
					return updateRecord(tmp->left, key);
				else
					return updateRecord(tmp->right, key);
		}
		else
		{
			cout << "No record available\n";
		}
	}
	void addNewRecord(BNode*& Node, int key, string s, ListofAuthors at, int r, int i)
	{
		if (Node == NULL)
		{
			Node = new BNode(key, NULL, NULL);
			database.addrecord(key, s, at, r, i, Node->address);
		}
		else
		{
			if (Node->ISSN > key)
				addNewRecord(Node->left, key, s, at, r, i);
			else if (Node->ISSN == key) {
				cout << "\nISSN already present";
				return;
			}
			else
				addNewRecord(Node->right, key, s, at, r, i);
		}
		balance(Node);
	}
	void addNewRecord(int key, string s, ListofAuthors at, int r, int i)
	{
		addNewRecord(root, key, s, at, r, i);

	}
	int getPredecessor(BNode* n, Blocks*& newadd)
	{
		while (n->right != NULL)

			n = n->right;
		newadd = n->address;
		return n->ISSN;

	}
	void makeAVL(BNode*& Node)
	{
		if (Node != NULL)
		{
			balance(Node);
			makeAVL(Node->left);
			makeAVL(Node->right);
		}
	}
	void deleteR(int d)

	{
		deleteR(d, root);
		makeAVL(root);
		cout << endl << endl;
		cout << "Deletion ended\n";
	}
	void deleteR(int d, BNode*& node)
	{
		if (node) {

			if (d > node->ISSN)
				deleteR(d, node->right);

			else if (d < node->ISSN)
				deleteR(d, node->left);
			else
			{
				deleteRecord(node);
				deleteNode(node);
			}

		}
		else
		{
			cout << "Record not found\n";
		}

	}
	void deleteNode(BNode*& node) {

		BNode* temp = node;

		if (node->left == NULL) {
			node = node->right;
			delete temp;

		}

		else if (node->right == NULL) {
			node = node->left;
			delete temp;
		}

		else {
			Blocks* add;
			int d = getPredecessor(node->left, add);
			node->ISSN = d;
			node->address = add;
			deleteR(d, node->left);
		}

	}
	void deleteRecord(BNode*& tmp)
	{
		if (tmp->address->prev && tmp->address->next)
		{
			Blocks* store = tmp->address;
			tmp->address->prev->next = tmp->address->next;
			tmp->address->next->prev = tmp->address->prev;
			delete store;
		}
		else
		{
			if (tmp->address->prev == NULL && tmp->address->next)
			{
				Blocks* store = tmp->address;
				database.head = database.head->next;
				database.head->prev = NULL;
				delete store;
			}
			else if (tmp->address->next == NULL && tmp->address->prev)
			{
				Blocks* store = tmp->address;
				database.tail = database.tail->prev;
				database.tail->next = NULL;
				delete store;
			}
			else
			{
				Blocks* store = tmp->address;
				database.head = NULL;
				database.tail = NULL;
				delete store;
			}
		}
	}
	void printdatabase()
	{
		printdatabase(root);
	}
	void printdatabase(BNode*& node)
	{
		if (node) {
			printdatabase(node->left);
			visit(node);
			printdatabase(node->right);
		}
	}
	void visit(BNode*& node)
	{
		node->address->PrintBlocks();
	}
	void Review(BNode*& tmp, int key)
	{
		if (tmp) {
			if (tmp->ISSN == key)
			{
				tmp->address->PrintBlocks();
			}
			else
				if (tmp->ISSN > key)
					return Review(tmp->left, key);
				else
					return Review(tmp->right, key);
		}
		else
		{
			cout << "No record available\n";
		}
	}
	void Review(int key)
	{
		Review(root, key);
	}
	void balance(BNode*& t)
	{
		if (t == nullptr)
			return;

		if (height(t->left) - height(t->right) > 1)
		{
			if (height(t->left->left) >= height(t->left->right))
				rightRotate(t);
			else
				doubleLeftRightRotation(t);
		}
		else if (height(t->right) - height(t->left) > 1)
		{

			if (height(t->right->right) >= height(t->right->left))
				leftRotate(t);
			else
				doubleRightLeftRotation(t);
		}

		t->height = max(height(t->left), height(t->right)) + 1;
	}
	int height(BNode*& Node)
	{
		if (Node == NULL)
		{
			return -1;
		}
		else
		{
			int left_height = height(Node->left);
			int right_height = height(Node->right);

			if (left_height >= right_height)
			{
				return left_height + 1;
			}
			else
				return right_height + 1;
		}
	}
	void rightRotate(BNode*& x) {

		BNode* orphan = x->left->right;	// 1. detach Y(left child’s) right subtree
		BNode* y = x->left;		// 2. consider Y(left child) to be the new parent
		x->left->right = x;		// 3. attach old parent onto right of new parent
		x->left = orphan;
		x->height = height(x);  // update nodes'
		y->height = height(y);  // height values
		x = y;
	}
	void Lrotate()
	{
		leftRotate(root);
	}
	void Rrotate()
	{
		rightRotate(root);
	}
	void leftRotate(BNode*& x) {

		BNode* orphan = x->right->left;	// 1. detach Y(left child’s) right subtree
		BNode* y = x->right;		// 2. consider Y(left child) to be the new parent
		x->right->left = x;		// 3. attach old parent onto right of new parent
		x->right = orphan;
		x->height = height(x);  // update nodes'
		y->height = height(y);  // height values
		x = y;
	}
	void doubleLeftRightRotation(BNode*& X)
	{
		leftRotate(X->left);
		rightRotate(X);
	}
	void doubleRightLeftRotation(BNode*& X)
	{
		rightRotate(X->right);
		leftRotate(X);
	}
	void temporary()
	{
		database.deletprint();
	}
};
int main()
{
	tree t1;
	int ISSN;
	char ans3;
	bool deleteflag;
	int authNo;
	char authname[100];
	char title[100];
	int copies;
	int issue;
	cout << "==========================||WELCOME TO LIBRARY MANAGMENT SYSTEM||==========================";
	bool mainflag = false;
	char mainans;
	while (!mainflag) {
		ListofAuthors authors;
		cout << "\nPlease Select From :\n\n";
		cout << "Enter 1 to create record\nEnter 2 to review a book\nEnter 3 to update book Record\nEnter 4 to delete book record\nEnter 5 to view full database\nEnter 0 exit\n";
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
			t1.addNewRecord(ISSN, title, authors, copies, issue);
			cout << "\n\nRecord Added Successfully\n\n";
			system("pause");
			system("cls");
			break;
		case '2':
			ISSN = 0;
			cout << "\nPlease enter ISSN No = ";
			cin >> ISSN;
			cout << endl;
			t1.Review(ISSN);
			cout << endl;
			system("pause");
			system("cls");
			break;
		case '3':
			ISSN = 0;
			cout << "\nPlease enter ISSN No = ";
			cin >> ISSN;
			cout << endl;
			t1.updateRecord(ISSN);
			system("pause");
			system("cls");
			break;
		case '4':
			deleteflag = false;
			while (!deleteflag)
			{
				ISSN = 0;
				t1.temporary();
				cout << "\nPlease enter ISSN No = ";
				cin >> ISSN;
				t1.deleteR(ISSN);
				cout << "Do you wish to exit  = ";
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
			t1.printdatabase();
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
