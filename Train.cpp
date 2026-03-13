#include<iostream>
#include<string.h>
#include<fstream>
#include<iomanip>
#include<conio.h>
using namespace std;

class Train
 {
	protected :
	    int train_code;
	    char train_name[20],source[20],destination[20],time[10];
	    float fare_km;
	
	public:
	    void addTrain()
		 {
	        cout<<"\nEnter Train Number: ";
	        cin>>train_code;
	        fflush(stdin);
	        cout<<"\nEnter Train Name: ";
	        cin.getline(train_name,20);
	        cout<<"\nEnter Source: ";
	        cin>>source;
	        cout<<"\nEnter Destination: ";
	        cin>>destination;
	        cout<<"\nEnter Time: ";
	        cin>>time;
	        cout<<"\nEnter fair per kilometer ";
	        cin>>fare_km;
	
	        cout << "Train added successfully!";
	     }
	
	    void viewTrains()
		 {
		 	ifstream fin;
		 	Train t;
	        fin.open("train.bin",ios::binary);
			 if(fin!= 0)
			  {
			   cout<<setw(15)<<setfill(' ')<<"\n\tTrain Code"<<setw(25)<<"Train Name"<<setw(20)<<"Source";
				 cout<<setw(20)<<"Destination"<<setw(20)<<"Departure Time";
				 while(1)
				 {
					fin.read((char*)&t,sizeof(t));
					if(fin.eof())
							break;
						cout<<"\n"<<setw(15)<<t.train_code<< setw(25)<<t.train_name<< setw(20)<<t.source<< setw(20)<<t.destination<< setw(15)<<t.time;
						 	
						 }
						 fin.close();
					 }
					 else
					 cout<<"\nNo Records found ";
	     }
	     
	     void removetrain()
	     {
	     	ifstream fin;
	     	ofstream fout;
	     	int item,flag;
	     	Train t;
            fin.open("train.bin",ios::binary);
	   		if(fin!=0)
			{
				
	            cout<<"\nEnter Train_code to remove : ";
	            cin>>item;
			   fout.open("temp.bin",ios::binary);
	        	flag = 0;
				while(1)
			   {
			  	fin.read((char*)&t,sizeof(t));
			 	if(fin.eof())
				break;
				if(item == t.train_code)
				flag = 1;
				else
					{
					fout.write((char*)&t,sizeof(t));
				    }
				}
					 fin.close();
					 fout.close();
					  remove("train.bin");
					  rename("temp.bin","train.bin");
					 if(flag == 0)
					 cout<<"\nNo record ";
					 else 
					  cout<<"\nRecord deleted ";
								   
					 fin.open("train.bin");
				     fin.read((char*)&t,sizeof(t));
					 if(fin.eof())
					 flag = 2;
				    fin.close();
					if(flag == 2)
					remove("train.bin");     	
			 }
			 else cout<<"\nNO Records ";
		}
		
		float t_fare(int item)
		{
		    ifstream fin;
	     	Train t;
            fin.open("train.bin",ios::binary);
	   		if(fin!=0)
			{
			 	while(1)
			   {
				  	fin.read((char*)&t,sizeof(t)); 
				 	if(fin.eof())
					break;
					if(item == t.train_code)
					{
						return t.fare_km;
						break;
				    }
				}
					 fin.close();
			}
		}
};

class Passenger : public Train
{
	protected:
	    char email_id[20],password[20],pass_name[30],gender[10],phone_no[15];
	    int total_pass,age;
	    int source_dist,destination_dist;
	    float total_amount, train_fare;
	    
	
	    void get_data() 
		{
	        cout<<"\nEnter the Email id: ";
	        fflush(stdin);
	        cin.getline(email_id,20);
	        cout<<"\nEnter the Password: ";
	        cin>>password;
	        cout<<"\nEnter the total number of passengers: ";
	        cin>>total_pass;
	        fflush(stdin);
	        cout<<"\nEnter the Passenger Name: ";
	        cin.getline(pass_name,30);
	        cout<<"\nEnter the Passenger Age: ";
	        cin>>age;
	        cout<<"\nEnter the Passenger Phone Number: ";
	        cin>>phone_no;
	        cout<<"\n\n**********************Train Schedule************************";
	        viewTrains();
	        cout<<"\n\nEnter Train Code: ";
	        cin>>train_code;
	        
	        train_fare = t_fare(train_code);
	        
	        cout<<"\n\n************************ Stations **********************";
	        cout<<"\nCSMT\tKalyan\t\tNashik\tManmad\t\tPachora\t\tJalgaon\t\tBhusawal\tRaver\tBurhanpur\tNepanagar\n";
	
	        cout<<"\n\nEnter the Source station : ";
	        cin>>source;
	        source_dist = calcDistance(source);
	        cout<<"\nEnter the destination station : ";
	        cin>>destination;
	        destination_dist = calcDistance(destination);
	         int distance = (destination_dist - source_dist);
	         if(distance>0)
	        total_amount = total_pass * distance * train_fare;
	        else
	        total_amount = total_pass * (-1* distance )* train_fare;
	        
	
	    }
	
	     int calcDistance(char station[])
		 {	
				  if(stricmp(station, "kalyan") == 0 )
		        return 56;
		     else if(stricmp(station, "nashik") == 0)
		        return 127;
		     else if (stricmp(station, "manmad") == 0 ) 
		        return 250;
		     else if (stricmp(station, "pachora") == 0) 
		        return 312;
		     else if (stricmp(station, "jalgaon") == 0 ) 
		        return 401;
		     else if (stricmp(station, "bhusawal") == 0 )
		        return 450;
		     else if (stricmp(station, "raver") == 0 ) 
		        return 501;
		     else if (stricmp(station, "burhanpur") == 0 )
		        return 654;
		     else if (stricmp(station, "nepanagar") == 0) 
		        return 701;
		     else if (stricmp(station, "CSMT") == 0) 
		        return 1;
		     else {
		        cout << "\n************************* Invalid station ******************************" ;
		        return -1; 
    }
        }
	        
};


