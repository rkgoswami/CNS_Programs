/*
    Problem : Perform the PlayFair encryption and decryption  
    BY:
        Rishav Kumar Goswami
*/
#include <bits/stdc++.h>

using namespace std;

/*Generate the play-fair matrix of 5x5 for the given key */
void genPlayFairMatrix(char mat[5][5],string key){
	
	int alphabet[26]={0};
	int len=key.length();
	int r=0,c=0;

	//Fill the unique alphabets of key into matrix 
	for(int i=0;i<len;++i){

		//to ignore 'i' in the process and use 'j' always
		if((key[i]=='i')){
			key[i]='j';
		}
		//if the key contains space in it just ignore it,
		//(key[i]-'a') is used to find the integer postion of the char in alphabet
		if(key[i]!=' ' && alphabet[key[i]-'a']==0){
			alphabet[key[i]-'a']=1;
			mat[r][c]=key[i];
			c++;
			if(c%5==0){
				r++;
				c=0;
			}
		}
	}
	
	//now fill the rest position in the matrix with remaining alphabet
	char k = 'a';
	for(int i=0;i<26;++i){

		//set 'i' to 'j' 
		if((k=='i')){
			k='j';
		}
		if(alphabet[k-'a']==0){
			alphabet[k-'a']=1;
			mat[r][c]=k;
			c++;
			if(c%5==0){
				r++;
				c=0;
			}
		}
		k++;
	}
	
}

/*Fuction to display the generate playfair matrix */
void displayMat(char mat[5][5]){
	cout<<"\nGenerate Play Fair Matrix :\n";
	for(int i=0;i<5;++i){
		for(int j=0;j<5;++j){
			cout<<" "<<mat[i][j];
		}
		cout<<"\n";
	}
}

/* Funtion to generate the pair for encryption and decryption process */
string genPairString(string msg){
	
	string newMsg="";
	int len = msg.length();
	
	for(int i=0;i<len;i+=2){
		
		if(msg[i]==msg[i+1]){
			newMsg+=msg[i];
			newMsg+='x';
			i--;
		}
		else{
			if(i+1==len){
				newMsg+=msg[i];
				newMsg+='x';
			}
			else{
				newMsg+=msg[i];
				newMsg+=msg[i+1];
			}
		}
	}
	cout<<"\nGenerated String for conversion : "<<newMsg<<endl;	
	
	return newMsg;
}

/* Function to perform the search pairs location in the matrix */
void searchMat(char mat[5][5],char ch,int &x,int &y){
	for(int i=0;i<5;++i){
		for(int j=0;j<5;++j){
			if(ch=='i')
				ch='j';
			if(mat[i][j]==ch){
				x=i;
				y=j;
				return;
			}
		}
	}
}

/* Function for Encryption */
string encryptTheMsg(string msg,char mat[5][5]){
	int len = msg.length();
	int r1,c1,r2,c2;
	
	for(int i=0;i<len;i+=2){
	
		//find the position of msg[i]
		searchMat(mat,msg[i],r1,c1); 
	
		//find the position of msg[i+1]
		searchMat(mat,msg[i+1],r2,c2);
		
		if(r1==r2)		//both char lies in same row
		{
			msg[i]=mat[r1][(c1+1)%5];
			msg[i+1]=mat[r2][(c2+1)%5];
		}
		else if(c1==c2)		//both char lies in same col
		{
			msg[i]=mat[(r1+1)%5][c1];
			msg[i+1]=mat[(r2+1)%5][c2];
		}
		else	//exchange the with corner positions of newly formed sub matrix 
		{
			msg[i]=mat[r1][c2];
			msg[i+1]=mat[r2][c1];	
		}	
	}
	return msg;
}

/* Function for Encryption */
string decryptTheMsg(string msg,char mat[5][5]){

	string decMsg="";
	int len = msg.length();
	int r1,c1,r2,c2;
	for(int i=0;i<len;i+=2){
		//search for msg[i]
		searchMat(mat,msg[i],r1,c1);
		//search for msg[i+1]
		searchMat(mat,msg[i+1],r2,c2);

		//check the row condition
		if(r1==r2){
			decMsg+=mat[r1][(c1-1)%5];
			decMsg+=mat[r1][(c2-1)%5];
		}
		else if(c1==c2){
			decMsg+=mat[(r1-1)%5][c1];
			decMsg+=mat[(r2-1)%5][c2];
		}
		else{
			decMsg+=mat[r1][c2];
			decMsg+=mat[r2][c1];
		}
	}

	return decMsg;
}


int main(){

	string key;
	string orgMsg; 
	
	cout<<"\nMessage( Plain Text ): ";
	getline(cin,orgMsg);
	cout<<"\nKey :";
	getline(cin,key);
	
	char mat[5][5];
	
	//call genPlayFairMatrix() to generate the play fair matrix
	genPlayFairMatrix(mat,key);
	
	//display the Matrix
	displayMat(mat);
	
	//call genPairString
	string newMsg = genPairString(orgMsg);
	
	//generate the encrypted message
	string enMsg = encryptTheMsg(newMsg,mat);
	
	//Display the encrypted text
    cout<<"\n===========================================";
    cout<<"\nMessage :"<<orgMsg;
    cout<<"\nKey :"<<key;
    cout<<"\nEncrypted text : "<<enMsg;
    cout<<"\n===========================================\n";

    cout<<"\nDecrypting the above generate encrypted message.... :";

    //call genPairString for encrypted message
	newMsg = genPairString(enMsg);

	//decrypt the encrypted message using the same key and playfair matrix above generated
	string decMsg = decryptTheMsg(newMsg,mat);

	//Display the decrypted text
    cout<<"\n===========================================";
    cout<<"\nEncrypted Message :"<<enMsg;
    cout<<"\nKey :"<<key;
    cout<<"\nOriginal message : "<<decMsg;
    cout<<"\n===========================================\n";

	return 0;
}
