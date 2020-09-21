#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
int q;
struct date
{int dd,mm,yy;
};

int tries=0;

class medicine
 {char brandname[120],medname[70],composition[120],category[100];
	date dexpiry;
	int rackno,qty,unit;
	float price;

	public:
		int checkrackno(char medi[34])//accessor for rack number
		{
		 return strcmp(medname,medi);
		}
		char *getmedname()           //accessor function for medicine name
		 { return medname;}

		void deletemed();            //delete details of medicines which are either expiry or have been banned etc....
		void newstock();             //enter details of new stock of medicine
		void outofstock();           //removing medicines from database which have quantity=0
		void modify();               //edit details of medicines
		void alldisplay();           //display all details of medicine
		void userdisplay();          //user-friendly display
		void billdisplay(int);				 //short display during billing
		void input();
	void output()
	{
			 cout<<endl<<brandname<<" "<<medname<<" "<<composition<<" "<<category<<" "<<rackno<<" "<<qty<<" "<<unit<<" "<<price<<" "<<dexpiry.dd<<" "<<dexpiry.mm<<" "<<dexpiry.yy<<endl;
			 }
	}m1;


void adminpass()                 //enter password to open admin menu
{
void adminenter();
 char password[25];
 cout<<"\n___Got itchy feet?Try a cold compress for quick relief. Aloe vera can also come to your rescue!___\nEnter Password\n";
 cin>>password;
 if(strcmpi(password,"relicare")==0)
	{cout<< "\nPassword Authenticated"<<endl<<"Welcome\n";
	 adminenter();
	}
 else
 {if(tries>=2)
	{cout<<"Wrong Password\nNO MORE TRIES :(";
	 getch();
	 exit(0);}
	else
	cout<<"Wrong Password!\n1.Try Again\n2.Exit\n";
	int c1;

	cin>>c1;
	 if(c1==1)
		{tries=tries+1;
		adminpass();
		}
	 else if(c1==2)
				 return ;
	 else
		{cout<<"Invalid Choice\nEnter Valid Choice";
		 adminpass();
		 }
	 }
	}
void adminenter()                //access admin's menu
 {
 void alldisplay();
 cout<<"\nWhat do you wish to do?"<<endl;
	cout<<"1.Add a medicine\n2.Delete a record\n3.Modify medicine\n4.Display all details of a medicine\n5.View the medicines that are out of stock\n6.Exit\n";
	medicine m;
	int c2;
while(c2)
{
cin>>c2;
if(c2==1)
	 m.input();
	else if(c2==2)
	 m.deletemed();
	else if(c2==3)
	 m.modify();
	else if(c2==4)
	 alldisplay();
	else if(c2==5)
	 m.outofstock();
	 else if(c2==6)
	 break;
	else
	 cout<<"Invalid Choice\nEnter Valid Choice";
		adminenter();
 break;}
	}

 void medicine::newstock()
	{cout<<"Enter brandname\n";
	 gets(brandname);
	 cout<<"Enter medicine name\n";
	 gets(medname);
	 cout<<"Enter composition\n";
	 gets(composition);
	 cout<<"Enter category\n";
	 gets(category);
	 cout<<"Enter rack number\n";
	 cin>>rackno;
	 cout<<"Enter quantity\n";
	 cin>>qty;
	 cout<<"Enter unit\n";
	 cin>>unit;
	 cout<<"Enter price\n";
	 cin>>price;
	 cout<<"Enter date of expiry in (dd-mm-yyyy)\n";
	 cin>>dexpiry.dd>>dexpiry.mm>>dexpiry.yy;

}
	 void medicine::input()
{  medicine m2;
		m2.newstock();
		ofstream f1("medicine.dat",ios::binary|ios::app);
		f1.write((char*)&m2,sizeof(medicine));
		f1.close();
}


 void medicine::deletemed()      //deletion from database
	{ char name[40];//name of medicine to deleted
	 medicine m3;
		cout<<"Enter name of medicine which is to be deleted";
		gets(name);

		ofstream f2;
		f2.open("temp.dat",ios::binary);
		 ifstream f3;
		f3.open("medicine.dat",ios::binary);
			while(f3.read((char*)&m3,sizeof(medicine)))
{
			if(strcmp(name,m3.getmedname())!=0)
			 {f2.write((char*)&m3,sizeof(medicine));
			 }
		 }
	 f3.close();
	 f2.close();
	 remove("medicine.dat");
	 rename("temp.dat","medicine.dat");
	 cout<<name<<"deleted";
	}

	void medicine::outofstock()
{
		int flag=0;
			 ifstream f6;
	medicine m8;
	f6.open("medicine.dat",ios::binary);
	while(!f6.eof())
	 { f6.read((char*)&m8,sizeof(medicine));
	 if (m8.qty==0)
	{          flag=1;
		cout<<m8.medname<<" is out of stock from rack number "<<m8.rackno;
		}
		}
			f6.close();
if(flag==0)
cout<<"\nCongratulations! All medicines are in stock :)\n";
		}


