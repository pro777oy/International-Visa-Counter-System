/*
  Saad Kabir Uddin
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <cmath>
#include <cctype>

using namespace std;

class billNode{
	public:
	int metricNum;
	float fees;
	string ic;
	string name;
	double total;
	string DateoI;
	string DateoE;
	int days;
	billNode *next;
};


class billQueue{
	billNode *frontPtr,*backPtr;
	public:
		billQueue(){
			backPtr=NULL;
			frontPtr=NULL;
		}
		~billQueue(){
			billNode *temp = frontPtr;
			while (temp){
			frontPtr = temp->next;
			delete temp; 
			temp=frontPtr;
			}
		}
		bool isEmpty(){
			return (backPtr == NULL && frontPtr == NULL);
		}
		
		//implementation of queue 
		void enQueue(int rn,float p,string ic,string n,string in,string out,int d){
			billNode *temp=new billNode;
			if (backPtr == NULL) {
    			temp->next = NULL;
    			temp->metricNum = rn;
    			temp->fees = p;
    			temp->ic = ic;
    			temp->name= n;
    			temp->DateoI = in;
				temp->DateoE = out;
				temp->days=d;
				frontPtr = backPtr = temp;
   			}   
			else { 
      			backPtr->next = temp;
      			temp->metricNum = rn;
    			temp->fees = p;
    			temp->ic = ic;
    			temp->name= n;
    			temp->DateoI = in;
				temp->DateoE = out;
				temp->days=d;
      			temp->next = NULL;
      			backPtr = temp;
   			}
		}
		void displayInvoice(billNode *temp){
			if(temp->days<=1){
				temp->days==1;
			}
			temp->total=temp->fees*1.06*(temp->days*1.0);
			cout<<"\n\n======	STUDENT PASS NEED TO CONFIRM		======";
			cout<<"\nSTUDENT NAME\t: "<<temp->name<<endl;
			cout<<"STUDENT IC\t: "<<temp->ic<<endl;
			cout<<"METRIC NO\t: "<<temp->metricNum<<endl;
			cout<<"DATE OF ISSUE\t: "<<temp->DateoI<<endl;
			cout<<"DATE OF EXPIRY\t: "<<temp->DateoE<<endl;
			cout<<"NUMBER OF DAYS\t: "<<temp->days<<endl;
			cout<<"FEES\t: RM"<<temp->fees<<endl;
			cout<<"TOTAL(INCLUDING ADMIN FEES): RM"<<temp->total<<endl;
		}
		
		//implementation of queue 
		string deQueue(){
			billNode *temp=new billNode;
			temp = frontPtr;
 			if (frontPtr == NULL) {
    			cout<<"NO PENDING STUDENT PASS NEED TO BE CONFIRMED"<<endl;
				return "NULL";
  			}
   			else if (temp->next != NULL) {
				
				int choice;
				displayInvoice(temp);	
				do{	
				cout<<"DO YOU WANT TO CONFIRM THIS STUDENT PASS? (0-PENDING, 1-CONFIRMED, 2-CANCELLED) : ";
				cin>>choice;
					if(choice==1){
						temp = temp->next;
    					frontPtr = temp;
    					return "STUDENT PASS-CONFIRMED";
    				}
    				else if(choice==0){
    				temp = temp->next;
    				frontPtr = temp;
					return "STUDENT PASS-PENDING";
					}
					else if(choice==2){
					temp = temp->next;
    				frontPtr = temp;
					return "CANCELLED";
					}
				}while(choice<0&&choice>2);
				
   				 
   			}
			else {
   				int choice;
   				displayInvoice(temp);
   				do{			   
   				cout<<"\n\nDO YOU WANT TO CONFIRM THIS RENEWAL? (0-PENDING, 1-CONFIRMED, 2-CANCELLED) : ";
   				cin>>choice;
   					if(choice==1){
   					temp = temp->next;
    				frontPtr = temp;
    				return "RENEWAL-CONFIRMED";
    				}
    				else if(choice==0){
    				return "RENEWAL-PENDING";
					}
					else if(choice==2){
					return "CANCELLED";
					}
				}while(choice<0&&choice>2);
			}
		
		}
		billNode* getFrontRN(){
			billNode *t=new billNode;
				if(frontPtr!=NULL){
				t=frontPtr;
				}
			return t;
		}
};

class applicantNode{
	public:
	string applicantName;
	string applicantPhone;
	string ic;
	string DateoI;
	string DateoE;
	int metricNum;
	applicantNode *next;
};

class applicants{
	applicantNode *head;
	public:
		applicants(){head=NULL;}
			
		void sortedApplicantIn(string n, string p, string ic, string in,string out,int rn){
			int currIndex=0;
			applicantNode *currNode=head;
			applicantNode *prevNode=NULL;
				while(currNode && n > currNode->applicantName){
					prevNode=currNode;
					currNode=currNode->next;
					currIndex++;	
				}	
			applicantNode *newNode=new applicantNode;
			newNode->applicantName=n;
			newNode->applicantPhone=p;
			newNode->ic=ic;
			newNode->DateoI=in;
			newNode->DateoE=out;
			newNode->metricNum=rn;
				if (currIndex==0){
					newNode->next=head;
					head=newNode;
				}
				else{
				newNode->next=prevNode->next;
				prevNode->next=newNode;
				}	
		}
		void deleteApplicant(string ic,int rn){ 
			applicantNode* prevNode = NULL;
			applicantNode* currNode = head;
			int currIndex = 1;
		
			string IC=currNode->ic.substr(0,12);
			int y = atoi(IC.c_str());
			int x= atoi(ic.c_str());
	
			while ((currNode && x!= y)||(currNode && currNode->metricNum!=rn)) {
				prevNode = currNode;
				currNode = currNode->next;
				currIndex++;
			}
			
			if(x==y){
				if (currNode) {
					if (prevNode) {
						prevNode->next = currNode->next;
						delete currNode;
					}
					else {
						head = currNode->next;
						delete currNode;
					}
				}
			cout<<"STUDENT PASS("<<rn<<") UNDER STUDENT WITH IC "<<ic<<" HAS BEEN DELETED "<<endl;
			}
	        else{
	        cout<<"STUDENT PASS RECORD OF "<<rn<<" UNDER STUDENT WITH IC "<<ic<<" CANNOT BE FOUND"<<endl;	
			}
		}
			
		bool findApplicant(string _ic){ 
			applicantNode* currNode = head;
			int currIndex = 1;
			string IC=currNode->ic.substr(0,13);
			int y = atoi(IC.c_str());
			int x= atoi(_ic.c_str());
			if (x==y)
				return true;
			else
				return false;
		}
		
		void displayApplicantRec(){ 
			int num = 0; 
			applicantNode* currNode = head; 
			cout<<"\n\n======================================    STUDENT PASS RECORD    ======================================"<<endl;
			cout<<"--------------------------------------------------------------------------------------------------------"<<endl;
			cout<<left<<setw(40) <<"NAME"<<setw(11)<<"METRIC NO."<<setw(15)<<"PHONE"<<setw(20)<<"IC"<<setw(12)<<"DATE OF ISSUE"<<setw(12)<<"DATE OF EXPIRY"<<endl;
			
			while (currNode != NULL){ 
				cout <<left<<setw(40)<<currNode->applicantName
					 <<setw(11)<< left<<currNode->metricNum
					 <<setw(15)<< left<<currNode->applicantPhone
					 <<setw(20)<< left<<currNode->ic
					 <<setw(12)<< left<<currNode->DateoI
					 <<setw(12)<< left<<currNode->DateoE
					 << endl; 
				currNode = currNode->next; 
				num++; 
			} 
			cout << "\nNUMBER OF STUDENT PASS: " << num << endl<<endl<<endl;
		}
		
};

class studentspassNode{
	public:
	int refNo;
	int metricNum;
	int studentspasstype;
	float fees;
	int status;
	studentspassNode *next;
	studentspassNode *prev;
};

string rt(int rt){
	if(rt==1){
		return "EFTB";
	}
	else if(rt==2){
		return "GETB";
	}
	else if(rt==3){
		return "TPIB";
	}
	else if(rt==4){
		return "OTHER";
	}
	else{
		return "DEFAULT";
	}
}

string status(int status){
	if(status==1){
		return "STUDENT PASS-PENDING";
	}
	else if(status==2){
		return "STUDENT PASS-CONFIRMED";
	}
	else if(status==0){
		return "VAILD";
	}
	else{
		return "DEFAULT";
	}
}

class studentspass{
	private:
		studentspassNode *head;
		int refcs = 0;
		
	public:
		studentspass(){
			head=NULL;
		}
		
		void insertSortedStudentspass(int metricNum){
			int currIndex=0;
			studentspassNode *currNode=head;
			studentspassNode *prevNode=NULL;
				while(currNode && metricNum > currNode->metricNum){
					prevNode=currNode;
					currNode=currNode->next;
					currIndex++;	
				}	
			studentspassNode *newNode=new studentspassNode;
			newNode->metricNum=metricNum;
			newNode->refNo= refcs++;
			newNode->studentspasstype=(metricNum-(metricNum/1000*1000))/100;
			newNode->fees=setfees(newNode);
			newNode->status=0;
			if (currIndex==0){
				newNode->next=head;
				head=newNode;
			}
			else{
				newNode->next=prevNode->next;
				prevNode->next=newNode;
			}
		}
		float setfees(studentspassNode *n){
			float p=0;
			studentspassNode *newNode=new studentspassNode;
			newNode=n;
			if(newNode->studentspasstype==1){
				p+=80.00;
			}
			else if(newNode->studentspasstype==2){
				p+=120.00;
			}
			else if(newNode->studentspasstype==3){
				p+=150.00;
			}
			else if(newNode->studentspasstype==4){
				p+=200.00;
			}
			else{
				p=0.00;
			}
			p+=(newNode->refNo*10.00);
			return p;
		}
		
		void deleteStudentspass(int rn){
			studentspassNode* prevNode = NULL;
			studentspassNode* currNode = head;
			int currIndex = 1;
			while (currNode && currNode->metricNum != rn) {
				prevNode = currNode;
				currNode = currNode->next;
				currIndex++;
			}
			if (currNode) {
			if (prevNode) {
				prevNode->next = currNode->next;
				delete currNode;
			}
			else {
				head = currNode->next;
				delete currNode;
			}
			cout<<"YOU SUCCESSFULLY DELETE THE STUDENT PASS WITH NUMBER :"<<rn<<endl;
	        }
	        else{
	        cout<<"STUDENT PASS NUMBER ("<<rn<<") DOES NOT EXIST."<<endl;	
			}
		}
		bool bookStudentspass(int rn){
			studentspassNode *newNode=new studentspassNode;
			newNode=findStudentspass(rn);
			if(!newNode){
				cout<<"STUDENT PASS NUMBER "<<rn<<" CANNOT BE FOUND\n"<<endl;
				return false;
			}
			else{
				if(newNode->status==0){
					newNode->status=1;
					cout<<"STUDENT PASS NUMBER "<<rn<<" IS SUCCESSFULLY ADDED\n\n"<<endl;
					return true;
				}
				else{
					cout<<"STUDENT PASS NUMBER "<<rn<<" IS NOT AVAILABLE\n\n"<<endl;
					return false;
				}
			}
		} 
		
		bool cancelStudentspass(int rn){
			studentspassNode *newNode=new studentspassNode;
			newNode=findStudentspass(rn);
			if(!newNode){
				cout<<"STUDENT PASS NUMBER "<<rn<<" CANNOT BE FOUND"<<endl;
				return false;
			}
			else{
				if(newNode->status==1){
					newNode->status=0;
					cout<<"STUDENT PASS WITH NUMBER"<<rn<<" IS SUCCESSFULLY CANCELLED"<<endl;
					return true;
				}
				else{
					cout<<"STUDENT PASS NUMBER ("<<rn<<") CANNOT BE FOUND"<<endl;
					cout<<"UNABLE TO MAKE CANCELLATION"<<endl;
					return false;
				}
			}
	};
		
		bool findBookStudentspass(int rn){
			studentspassNode *newNode=new studentspassNode;
			newNode=findStudentspass(rn);
			if(!newNode){
				return false;
			}
			else{
				if(newNode->status==1){
					return true;
				}
				else{
					return false;
				}
			}
		}

		studentspassNode* findStudentspass(int rn){			
			studentspassNode* currNode = head;
			int currIndex = 1;
			while (currNode && currNode->metricNum != rn) {
			currNode = currNode->next;
			currIndex++;
			}
			if (currNode)
				return currNode;
			else
			return 0;
		}
		
		void displayStudentspass(){
			int num = 0; 
			studentspassNode* currNode = head; 
			cout<<"====================    STUDENT PASS RECORD    ===================="<<endl;
			cout<<"-----------------------------------------------------------------"<<endl;
			cout<<"REF.\tMETRIC NO.\tINSURANCE TYPE\tFEES\tSTATUS"<<endl;
			
			
			while (currNode != NULL){ 
				cout <<currNode->refNo<<"\t"
					 <<currNode->metricNum <<"\t\t"
					 <<rt(currNode->studentspasstype)<<"\t\t"
					 <<currNode->fees<<"\t"
					 <<status(currNode->status)<<"\t"
					 << endl; 
				currNode = currNode->next; 
				num++; 
			} 
			cout << "\nNUMBER OF STUDENTS IN THE RECORD: " << num << endl<<endl<<endl;
		}
};

int getDays(string date) {
        int year = atoi(date.substr(0, 4).c_str());
        int month = atoi(date.substr(4, 2).c_str());
        int day = atoi(date.substr(6, 2).c_str());
        int ans = 0;
        for (int i = 1900; i < year; ++ i) {
            if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
                ans += 366;
            } else {
                ans += 365;
            }
        }
        for (int i = 1; i < month; ++ i) {
            switch(i) {
                case 1: ans += 31; break;
                case 2: ans += (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) ? 29 : 28; break;
                case 3: ans += 31; break;
                case 4: ans += 30; break;
                case 5: ans += 31; break;
                case 6: ans += 30; break;
                case 7: ans += 31; break;
                case 8: ans += 31; break;
                case 9: ans += 30; break;
                case 10: ans += 31; break;
                case 11: ans += 30; break;
                case 12: ans += 31; break;
            }
        }
        return ans += day - 1;
    }

int daysBetweenDates(string date1, string date2) {
        return abs(getDays(date1) - getDays(date2));
}

int main(){
	
	//CREATE STUDENT PASS
	studentspass h;
	applicants cn;
	billQueue bq;
	int choice;
	
	//ADD DEFAULT STUDENT PASS
	int defaultstudentspass[]={1101,1102,1103,1104,1202,1303,2201,2202,2203,3301,3302,3303,3304,4401,4402} ;
	for(int x=0;x<15;x++){
		h.insertSortedStudentspass(defaultstudentspass[x]);
	}

	do{
		system("CLS");
		cout<<"=============		UTM International Visa Counter System		============="<<endl;
		cout<<"\t\t\tLOGIN AS"<<endl;
		cout<<"\t\t\t1. ADMIN\n\t\t\t2. STUDENT \n\t\t\t3. EXIT\n"<<endl;
		cout<<"CHOICE : ";
		cin>>choice;
		switch(choice){
			case 1:{
				int ch1;
				int rn;
				int cont1;
				do{
				system("CLS");
				cout<<"=============	ADMIN MENU	============="<<endl;
				cout<<"\t1. ADD STUDENT\n\t2. DELETE STUDENT\n\t3. DISPLAY STUDENTS\n\t4. CHANGE FEES\n\t5. CHECK RECORD LIST\n\t6. REVIEW AND CONFIRM PENDING STUDENTS\n\t7. BACK TO MAIN MENU\n"<<endl;
				cout<<"CHOICE : ";
				cin>>ch1;
				switch(ch1){
				case 1:
					cont1=1;
					do{
					cout<<"\nENTER THE STUDENT NUMBER YOU WANT TO ADD : ";
					cin>>rn;
					if(!h.findStudentspass(rn)){
						h.insertSortedStudentspass(rn);
						cout<<"YOU SUCCESSFULLY ADD STUDENT NUMBER ("<<rn<<") TO THE LIST"<<endl;
					}
					else{
						cout<<"STUDENT NUMBERED "<<rn<<" EXISTED.  ENTER OTHER STUDENT NUMBER."<<endl;
					}
					cout<<"DO YOU WANT TO CONTINUE TO ADD MORE STUDENT ( 1-YES, 0-NO ) :";
					cin>>cont1;
					}while(cont1!=0);
					break;
				case 2:
					cont1=1;
					do{
					cout<<"\nENTER THE STUDENT NUMBER YOU WANT TO DELETE : ";
					cin>>rn;
					if(h.findStudentspass(rn)){
						h.deleteStudentspass(rn);
					}
					else{
						cout<<"STUDENT CANNOT BE FOUND! ENTER OTHER STUDENT NUMBER."<<endl;
					}
					cout<<"DO YOU WANT TO CONTINUE TO DELETE MORE STUDENTS( 1-YES, 0-NO ) : ";
					cin>>cont1;
					}while(cont1!=0);
					break;
				case 3:
					h.displayStudentspass();
					break;
				case 4:
					cont1=1;
					do{
					cout<<"\nENTER THE STUDENT NUMBER THAT YOU WANT CHANGE FEES: "<<endl;
					cout<<"STUDENT NUMBER        : ";
					cin>>rn;
					if(h.findStudentspass(rn)){
						float p;
						cout<<"CHANGE TO FFES RM : ";
						cin>>p;
						studentspassNode *newNode=h.findStudentspass(rn);
						newNode->fees=p;
						cout<<"YOU SUCCESSFULLY CHANGE THE FEES OF STUDENT NUMBER "<<rn<<" TO FEES RM "<<p<<endl<<endl;
					}
					else{
						cout<<"STUDENT NUMBER ("<<rn<<") CANNOT BE FOUND. ENTER OTHER STUDENT NUMBER."<<endl<<endl;
					}
					cout<<"DO YOU WANT TO CONTINUE TO CHANGE FEES OF THE OTHER STUDENTS ( 1-YES, 0-NO ) :";
					cin>>cont1;
					}while(cont1!=0);
					break;
				case 5:
					cn.displayApplicantRec();
					break;
				case 6:
					cont1=1;
					
					cout<<"\n\n======     START TO REVIEW STUDENT PASS INFORMATION     ======\n";
					do{
					
					billNode* rno=new billNode;
					rno=bq.getFrontRN();
					string con=bq.deQueue();
					studentspassNode *t=new studentspassNode;
					t=h.findStudentspass(rno->metricNum);
					if(con=="ADDED & CONFIRMED"){
						t->status=2;
						
						break;
					}
					else if(con=="CANCELLED"){
						t->status=0;
						break;
					}
					else if(con=="ADDED & PENDING"){
						t->status=1;
						bq.enQueue(rno->metricNum,rno->fees,rno->ic,rno->name,rno->DateoI,rno->DateoE,rno->days);
						break;	
					}
					else {}
					
					cout<<"DO YOU WANT TO CONTINUE TO REVIEW ( 1-YES, 0-NO ) :";
					cin>>cont1;
						
				}while(cont1!=0);	
					break;
				case 7:
					break;
				default:
					cout<<"INVALID CHOICE."<<endl;
					break;
			}
				system("pause");
				getch();	
			
			}while(ch1!=7);
			break;
			}
			break;
			
			case 2:{
				int ch2;
				int rn,rn2;
				int cont2;
				do{
				system("CLS");
				cout<<"=============	STUDENT MENU	============="<<endl;
				cout<<"\t1. DISPLAY STUDENT PASS\n\t2. RENEW A STUDENT PASS\n\t3. CANCEL A STUDENT PASS\n\t4. BACK TO MAIN MENU"<<endl;
				cout<<"CHOICE : ";
				cin>>ch2;
				switch(ch2){
				case 1:
					h.displayStudentspass();
					break;
				case 2:
					cont2=1;
					do{
					cout<<"\nENTER YOUR METRIC NUMBER : ";
					cin>>rn;
					bool book=h.bookStudentspass(rn);
					if(book){
					string n, p, ic, in, out;
					int din,min,yin,dout,mout,yout;
					char s;
					cout<<"======== YOUR PERSONAL DETAILS ========"<<endl;
					cout<<"ENTER YOUR NAME      : ";
					cin.ignore();
					getline(cin,n);
					cout<<"ENTER YOUR PHONE NO  : ";
					getline(cin,p);
					cout<<"ENTER YOUR IC (xxxxxx-xx-xxxx): ";
					getline(cin,ic);
					cout<<"DATE OF ISSUE (YYYYMMDD)   : ";
					getline(cin,in);
					cout<<"DATE OF EXPIRY (YYYYMMDD)  : ";
					getline(cin,out);
					int days=daysBetweenDates(in,out);
					cn.sortedApplicantIn(n,p,ic,in,out,rn);
					cout<<"\n----------------------------------\n";
					cout<<"\nPLEASE PROCEEED TO BILL AT COUNTER\n";
					cout<<"\n----------------------------------\n";
					studentspassNode *t=new studentspassNode;
					t=h.findStudentspass(rn);
					bq.enQueue(rn,t->fees,ic,n,in,out,days);
					}
					cout<<"DO YOU WANT TO CONTINUE( 1-YES, 0-NO ) :";
					cin>>cont2;
					}while(cont2!=0);
					break;
					
				case 3:
					cont2=1;
					do{
					string ic2;
					int rn2=0;
					cout<<"\nENTER METRIC NUMBER TO CANCEL STUDENT PASS : ";
					cin>>rn2;
					cout<<"ENTER YOUR IC TO MAKE CANCELLATION (xxxxxx-xx-xxxx): ";
					cin.ignore();
					getline(cin,ic2);
					
					bool targetStudentspass=h.findBookStudentspass(rn2);
					if(targetStudentspass){
						bool targetApplicant=cn.findApplicant(ic2);
						if(targetApplicant){
							h.cancelStudentspass(rn2);
							cn.deleteApplicant(ic2,rn2);
						}
						else{
						cout<<"\nRECORD CANNOT BE FOUND\nUNABLE TO MAKE CANCELLATION"<<endl;
						}
					}
					else{
						cout<<"RECORD CANNOT BE FOUND\nUNABLE TO MAKE CANCELLATION"<<endl;
					}
					
					cout<<"DO YOU WANT TO CONTINUE ( 1-YES, 0-NO ) : ";
					cin>>cont2;
					}while(cont2!=0);
					break;
				case 4:
					break;
				default:
					cout<<"INVALID CHOICE."<<endl;
					break;
			}
				system("pause");
				getch();
				
			}while(ch2!=4);
				break;
			}
			case 3: 
				cout<<"THANK YOU AND HAVE NICE DAY!"<<endl;
				exit(0);
			default:
				cout<<"INVALID CHOICE."<<endl;
				break;	
		}
		
	getch();
	}while (choice!=3);
	
	return 0;
}

