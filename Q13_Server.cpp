/*
    Problem : Implementation of Diffe-Hellman Server
    BY:
        Rishav Kumar Goswami
*/

#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

void connectionSetup(int &newsockfd){

	struct sockaddr_in server,client;

	//Step 1: Intialize sockfd
	int sockfd = socket(AF_INET,SOCK_STREAM,0);

	bzero((char*)&server,sizeof(server));

	//Step 2: Intialize the struct member
	server.sin_family = AF_INET;
	server.sin_port = htons(4915);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Step 3: binding
	bind(sockfd,(struct sockaddr* )&server,sizeof(server));

	//Step 4: Start listening
	listen(sockfd,1);
	socklen_t clientLen = sizeof(client);
	cout<<"\nUser A is ready of connection! ";
	newsockfd = accept(sockfd,(struct sockaddr* )&client,&clientLen);

	cout<<"\nUser A connected successfully with User B\n";

}


int main(){

	/*
		Step 1: call the connection Setup function
		Step 2: Read the values of alpha, Xa, q
		Step 3: Calculate the Ya i.e User A Public Key
		Step 4: Send the your Public Key(Ya) to User B(Client)
		Step 5: Receive the Public key(Yb) of User B(Client) 
		Step 6: Calculate the Secret Key
	*/

	cout<<"\n=====================";
	cout<<"\n\tUser A";
	cout<<"\n=====================";
	
	int newsockfd;
	//Step 1:
	connectionSetup(newsockfd);
	
	//Step 2:
	int alpha,Xa,q;
	cout<<"\nEnter values of alpha, Xa, q( Must: alpha < q ): ";
	cin>>alpha>>Xa>>q;

	if(alpha >= q){
		cout<<"\nInvalid input, alpha < q is a required condition\n";
		return -1;
	}
	
	//Step 3:
	long Ya,Yb;
	Ya = long(pow(alpha,Xa)) % q;	 
	cout<<"\nPublic Key Generated(Ya) : "<<Ya;

	//Step 4:
	long temp=htonl(Ya);		//For sending long type into network, we use htonl()
	send(newsockfd,&temp,sizeof(temp),0);

	//Step 5:
	recv(newsockfd,&temp,sizeof(temp),0);
	Yb = ntohl(temp);			//For recieving long type from network, we use ntohl() 
	cout<<"\nRecieved Public Key(Yb) of User B: "<<Yb<<"\n";

	//Step 6:
	long Key = long(pow(Yb,Xa)) % q;
	cout<<"\nSecret Key at User A : "<<Key<<"\n";
	

	return 0;


}