void alldisplay()
 {
		 medicine m2;
	ifstream k1;
	k1.open("medicine.dat",ios::binary);
	char name[80];
	cout<<"Enter Medicine Name Whose Details Need To Be Displayed";
	gets(name);
while(k1.read((char*)&m2,sizeof(medicine)))
{   if(strcmpi(name,m2.getmedname())==0 )
		{
	m2.output();

	}
}
 k1.close();

 }

 void medicine::modify()
 {fstream f4;
	 f4.open("medicine.dat",ios::binary|ios::in|ios::out);
	medicine m4,m5;
	 m5.newstock();
		while(!f4.eof())
		 {int a=f4.tellg();
			f4.read((char*)&m4,sizeof(medicine));
			if(strcmpi(m4.medname,m5.medname)==0)
			 {f4.seekp(a,ios::beg);
	f4.write((char*)&m5,sizeof(medicine));
	break;
			 }
		 }
	 f4.close();
	}

 void medicine::userdisplay()
	{cout<<"\nMedicine Name\t"<<medname<<"\nRack Number\t"<<rackno<<"\nBest Before\t"<<dexpiry.dd<<" - "<<dexpiry.mm<<" - "<<dexpiry.yy<<"\nPrice\t"<<price<<"\nQuantity\t"<<qty;
 }

 void medicine::billdisplay(int q)
	{
	m1.qty=m1.qty-1;
	cout<<"\nMedicine Name\t"<<medname<<"\nPrice\t"<<price*q;
fstream f7;
	 f7.open("medicine.dat",ios::binary|ios::in|ios::out);
	medicine m0;
			while(!f7.eof())
		 {int a=f7.tellg();
			f7.read((char*)&m0,sizeof(medicine));
			if(strcmpi(m0.medname,medname)==0)
			 {f7.seekp(a,ios::beg);
	f7.write((char*)&m1,sizeof(medicine));
	break;
			 }
		 }
	 f7.close();
	}

int purchase()
 {
 medicine m6;
	char mediname[50];
	cout<<"\nEnter Medicine Name";
	gets(mediname);
	ifstream f5;
	f5.open("medicine.dat",ios::binary);
	int f=0;
	while(f5.read((char*)&m6,sizeof(medicine)))
{
//cout<<"inside while";
if(m6.checkrackno(mediname)==0)
		{ f=1;
		m6.userdisplay();
		}  }
		f5.close();
	//		  cout<<"outside";

	 if(f==0)
		{cout<<"\nNO RECORD FOUND\n1.Enter Medicine Name again\n2.Exit";
		 int c3;
		 cin>>c3;
		 if(c3==1)
			purchase();
		if(c3==2)
{
			return 0;}
		 else
			cout<<"\nInvalid Indirection";     }
return 0;
}

class customer
{char customername[50];
 unsigned long long mobileno;
 date dob;
 char doctorname[80];
 public:
	date calage(date);


 void customerinput()
 {cout<<"Enter Customer Name";
	 gets(customername);
	 cout<<"Enter Customer's Mobile Number";
	 cin>>mobileno;
	 cout<<"Enter Doctor's Name";
	 gets(doctorname);
	 cout<<"Enter Date of Birth (dd-mm-yyyy)";
	 cin>>dob.dd>>dob.mm>>dob.yy;
 }
 void customerdisplay()
 {cout<<"\nCustomer Name:\t" <<customername;
	 cout<<"\nMobile Number:\t"<<mobileno;
 }
}customer;

 void addtobill(q)
	 {
		m1.billdisplay(q);
	 }

