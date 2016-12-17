/*
    Problem : Perform the PlayFair encryption and decryption  
    BY:
        Rishav Kumar Goswami
*/
#include <bits/stdc++.h>

using namespace std;

/*Generate the play-fair matrix of 5x5 for the given key */
void genPlayFairMatrix(char mat[5][5],string key){

	int klen = key.length();
	int alphabet[26];
	memset(alphabet,0,26*sizeof(int));
	
	int r=0,c=0;
	for (int i = 0; i < klen; ++i){
		int idx = key[i]-'a';
		if(alphabet[idx]==0){
			mat[r][c]=key[i];
			alphabet[idx]=1;
			
			if (c==4){
				r++;
				c=0;
			}
			else{
				c++;
			}
		}
	}
	//fill the remaining box
	for (int i = 0; i < 26; ++i){
		if(i==8){
			//ignore 'i'
			continue;
		}
		if(alphabet[i]==0){
			mat[r][c]=char(i+'a');
			alphabet[i]=1;
			if (c==4){
				r++;
				c=0;
			}
			else{
				c++;
			}
		}
		
	}
}

/* Funtion to generate the pair for encryption and decryption process */
string genPair(string msg){

	string genPairStr="";
	int len = msg.length();

	for (int i = 0; i < len; ++i){
		if(msg[i]==msg[i+1]){
			genPairStr+=msg[i];
			genPairStr+='x';
		}
		else{
			if(i+1==len){
				genPairStr+=msg[i];
				genPairStr+='x';
				break;
			}
			else{
				genPairStr+=msg[i];
				genPairStr+=msg[i+1];
			}
			i++;
		}
	}
	return genPairStr;
}

/* Function to perform the search pairs location in the matrix */
void search(char mat[5][5],char ch,int &r,int &c){
	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 5; ++j){
			if(mat[i][j]==ch){
				r=i;
				c=j;
				return;
			}
		}
	}
}

string encryption(char mat[5][5],string msg){

	int r1,c1,r2,c2;
	string enMsg="";
	for (int i = 0; i < msg.length()-1; i+=2){
		//search
		search(mat,msg[i],r1,c1);
		search(mat,msg[i+1],r2,c2);

		if (r1==r2){
			enMsg+=mat[r1][(c1+1)%5];
			enMsg+=mat[r2][(c2+1)%5];
		}
		else if (c1==c2){
			enMsg+=mat[(r1+1)%5][c1];
			enMsg+mat[(r2+1)%5][c2];
		}
		else{
			enMsg+=mat[r1][c2];
			enMsg+=mat[r2][c1];
		}
	}

	return enMsg;

}

string decryption(char mat[5][5],string msg){

	int r1,c1,r2,c2;
	string enMsg="";
	for (int i = 0; i < msg.length()-1; i+=2){
		//search
		search(mat,msg[i],r1,c1);
		search(mat,msg[i+1],r2,c2);

		if (r1==r2){
			if((c1-1)<0)
				c1=c1+4;
			else
				c1=c1-1;

			if((c2-1)<0)
				c2=c2+4;
			else
				c2=c2-1;
			enMsg+=mat[r1][c1];
			enMsg+=mat[r2][c2];
		}
		else if (c1==c2){
			if((r1-1)<0)
				r1=r1+4;
			else
				r1=r1-1;

			if((r2-1)<0)
				r2=r2+4;
			else
				r2=r2-1;
			enMsg+=mat[r1][c1];
			enMsg+=mat[r2][c2];
		}
		else{
			enMsg+=mat[r1][c2];
			enMsg+=mat[r2][c1];
		}
	}
	return enMsg;
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

int main(){

	int klen,mlen;
	string msg,key;
	
	cout<<"\nEnter the key : ";
	cin>>key;
	klen = key.length();
	for (int i = 0; i < klen; ++i){
		if (key[i]=='i'){
			//replace it with j
			key[i]='j';
		}
	}

	
	cout<<"\nGenerating PlayFair Matrix:\n";
	char mat[5][5];

	genPlayFairMatrix(mat,key);	
	displayMat(mat);


	cout<<"\nEnter the message : ";
	cin>>msg;

	mlen = msg.length();
	for (int i = 0; i < mlen; ++i){
		if (msg[i]=='i'){
			//replace it with j
			msg[i]='j';
		}
	}

	string pairStr = genPair(msg);
	cout<<"\nPaired String for Original message = "<<pairStr<<endl;

	//encryption
	string enMsg = encryption(mat,pairStr);

	//Display the encrypted text
    cout<<"\n===========================================";
    cout<<"\nMessage :"<<msg;
    cout<<"\nKey :"<<key;
    cout<<"\nEncrypted text : "<<enMsg;
    cout<<"\n===========================================\n";
	

	cout<<"\nDecrypting the above generate encrypted message.... :";

	pairStr = genPair(msg);
	cout<<"\nPaired String for encrypted text = "<<pairStr<<endl;
	//decryption
	string decMsg = decryption(mat,enMsg);
	
	//Display the decrypted text
    cout<<"\n===========================================";
    cout<<"\nEncrypted Message :"<<enMsg;
    cout<<"\nKey :"<<key;
    cout<<"\nOriginal message : "<<decMsg;
    cout<<"\n===========================================\n";
	
	cout<<endl;
	return 0;
}