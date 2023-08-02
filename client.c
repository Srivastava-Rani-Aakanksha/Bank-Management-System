//Aakanksha Rani
//MT2022001
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>               // Internet Protocol family
#include<arpa/inet.h>                // for htons()
#include<unistd.h>
#include<stdbool.h>

typedef struct normalUser{
	int userID;
	char name[30];
	char password[10];
	int account_no;
	float balance;
	char status[20];
}normalUser;

typedef struct jointUser{
	int userID;
	char name1[30];
	char name2[30];
	char password[10];
	int account_no;
	float balance;
	char status[20];
}jointUser;

typedef struct admin{
	int userID;
	char username[30];
	char password[10];
}admin;

void attemptNormalUserLogin(int sd);
void attemptJointUserLogin(int sd);
void attemptAdminLogin(int sd);
void showMenu(int sd);
void deposit(int sd);
void withdraw(int sd);
void balanceEnquiry(int sd);
void changePassword(int sd);
void viewDetails(int sd);
void addAccount(int sd);
void deleteAccount(int sd);
void modifyAccount(int sd);
void searchAccount(int sd);
int option,currUserID;

void chooseOption(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------WELCOME TO ARS BANK----------------- ");
    printf("\n\n\t\t1. User-Login \n\t\t2. JointUser-Login\n\t\t3. Admin-Login\n\n\n\n\n\t\tEnter your choice:");

	scanf("%d",&option);
	printf("Option : %d\n",option);

	switch(option){
		case 1 :
			attemptNormalUserLogin(sd);
			break;
		case 2 :
			attemptJointUserLogin(sd);
			break;
		case 3 :
			attemptAdminLogin(sd);
			break;
		default :
			printf("INVALID INPUT ... \n TRY AGAIN\n");
			chooseOption(sd);
			break;
	}
	return;
}

void showMenu(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------LOGIN-OPTIONS----------------- ");
	
	int select;
	if(option==1 || option==2){

		printf("\n\n\t\t1. Deposit");
		printf("\n\t\t2. Withdraw");
		printf("\n\t\t3. Balance Enquiry");
		printf("\n\t\t4. Change Password");
		printf("\n\t\t5. Account Details");
		printf("\n\t\t6. Exit");
		printf("\n\t\t Enter your choice: ");

		scanf("%d",&select);
		printf("Option Selected : %d\n",select);

		switch(select){
		case 1 :
			deposit(sd);
			break;
		case 2 :
			withdraw(sd);
			break;
		case 3 :
			balanceEnquiry(sd);
			break;
		case 4 :
			changePassword(sd);
			break;
		case 5 :
			viewDetails(sd);
			break;
		case 6 :
			write(sd,&select,sizeof(int));
			printf("\n\n\n.........THANK YOU.........\n\n\n Developed by Aakanksha Rani\n\n\nRollNo: MT2022001");
			exit(0);
		default :
			printf("INVALID INPUT ... \n TRY AGAIN\n");
			showMenu(sd);
			break;
		}
	}
	else if(option==3){

		printf("\n\n\t\t1. Add Account");
		printf("\n\t\t2. Delete Account");
		printf("\n\t\t3. Modify Account");
		printf("\n\t\t4. Search Account");
		printf("\n\t\t5. Exit");
		printf("\n\t\t Enter your choice: ");

		scanf("%d",&select);
		printf("Option : %d\n",select);

		switch(select){
		case 1 :
			addAccount(sd);
			break;
		case 2 :
			deleteAccount(sd);
			break;
		case 3 :
			modifyAccount(sd);
			break;
		case 4 :
			searchAccount(sd);
			break;
		case 5 :
			write(sd,&select,sizeof(int));
			printf("\n\n\n.........THANK YOU.........\n\n\n Developed by Aakanksha Rani\n\n\nRollNo: MT2022001");
			exit(0);
		default :
			printf("INVALID INPUT ... \n TRY AGAIN\n");
			showMenu(sd);
			break;
		}
	}
}

