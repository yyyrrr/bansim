#include "Queue.h"
#include <iostream>
#include <cstddef>
#include <cstdlib>

Queue::Queue(int qs):qsize(qs)
{
	front = rear = NULL;
	items = 0;
}

Queue::~Queue()
{
	Node* temp;
	while (front !=NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

bool Queue::isempty() const
{
	return items==0;
}

bool Queue::isfull() const
{
	return items==qsize;
}

int Queue::queuecount() const
{
	return items;
}

bool Queue::enqueue(const Item & item)
{
	if (isfull())
	{
		std::cout << "Queue is full" << '\n';
		return false;
	}
		
	Node* add = new Node;
	add->item = item;
	add->next = NULL;
	items++;
	if (front == NULL)
		front = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

bool Queue::dequeue(Item & item)
{
	if(front==NULL)
		return false;
	item = front->item;
	items--;
	Node* temp = front;
	front = front->next;
	delete temp;
	if (items = 0)
		rear = NULL;
	return true;
}

void Queue::show() const
{
	Node *p;
	p = front;
	while (p)
	{
		std::cout << p->item.when() << '\n';
		p = p->next;
	}
}

void Customer::set(long when)
{
	processtime = std::rand() % 3 + 3;//每个顾客的消耗时间2-4分钟
	arrive = when;
}
