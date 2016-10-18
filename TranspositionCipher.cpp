#include <bits/stdc++.h>

using namespace std;

int main(){

	/*Input the Message to be encrypted */
	string message;
	cout<<"\nEnter the Message to encrypted : ";
	getline(cin,message);
	int n;
	cout<<"\nEnter the size of key :";
	cin>>n;	

	/* 	Apply a simple transformation trick while storing the value of column permutation in the key[i] 
		such that new array say 'index[i]' contain the position of column to be taken/considered in sequence
		i.e
			index[key[i]-1]=i;	
	*/

	int tempK,index[n];
	string keyStr="";
	cout<<"\nKey(Column Permutation): ";
	for(int i=0;i<n;++i){
		cin>>tempK;			//tempK contain key permutation value at i-th index i.e key[i]
		
		index[tempK-1]=i;

		//append the tempK for sake of reference the key value printed together
		keyStr+=(tempK+'0');
	}

	/* 	Logic for tranposition cipher:
		==============================
		Step 1: Find out the row and column value for the desired matrix to be generated.
		Step 2: Fill up the matrix row-wise with the message alphabet sequencially.
		Step 3: Read the column based on the column permutation provided as key and store it.
		Step 4: Display the encrypted text.
	*/

	//check length is factor of n or not
	int rem = message.length()%n;
	if(rem){
		//append (n-rem)x's at the end of message
		for(int i=0;i<(n-rem)-1;++i)
			message+='x';
	}

	//Step 1:
	int row = message.length()/n;
	int col = n;
	int k=0;

	cout<<"\nrow = "<<row;

	char mat[row][col];
	//Step 2:
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			if(message[k]!=' ')
				mat[i][j]=message[k];
			else
				j--;
			k++;
		}
	}

	//print the matrix generated from above tranposition
	cout<<"\nMatrix generated from given plain text :\n";
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			cout<<" "<<mat[i][j];
		}
		cout<<"\n";
	}


	/* Logic to transpose the matrix */
	string enMsg="";
	//Step 3:
	for(int i=0;i<n;++i){
		//read the column based on column postion defined in index[i]
		for(int j=0;j<row;++j){
			enMsg+=mat[j][index[i]];
		}
	}

	//Step 4:
	//Display the encrypted text
	cout<<"\nEncryption Process:";
    cout<<"\n===========================================";
    cout<<"\nPlain Text :"<<message;
    cout<<"\nKey :"<<keyStr;
    cout<<"\nEncrypted text : "<<enMsg;
    cout<<"\n===========================================\n";

    
    /*	Logic for Decryption process
    	============================
    	For decryption, follow the same sequence of step in encryption in reverse order.
    	Step 1: Find out the row and column value for the desired matrix to be generated.
		Step 2: Fill up the matrix column-wise with the message alphabet using 
				the index[] array containing the permutation sequence.
		Step 3: Read the row sequencially (from 0 to row-1) and store it.
		Step 4: Display the decrypted text.

    */

	//Step 1:
	k=0;
	row = enMsg.length()/n;
	col = n;
	char newMat[row][col];
	//Step 2:
	for (int i = 0; i < col; ++i){
		for (int j = 0; j < row; ++j){
			newMat[j][index[i]]=enMsg[k++];
		}
	}

	//print the matrix generated from above tranposition
	cout<<"\nMatrix generated from above Encrypted text :\n";
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			cout<<" "<<newMat[i][j];
		}
		cout<<"\n";
	}

	string decMsg="";
	//Step 3:
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			decMsg+=newMat[i][j];
		}
	}

	//Step 4:
	//Display the decrypted text
	cout<<"\nDecryption Process:";
    cout<<"\n===========================================";
    cout<<"\nEncrypted Text :"<<enMsg;
    cout<<"\nKey :"<<keyStr;
    cout<<"\nPlain Text : "<<decMsg;
    cout<<"\n===========================================\n";

    

	return 0;
}