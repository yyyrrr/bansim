#pragma once

class Customer
{
private:
	long arrive; //消费者到达时间
	int processtime; //办理业务的时间
public:
	Customer() { arrive = processtime = 0; }
	void set(long when);
	long when() const { return arrive; }
	int ptime() const { return processtime; }
};

typedef Customer Item; //给类换个别名，这个可以复用代码


class Queue
{
private:
	enum {Q_SIZE=10};//为什么这里用枚举而不是静态类型
	struct Node
	{
		Item item;
		struct Node* next;
	};
private:
	Node* front;//第一个项目
	Node* rear; //最后一个项目
	int items; //项目总数
	const int qsize;
public: 
	Queue(int qs=Q_SIZE);//构造函数
	~Queue();//析构函数
	//Queue(const Queue& q) :qsize(0) {} //复制构造函数定义
	//Queue & operator=(const Queue& q) { return*this; }//赋值运算符重载

	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item & item);
	bool dequeue(Item & item);

	void show() const;//展示整个队列
};



