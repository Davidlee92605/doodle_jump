
#include <iostream.h>
class Time
{ private:
int hour,minute,second;
public:
Time(int hr=0, int min=0,int sec=0)
{ hour=hr; minute=min; second=sec; }
void print()
{ cout << hour << ":"
<< minute << ":"
<< second << endl;}
};
void main()
{Time t1,t2(2),t3(21,34),t4(12,25,42);
t1.print();
t2.print();
t3.print();
t4.print();
}
