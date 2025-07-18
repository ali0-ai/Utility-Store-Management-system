#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<typeinfo>
#include <cmath>
using namespace std;
struct order
{
      int prodid1;
      char pname1[50];
      char compy1[50];
      int qty1;
      float price1,dis1;
}o1[50];
int orderk=0;
void mainMenu();
int Login();
void write_customer1();
void administratormenu();
void copyme(int k,order order1[],int q1,int &c2);
int getproduct();
int getcustomers();
void product_detail_heading();
void customer_detail_heading();
void prod_tabular();
void cust_menu1();
void cust_menu2();
void cust_menu3();
void modify_record(int n);
void delete_record(int n);
void againopenandclose();
void againopenandclosecust();
int search(int p);
void changeqty(int pr1,int q11);

//customer class:
class customer
{
      int cust_id;
      char cname[100];
      char address[100];
      char phno[15];
public:
      void modifycust_data(int n1,char nm[15],char add[15],char q[15]);
      int getcustid()
      {
            return cust_id;
      }
      char *getcustnm()
      {
            return cname;
      }
      char *getcustadd()
      {
            return address;
      }
      char *getphno()
      {
            return phno;
      }
      //function for taking input from customer
      void cust_input(int custid)
      {
            cout<<"-------------------------------------------------------------------------"<<endl;
            cout<<"CUSTOMER NO: ";
            cust_id=custid;
            cout<<cust_id<<endl;
            cout<<"NAME OF CUSTOMER:"<<endl;
            cin>>cname;
            cout<<"ADDRESS:"<<endl;
            cin>>address;
            cout<<"PHONE NO.:"<<endl;
            cin>>phno;
            cout<<"-------------------------------------------------------------------------"<<endl;
      }
      //function to show customer details
      void showallcust(int c)
      {
            cout<<"   "<<cust_id<<setw(15)<<cname<<setw(23)<<address<<setw(27)<<phno<<endl;
      }
      void show_cust()
      {
             cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"CUSTOMER NO      : "<<cust_id<<endl;
             cout<<"NAME OF CUSTOMER : "<<cname<<endl;
             cout<<"ADDRESS 	 : "<<address<<endl;
             cout<<"PHONE NO.	 : "<<phno<<endl;
             cout<<"-------------------------------------------------------------------------"<<endl;
      }
};
//customer class ends here
//Function to modify the customer details
void customer::modifycust_data(int n1,char nm[15],char add[15],char q[15])
{
      char tmpnm[40],tmpnm2[40],tmpnm3[15];
      char yes1,yes2,yes3;
      cust_id=n1;
      strcpy(cname,nm);
      cout<<"ENTER THE NAME OF CUSTOMER:"<<endl;
      cout<<cname<<endl;
      cout<<"Do You Want To Change The Name Of Customer ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      int flag=0;
      while(1)
      {
            cin>>yes1;
            if(yes1== 'Y' || yes1== 'y')
            {
                  cout<<"Enter new name\n";
                  cin>>tmpnm;
                  flag=1;
                  break;
            }
            if(yes1== 'N' || yes1== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            strcpy(cname,tmpnm);
      }
      strcpy(address,add);
      cout<<"CUSTOMER ADDRESS:"<<endl;
      cout<<address<<endl;
      cout<<"Want to change the address ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes2;
            if(yes2== 'Y' || yes2== 'y')
            {
                  cout<<"Enter new address\n";
                  cin>>tmpnm2;
                  flag=1;
                  break;
            }
            if(yes2== 'N' || yes2== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            strcpy(address,tmpnm2);
      }
      strcpy(phno,q);
      cout<<"CUSTOMER PHONE NO.:"<<endl;
      cout<<phno<<endl;
      cout<<"Want to change the phone no. ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes3;
            if(yes3== 'Y' || yes3== 'y')
            {
                  cout<<"Enter new phone no.\n";
                  cin>>tmpnm3;
                  flag=1;
                  break;
            }
            if(yes3== 'N' || yes3== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            strcpy(phno,tmpnm3);
      }
      if((yes3== 'Y' || yes3== 'y') || (yes2== 'Y' || yes2== 'y') || (yes1== 'Y' || yes1== 'y'))
            cout<<"*********************   NEW CUSTOMER RECORD SAVED   **********************"<<endl;
      else
            cout<<"********************   NO CUSTOMER RECORD CHANGED   **********************"<<endl;
}
//Function to add the records in file
void write_customer()
{
      ofstream objoff;
      customer cobj;
      objoff.open("customer.csv",ios::out|ios::app);
      int r=getcustomers();
      if(r>100) //1000
      {
            r=1; // r=100
      }
       cobj.cust_input(r);
       objoff.write((char*)&cobj,sizeof(customer));
       objoff.close();
       cout<<"***********************   CUSTOMER RECORD SAVED   ***********************"<<endl;
       cin.ignore();
       cin.get();
}
//Function to check the customer number already given or not
int getcustomers()
{
      ifstream objiff;
      customer cust;
      int count=0;
      objiff.open("customer.csv",ios::binary);
      objiff.seekg(0,ios::beg);
      if(!objiff)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
      }
      while(objiff.read((char *) &cust, sizeof(customer)))
      {
            count++;
      }
      //***********jump to the last line
      objiff.seekg(count-sizeof(cust),ios::beg);
      objiff.read((char *) &cust, sizeof(customer));
      count=cust.getcustid();
      count++;
      objiff.close();
      return count;
}
// Function to read specific record from file
void display_cust_sp(int n)
{
       ifstream objfp;
       customer cust;
       int flag=0;
       objfp.open("customer.csv",ios::binary);
       if(!objfp)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      while(objfp.read((char*)&cust,sizeof(customer)))
      {
             if(cust.getcustid()==n)
            {
                  cust.show_cust();
                  flag=1;
            }
      }
      objfp.close();
      if(flag==0)
      cout<<"\n\nRecord doesnot exist"<<endl;
      cin.get();
}
//FUNCTION TO DISPLAY ALL THE CUSTOMER TABULAR FORM
void cust_tabular()
{
      int r=0,col=10;
      customer cust;
      ifstream inFile;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      customer_detail_heading();
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
             if(r<=12)
             {
                   r++;
                   cust.showallcust(col);
                   col++;
             }
             else
             {
                   cout<<"----------------------------- Press any key -----------------------------"<<endl;
                   cin.get();
                   customer_detail_heading();
                   col=10;
                   r=0;
            }
      }
      inFile.close();
      cin.get();
}
//function to display heading of customer details
void customer_detail_heading()
{
      cout<<"========================================================================="<<endl;
      cout<<"   ************************  CUSTOMER DETAILS  **********************    "<<endl;
      cout<<"========================================================================="<<endl;
      cout<<"CUST.NO"<<setw(13)<<"NAME"<<setw(23)<<"ADDRESS"<<setw(27)<<"PHONE NO"<<endl;
      cout<<"-------------------------------------------------------------------------"<<endl;
}
//FUNCTION TO MODIFY customer RECORD
void modify_cust_record(int n)
{
      customer cust,temp;
      char tmpnm[50],tmpaddress[50];
      ifstream inFile;
      int fpos1=-1;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      int flag=0;
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
            if(cust.getcustid()==n)
            {
             cust.show_cust();
             flag=1;
            }
      }
      inFile.close();
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      else
      {
      //modifying the records starts here
            fstream File;
            File.open("customer.csv",ios::binary|ios::in|ios::out);
            if(!File)
            {
                  cout<<"File could not be open !! Press any Key..."<<endl;
                  cin.get();
                  return;
            }
            while(File.read((char *) &cust, sizeof(customer)))
            {
                  if(cust.getcustid()==n)
                  {
                        fpos1=(int)File.tellg();
                        break;
                  }
            }
            File.seekp(fpos1-sizeof(customer),ios::beg);
            strcpy(tmpnm,cust.getcustnm());
            strcpy(tmpaddress,cust.getcustadd());
            char q1[15];
            strcpy(q1,cust.getphno());
            cout<<"============  ENTER NEW VALUES FOR THE RECORDS GIVEN ABOVE  ============="<<endl;
            temp.modifycust_data(n,tmpnm,tmpaddress,q1);
            File.write((char *) &temp, sizeof(customer));
            File.close();
      }
}
//FUNCTION TO DELETE THE RECORD OF THE CUSTOMER AVAILABLE
void deletecust_record(int n)
{
      customer cust;
      ifstream inFile;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      int flag=0;
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
            if(cust.getcustid()==n)
            {
                   cust.show_cust();
                   flag=1;
            }
      }
      inFile.close();
      char ch;
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      else
      {
      //Deletion of the records starts from here
            cout<<"DO YOU WANT TO DELETE THE RECORDS GIVEN ABOVE [YES(Y or y) OR NO(N or n)]"<<endl;
            cin>>ch;
            if (toupper(ch)=='Y')
            {
                   ofstream outFile;
                   outFile.open("Temp2.csv",ios::binary);
                   ifstream objiff("customer.csv",ios::binary);
                   objiff.seekg(0,ios::beg);
                   while(objiff.read((char *) &cust, sizeof(customer)))
                   {
                         if(cust.getcustid()!=n)
                         {
                              outFile.write((char *) &cust, sizeof(customer));
                         }
                  }
                  outFile.close();
                  objiff.close();
                  remove("customer.csv");
                  rename("Temp2.csv","customer.csv");
                  againopenandclosecust();
                  cout<<"---------------------------Record Deleted--------------------------------"<<endl;
            }
      }
      cin.get();
}
void againopenandclosecust()
{
      ifstream inFile;
      customer cust;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cin.get();
            return;
      }
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
      }
      inFile.close();
}
//Search the customer
int searchcust(int p)
{
      customer cust;
      int tmprt=0;
      ifstream inFile;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return -1;
      }
      int flag=0;
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
            if(cust.getcustid()==p)
            {
                   cust.show_cust();
                   flag=1;
                   tmprt=(int)inFile.tellg();
                   break;
            }
      }
      inFile.close();
      if(flag==0)
            return 1;
      //cout<<"\n\nRecord doesnot exist";
      else
      {
            return tmprt;
      }
}
//Fuction to write customer data
void write_customer1()
{
      ofstream objoff;
      customer cobj;
      objoff.open("customer.csv",ios::out|ios::app);
      int r=getcustomers();
      if(r>100) //1000
      {
            r=1; // r=100
      }
       cobj.cust_input(r);
       objoff.write((char*)&cobj,sizeof(customer));
       objoff.close();
       cout<<"***********************   CUSTOMER RECORD SAVED   ***********************"<<endl;
       cin.ignore();
       cin.get();
       cust_menu3();
}
int before_order()
{
      int f=-1,num=0;
      customer cust;
      cout<<"ENTER THE CUSTOMER ID TO BILL:"<<endl;
      cin>>num;
      ifstream inFile;
      inFile.open("customer.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return -1;
      }
      while(inFile.read((char *) &cust, sizeof(customer)))
      {
            if(cust.getcustid()==num)
            {
                   cust.show_cust();
                   f=1;
                   //tmprt=(int)inFile.tellg();
                   break;
            }
      }
      inFile.close();
      return f;
}
//Product class starts here:
class product
{
      int prodid;
      char name[50];
      char company[50];
      int qty;
      float price,dis;
      public:
      product()
      {
            qty=0;
            price=0;
            dis=0;
      }
      void modifydata(int n1,char snm[15],char companynm[15],int q);
      void create_prod(int rn1)
      {
             cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"PRODUCT NO: ";
             prodid=rn1;
             cout<<prodid<<endl;
             cout<<"NAME OF PRODUCT:"<<endl;
             cin>>name;
             cout<<"COMPANY:"<<endl;
             cin>>company;
             cout<<"PRODUCT PRICE:"<<endl;
             cin>>price;
             cout<<"QUANTITY:"<<endl;
             cin>>qty;
             cout<<"DISCOUNT%:"<<endl;
             cin>>dis;
             cout<<"-------------------------------------------------------------------------"<<endl;
      }
      void show_prod()
      {
             cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"PRODUCT NO 		: "<<prodid<<endl;
             cout<<"NAME OF PRODUCT 	: "<<name<<endl;
             cout<<"COMPANY NAME      	: "<<company<<endl;
             cout<<"PRODUCT PRICE   	: "<<price<<endl;
             cout<<"QUANTITY OF STOCK	: "<<qty<<endl;
             cout<<"DISCOUNT % 		: "<<dis<<"%"<<endl;
             cout<<"-------------------------------------------------------------------------"<<endl;
       }
      //Function shows product data in tabular form
      void showall(int c)
      {
            cout<<"  "<<prodid<<setw(15)<<name<<setw(11)<<company<<setw(11)<<"Rs."<<price<<setw(10)<<qty<<setw(13)<<dis<<"%"<<endl;
      }
      int retpno()
      {
           return prodid;
      }
      float retprice()
      {
           return price;
      }
      char* getcompany()
      {
          return company;
      }
      char* getname()
      {
          return name;
      }
      int getqty()
      {
          return qty;
      }
      float retdis()
      {
          return dis;
      }
      void setqty(int q21)
      {
          qty=q21;
      }
};
// Product class ends here
// Fuction to modify product details
void product::modifydata(int n1,char snm[15],char companynm[15],int q)
{
      char tmpnm[40],tmpnm2[40];
      char yes1,yes2;
       cout<<"PRODUCT NO: ";
       prodid=n1;
       cout<<prodid<<endl;
       strcpy(name,snm);
       cout<<"NAME OF PRODUCT:"<<endl;
       cout<<name<<endl;
       cout<<"Want to change the name of product ? (Yes[ y or Y ] or NO [n or N])"<<endl;
       int flag=0;
       while(1)
       {
            cin>>yes1;
            if(yes1== 'Y' || yes1== 'y')
            {
                  cout<<"Enter new name\n";
                  cin>>tmpnm;
                  flag=1;
                  break;
            }
            if(yes1== 'N' || yes1== 'n')
            {
                  flag=0;
                  break;
            }
       }
       if(flag==1)
       {
            strcpy(name,tmpnm);
       }
       strcpy(company,companynm);
       //COMPANY NAME TO BE MODIFY
       cout<<"COMPANY NAME:"<<endl;
       cout<<company<<endl;
       cout<<"Want to change the company name ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes2;
            if(yes2== 'Y' || yes2== 'y')
            {
                  cout<<"Enter new company name:\n";
                  cin>>tmpnm2;
                  flag=1;
                  break;
            }
            if(yes2== 'N' || yes2== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            strcpy(company,tmpnm2);
      }
      cout<<"PRICE:"<<endl;
      //add the line to display price
      float tmppr=0;
      char yes4,yes3,yes5;
      cout<<"Want to change the price of product ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes3;
            if(yes3== 'Y' || yes3== 'y')
            {
                  cout<<"Enter new price of product:\n";
                  cin>>tmppr;
                  flag=1;
                  break;
            }
            if(yes3== 'N' || yes3== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            price=tmppr;
      }
      cout<<"QUANTITY:"<<endl;
      //add the line to display quantity
      int tmpqty=0;
      cout<<"Want to change the quantity of product ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes4;
            if(yes4== 'Y' || yes4== 'y')
            {
                  cout<<"Enter new quantity:\n";
                  cin>>tmpqty;
                  flag=1;
                  break;
            }
            if(yes4== 'N' || yes4== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            qty=tmpqty;
      }
      cout<<"DISCOUNT%:"<<endl;
       //add the line to display discount
      float tmpdis=0;
      cout<<"Want to change the discount of product ? (Yes[ y or Y ] or NO [n or N])"<<endl;
      flag=0;
      while(1)
      {
            cin>>yes5;
            if(yes5== 'Y' || yes5== 'y')
            {
                  cout<<"Enter new discount"<<'%'<<"on the product:\n";
                  cin>>tmpdis;
                  flag=1;
                  break;
            }
            if(yes5== 'N' || yes5== 'n')
            {
                  flag=0;
                  break;
            }
      }
      if(flag==1)
      {
            dis=tmpdis;
      }
      if((yes3== 'Y' || yes3== 'y') || (yes2== 'Y' || yes2== 'y') || (yes1== 'Y' || yes1== 'y') || (yes4== 'Y' || yes4== 'y') || (yes5== 'Y' || yes5== 'y'))
            cout<<"*********************   NEW PRODUCT RECORD SAVED   *********************"<<endl;
      else
            cout<<"********************   NO PRODUCT RECORD CHANGED   *********************"<<endl;
}
// Global declaration for stream object
fstream fp;
// Class function outside
product pr;
// Function to write product details in file
void write_book()
{
      fp.open("product.csv",ios::out|ios::app);
      int rnn=getproduct();
      if(rnn>100)
      {
            rnn=1;
      }
      pr.create_prod(rnn);
      fp.write((char*)&pr,sizeof(product));
      fp.close();
      cout<<"***********************  PRODUCTS RECORD SAVED  ************************"<<endl;
      cin.ignore();
      cin.get();
}
//Function to check the product number already given or not
int getproduct()
{
      ifstream objiff;
      product st;
      int count=0;
      objiff.open("product.csv",ios::binary);
      objiff.seekg(0,ios::beg);
      if(!objiff)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
      }
      while(objiff.read((char *) &st, sizeof(product)))
      {
            count++;
      }
      objiff.seekg(count-sizeof(st),ios::beg);
      objiff.read((char *) &st, sizeof(product));
      count=st.retpno();
      count++;
      objiff.close();
      return count;
}
//Function to read specific record from file
void display_sp(int n)
{
      int flag=0;
      fp.open("product.csv",ios::in);
      if(!fp)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      while(fp.read((char*)&pr,sizeof(product)))
      {
            if(pr.retpno()==n)
            {
                  pr.show_prod();
                  flag=1;
            }
      }
      fp.close();
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      cin.get();
}
//Function to place order and generating invoice for PRODUCT PURCHASED
void place_order()
{
      order o1[50];
      int c=0,pr1=0;
      float amt=0,damt=0,total=0,ttaxt=0;
      int k=0,q1;
      char ch='Y';
      int ptx[100];
      int v=0;
      int value=before_order();
      if(value==1)
      {
            cout<<endl;
            prod_tabular();
            cout<<"========================================================================"<<endl;
            cout<<"                             PLACE YOUR ORDER                           "<<endl;
            cout<<"========================================================================"<<endl;
            do
            {
                  cout<<"ENTER THE PRODUCT NO: "<<endl;
                  cin>>pr1;
                  k=search(pr1);
                  if(k>0)
                  {
                        cout<<"Enter the Quantity:"<<endl;
                        cin>>q1;
                        copyme(k,o1,q1,c);
                        ptx[v]=pr1;
                        v++;
                  }
                  else
                  {
                        cout<<"PRODUCT not found"<<endl;
                  }
                  cout<<"Do you want purchase more ? (Yes[ y or Y ] or NO [n or N])"<<endl;
                  cin>>ch;
            }while(ch=='y' || ch=='Y');
            cout<<"Thank You For Placing The Order  ........"<<endl<<endl;
            cin.get();
            cout<<"========================================================================\n"<<endl;
            cout<<"*****************************   INVOICE   ******************************"<<endl;
            cout<<"------------------------------------------------------------------------"<<endl;
            cout<<"PR.No."<<setw(7)<<"NAME"<<setw(10)<<"Qty"<<setw(12)<<"Price"<<setw(13)<<"Amount"<<setw(23)<<"Amount - discount"<<endl<<endl;
            int yy=8;
            for(int x=0;x<c;x++)
            {
                  amt=o1[x].qty1*o1[x].price1;
                  damt=amt-o1[x].dis1;
                  cout<<"  "<<ptx[x]<<setw(10)<<o1[x].pname1<<setw(9)<<o1[x].qty1<<setw(12)<<"Rs."<<o1[x].price1<<setw(10)<<"Rs."<<amt<<setw(14)<<"Rs."<<damt<<endl;
                  total+=damt;
                   //ttaxt+=o1[x].tax1;
                  yy++;
             }
             ttaxt=18;
             cout<<"\n-------------------------------------------------------------------------"<<endl;
             yy++;
             cout<<"\n\t\t  TOTAL AMOUNT     :   "<<"Rs."<<total<<endl;
             yy++;
             cout<<"\t\t  CGST             :   "<<"+"<<ttaxt/2<<"%"<<endl;
             cout<<"\t\t  SGST             :   "<<"+"<<ttaxt/2<<"%"<<endl;
             yy++;
             cout<<"-------------------------------------------------------------------------"<<endl;
             yy++;
             cout<<"\t\t  NET TOTAL        :   "<<"Rs."<<(total+((ttaxt*total)/100))<<endl;
             yy++;
             cout<<"\t\t  ROUND OFF AMOUNT :   "<<"Rs."<<setprecision(2)<<(round(total+((ttaxt*total)/100))-(total+((ttaxt*total)/100)))<<endl;
             cout<<"\t\t  NET AMOUNT DUE   :   "<<"Rs."<<fixed<<round(total+((ttaxt*total)/100))<<endl<<endl;
             cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"\t\t   P A Y M E N T  S U M M A R Y  "<<endl;
             cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"\t\t  Enter CASH value :   Rs.";
             float vb,xy;
             cin>>vb;
             xy=(vb-round(total+((ttaxt*total)/100)));
             if(xy<0)
             {
                cout<<"\nSorry! You have paid Insufficient cash. Please reinitiate billing. Thank You."<<endl;
                cust_menu1();
             }
             else
             {
                cout<<"\t     Change to be returned :   Rs."<<xy<<endl;
                changeqty(pr1,q1);
                cout<<"-------------------------------------------------------------------------"<<endl;
             cout<<"\n\n\t   WE ARE EAGERLY LOOKING FORWARD TO SERVE YOU AGAIN\n";
             cout<<"\n\t\t\t    HAVE A NICE DAY !\n\n";
             cout<<"=========================================================================\n"<<endl;
             }
             cin.get();
      }
      else
      {
            cout<<"**************************  YOUR ID IS WRONG  ***************************"<<endl;
      		cust_menu1();
      }
}
//FUNCTION TO DISPLAY ALL THE PRODUCTS IN TABULAR FORM
void prod_tabular()
{
      int r=0,col=10;
      product st;
      ifstream inFile;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      product_detail_heading();
      while(inFile.read((char *) &st, sizeof(product)))
      {
            if(r<=12)
            {
                  r++;
                  st.showall(col);
                  col++;
            }
            else
            {
                  cout<<"----------------------------- Press any key ----------------------------"<<endl;
                  cin.get();
                  product_detail_heading();
                  col=10;
                  r=0;
            }
      }
      inFile.close();
      cin.get();
}
//Function to display heading of the product details
void product_detail_heading()
{
      cout<<"========================================================================"<<endl;
      cout<<"*************************   PRODUCTS DETAILS   *************************"<<endl;
      cout<<"========================================================================"<<endl;
      cout<<"PROD.NO"<<setw(10)<<"NAME"<<setw(13)<<"COMPANY"<<setw(12)<<"PRICE"<<setw(13)<<"QUANTITY"<<setw(15)<<"DISCOUNT"<<endl;
      cout<<"------------------------------------------------------------------------"<<endl;
}
//FUNCTION TO MODIFY RECORD
void modify_record(int n)
{
      product st,temp;
      char tmpnm[50],tmpcompany[50];
      ifstream inFile;
      int fpos=-1;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      int flag=0;
      while(inFile.read((char *) &st, sizeof(product)))
      {
            if(st.retpno()==n)
            {
                  st.show_prod();
                  flag=1;
            }
      }
      inFile.close();
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      else
      {
            fstream File;
            File.open("product.csv",ios::binary|ios::in|ios::out);
            if(!File)
            {
                  cout<<"File could not be open !! Press any Key..."<<endl;
                  cin.get();
                  return;
            }
            while(File.read((char *) &st, sizeof(product)))
            {
                  if(st.retpno()==n)
                  {
                        fpos=(int)File.tellg();
                        break;
                  }
            }
            File.seekp(fpos-sizeof(product),ios::beg);
            strcpy(tmpnm,st.getname());
            strcpy(tmpcompany,st.getcompany());
            int q1=st.getqty();
            cout<<"===========   ENTER NEW VALUES FOR THE RECORDS GIVEN ABOVE   ==========="<<endl;
            temp.modifydata(n,tmpnm,tmpcompany,q1);
            File.write((char *) &temp, sizeof(product));
            File.close();
      }
}
//FUNCTION TO DELETE THE RECORD OF THE PRODUCTS 
void delete_record(int n)
{
      product st;
      ifstream inFile;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      int flag=0;
      while(inFile.read((char *) &st, sizeof(product)))
      {
            if(st.retpno()==n)
            {
                  st.show_prod();
                  flag=1;
            }
      }
      inFile.close();
      char ch;
      if(flag==0)
            cout<<"\n\nRecord doesnot exist"<<endl;
      else
      {
            cout<<"DO YOU WANT TO DELETE THE RECORDS GIVEN ABOVE [YES(Y or y) OR NO(N or n)]"<<endl;
            cin>>ch;
            if (toupper(ch)=='Y')
            {
                  ofstream outFile;
                  outFile.open("Temp1.csv",ios::binary);
                  ifstream objiff("product.csv",ios::binary);
                  objiff.seekg(0,ios::beg);
                  while(objiff.read((char *) &st, sizeof(product)))
                  {
                        if(st.retpno()!=n)
                        {
                              outFile.write((char *) &st, sizeof(product));
                        }
                  }
                  outFile.close();
                  objiff.close();
                  remove("product.csv");
                  rename("Temp1.csv","product.csv");
                  againopenandclose();
                  cout<<"------------------------------Record Deleted----------------------------"<<endl;
            }
      }
      cin.get();
}
void againopenandclose()
{
      ifstream inFile;
      product st;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cin.get();
            return;
      }
      while(inFile.read((char *) &st, sizeof(product)))
      {
      }
      inFile.close();
}
//Fuction to search the product
int search(int p)
{
      product st;
      int tmprt=0;
      ifstream inFile;
      inFile.open("product.csv",ios::binary);
      if(!inFile)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return -1;
      }
      int flag=0;
      while(inFile.read((char *) &st, sizeof(product)))
      {
            if(st.retpno()==p)
            {
                  st.show_prod();
                  flag=1;
                  tmprt=(int)inFile.tellg();
                  break;
            }
      }
      inFile.close();
      if(flag==0)
            return 1;
      else
      {
            return tmprt;
      }
}
//Function to change quantity of product
void changeqty(int pr1,int q11)
{
      product st;
      int fpos=-1;
      fstream File;
      File.open("product.csv",ios::binary|ios::in|ios::out);
      if(!File)
      {
            cout<<"File could not be open !! Press any Key..."<<endl;
            cin.get();
            return;
      }
      while(File.read((char *) &st, sizeof(product)))
      {
            if(st.retpno()==pr1)
            {
                  fpos=(int)File.tellg();
                  break;
            }
      }
      File.seekp(fpos-sizeof(product),ios::beg);
      int q1=st.getqty();
      q1=q1-q11;
      if(q1>0)
      {
        st.setqty(q1);
      } 
      else
      {
            cout<<"Insufficient quantity !"<<endl;
            cout<<"Please reinitiate the billing process.Thank you."<<endl;
            administratormenu();
      }
	  File.write((char *) &st, sizeof(product));
      File.close();
}
//Fuction to copy all record to a structure
void copyme(int k2,order order1[50],int q1,int &c2)
{
      ifstream objiff2("product.csv",ios::binary);
      product bk1;
      objiff2.seekg(k2-sizeof(product));
      objiff2.read((char*)&bk1,sizeof(product));
      strcpy(order1[c2].pname1,bk1.getname());
      strcpy(order1[c2].compy1,bk1.getcompany());
      order1[c2].dis1=bk1.retdis();
      order1[c2].price1=bk1.retprice();
      //COPY RECORD
      order1[c2].qty1=q1;
      c2++;
      objiff2.close();
}
// INTRODUCTION FUNCTION
void intro()
{

}
// Customer Menu Function
void customer_menu()
{
      char ch2;
      int num;
      cout<<"\n==========================   CUSTOMERS MENU   =========================="<<endl;
      cout<<"1.CREATE CUSTOMERS DETAILS"<<endl;
      cout<<"2.DISPLAY ALL CUSTOMERS DETAILS"<<endl;
      cout<<"3.SEARCH RECORD (QUERY) "<<endl;
      cout<<"4.MODIFY CUSTOMERS RECORDS"<<endl;
      cout<<"5.DELETE CUSTOMERS RECORDS"<<endl;
      cout<<"6.BACK TO MAIN MENU"<<endl;
      cout<<"Please Enter Your Choice (1-6) "<<endl;
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  write_customer();
                  customer_menu();
                  break;
            case '2':
                  cust_tabular();
                  customer_menu();
                  break;
            case '3':
                  cout<<"ENTER THE CUSTOMER NO TO BE SEARCHED:"<<endl;
                  cin>>num;
                  display_cust_sp(num);
                  customer_menu();
                  break;
            case '4':
                  cust_tabular();
                  cout<<"\nENTER THE CUSTOMER NO TO BE MODIFIED:"<<endl;
                  cin>>num;
                  modify_cust_record(num);
                  customer_menu();
                  break;
            case '5':
                  cust_tabular();
                  cout<<"\nENTER THE CUST NO TO BE DELETED:"<<endl;
                  cin>>num;
                  deletecust_record(num);
                  customer_menu();
                  break;
            case '6':
                  mainMenu();
                  break;
            default:
                  cout<<"Please enter valid option"<<endl;
      }
}
// Product menu Function
void product_menu()
{
      char ch2;
      int num;
      cout<<"\n==========================   PRODUCTS MENU   ==========================="<<endl;
      cout<<"1.CREATE PRODUCTS"<<endl;
      cout<<"2.DISPLAY ALL PRODUCTS AVAILABLE"<<endl;
      cout<<"3.SEARCH RECORD (QUERY) "<<endl;
      cout<<"4.MODIFY PRODUCTS"<<endl;
      cout<<"5.DELETE PRODUCTS"<<endl;
      cout<<"6.BACK TO MAIN MENU"<<endl;
      cout<<"Please Enter Your Choice (1-6) "<<endl;
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  write_book();
                  product_menu();
                  break;
            case '2':
                  prod_tabular();//product_detail_heading();
                  product_menu();
                  break;
            case '3':
                  cout<<"\nENTER THE PRODUCT ID TO BE SEARCHED:"<<endl;
                  cin>>num;
                  display_sp(num);
                  product_menu();
                  break;
            case '4':
                  prod_tabular();
                  cout<<"\nENTER THE PRODUCT ID TO BE MODIFIED:"<<endl;
                  cin>>num;
                  modify_record(num);
                  product_menu();
                  break;
            case '5':
                  prod_tabular();
                  cout<<"\nENTER THE PRODUCT ID TO BE DELETED:"<<endl;
                  cin>>num;
                  delete_record(num);
                  product_menu();
                  break;
            case '6':
                  mainMenu();
                  break;
            default:
                  cout<<"\a";
                  product_menu();
      }
}
// 1st type Function to be display customer options while placing order 
void cust_menu1()
{
      char ch2;
      int num;
      cout<<"\n-------------------------------------------------------------------------"<<endl;
      cout<<"\t\tE N T E R   C U S T O M E R   D E T A I L S :\n";
      cout<<"-------------------------------------------------------------------------"<<endl;
      cout<<"1.CREATE NEW CUSTOMER DETAIL"<<endl;
      cout<<"2.DISPLAY ALL CUSTOMERS DETAILS"<<endl;
      cout<<"3.BACK TO MAIN MENU"<<endl;
      cout<<"4.CONTINUE TO BILL\n"<<endl;
      cout<<"Please Enter Your Choice (1-4) "<<endl;
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  write_customer1();
                  break;
            case '2':
                  cust_tabular();
                  cust_menu2();
                  break;
            case '3':
                  mainMenu();
                  break;
            case '4':
                  orderk=0;
                  place_order();
                  break;
            default:
                  cout<<"Please enter valid option"<<endl;
      }
}
// 2nd type Function to be display customer options while placing order 
void cust_menu2()
{
      char ch2;
      int num;
      cout<<"\n-------------------------------------------------------------------------"<<endl;
      cout<<"\t\tC H O O S E   N E X T   O P T I O N S:\n";
      cout<<"-------------------------------------------------------------------------"<<endl;
      cout<<"1.CREATE NEW CUSTOMER DETAIL"<<endl;
      cout<<"2.BACK TO MAIN MENU"<<endl;
      cout<<"3.CONTINUE TO BILL\n"<<endl;
      cout<<"Please Enter Your Choice (1-3) "<<endl;
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  write_customer1();
                  break;
            case '2':
                  mainMenu();
                  break;
            case '3':
                  orderk=0;
                  place_order();
                  break;
            default:
                  cout<<"Please enter valid option"<<endl;
      }
}
// 3rd type Function to be display customer options while placing order 
void cust_menu3()
{
      char ch2;
      int num;
      cout<<"\n-------------------------------------------------------------------------"<<endl;
      cout<<"\t\tC H O O S E   N E X T   O P T I O N S:\n";
      cout<<"-------------------------------------------------------------------------"<<endl;
      cout<<"1.DISPLAY ALL CUSTOMERS DETAILS"<<endl;
      cout<<"2.BACK TO MAIN MENU"<<endl;
      cout<<"3.CONTINUE TO BILL\n"<<endl;
      cout<<"Please Enter Your Choice (1-3) "<<endl;
      cin>>ch2;
      switch(ch2)
      {
            case '1':
                  cust_tabular();
                  cust_menu2();
                  break;
            case '2':
                  mainMenu();
                  break;
            case '3':
                  orderk=0;
                  place_order();
                  break;
            default:
                  cout<<"Please enter valid option"<<endl;
      }
}
// Function for mainmenu
void mainMenu(){
     char ch;
      do
      {
      		cout<<endl;
      		cout<<"-------------------------------------------------------------------------"<<endl;
      		cout<<"*********   C A N T E E N  M A N A G E M E N T  S Y S T E M   ***********"<<endl;
      		cout<<"-------------------------------------------------------------------------"<<endl;
      		cout<<endl;
            cout<<"=============================   MAIN MENU   ============================"<<endl;
            cout<<"1. PLACE ORDER"<<endl;
            cout<<"2. ADMINISTRATOR MODE"<<endl;
            cout<<"3. EXIT"<<endl;
            cout<<"========================================================================"<<endl;
            cout<<"Please Select Your Option (1-3) "<<endl;
            cin>>ch;
            switch(ch)
            {
                  case '1':
                        cust_menu1();
                        break;
                  case '2':
                        administratormenu();
                        break;
                  case '3':
                        exit(0);
                  default :
                        cout<<"Please enter valid option"<<endl;
            }
      }while(ch!='3');
    }