void attemptNormalUserLogin(int sd){
	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------USER-LOGIN----------------- ");
	bool result;
	normalUser currUser;

	printf("\n\n\t\t\tEnter USER-ID: \n");
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;

	printf("\n\n\t\t\tEnter Password:");
	scanf("%s",currUser.password);

	//to the server
	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(normalUser));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		printf("INVALID INPUT ... \n TRY AGAIN\n");
		// write(1,"Invalid login!!\n\n",sizeof("Invalid login!!\n\n"));
		chooseOption(sd);
	}
	else{
		printf("Logged in Succesfully!\n");
	}
	return;
}

void attemptJointUserLogin(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------JOINT-USER-LOGIN----------------- ");

	bool result;
	jointUser currUser;


	printf("\n\n\t\t\tEnter USER-ID: \n");
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;

	printf("\n\n\t\t\tEnter Password:");
	scanf("%s",currUser.password);

	//to the server
	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(jointUser));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		printf("INVALID INPUT ... \n TRY AGAIN\n");
		chooseOption(sd);
	}
	else{
		printf("Logged in Succesfully!\t Welcome\n");
	}
	return;
}

void attemptAdminLogin(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------ADMIN-LOGIN----------------- ");

	bool result;
	admin currUser;

	printf("\n\n\t\t\tEnter USER-ID: \n");
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;

	printf("\n\n\t\t\tEnter Password:");
	scanf("%s",currUser.password);

	//to the server
	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(admin));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		printf("INVALID INPUT ... \n TRY AGAIN\n");
		chooseOption(sd);
	}
	else{
		printf("Logged in Succesfully!\t Welcome\n");
	}
	return;
}

void deposit(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------DEPOSIT----------------- ");

	float amt;
	int select=1;
	bool result;

	printf("\n\n\t\t\tAmount to Deposit : Rs. \n");
	scanf("%f",&amt);

	while(amt<=0){
		printf("Enter an amount to deposit: Rs.\n");
		scanf("%f",&amt);
	}

	//to the server
	write(sd,&select,sizeof(int));
	write(sd,&amt,sizeof(float));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		printf("Error depositing! Please connect with the bank\n\n");
	}
	else{
		printf("Succesfully deposited...");
	}
	showMenu(sd);
	return;
}

void withdraw(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------WITHDRAW----------------- ");

	float amt;
	int select=2;
	bool result;

	printf("\n\n\t\t\tAmount to Withdraw : Rs. \n");
	scanf("%f",&amt);

	while(amt<=0){
		printf("Enter an amount to withdraw\n");
		printf("\n\n\t\t\tAmount to Withdraw : Rs.");
		scanf("%f",&amt);
	}

	//to the server
	write(sd,&select,sizeof(int));
	write(sd,&amt,sizeof(float));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){

		printf("Error withdrawing! Please connect with the bank or balance insufficient\n\n");
	}
	else{
		printf("Succesfully withdrew...");
	}
	showMenu(sd);
	return;
}

void balanceEnquiry(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------BALANCE  ENQUIRY---------------- ");

	float amt;
	int select=3;
	int len;

	//to the server
	write(sd,&select,sizeof(int));

	len=read(sd,&amt,sizeof(float));	//from server

	printf("\n\n\t\t\tAvailable Balance : Rs. ");
	
	printf("%0.2f\n\n",amt);

	sleep(2);
	getchar();
	getchar();
	showMenu(sd);
	return;
}

void changePassword(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------CHANGE PASSWORD---------------- ");

	int select=4;
	char nPassword[10];
	bool result;

	printf("\n\n\t\t\tNew Password (maximum 10 characters): ");

	scanf("%s",nPassword);

	//to the server
	write(sd,&select,sizeof(int));
	write(sd,nPassword,sizeof(nPassword));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		printf("\n\n\nError changing password\n\n");
	}
	else{
		printf("\n\n\nPassword changed Succesfully!\n\n");
	}

	showMenu(sd);
	return;
}

