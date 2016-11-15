/*
    Problem : Implementation of RC4 ( Show the stream )
    BY:
        Rishav Kumar Goswami
*/

#include <bits/stdc++.h>

using namespace std;

void intialization_Of_S(int S[],int T[],int K[],int keylen){

	for (int i = 0; i < 256; ++i){
		S[i]=i;
		T[i]=K[i % keylen];
	}
}

void permutation_Of_S(int S[],int T[]){

	int j = 0;
	for (int i = 0; i < 255; ++i){
		j = (j+S[i]+T[i]) % 256;
		
		//swap(S[i],S[j]);
		int t = S[i];
		S[i]=S[j];
		S[j]=t;
	}
}

void displaySet(int Set[],int n){
	for (int i = 0; i < n; ++i){
		cout<<" "<<Set[i];
	}
	cout<<" ]\n";
}

void streamGenerator(int S[],int Stream[],int n){

	int l=0;
	
	/*Stream generation*/
	int i=0,j=0;

	while(l < n){
		i = (i+1) % 256;

		j = (j+S[i]) % 256;

		//swap(S[i],S[j]);
		int t = S[i];
		S[i]=S[j];
		S[j]=t;

		t = (S[i]+S[j]) % 256;
		
		//Generate stream stored in Stream
		Stream[l]=S[t];
		l++;
	}

	cout<<"\nGenerated Stream Set : [";
	displaySet(Stream,n);
}

void EncryptAndDecrypt(int P[],int n,int Stream[]){

	/*Encryption Process*/
	int C[n];
	for (int i = 0; i < n; ++i){
		//xor the plain text with generated stream
		C[i]=P[i]^Stream[i];
	}

	cout<<"\nPlain Text Set : [";
	displaySet(P,n);

	cout<<"\nEncrypted Text Set : [";
	displaySet(C,n);

	/*Decryption Process*/
	int D[n];
	for (int i = 0; i < n; ++i){
		//xor the Cipher text with generated stream
		D[i]=C[i]^Stream[i];
	}

	cout<<"\nDecrypted Text Set : [";
	displaySet(D,n);
}

int main(){

	int S[256],T[256];
	int keylen;

	//Step 1: Input Key Set 
	cout<<"\nEnter the keylen : ";
	cin>>keylen;

	int K[keylen];
	cout<<"\nEnter the key Set : ";
	for (int i = 0; i < keylen; ++i){
		cin>>K[i];
	}

	//Step 2: Intialize the S[] and T[];
	intialization_Of_S(S,T,K,keylen);

	//Step 3: Perform the permutation of S
	permutation_Of_S(S,T);

	//Step 5: Generate the byte stream 
	int sLen;
	cout<<"\nEnter the stream size to be generated :";
	cin>>sLen;
	int Stream[sLen];
	streamGenerator(S,Stream,sLen);

	//Step 6: Take input n-bytes Plain Text Set
	int pLen;
	cout<<"\nEnter the size of plain text : ";
	cin>>pLen;
	int P[pLen];
	cout<<"\nEnter the Plain Text Set :";
	for (int i = 0; i < pLen; ++i){
		cin>>P[i];
	}
	//Step 5: Encrypt and Decrypt
	EncryptAndDecrypt(P,pLen,Stream);

	return 0;
}