// Administrator menu function
void administratormenu()
{
      char ch;
      do
      {
            cout<<endl;
            cout<<"=========================   ADMINISTRATOR MENU   ======================="<<endl;
            cout<<"1. CUSTOMERS MENU"<<endl;
            cout<<"2. PRODUCTS MENU"<<endl;
            cout<<"3. BACK TO MAIN MENU"<<endl;
            cout<<"========================================================================"<<endl;
            cout<<"Please Select Your Option (1-3) "<<endl;
            cin>>ch;
                  switch(ch)
                  {
                        case '1':
                              customer_menu();
                              break;
                        case '2':
                              product_menu();
                              break;
                        case '3':
                              mainMenu();
                              break;
                        default :
                              cout<<"Please enter valid option"<<endl;
                  }
      }while(ch!='3');
}
int Login()
{
	label:
    cout<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"*********  U T I L I T Y S T O R E M A N A G E M E N T  S Y S T E M   ***********"<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<endl;
	cout<<"1.ENTER (1) TO REGISTER"<<endl;
	cout<<"2.ENTER (2) TO LOGIN"<<endl;
	cout<<"3.ENTER (3) TO EXIT"<<endl;
	string p,q,w;
	int x;string s;
	cin>>x;
	if(x==1)
	{
  			ofstream fout;
  			cout<<"ENTER YOUR USERNAME"<<endl;
  			cin>>s;
  			cout<<"ENTER YOUR PASSWORD"<<endl;
  			cin>>p;
  			s=s+p;
  			ifstream fin;
  			string line;
  			int offset=0;
  			fin.open("myfile.txt");
  			if(fin.is_open())
  			{
  				while(!fin.eof())
  				{
  					getline(fin,line);
					if(line.find(s,0)!=-1)
					{
						cout<<"Sorry! This username is not available"<<endl;
						cout<<"Press any key to go to Home Page"<<endl;
						char kk;
						cin>>kk;
						goto label;
						//break;
					}
				}
			}
  			fin.close();
  			fout.open("myfile.txt",ios::app);
  			fout<<s+"\n";
  			fout.close();
  			goto label;
	}
	else if(x==2){
 		string line;
 		ifstream fin;
  		int offset=0;
  		cout<<"ENTER YOUR USERNAME"<<endl;
  		cin>>q;
  		cout<<"ENTER YOUR PASSWORD"<<endl;
  		cin>>w;
  		q=q+w;
  		fin.open("myfile.txt");
  		if(fin.is_open())
  		{
  			while(!fin.eof())
  			{
  				getline(fin,line);
				if(line.find(q,0)!=-1)
				{
					cout<<"You Are Logged In !!"<<endl;
					offset=1;
                    			mainMenu();
					break;
                }
			}
			if(offset==0)
			{
				cout<<"Sorry, You are UNAUTHORIZED!!"<<endl;
				cout<<"Press 1 and Enter, To Go To Home Page"<<endl;
				char o;
				cin>>o;
				goto label;
			}
		}
  		fin.close();
	}
	
 }