void viewDetails(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------ACCOUNT DETAILS---------------- \n\n\n");
	int select=5;

	//to the server
	write(sd,&select,sizeof(int));

	if(option==1){
		normalUser currUser1;
		read(sd,&currUser1,sizeof(normalUser));

		printf("User ID : %d\n",currUser1.userID);
		printf("Account Holder Name : %s\n",currUser1.name);
		printf("Account Number : %d\n",currUser1.account_no);
		printf("Available Balance : Rs.%0.2f\n",currUser1.balance);
		printf("Status : %s\n\n",currUser1.status);
	}
	else if(option==2){
		jointUser currUser2;
		read(sd,&currUser2,sizeof(jointUser));

		printf("User ID : %d\n",currUser2.userID);
		printf("Main Account Holder's Name : %s\n",currUser2.name1);
		printf("Other Account Holder's Name : %s\n",currUser2.name2);
		printf("Account Number : %d\n",currUser2.account_no);
		printf("Available Balance : Rs.%0.2f\n",currUser2.balance);
		printf("Status : %s\n\n",currUser2.status);
	}
	sleep(5);
	getchar();
	getchar();
	showMenu(sd);
	return;
}

void addAccount(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------NEW ACCOUNT---------------- ");
	int select=1;
	int type;
	bool result;

	write(sd,&select,sizeof(int));

	printf("\n\n\t\t\tAccount Type:\n\t\t\t1: Normal Account \n\t\t\t2: Joint Account");
	printf("\n\n\t\t\tEnter your choice: ");
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser addUser1;
		printf("\n\n\t\t\tName of the account holder :");
		scanf(" %[^\n]",addUser1.name);
		printf("\n\n\t\t\tSet Password(maximum 10 characters) :");
		scanf("%s",addUser1.password);
		printf("\n\n\t\t\tInitial amount to be deposited: Rs.");
		scanf("%f",&addUser1.balance);
		write(sd,&addUser1,sizeof(normalUser));
	}

	if(type==2){
		jointUser addUser2;
		printf("\n\n\t\t\tName of the primary account holder :");
		scanf(" %[^\n]",addUser2.name1);
		printf("\n\n\t\t\tName of the secondary account holder :");
		scanf(" %[^\n]",addUser2.name2);
		printf("\n\n\t\t\tSet Password(maximum 10 characters) :");
		scanf("%s",addUser2.password);
		printf("\n\n\t\t\tInitial amount to be deposited: Rs.");
		scanf("%f",&addUser2.balance);
		write(sd,&addUser2,sizeof(jointUser));
	}

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		printf("\n\n\n\t\t\tError creating new account ");
	}
	else{

		printf("Succesfully created the new account!\n\n");
	}
	showMenu(sd);
	return;
}

void deleteAccount(int sd){
	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------DELETE ACCOUNT---------------- ");

	int select=2;
	int type,userID;
	bool result;

	write(sd,&select,sizeof(int));

	printf("\n\n\t\t\tAccount Type:\n\t\t\t1: Normal Account \n\t\t\t2: Joint Account");
	printf("\n\n\t\t\tEnter your choice: ");
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	printf("\n\n\t\t\tUser ID : ");
	scanf("%d",&userID);
	write(sd,&userID,sizeof(int));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		printf("\n\n\nError deleting the account ,please re-check the User ID or connect with the bank!\n\n");
	}
	else{
		printf("\n\n\nSuccesfully deleted the account!\n\n");
	}
	showMenu(sd);
	return;
}

void modifyAccount(int sd){

	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------MODIFY ACCOUNT---------------- ");
	int select=3;
	int type;
	bool result;

	write(sd,&select,sizeof(int));

	printf("\n\n\t\t\tAccount Type:\n\t\t\t1: Normal Account \n\t\t\t2: Joint Account");
	printf("\n\n\t\t\tEnter your choice: ");
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser modUser1;
		printf("\n\n\n\t\t\tUser ID : ");
		scanf("%d",&modUser1.userID);
		printf("\n\n\n\t\t\tAccount Number : ");
		scanf("%d",&modUser1.account_no);
		printf("\n\n\n\t\t\tNew Name of the account holder : ");
		scanf(" %[^\n]",modUser1.name);
		printf("\n\n\n\t\t\tNew Password(max 10 characters) : ");
		scanf("%s",modUser1.password);
		printf("\n\n\n\t\t\tNew Balance : ");
		scanf("%f",&modUser1.balance);
		write(sd,&modUser1,sizeof(normalUser));
	}

	if(type==2){
		jointUser modUser2;
		printf("\n\n\n\t\t\tUser ID : ");
		scanf("%d",&modUser2.userID);
		printf("\n\n\n\t\t\tAccount Number : ");
		scanf("%d",&modUser2.account_no);
		printf("\n\n\n\t\t\tNew Name of the primary account holder : ");
		scanf(" %[^\n]",modUser2.name1);
		printf("\n\n\n\t\t\tNew Name of the other account holder : ");
		scanf(" %[^\n]",modUser2.name2);
		printf("\n\n\n\t\t\tNew Password(max 10 characters) : ");
		scanf("%s",modUser2.password);
		printf("\n\n\n\t\t\tNew Balance : ");
		scanf("%f",&modUser2.balance);
		write(sd,&modUser2,sizeof(jointUser));
	}

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		printf("\n\n\n\t\t\tError modifying the account ,please re-check the User ID and Account No!\n\n");
	}
	else{
		printf("\n\n\n\t\t\tSuccesfully modified the account!!\n\n");
	}
	showMenu(sd);
	return;
}

