#pragma once
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
template <class T>
class Node
{
public:

	Node<T>* left, *right;
	T word, meaning;

	Node();
	Node(T wor, T mean);

};

template <class T>
class tree
{
	int size;
	Node<T>* root;
public:
	tree(void);
	bool contains(T wor);
	void readfromfile();
	Node<T>* findNode(T wor);
	void insert(T wor, T mean);
	void traverse();
	void inOrder(Node<T>* start);
	void add();
	void edit();
	void search();
	void deleteword();
	Node<T>* findMin(Node<T>* start);
	Node<T>* findParent(T wor);
	void menu();
	void updateword(ofstream& myfile, Node<T>* start);
	void updatemeaning(ofstream& qfile, Node<T>* start);
	void update();
	void Exit();
	

};
