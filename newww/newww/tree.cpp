#include "tree.h"
#include <iostream>
#include <assert.h>
#include<fstream>
#include<string>
using namespace std;

template <class T>
Node<T>::Node()
{
	left = right = NULL;
	word = NULL;
	meaning = NULL;
}

template <class T>
Node<T>::Node(T wor, T mean)
{
	word = wor;
	meaning = mean;
	left = right = NULL;
}
template <class T>
void tree<T>::readfromfile()
{
	string line1, line2; 
	ifstream myfile("word.txt"); //opening the file.
	ifstream qfile("meaning.txt");

	if (!myfile || !qfile) //Always test the file open.
	{
		cout << "Error opening output file" << endl;
	}
	while (!myfile.eof() && !qfile.eof())
	{
		
			getline(myfile, line1); //get one line from the file
			getline(qfile, line2);
			if (!line1.empty() && !line2.empty())
			{
				insert(line1, line2);
			}
		

	}
}

template <class T>
tree<T>::tree(void)
{
	root = NULL;
	size = 0;
}

template <class T>
void tree<T>::insert(T wor, T mean)
{
	Node<T>* tmp = root;
	Node<T>* newNode = new Node<T>(wor, mean);
	if (root == NULL)
	{
		root = newNode;
	}
	else
	{
		while (true)
		{
			if (tmp->word > wor)
			{
				if (tmp->left == NULL)
				{
					tmp->left = newNode;
					break;
				}
				else
				{
					tmp = tmp->left;
				}
			}
			else
			{
				if (tmp->right == NULL)
				{
					tmp->right = newNode;
					break;
				}
				else
				{
					tmp = tmp->right;
				}
			}
		}
	}
}

template <class T>
void tree<T>::traverse()
{
	cin.ignore();
	system("cls");
	
	inOrder(root);
	update();
	menu();

}

template <class T>
void tree<T>::inOrder(Node<T>* start)
{

	if (start != NULL)
	{
		inOrder(start->left);
		cout << start->word << " = " << start->meaning << endl;
		inOrder(start->right);
	}
}


template <class T>
bool tree<T>::contains(T wor)
{
	Node<T>* tmp = findNode(wor);

	return (tmp != NULL);
}

template <class T>
Node<T>* tree<T>::findNode(T wor)
{
	Node<T>* tmp = root;

	while ((tmp != NULL) && (tmp->word != wor))
		if (tmp->word > wor)
		{
			tmp = tmp->left;
		}
		else
		{
			tmp = tmp->right;
		}
	return tmp;
}

template <class T>
void tree<T>::add()
{
	cin.ignore();
	system("cls");
	T xword;
	T xmeaning;
	cout << "Enter word : ";
	getline(cin, xword);
	if (contains(xword) == true)
	{
		cout << "already exist" << endl;
		menu();
	}
	else
	{
		cout << "Enter meaning :";
		getline(cin, xmeaning);
		insert(xword, xmeaning);
		update();
		cout << "added successfuly" << endl;
		menu();
	}

}


template <class T>
void tree<T>::update()
{
	ofstream myfile("word.txt");
	updateword(myfile, root);
	ofstream qfile("meaning.txt");
	updatemeaning(qfile, root);
}

template <class T>
void tree<T>::updateword(ofstream& myfile, Node<T>* start)
{
	if (start != NULL)
	{
		updateword(myfile, start->left);
		myfile << start->word;
		myfile << endl;
		updateword(myfile, start->right);
	}

}
template <class T>
void tree<T>::updatemeaning(ofstream& qfile, Node<T>* start)
{
	if (start != NULL)
	{
		updatemeaning(qfile, start->left);
		qfile << start->meaning;
		qfile << endl;
		updatemeaning(qfile, start->right);
	}

}

