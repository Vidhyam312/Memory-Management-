/*
C++ Project
Vidhya M
1NH17CS428
NEW HORIZON
CS DEPT
*/

#include<iostream.h>
#include<stdlib.h>
#include<conio.h>
//using namespace std;

class data              //base class
{
    protected:
    int mem[10],processes[10],n1,n2,flags[10],allocation[10];
public:
data()              // constructor to initialize predefined values
    {
        int i,j;
	for(i=0;i < 10;i++)
	{
		flags[i]=0;
		allocation[i]=-1;
	}
    }
  void display()
    {
        int i;
        cout<<"\nPartiton   Size   Process no.   Size";
	for(i=0;i < n1;i++)
	{
		cout<<"\n   "<<i<<"       "<<mem[i]<<"        ";
		if(flags[i]==1)
			cout<<allocation[i]<<"          "<<processes[allocation[i]];
		else
        cout<<"NA";

	}
    }
   void copy(data d)
    {
        int i;
        n1=d.n1;
        n2=d.n2;
		for(i=0;i < n1;i++)
                mem[i]=d.mem[i];

	for(i=0;i < n2;i++)
            processes[i]=d.processes[i];

    }
    friend data getdata(data d);                        //friend function decleration
virtual void calc()
{
	cout<<"Vitrual class";
}


};

data getdata(data d)                                 //friend function
    {
clrscr(); 
       int i,j;
    cout<<"\nEnter no. of memory blocks: ";
getch();	
cin>>d.n1;

	for(i=0;i < d.n1;i++){
        cout<<"Enter size of block "<<i<<" : ";
        cin>>d.mem[i];
	}
	cout<<"\nEnter no. of processes :";
	cin>>d.n2;
	for(i=0;i < d.n2;i++){
        cout<<"Enter size of process "<<i<<" : ";
		cin>>d.processes[i];
    }
    return d;
    }


class firstfit :public data
{
    public:
    void calc()
    {
       int i,j;
	for(i=0;i < n2;i++)         //loop for each process
		for(j=0;j < n1;j++)         //loop for each memory block
			if(flags[j]==0 && mem[j]>=processes[i])
			{
				allocation[j]=i;
				flags[j]=1;
				break;
			}
    }
};



class bestfit :public data
{
    int i,j,smallest;
public:
    void calc()
    {
	for(i=0;i < n2;i++)             //loop for each process
	{
		smallest=-1;
		for(j=0;j < n1;j++)             //loop to find if process can fint n which block
			if(flags[j]==0 && mem[j] >= processes[i])
			{
				smallest=j;
				break;
			}
		for(;j < n1;j++)                   //loop to find the smallest block that can be allocated
			if(flags[j]==0 && mem[j] >= processes[i] && mem[j] < mem[smallest])
				smallest=j;
		if(smallest!=-1)
		{
			allocation[smallest]=i;
			flags[smallest]=1;
		}
	}
    }
};



class worstfit :public data
{
    int i,j,big;
public:
    void calc()
    {
	for(i=0;i < n2;i++)                 //loop for each process
	{
		big=-1;
		for(j=0;j < n1;j++)                    //loop to find if process can find n which block
			if(flags[j]==0 && mem[j] >= processes[i])
			{
				big=j;
				break;
			}
		for(;j < n1;j++)                     //loop to find the biggest block that can be allocated
			if(flags[j]==0 && mem[j] >= processes[i] && mem[j] > mem[big])
				big=j;
		if(big!=-1)
		{
			allocation[big]=i;
			flags[big]=1;
		}
	}
    }
};



class nextfit :public data
{
public:
    void calc()
    {
        int i,j;
        int k=0;//to remember the last position
        int c=0;//to keep the count
	for(i=0;i < n2;i++){        //loop for each process
                if(k==n1)
                {
                    k=0;
                }
                c=0;
		for(j=k;j < n1;j++){            //loop for each block
                c++;
			if(flags[j]==0 && mem[j]>=processes[i])
			{
				allocation[j]=i;
				flags[j]=1;
				k=j+1;
				break;
			}//if loop
		if(j==n1)
		{
		    j=0;
		}
		if(c==n1)
        {
            break;
        }
		}//j loop

		}//i loop
    }
};




int main()
{
    data d,*p;
    d=getdata(d);
    bestfit b;
    firstfit f;
    worstfit w;
    	nextfit m;
    int c,flag=0;
while(flag==0)
{
    cout<<"\n\n\nEnter\n   1 for first fit\n   2 for best fit\n   3 for worst fit\n   4 for next fit\n   5 to exit\n                  :";
    cin>>c;
    switch(c)
    {
case 1: clrscr();
    cout<<"\n\n*--------------------------------FIRST FIT--------------------------------*";
	f.copy(d);
	//f.calc();
	p=&f;
	p->calc();
	f.display();
	break;
case 2: clrscr();
    cout<<"\n\n*--------------------------------BEST FIT--------------------------------*";
	b.copy(d);
	//b.calc();
	p=&b;
	p->calc();
	b.display();
    break;
case 3:  clrscr();
    cout<<"\n\n*--------------------------------WORST FIT--------------------------------*";
	w.copy(d);
	//w.calc();
	p=&w;
	p->calc();
	w.display();
	break;
case 4: clrscr();
    cout<<"\n\n*--------------------------------NEXT FIT--------------------------------*";
	m.copy(d);
	//m.calc();
	p=&m;
	p->calc();
	m.display();
    break;

case 5: clrscr();
    cout<<"\n\nExiting.........\n";
    flag=1;
    break;
default:
    cout<<"Wrong choice try again\n";
    break;

}
}
getch();
return 0;
}
