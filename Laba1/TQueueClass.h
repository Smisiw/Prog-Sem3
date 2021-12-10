#pragma once
#include "Polynomial.h"
#include "PolWithDegree.h"
#include "PolWithString.h"
#include "MyFunctions.hpp"
#include <string>

template <class T> class QueueT
{
public:
	QueueT();
	~QueueT();
	void push(T obj);
	T* pop();
	char* show();
	bool empty();
	int size();

private:
	class Node
	{
	public:
		Node();
		Node(T obj);
		~Node();
		friend class QueueT;

	private:
		T* object;
		Node* next;
		Node* prev;
	};

	int _size;
	Node* front;
	Node* rear;
};

template <class T> QueueT<T>::QueueT()
{
	this->_size = 0;
	this->front = NULL;
	this->rear = NULL;
}

template <class T> void QueueT<T>::push(T obj)
{
	Node* temp = new Node(obj);
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

template <class T> T* QueueT<T>::pop()
{
	try {
		if (this->empty()) {
			throw exception("Queue is empty");
		}
		
		T* temp = this->front->object;
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

template <class T> bool QueueT<T>::empty()
{
	if (this->front == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template <class T> int QueueT<T>::size()
{
	return this->_size;
}

template <class T> char* QueueT<T>::show()
{
	if (!this->empty()) {
		Node* p = this->front;
		int size = 0;
		do {
			size += getLengthOfInt(*p->object);
			p = p->next;
		} while (p->prev != this->rear);
		p = this->front;
		char* str = new char[size];
		sprintf(str, "");
		do {
			char* strint = new char[getLengthOfInt(*p->object)];
			snprintf(strint,getLengthOfInt(*p->object)+1, "%d", *p->object);
			strcat(str, strint);
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

template <class T> QueueT<T>::~QueueT() {
	while (!this->empty()) {
		this->pop();
	}
}

	template <class T> QueueT<T>::Node::Node()
	{
		this->object = new T();
		this->next = NULL;
		this->prev = NULL;
	}

	template <class T> QueueT<T>::Node::Node(T obj)
	{
		this->object = new T(obj);
		this->next = NULL;
		this->prev = NULL;
	}

	template <class T> QueueT<T>::Node::~Node()
	{
		delete this->object;
	}

	//Специализация
	template <> class QueueT<Polynomial>
	{
	public:
		QueueT();
		~QueueT();
		void push(Polynomial obj);
		Polynomial* pop();
		char* show();
		bool empty();
		int size();

	private:
		class Node
		{
		public:
			Node();
			Node(Polynomial obj);
			~Node();
			friend class QueueT;

		private:
			Polynomial* object;
			Node* next;
			Node* prev;
		};

		int _size;
		Node* front;
		Node* rear;
	};

	QueueT<Polynomial>::QueueT()
	{
		this->_size = 0;
		this->front = NULL;
		this->rear = NULL;
	}

	void QueueT<Polynomial>::push(Polynomial obj)
	{
		Node* temp = new Node(obj);
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

	Polynomial* QueueT<Polynomial>::pop()
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

	bool QueueT<Polynomial>::empty()
	{
		if (this->front == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	int QueueT<Polynomial>::size()
	{
		return this->_size;
	}

	char* QueueT<Polynomial>::show()
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

	QueueT<Polynomial>::~QueueT() {
		while (!this->empty()) {
			this->pop();
		}
	}

	QueueT<Polynomial>::Node::Node()
	{
		this->object = new Polynomial();
		this->next = NULL;
		this->prev = NULL;
	}

	QueueT<Polynomial>::Node::Node(Polynomial obj)
	{
		this->object = new Polynomial(obj);
		this->next = NULL;
		this->prev = NULL;
	}

	QueueT<Polynomial>::Node::~Node()
	{
		delete this->object;
	}