void billing()
 {      customer.customerinput();
	cout<<"Enter Today's Date(dd-mm-yyyy)";
	date dtoday;
	cin>>dtoday.dd>>dtoday.mm>>dtoday.yy;

		customer.customerdisplay();
		cout<<"\nAge:\t";
		customer.calage(dtoday);
 addtobill(q);
}

 void searchmedicine()
 { medicine m7;
 cout<<"\n___Want to curb that everlasting cough?Simple.Indulge in a square or two of dark chocolate!___\nWhat  medicines do you require?";
 char mname[50];
 gets(mname);
 ifstream f6;
 f6.open("medicine.dat",ios::binary);
 while(!f6.eof())
	{f6.read((char*)&m7,sizeof(medicine));
		if(strcmpi(mname,m7.getmedname())==0)
		 {	 cout<<m7.getmedname()<<"FOUND\n";
				m1=m7;
				cout<<"Enter qty";
				cin>>q;
				break;
		 }
			}
}

void bill()
{
searchmedicine();
 cout<<"\n1. Want another medicine?\n2. Billing\n3. Exit\n";
 int c4;

 cin>>c4;
while(c4)
{
 if(c4==1)

searchmedicine();

 else if(c4==2)

	billing();
else  if(c4==3)

 return;
 cout<<"\n1. Want another medicine?\n2. Billing\n3. Exit\n";
 cin>>c4;
}
}

void main()
{clrscr();
 int choice;
cout<<"Welcome to PHARMA medicos\n";
 cout<<"1.\Admin\n2.User\n3.Exit\n";
 cin>>choice;
while(choice)
	{

	if(choice==1)
		{
		 adminpass();
		}
else if(choice==2)

 {int c;
 cout<<"\n1.Purchase\n2.Billing\n3.Exit";
 cin>>c;
 while (c)
 {
	if(c==1)
	{ int h=	purchase();
       }
 else if(c==2)
	bill();
 else if(c==3)
	break;
 //	exit(0);
 else
 { cout<<"INVALID CHOICE\nEnter choice again";
       //	 cin>>c;
 }
 cout<<"\n1.Purchase\n2.Billing\n3.Exit";
 cin>>c;
 }

}

else if (choice== 3)
exit(0);
else
 { cout<<"INVALID CHOICE /n Enter choice again";
	 cin>>choice;
}
 cout<<"Welcome to PHARMA medicos\n";
 cout<<"1.\Admin\n2.User\n3.Exit\n";
 cin>>choice;
}
getch();
}

date customer::calage(date dtoday)
	{date age;
	 age.yy=dtoday.yy-dob.yy;
	 if(dtoday.mm>dob.mm)
		age.mm=dtoday.mm-dob.mm;
	 else
	 {
		age.mm=12+(dtoday.mm-dob.mm);
		age.yy=age.yy-1;
	 }
	if(dtoday.dd>dob.dd)
	 age.dd=dtoday.dd-dob.dd;
	else
	 {
		if ((age.mm)==1||(age.mm)==3||(age.mm)==5||(age.mm)==7||(age.mm)==8||(age.mm)==10||(age.mm)==12)
		 {
			age.dd=31+(dtoday.dd-dob.dd);
			age.mm=age.mm-1;
		 }
	 else if ((age.mm)==4||(age.mm)==6||(age.mm)==9||(age.mm)==11)
		{
		 age.dd=30+(dtoday.dd-dob.dd);
		 age.mm=age.mm-1;
		}
	 else if((age.mm)==2)
		{
		 age.dd=28+(dtoday.dd-dob.dd);
		 age.mm=age.mm-1;
		}
	 else
		cout<<"Invalid Input";
	}
 if (age.dd>=30)
 {
	age.dd=age.dd-30;
	age.mm=age.mm+1;
 }
 if (age.mm>=12)
 {
	age.mm=age.mm-12;
	age.yy=age.yy+1;
 }
cout<<" "<<age.yy<<"years "<<age.mm<<"months "<<age.dd<<"days";
}