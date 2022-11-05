//#include <iostream>
//using namespace std;

//void Func(char str[100])
//{
//	cout<<str<<endl;
//	cout<<sizeof(str)<<endl;
//}
//
//int main()
//{
//	char str[] = "KYKY SEM Team";
//	char *p = str;
//
//	cout<<sizeof(str)<<endl;
//	cout<<sizeof(p)<<endl;
//	Func(str);
//	return 0;
//}


//struct stu{
//	int NO;
//	char gender;
//	int age;
//	struct stu * next;
//}*ListNode;
//
//stu group[10] = {{1001,'M',18},{1002,'F',18},{1003,'F',20},{1004,'F',21},{1005,'M',19},{1006,'F',17},{1007,'F',19},{1008,'F',17},{1009,'M',21},{1010,'F',21}};
//
//
//struct stu *creatlist(stu* group,int nCount)
//{
//	//header为头结点，p为前一结点，s为当前结点
//	struct stu *header,*p,*s;
//	header = (struct stu *)malloc(sizeof(struct stu));
//	header->next = NULL;
//	p = header;
//	for(int i=0;i < nCount;i++)
//	{  
//		s = (struct stu *)malloc(sizeof(struct stu));
//		stu e = group[i];
//		s->gender = e.gender;
//		s->NO = e.NO;
//		s->age = e.age;
//		p->next = s;
//		s->next = NULL;
//		p = s;
//	}
//	return header;
//}
//
//
//stu *removeElement(stu *head, int val)
//{
//	if (head == NULL) return head;
//	stu* prev = head;
//	stu *p = prev->next;
//	while (p != NULL)
//	{
//		if (p->age >= val)
//		{
//			stu *temp = p;
//			p = p->next;
//			prev->next = p;
//			free(temp);
//			temp = NULL;
//		}
//		else
//		{
//			prev = p;
//			p = p->next;
//			prev->next = p;
//		}
//	}
//	return head;
//}
//
//
//void display(struct stu *head)
//{
//	if(!head) return;
//
//	stu* s = head->next;
//	while(s!=NULL)
//	{
//		printf("%c %d %d \n",s->gender,s->NO,s->age);
//		s = s->next;
//	}
//}
//
//
//int main()
//{
//	stu* head = creatlist(group,10);
//	display(head);
//
//	printf("\r\n\r\n");
//
//	head = removeElement(head,19);
//	display(head);
//	return 0;
//}



//int main()
//{
//	int x = 10,y=25;
//	x = y-- + x++;
//	y = ++y + ++x;
//	printf("%d, %d \n",x,y);
//	return 0;
//}


//void GetMemory(char *p)
//{
//	p = (char *)malloc(100);
//	strcat(p, "SEM Team  ");
//}
//
//
//void Test(void)
//{
//	char str[100] = "KYKY ";
//	GetMemory(str);
//	strcat(str, "hello world");
//	cout<<str<<endl;
//}
//
//
//int main()
//{
//	Test();
//	return 0;
//}

//#include "C.h"
//
//int main()
//{
//	//C obj1;
//	//A& oA1 = obj1.GetA();
//	//oA1.Display();
//
//	//cout<<"\r\n--------------------------\r\n"<<endl;
//	//C obj2;
//	//obj2 = obj1;
//	//A& oA2 = obj2.GetA();
//	//oA2.Display();
//
//	A objA;
//	objA.Display();
//
//	return 0;
//}

//class A
//{
//public:
//	A(){m_nA++;cout<<"A()"<<endl;}
//	~A(){cout<<"~A()"<<endl;}
//	A(const A& obj){m_nA++;cout<<"A() Copy" <<endl;}
//	A& operator=(const A &obj){m_nA++;cout<<"A() =" <<endl;}
//
//	int GetNO(){return m_nA;}
//public:
//	static int m_nA;
//};
//
//int A::m_nA = 0;
//
//class B
//{
//public:
//	B(){m_nB++;cout<<"B()"<<endl;}
//	~B(){cout<<"~B()"<<endl;}
//	B(const B& obj){m_nB++;cout<<"B() Copy" <<endl;}
//	B& operator=(const B &obj){m_nB++;cout<<"B() =" <<endl;}
//	int GetNO(){return m_nB;}
//
//public:
//	static int m_nB;
//};
//
//int B::m_nB = 10;
//
//class C
//{
//public:
//	C(){cout<<"C()" <<endl;}
//	~C(){cout<<"~C()" <<endl;}
//	C(const C& obj){cout<<"C() Copy" <<endl;}
//	C& operator=(const C &obj){cout<<"C() =" <<endl;}
//	void Display()
//	{
//		char sz[64] = {0};
//		sprintf_s(sz,64,"%d,%d",m_A.GetNO(),m_B.GetNO());
//		cout<<sz<<endl;
//	}
//
//public:
//	B m_B;
//	A m_A;
//};


//int main()
//{
//	C ObjC1;
//	ObjC1.Display();
//
//	C ObjC2 = ObjC1;
//	ObjC2.Display();
//	return 0;
//}


#include <iostream>
using namespace std;

