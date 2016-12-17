#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

void connectionSetup(int &newsockfd){

	struct sockaddr_in server,client;

	//intialize the socket file discriptor
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&server,sizeof(server));

	//assign value to sockadd_in members
	server.sin_family = AF_INET;
	server.sin_port = htons(4912);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//binding 
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));

	//listen
	listen(sockfd,1);
	socklen_t clientLen = sizeof(client); 
	newsockfd = accept(sockfd,(struct sockaddr*)&client,&clientLen);

	cout<<"\nUser A is connected to User B successfully..";

}

int RSA_EncryptAndDecrypt(long Pi,int key[]){

	long val = Pi % key[1];
	long temp = 1;

	for (int i = 1; i <= key[0]; ++i){
		temp=(temp *val)%key[1];
	}

	return temp;
}

int main(int argc, char const *argv[]){
	
	int newsockfd;
	connectionSetup(newsockfd);

	int PU[2];
	//recive the public key of client
	int temp;
	recv(newsockfd,&temp,sizeof(temp),0);
	PU[0]=ntohs(temp);

	recv(newsockfd,&temp,sizeof(temp),0);
	PU[1]=ntohs(temp);
	cout<<"\nPU{e,n} = { "<<PU[0]<<" , "<<PU[1]<<" }";

	long msg;
	cout<<"\nEnter the message to encrypt and send : ";
	cin>>msg;
	
	long enMsg = RSA_EncryptAndDecrypt(msg,PU);
	cout<<"\nEnMsg = "<<enMsg;
	long Ltemp = htonl(enMsg);
	send(newsockfd,&Ltemp,sizeof(Ltemp),0);


	return 0;
}