void searchAccount(int sd){
	system("clear");
	printf("\n\n\t\t\t----------------- CUSTOMER ONLINE BANKING MANAGEMENT SYSTEM ----------------- ");
    printf("\n\n\t\t\t\t\t\t-----------------ACCOUNT SEARCH---------------- ");

	int select=4;
	int type,len;
	bool result;

	write(sd,&select,sizeof(int));

	printf("\n\n\t\t\tAccount Type:\n\t\t\t1: Normal Account \n\t\t\t2: Joint Account");
	printf("\n\n\t\t\tEnter your choice: ");
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser searchUser1;
		int userID;
		printf("\n\n\n\t\t\tUser ID : ");
		scanf("%d",&userID);
		write(sd,&userID,sizeof(int));

		len=read(sd,&searchUser1,sizeof(normalUser));
		if(len==0){
			write(1,"Please re-check the User ID!!\n\n",sizeof("Please re-check the User ID!!\n\n"));
		}
		else{
			printf("User ID : %d\n",searchUser1.userID);
			printf("Name : %s\n",searchUser1.name);
			printf("Account Number : %d\n",searchUser1.account_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser1.balance);
			printf("Status : %s\n\n",searchUser1.status);
		}
	}

	if(type==2){
		jointUser searchUser2;
		int userID1;
		printf("\n\n\n\t\t\tUser ID : ");
		scanf("%d",&userID1);
		write(sd,&userID1,sizeof(int));

		len=read(sd,&searchUser2,sizeof(jointUser));
		if(len==0){
			write(1,"Please re-check the User ID!!\n\n",sizeof("Please re-check the User ID!!\n\n"));
		}
		else{
			printf("User ID : %d\n",searchUser2.userID);
			printf("Main Account Holder's Name : %s\n",searchUser2.name1);
			printf("Other Account Holder's Name : %s\n",searchUser2.name2);
			printf("Account Number : %d\n",searchUser2.account_no);
			printf("Available Balance : Rs.%0.2f\n",searchUser2.balance);
			printf("Status : %s\n\n",searchUser2.status);
		}
	}
	getchar();
	getchar();
	showMenu(sd);
	return;
}

int main(){

	system("clear");
	struct sockaddr_in server;       // The <netinet/in.h> header defines the sockaddr_in structure
	int sd,msgLength;
	char buff[50];
	char result;

	// connection establishment
	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	// server.sin_addr.s_addr=inet_addr("172.16.81.54"); //other machine
	// server.sin_addr.s_addr=INADDR_ANY; //same machine
	server.sin_addr.s_addr=inet_addr("127.0.0.1");  //same machine  // If inet_addr is successful, it returns the address in network byte order.
	server.sin_port=htons(5555);   // the htons() function converts values between host and network byte orders. These routines convert 16 and 32 bit quantities between network byte order and host byte order. (Network byte order is big endian, or most significant byte first.)

	connect(sd,(struct sockaddr *)&server,sizeof(server));   // int connect(int socket, const struct sockaddr *address, socklen_t address_len);
	chooseOption(sd);
	showMenu(sd);
	close(sd);
	return 0;
}