template <class T>
void tree<T>::edit()
{
	cin.ignore();
	system("cls");
	T xword, xmeaning;
	cout << "Enter word : ";
	getline(cin, xword);
	if (contains(xword) == true)
	{
		cout << "Enter new meaning : ";
		getline(cin, xmeaning);
		Node<T>* tmp = findNode(xword);
		tmp->meaning = xmeaning;
		update();
		cout << "Meaning edited successfuly" << endl;
		menu();

	}
	else
	{
		cout << "word doesnt exist" << endl;
		menu();
	}
}

template <class T>
void tree<T>::search()
{
	cin.ignore();
	system("cls");
	cout << "Enter word : ";
	T xword;
	getline(cin, xword);

	if (contains(xword) == true)
	{
		Node<T>* tmp = findNode(xword);
		cout << tmp->word << " = " << tmp->meaning << endl;
		menu();
	}
	else
	{
		cout << "word doesnt exist" << endl;
		menu();
	}
}
template<class T>
void tree<T>::deleteword()
{
	cin.ignore();
	system("cls");
	T xword;
	cout << "Enter word : ";
	getline(cin, xword);
	if (contains(xword) == true)
	{
		Node<T>* tmp = findNode(xword);
		if ((tmp->left == NULL) && (tmp->right == NULL)) //deleting a leaf node
		{
			if (tmp == root)
				root = NULL;
			else
			{
				Node<T>* parent = findParent(xword);
				if (xword < parent->word)
					parent->left = NULL;
				else
					parent->right = NULL;
			}
			delete tmp;
		}
		else if ((tmp->left == NULL) && (tmp->right != NULL))
		{
			Node<T>* parent = findParent(xword);
			if (tmp == root)
				root = tmp->right;
			else
			{
				if (xword < parent->word)
					parent->left = tmp->right;
				else
					parent->right = tmp->right;
			}
			delete tmp;
		}
		else if ((tmp->left != NULL) && (tmp->right == NULL))
		{
			Node<T>* parent = findParent(xword);
			if (tmp == root)
				root = tmp->left;
			else
			{
				if (xword < parent->word)
					parent->left = tmp->left;
				else
					parent->right = tmp->left;
			}
			delete tmp;
		}
		else
		{
			Node<T>* minNode = findMin(tmp->right);
			Node<T>* parent = findParent(minNode->word);
			tmp->word = minNode->word;

			if (parent == tmp)
				parent->right = minNode->right;
			else
				parent->left = minNode->right;
			delete minNode;
		}
		cout << "Removed successfully" << endl;
		update();
		menu();
	}
	else
	{
		cout << "word doesn't exist.." << endl;
		menu();
	}

}

template <class T>
Node<T>* tree<T>::findMin(Node<T>* start)
{
	Node<T>* minNode = start;
	while (minNode->left != NULL)
		minNode = minNode->left;
	return minNode;
}

template <class T>
Node<T>* tree<T>::findParent(T wor)
{
	Node<T>* a, *b;
	a = root;
	b = NULL;
	while ((a != NULL) && (a->word != wor))
	{
		b = a;
		if (a->word > wor)
			a = a->left;
		else
			a = a->right;
	}
	return b;
}

template<class T>
void tree<T>::Exit()
{
	system("cls");
	exit(0);
}

template<class T>
void tree<T>::menu()
{
	cin.ignore();
	system("cls");
	cout << "1. add a new word" << endl;
	cout << "2. Edit the meaning of certain word" << endl;
	cout << "3. Search for meaning" << endl;
	cout << "4. Display words with it's meaning" << endl;
	cout << "5. Remove word" << endl;
	cout << "6. exit" << endl;
	int choice;
	cin >> choice;

	if (choice == 1)
		add();
	else if (choice == 2)
		edit();
	else if (choice == 3)
		search();
	else if (choice == 4)
		traverse();
	else if (choice == 5)
		deleteword();
	else if (choice == 6)
		Exit();
	else
	{
		cout << "Wrong choice, please try again.." << endl;
		menu();
	}
}
