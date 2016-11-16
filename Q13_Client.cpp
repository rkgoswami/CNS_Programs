/*
    Problem : Implementation of Diffe-Hellman Client
    BY:
        Rishav Kumar Goswami
*/

#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

void connectionSetup(int &sockfd){

	struct sockaddr_in server,client;

	//Step 1: Intialize sockfd
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&server,sizeof(server));

	//Step 2: Intialize the struct member
	server.sin_family = AF_INET;
	server.sin_port = htons(4915);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Step 3: Binding
	connect(sockfd,(struct sockaddr* )&server,sizeof(server));
	cout<<"\nUser B connected successfully with User A\n";
}


int main(){

	/*
		Step 1: call the connection Setup function
		Step 2: Read the values of alpha,Xa,q
		Step 3: Calculate the Yb i.e User B Public Key
		Step 4: Receive the Public key(Ya) of User A(Server) 
		Step 5: Send the your Public Key (Yb) to User A(Server)
		Step 6: Calculate the Secret Key
	*/

	cout<<"\n========================";
	cout<<"\n\tUser B";
	cout<<"\n========================";
	int sockfd;
	//Step 1:
	connectionSetup(sockfd);

	//Step 2:
	int alpha,Xb,q;
	cout<<"Enter values of alpha, Xb, q( Must: alpha < q ): ";
	cin>>alpha>>Xb>>q;

	if(alpha >= q){
		cout<<"\nInvalid input, alpha < q is a required condition\n";
		return -1;
	}
	
	//Step 3: 
	long Ya,Yb;
	Yb = long(pow(alpha,Xb)) % q;
	cout<<"\nPublic Key Generated(Yb) : "<<Yb;

	//Step 4:
	long temp;
	recv(sockfd,&temp,sizeof(temp),0);
	Ya = ntohl(temp);					//For recieving long type variable/data from network
	cout<<"\nRecieved Public Key(Ya) of User A: "<<Ya<<"\n";
	
	//Step 5:
	temp = htonl(Yb);					//For sending long type variable/data into network
	send(sockfd,&temp,sizeof(temp),0);

	//Step 6: 
	long Key = long(pow(Ya,Xb)) % q;
	cout<<"\nSecret Key at User B: "<<Key<<"\n";


	return 0;
}