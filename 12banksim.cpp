// 12banksim.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Queue.h"

const int MIN_PER_HR = 60;//每小时60分钟

bool newcustomer(double x);

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios_base;

    std::srand(std::time(0));// initizlizing of rand()

    /*
    Queue line(3);
    Item temp;
    temp.set(1);
    line.enqueue(temp);
    temp.set(2);
    line.enqueue(temp);
    temp.set(3);
    line.enqueue(temp);
    line.enqueue(temp);

    //line.dequeue(temp);
    //line.dequeue(temp);
    //cout << temp.when()<<'\n';
    cout << "SHOW LINE" << '\n';
    line.show();
*/
    
    cout << "Case Study: Band of Heather Automatic Teller\n";
    cout << "Enter maximum size of queue: ";
    int qs;
    cin >> qs;
    Queue line(qs);//创建队列

    cout << "Enter the number of simulation hours: ";
    int hours;
    cin >> hours;

    long cyclelimit = MIN_PER_HR * hours;

    cout << "Enter the average number of customers per hours: ";
    double perhour;
    cin >> perhour;
    double min_per_cust;
    min_per_cust = MIN_PER_HR/ perhour; //客户平均到达间隔时间单位分钟

    Item temp;

    long turnaways = 0; //因队列已满而被拒之门外的人次
    long customers = 0;  //客人来的人数
    long served = 0; //服务人数
    long sum_line = 0; //累积队列长度
    int wait_time = 0;//到柜员机的时间
    long line_wait = 0;//累积时间

    // running the simulation
    //每次循环代表一分钟时间
    for (int cycle = 0; cycle < cyclelimit; cycle++)
    {
        if (newcustomer(min_per_cust))//每分钟判断有无新顾客
        {
            if (line.isfull())
                turnaways++;  //顾客因队列满了而离开的人次
            else
            {
                customers++;  //加入队列的顾客
                temp.set(cycle); //设置到达时间与随机的办理时间
                line.enqueue(temp);  
            }
        }
        if (wait_time <= 0 && !line.isempty())//判断有业务办理完成，完成开始办理下一个
        {
            line.dequeue(temp); //弹出第一个办理好的人
            wait_time = temp.ptime();//
            line_wait += cycle - temp.when();
            served++;  //办理人数
        }
        if (wait_time>0)
            wait_time--;
        sum_line += line.queuecount();
    }


    //reporting results
    if (customers > 0)
    {
        cout << "customers accepted: " << customers << endl;
        cout << " customers served: " << served << endl;
        cout << "    turnaways: " << turnaways << endl;
        cout << "average queue size: ";
        cout.precision(2);
        cout.setf(ios_base::fixed, ios_base::floatfield);
        cout << (double)sum_line / cyclelimit << endl;
        cout << "average wait time: "
            << (double)line_wait / served << " minutes\n";
    }
    else
        cout << "No customers!\n";
    cout << "Done!\n";
    

    return 0;

}

bool newcustomer(double x)
{//模拟新顾客是否到来
    double a = std::rand() * x / RAND_MAX ;
    return a<1;
}