class Reservation : public Passenger
 {
	public:
		
	    void reserveTicket() 
		{
			ifstream fin;
			 fin.open("train.bin");
			 if(!fin)
			{
				fin.close();
				cout<<"\nNO TRAINS AVAILABLE ";
				return;
     		}
			 fin.close();
			
			Reservation b;
			ofstream fout;
	        fout.open("Reservation.bin", ios::app | ios::binary);
	        b.get_data();
			fout.write((char*)&b,sizeof(b));
			fout.close();
	    
	        cout << "Ticket booked successfully!";
	    }
	    
	
	    void viewReservations() 
		{
			system("cls");
	        ifstream fin;
	        Reservation b;
			fin.open("Reservation.bin",ios::binary);
			if(fin!= 0)
			  {
	    		cout<<"Reservation Details: ";
		        while(1)
				{
					fin.read((char*)&b,sizeof(b));
		    		if(fin.eof())
		    		break;
		    		cout<<"\n----------------------------------------------------------------------------";
		            cout<<"\nTrain No: "<<b.train_code<<"\nPassenger Name: "<<b.pass_name<<"\nPhone No.: "<<b.phone_no
		                 <<"\nSource Station: "<<b.source<<"\nDesti. Station: "<<b.destination<<"\nTotal Amount: "<<b.total_amount;
		         }
		        fin.close();
	          }
	          else
	          cout<<"\nNO RESERVATION RECORDS ";
	    }
	
	    void cancelTicket() 
		{
			
	         char item[15],name[30];
	         ofstream fout;
	         ifstream fin;
	         int flag=0;
	            Reservation b;
	        	fin.open("Reservation.bin",ios::binary);
	        	if(fin!=0)
	        	{
	        		fout.open("temp.bin",ios::binary );
	        		cout<<"\nEnter name  ";
	        		cin>>name;
	        		while(1)
	        		{
		                 fin.read((char*)&b,sizeof(b));
		                 if(fin.eof())
		                 break;
		                 int x = stricmp(b.pass_name,name);
		                 if(x==0)
		                 {
		                 	flag = 1;
				        	cout<<"\n*****RESERVATION FOUND**** ";
				        	cout<<"\nEnter the Password to cancel the Ticket : ";
				            cin>>item;
				            x=strcmp(b.password,item);
				            if(x==0)
		                   {
		                	cout << "Reservation canceled successfully!";
		                	
		                    }
		                   else
						    {
						     cout<<"\nWRONG PASSWORD ";
						     goto HERE;
		                    }
		                }
		                else
		                {
		                	HERE:
		               	    fout.write((char*)&b,sizeof(b));
				        }
	                }
				}
				else
				{
					cout<<"\nNo RESERVATION RECORDS FOUND ";
					return;
			    }
			    if(flag == 0)
			    {
			    	cout<<"\nNO RESERVATION FOUND";
				}
		        fin.close();
		        fout.close();
		
		        remove("Reservation.bin");
		        rename("temp.bin","Reservation.bin");
		        
		          
					
				}
		
};

int main()
 {
    Train t;
    Reservation b;
    ifstream fin;
    ofstream fout;
    int choice;
     do{
     	system("cls");
        cout<<setw(70)<<setfill('*')<<" INDIAN RAILWAYS"<<setw(55)<<setfill('*')<<" ";
        cout<<"\n1.Passenger login\n2.Employee login \n5.Exit app\
	      \nEnter your choice : ";
		 cin>>choice;
		 if(choice == 1)
		 {
		 	do{
		 		system("cls");
			cout<<"\n-----------PASSENGER LOGIN-----------\n";
		 	cout << "1. Reserve Ticket\n";
	        cout << "2. View Reservation\n";
	        cout << "3. Cancel Reservation\n";
	        cout << "0. Exit\n";
	        cout << "Enter your choice: ";
	        cin >> choice;
	        
	         switch (choice)
			  {
	            case 1:b.reserveTicket(); break;
	            case 2: b.viewReservations();break;
	            case 3: b.cancelTicket(); break;
	            case 0:cout<<"\nThank you ";break;
	            default:cout << "Invalid choice!";
	          }
	          getch();
	      }while(choice!=0);
	  }
	      
	     else if(choice == 2)
	        {
	        	
		         do{
		         	system("cls");
		         	cout<<"\n-----------EMPLOYEE LOGIN-----------\n";
				 	cout<<"1. Add Train\n";
			        cout<<"2. Remove Train\n";
			        cout<<"3. View Trains\n";
			        cout<<"0. Exit\n";
			        cout<<"Enter your choice: ";
			        cin>>choice;
			        
			        switch(choice)
			        {
			        	case 1 :fout.open("train.bin",ios::app | ios::binary);
								 t.addTrain();
						         fout.write((char*)&t,sizeof(t));
						         fout.close();
								 break;
								 
			        	case 2 :  t.removetrain();
								  break;	
			        	
			        	case 3 :t.viewTrains();
								break; 
						
								 
			        	case 0 : cout<<"\nThank you "; break;
			        	default : cout<<"\nINVALID CHOICE ";
					}
			        getch();
				} while(choice!=0);
			}
		else if(choice == 5)
				cout<<"\n*********VISIT AGAIN**********";
		else
			cout<<"\nINVALID CHOICE ";
			
		}while(choice !=5 );
      return 0;
}
