#pragma once
#include "Polynomial.h"
#include "PolWithDegree.h"
#include "PolWithString.h"
#include <string>

class Queue
{
public:
	Queue();
	~Queue();
	void push(Polynomial pol);
	void push(PolWithDegree pol);
	void push(PolWithString pol);
	Polynomial* pop();
	char* show();
	bool empty();
	int size();

private:
	class Node
	{
	public:
		Node();
		Node(Polynomial pol);
		Node(PolWithDegree pol);
		Node(PolWithString pol);
		~Node();
		friend class Queue;

	private:
		Polynomial* object;
		Node* next;
		Node* prev;
	};

	int _size;
	Node* front;
	Node* rear;
};

Queue::Queue()
{
	this->_size = 0;
	this->front = NULL;
	this->rear = NULL;
}

void Queue::push(Polynomial pol)
{
	Node* temp = new Node(pol);
	this->_size++;
	if (this->empty()) {
		this->front = temp;
		this->rear = temp;
	}
	temp->prev = this->rear;
	temp->next = this->front;
	this->rear = temp;
	this->rear->prev->next = temp;
	this->rear->next->prev = temp;
}

void Queue::push(PolWithDegree pol)
{
	Node* temp = new Node(pol);
	this->_size++;
	if (this->empty()) {
		this->front = temp;
		this->rear = temp;
	}
	temp->prev = this->rear;
	temp->next = this->front;
	this->rear = temp;
	this->rear->prev->next = temp;
	this->rear->next->prev = temp;
}

void Queue::push(PolWithString pol)
{
	Node* temp = new Node(pol);
	this->_size++;
	if (this->empty()) {
		this->front = temp;
		this->rear = temp;
	}
	temp->prev = this->rear;
	temp->next = this->front;
	this->rear = temp;
	this->rear->prev->next = temp;
	this->rear->next->prev = temp;
}

Polynomial* Queue::pop()
{
	try {
		if (this->empty()) {
			throw exception("Queue is empty");
		}
		
		Polynomial* temp = this->front->object;
		this->front->object = NULL;
		if (this->front == this->rear) {
			delete this->front;
			this->front = NULL;
			this->rear = NULL;
		}
		else {
			this->front->next->prev = this->rear;
			this->rear->next = this->front->next;
			delete this->front;
			this->front = this->rear->next;
		}
		this->_size--;
		return temp;
	}
	catch (const exception ex) {
		cerr << ex.what() << endl;
		exit(1);
	}
}

bool Queue::empty()
{
	if (this->front == NULL) {
		return true;
	}
	else {
		return false;
	}
}

int Queue::size()
{
	return this->_size;
}

char* Queue::show()
{
	if (!this->empty()) {
		Node* p = this->front;
		int size = 0;
		do {
			size += p->object->getSize();
			p = p->next;
		} while (p->prev != this->rear);
		p = this->front;
		char* str = new char[size];
		sprintf(str, "");
		do {
			strcat(str, p->object->toString());
			strcat(str, "\n");
			p = p->next;
		} while (p->prev != this->rear);
		return str;
	}
	else {
		char* str = new char[1];
		str[0] = '\0';
		return str;
	}
}

Queue::~Queue() {
	while (!this->empty()) {
		this->pop();
	}
}

	Queue::Node::Node()
	{
		this->object = new Polynomial();
		this->next = NULL;
		this->prev = NULL;
	}

	Queue::Node::Node(PolWithDegree pol)
	{
		this->object = new PolWithDegree(pol);
		this->next = NULL;
		this->prev = NULL;
	}

	Queue::Node::Node(PolWithString pol)
	{
		this->object = new PolWithString(pol);
		this->next = NULL;
		this->prev = NULL;
	}

	Queue::Node::Node(Polynomial pol)
	{
		this->object = new Polynomial(pol);
		this->next = NULL;
		this->prev = NULL;
	}

	Queue::Node::~Node()
	{
		delete this->object;
	}