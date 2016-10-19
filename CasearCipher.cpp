/*
    Problem : Perform the Cesear cipher encryption and decryption. And also launch a brute force attack and find the key 
    BY:
        Rishav Kumar Goswami
*/
#include <bits/stdc++.h>

using namespace std;

/*Function for encryption */
string encryption(string msg,int key1,int key2){

	string enMsg="";
	for (int i = 0; i < msg.length() ; ++i){
		if(msg[i]!=' '){
			if(islower(msg[i])){
				enMsg+=( ( (msg[i]-'a') + key1 ) %26)+'a';
			}
			else{
				enMsg+=( ( (msg[i]-'A') + key2 ) %26)+'A';
			}
		}
		else{
			enMsg+=msg[i];
		}
	}
	return enMsg;		
}

/*Function for decryption */
string decryption(string enMsg,int key1,int key2){

	string decMsg="";
	int temp;
	for (int i = 0; i < enMsg.length() ; ++i){
		if(enMsg[i]!=' '){
			if(islower(enMsg[i])){
				temp = (enMsg[i]-'a') - key1 ;
				
				//c++ does have any thing like negative modulus operation
				if(temp<0){
					temp+=26;
				}
				decMsg+=((temp %26)+'a');
			}
			else{
				temp = (enMsg[i]-'A') - key2;
				//c++ does have any thing like negative modulus operation
				if(temp<0){
					temp+=26;
				}
				decMsg+=((temp %26)+'A');
			}
		}
		else{
			decMsg+=enMsg[i];
		}
	}

	return decMsg;
}

int main(){

	/*Input the Message to be encrypted */
	string msg;
	cout<<"\nEnter the Message to encrypted : ";
	getline(cin,msg);
	int key1,key2;
	cout<<"\nEnter the key1 : ";
	cin>>key1;
	cout<<"\nEnter the key2 : ";
	cin>>key2;

	//call the encryption function
	string enMsg = encryption(msg,key1,key2);
	
	//Display the encrypted text
	cout<<"\n===========================================";
	cout<<"\nEncryption Process:";
    cout<<"\n===========================================";
    cout<<"\nPlain Text :"<<msg;
    cout<<"\nKey 1: "<<key1;
    cout<<"\nKey 2: "<<key2;
    cout<<"\nEncrypted Text : "<<enMsg;
    cout<<"\n===========================================\n";
	
	
	//call the decryption function
	string decMsg = decryption(enMsg,key1,key2);
	
	//Display the encrypted text
	cout<<"\n===========================================";
	cout<<"\nDecryption Process:";
    cout<<"\n===========================================";
    cout<<"\nEncrypted Text :"<<enMsg;
    cout<<"\nKey 1: "<<key1;
    cout<<"\nKey 2: "<<key2;
    cout<<"\nDecrypted Text : "<<decMsg;
    cout<<"\n===========================================\n";


    /* 	Logic for Brute force attack to find the possible 
    	key1 and key2 generating some meaningfull message
    	by applying all possible combination
    */ 
    cout<<"\n=======================================";
    cout<<"\nBrute force attack:";
    cout<<"\n=======================================";
  	cout<<"\nPress ctrl+c to break, if you find a meaningfull message.\n";
	for (int i = 0; i < 26; ++i){
		for (int j = 0; j < 26; ++j){
			//call decryption fuction for key1= i and key2=j
			decMsg = decryption(enMsg,i,j);
			cout<<"\n"<<decMsg<<"\t\tKey1="<<i<<"\t\tKey2="<<j;

			//check if any upper case exit in the string
			if((std::find_if(enMsg.begin(), enMsg.end(), ::isupper) == enMsg.end())==1){
				break;
			}
			getchar();
		}

		//To check if the enMsg only have upper case characters 
		if((std::find_if(enMsg.begin(), enMsg.end(), ::islower) == enMsg.end())==1){
			break;
		}
	}

	cout<<"\nNow its your task to analyse the Decrypted text, identify meaningfull message and thus find the keys.";

	cout<<"\n";
	return 0;
}