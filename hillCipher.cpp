/*
    Problem : Perform encryption and decryption usind Hill Cipher technique. 
    BY:
        Rishav Kumar Goswami
*/
#include <bits/stdc++.h>

using namespace std;
#define N 3

void getCofactorMatrix(int matrix[N][N],int coMatrix[N][N],int pr,int pc,int n){

	int r=0,c=0;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if (pr!=i && pc!=j){
				coMatrix[r][c++]=matrix[i][j];

				if (c==n-1){
					r++;
					c=0;
				}
			}
		}
	}
}

int getDeterminant(int matrix[N][N],int n){

	//base condition
	if (n==2){
		return (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]);
	}
	int det=0,sign=1;
	int coMatrix[N][N];
	for (int i = 0; i < n; ++i){
		
		//get the cofactor matrix
		getCofactorMatrix(matrix,coMatrix,0,i,n);

		//call for determinant again
		int val = getDeterminant(coMatrix,n-1);
		det+=matrix[0][i]*val*sign;
		sign*=-1;
	}
	return det;
}

int findMulInverse(int det){
	int i=0;
	while((det*i)%26!=1){
		i++;
	}
	return i;
}

int negMod(int val){
	int absV = abs(val);
	int q = absV/26;

	int negVal = (q+1)*26 - absV;

	return negVal%26;
}

void inverseMatrix(int matrix[N][N],int invMatrix[N][N],int n){

	//calculate the detereminant and find d^-1
	int det = getDeterminant(matrix,n);
	det = (det<0)?negMod(det):(det%26);

	//find d^-1
	int k_inv = findMulInverse(det);
	cout<<"\n"<<det<<"^-1 = "<<k_inv; 

	if(n==2){
		//exchange the main diagonal

		invMatrix[0][0]=matrix[1][1];
		invMatrix[1][1]=matrix[0][0];

		//negate the off diagonal
		invMatrix[0][1]=-1*matrix[0][1];
		invMatrix[1][0]=-1*matrix[1][0];

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				int val = invMatrix[i][j]*k_inv;
				val = (val<0)?negMod(val):(val%26);
				invMatrix[i][j]=val;
			}
		}
	}
	else{
		int coMatrix[N][N],temp[N][N];
		int sign=1;
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				getCofactorMatrix(matrix,coMatrix,i,j,n);

				//call for determinant again
				int val = getDeterminant(coMatrix,n-1)*sign*k_inv;
				val = (val<0)?negMod(val):(val%26);

				temp[i][j]=val;
				sign*=-1;
			}
		}
		//transpose the matrix
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				invMatrix[j][i]=temp[i][j];
			}
		}
	}
	

}

void displayMat(int matrix[N][N],int n){

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			cout<<matrix[i][j]<<" ";
		}
		cout<<"\n";
	}
}

void matrixMultiply(int keyMatrix[N][N],int strMat[N][1],int result[N][1],int n){

	for(int i=0;i<n;++i){
		for(int j=0;j<1;++j){
			result[i][j]=0;
			for(int k=0;k<n;++k){
				result[i][j]+=keyMatrix[i][k]*strMat[k][j];
			}
		}
	}

}

string encryptAndDecryption(int keyMatrix[N][N],string msg,int n){

	//form mat[n][1];
	int strMat[N][1],result[N][1];

	//check if strlen is factor of n or not
	if(msg.length()%n!=0){
		int rem = n - msg.length()%n;
		for (int i = 0; i < rem; ++i){
			msg+='x';
		}
	}

	string enMsg="";
	int len = msg.length();
	for (int i = 0; i < len;){
		
		//generate the strMat
		for (int j = 0; j < n; ++j){
			strMat[j][0]=msg[i++]-'a';
		}
		
		//multiply
		matrixMultiply(keyMatrix,strMat,result,n);

		for (int i = 0; i < n; ++i){
			enMsg += ((result[i][0]%26)+'a');
		}
	}
	return enMsg;
}

int main(int argc, char const *argv[]){
	
	int n;
	int matrix[N][N];
	cout<<"\nSelect the choice for n (2 or 3): ";
	cin>>n;

	cout<<"\nEnter the Key matrix :\n ";
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			cin>>matrix[i][j];
		}
	}

	string msg;
	cout<<"\nEnter the Message : ";
	cin>>msg;

	/*Encryption Process*/
	string enMsg = encryptAndDecryption(matrix,msg,n);
	
	//Display the encrypted text
	cout<<"\n===========================================";
	cout<<"\nEncryption Process:";
    cout<<"\n===========================================";
    cout<<"\nPlain Text : "<<msg;
    cout<<"\nDecrypted Text : "<<enMsg;
    cout<<"\n===========================================\n";
	
	/*Decryption Process*/
	int invMatrix[N][N];
	inverseMatrix(matrix,invMatrix,n);
	
	cout<<"\nInverse of Key matrix : \n";
	displayMat(invMatrix,n);

	string decMsg = encryptAndDecryption(invMatrix,enMsg,n);

	//Display the encrypted text
	cout<<"\n===========================================";
	cout<<"\nDecryption Process:";
    cout<<"\n===========================================";
    cout<<"\nPlain Text : "<<enMsg;
    cout<<"\nDecrypted Text : "<<decMsg;
    cout<<"\n===========================================\n";
		

	return 0;
}