//class B
//{
//public:
//	B()
//	{
//		cout<<"B()"<<endl;
//		for (int i = 0; i < 64; i++)
//		{
//			b[i] = i;
//		}
//	}
//
//	~B(){cout<<"~B()"<<endl;}
//
//	B(const B& obj){cout<<"B() Copy" <<endl;}
//	B& operator=(const B &obj){cout<<"B() =" <<endl;}
//
//	void Display()
//	{
//		int sum = 0;
//		for (int i = 0;i++;i<64)
//		{
//			sum += b[i];
//		}
//
//		cout <<"B sum = "<<sum <<endl;
//	}
//
//protected:
//	int b[64];
//};
//
//class D1:public B
//{
//public:
//	D1()
//	{
//		cout<<"D1()"<<endl;
//		for (int i = 0; i < 64; i++)
//		{
//			d1[i] = b[i] + 10;
//		}
//
//	}
//
//	~D1(){cout<<"~D1()"<<endl;}
//	D1(const D1& obj){cout<<"D1() Copy" <<endl;}
//	D1& operator=(const D1 &obj){cout<<"D1() =" <<endl; return *this;}
//
//	void Display()
//	{
//		int sum = 0;
//		for (int i = 0;i++;i<64)
//		{
//			sum += d1[i];
//		}
//
//		cout <<"D1 sum = "<<sum <<endl;
//	}
//
//protected:
//	int d1[64];
//};
//
//
//class D2:public D1
//{
//public:
//	D2()
//	{
//		cout<<"D2()"<<endl;
//		for (int i = 0; i < 64; i++)
//		{
//			d1[i] = b[i] + 20;
//		}
//	}
//
//	~D2(){cout<<"~D2()"<<endl;}
//	D2(const D2& obj){cout<<"D2() Copy" <<endl;}
//	D2& operator=(const D2 &obj){cout<<"D2() =" <<endl; return *this;}
//
//	void Display()
//	{
//		int sum = 0;
//		for (int i = 0;i++;i<64)
//		{
//			sum += d1[i];
//		}
//
//		cout <<"D2 sum = "<<sum <<endl;
//	}
//};
//
//
//class C
//{
//public:
//    C(){cout<<"C()"<<endl;}
//	~C(){cout<<"~C()"<<endl;}
//
//	D2& GetD(){return m_d;}
//
//	void Display(D2 o)
//	{
//		m_d = o;
//		o.Display();
//		return;
//	}
//
//protected:
//	D2 m_d;
//};
//
//
//int main()
//{
//	D2 oD;
//	C oC;
//	oC.Display(oD);
//	return 0;
//}



struct stu{
	int NO;
	char gender;
	int age;
	struct stu * next;
}*ListNode;

stu group[10] = {{1001,'M',18},{1002,'F',18},{1003,'F',20},{1004,'F',21},{1005,'M',19},{1006,'F',17},{1007,'F',19},{1008,'F',17},{1009,'M',21},{1010,'F',21}};


struct stu *creatlist(stu* group,int nCount)
{
	//header为头结点，p为前一结点，s为当前结点
	struct stu *header,*p,*s;
	header = (struct stu *)malloc(sizeof(struct stu));
	header->next = NULL;
	p = header;
	for(int i=0;i < nCount;i++)
	{  
		s = (struct stu *)malloc(sizeof(struct stu));
		stu e = group[i];
		s->gender = e.gender;
		s->NO = e.NO;
		s->age = e.age;
		p->next = s;
		s->next = NULL;
		p = s;
	}
	return header;
}


//stu *removeElement(stu *head, int val)
//{
//	if (head == NULL) return head;
//	stu* prev = head;
//	stu *p = prev->next;
//	while (p != NULL)
//	{
//		if (p->age >= val)
//		{
//			stu *temp = p;
//			p = p->next;
//			prev->next = p;
//			free(temp);
//			temp = NULL;
//		}
//		else
//		{
//			prev = p;
//			p = p->next;
//			prev->next = p;
//		}
//	}
//	return head;
//}


//stu *removeElement(stu *head, int val)
//{
//	if (head == NULL) return head;
//	stu* prev = head;
//	stu *p = prev->next;
//	while (p != NULL)
//	{
//		if (p->age >= val)
//		{
//			stu *temp = p;
//			p = p->next;
//			prev->next = p;
//			free(temp);
//			temp = NULL;
//		}
//		else
//		{
//			prev = p;
//			p = p->next;
//			prev->next = p;
//		}
//	}
//	return head;
//}


//
//stu *removeElement(stu *head, int val)
//{
//	if (head == NULL) return head;
//	stu* p = head;
//	stu *q= head->next;
//	while (q != NULL)
//	{
//		if (q->age >= val)
//		{
//			p->next = q->next;
//			delete q;
//			q = p->next;
//		}
//		else
//		{
//			p = p->next;
//			q = q->next;
//		}
//	}
//	return head;
//}

stu *removeElement(stu *head, int val)
{
	if (head == NULL)
	{
		return NULL;
	}
	else if (head->age >= val)
	{
		return removeElement(head->next,val);
	}
	else
	{
		head->next = removeElement(head->next,val);
		return head;
	}

	return head;
}


void display(struct stu *head)
{
	if(!head) return;

	stu* s = head->next;
	while(s!=NULL)
	{
		printf("%c %d %d \n",s->gender,s->NO,s->age);
		s = s->next;
	}
}


//int main()
//{
//	stu* head = creatlist(group,10);
//	display(head);
//
//	printf("\r\n\r\n");
//
//	head = removeElement(head,19);
//	display(head);
//	return 0;
//}

int main()
{
	char sz[64] = {0};
	//sprintf_s(sz,"%c",'\\');
	//sprintf_s(sz,"%cu00b5m",'\\');
	sprintf( sz, "%cu00b5m", '\\' );
	cout <<sz<<endl;
	return 0;
}