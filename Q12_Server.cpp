/*
    Problem : Implementation of RSA
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
	server.sin_port = htons(4910);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Step 3: binding
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));

	//Step 4: Start listening
	listen(sockfd,1);
	socklen_t clientLen = sizeof(client);
	newsockfd = accept(sockfd,(struct sockaddr* )&client,&clientLen);
	
	cout<<"\nUser A connected successfully with User B\n";

}

long RSAEncryptAndDecrypt(long Pi,int key[]){

	long val = Pi % key[1];
	long tVal=1;
	for (int i = 1; i <= key[0]; ++i){
		tVal = (tVal*val)% key[1];
	}
	return tVal;
}



int gcd(int a,int b){
	if(b==0)
		return a;
	else
		gcd(b,a%b);
}

int main(){

	cout<<"\n=====================";
	cout<<"\n\tUser A";
	cout<<"\n=====================";
	
	/* 	RSA Algorithm :
		==============
		Step 0: Setup a TCP connection between User A and User B
		Step 1: Take input prime p and q
		Step 2: Calculate n = p*q
		Step 3: Calculate fi(n) = fi(p)*fi(q)=(p-1)*(q-1), 
				since both are prime and applying Euler Totient theorem 
		Step 4: Find e such that gcd(e,fi(n))=1
				Step 4.1: Iterate Step 4 until the condition satisfy 
				Step 4.2: Display Public Key as PU_a = {e,n}
		Step 5: Calculate the Private key
				Step 5.1: Find 'd' such that (d*e) mod fi(n) = 1
				Step 5.2: Display Private Key as PR_a = {d,n}
		
		Step 6: Share its Public Key to User B
		Step 7: Recieve the Public key of User B
		Step 8: Read message to be send to User B,
		Step 9: Encrypt the message using the public key of User B(PU_b) and Send
				-----------------------------------------------------------------
				Step 8.1: Calculate C = M^( PU_b ) mod n 
				Step 8.2: Send the Cipher Text C to User B
		Step 10: Recieve the message from User B
		Step 11: Decrypt the recieved message using its private key(PR_a) and Send
				-----------------------------------------------------------------
				Step 11.1: Calculate M = C^( PR_a ) mod n
				Step 11.2: Display the Decrypted text
	*/

	//Step 0:
	int newsockfd;
	connectionSetup(newsockfd);
	
	//Step 1:
	int p,q;
	cout<<"\nEnter the value of p and q (both must be prime): ";
	cin>>p>>q;

	//Step 2:
	long n = p*q;

	//Step 3:
	long fiN = (p-1)*(q-1);

	//Step 4:
	int e;
	cout<<"\nEnter a prime no. 'e' less than "<<fiN<<" : ";
	cin>>e;

	while(gcd(e,fiN)!=1){
		cout<<"\nReEnter the value of e ( gcd(e,fi(n)) = 1 ): ";
		cin>>e;
	}
	cout<<"\nPublic Key : {"<<e<<","<<n<<"}";
	//Step 5:
	int d=1;
	while(1){

		if( (e*d)%fiN == 1)
			break;
		d++;
	}
	cout<<"\nPrivate Key : {"<<d<<","<<n<<"}";

	//Step 6:
	int PU_a[] = {e,n};
	int PR_a[] = {d,n};

	int temp = htons(e);
	send(newsockfd,&temp,sizeof(temp),0);
	temp = htons(n);
	send(newsockfd,&temp,sizeof(temp),0);
	cout<<"\nPublic Key is Sent..";

	//Step 7:
	int PU_b[2];
	recv(newsockfd,&temp,sizeof(temp),0);
	PU_b[0] = ntohs(temp);
	recv(newsockfd,&temp,sizeof(temp),0);
	PU_b[1] = ntohs(temp);

	cout<<"\nRecived Public Key of User B : {"<<PU_b[0]<<","<<PU_b[1]<<"}\n";
	

	//Transaction Authentication
	/*
		Step T1 : 'A' sends Nonce N1 along with ID_A as E(PU_b,[N1||ID_A])
		Step T2 : 'B' return Nonce N1 and N2 as E(PU_a,[N1||N2])
		Step T3 : 'A' sends N2 to 'B' as E(PU_b,N2)
		Step T4 : 'A' sends K to 'B' as E(PU_b,[E(PR_a,K)]) 
	*/

	//'A' send N1 and ID_A
	long N1,N2,ID_A;
	long enN1,enN2,Ltemp,enID_A;

	cout<<"\nEnter the value of nonce n1 and ID_A: ";
	cin>>N1>>ID_A;
	
	enN1 = RSAEncryptAndDecrypt(N1,PU_b);
	enID_A = RSAEncryptAndDecrypt(ID_A,PU_b);
	
	Ltemp = htonl(enN1);
	send(newsockfd,&Ltemp,sizeof(Ltemp),0);
	Ltemp = htonl(enID_A);
	send(newsockfd,&Ltemp,sizeof(Ltemp),0);


	//Recive the nonce N1 and N2 from 'B'
	recv(newsockfd,&Ltemp,sizeof(Ltemp),0);
	enN1 = ntohl(Ltemp);
	long recN1 = RSAEncryptAndDecrypt(enN1,PR_a);
	cout<<"\nNonce N1 recv = "<<recN1;

	if(recN1 == N1){
		cout<<"\nReciver is verified...";
	}

	recv(newsockfd,&Ltemp,sizeof(Ltemp),0);
	enN2 = ntohl(Ltemp);
	N2 = RSAEncryptAndDecrypt(enN2,PR_a);
	cout<<"\nNonce N2 recv = "<<N2;

	//Send the N2
	enN2 = RSAEncryptAndDecrypt(N2,PU_b);
	Ltemp = htonl(enN2);
	send(newsockfd,&Ltemp,sizeof(Ltemp),0);

	//Send the secret key
	long secKey;
	cout<<"\nEnter the value of secret key: ";
	cin>>secKey;

	long enKey = RSAEncryptAndDecrypt(secKey,PR_a);
	enKey = RSAEncryptAndDecrypt(enKey,PU_b);

	Ltemp = htonl(enKey);
	send(newsockfd,&Ltemp,sizeof(Ltemp),0);
	
	return 0;
}