/*
    Problem : Perform encryption and decryption usind Hill Cipher technique. 
    BY:
        Rishav Kumar Goswami
*/
#include <bits/stdc++.h>

using namespace std;
#define N 3

void getCoFactorMatrix(int mat[N][N], int temp[N][N], int pr, int pc, int n){
    int r=0,c=0;
 
    // Looping for each element of the matrix
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
        {
            /* Copying element into temporary co-factor matrix */
            if (i!= pr && j!= pc){
                temp[r][c++] = mat[i][j];
				
               //increament the row	
                if (c == n-1){
                    c = 0;
                    r++;
                }
            }
        }
    }
}

int determinant(int A[N][N], int n){

    int Det = 0;
    
    //base condition
    if (n==2){
    	return ((A[0][0]*A[1][1]) - (A[0][1]*A[1][0]));
    }
 
    int temp[N][N]; // To store co-factors
    int sign = 1;  // To store sign multiplier

    /* for each element of first row iterate */
    for (int i=0; i<n; i++){
        /* Getting Cofactor of A[0][i] */
        
        getCoFactorMatrix(A,temp, 0, i, n);
        Det += sign * A[0][i] * determinant(temp,n - 1);
 
        /* alternate sign */
        sign = -1*sign;
    }
    return Det;
}

void matrixMultiply(int res[3][1],int key[3][3],int mat[3][1],int n){

	for(int i=0;i<n;++i){
		for(int j=0;j<1;++j){
			res[i][j]=0;
			for(int k=0;k<n;++k){
				res[i][j]+=key[i][k]*mat[k][j];
			}
		}
	}
}

int moduloInverse(int num){
	int i=1;
	while(true){
		if( (num*i % 26) == 1){
			break;
		}
		i++;
	}
	return i;
}

int negModulus(int num){
	int absVal = abs(num);
	int fac = absVal/26;
	int val = abs( ((fac+1)*26) - absVal);

	return val;
}

int printMatrix(int mat[N][N],int n){

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			cout<<mat[i][j]<<" ";
		}
	}
}

void inverseMatrix2x2(int mat[N][N],int invMat[N][N],int n){

	//swap the main digonal 
	invMat[0][0]=mat[1][1];
	invMat[1][1]=mat[0][0];

	//negate the off diagonal
	invMat[0][1]=-1*mat[0][1];
	invMat[1][0]=-1*mat[1][0];


	int det = determinant(mat,n);

	det = (det<0)?negModulus(det):(det%26);

	int k = moduloInverse(det);

	cout<<"\nDet = "<<det;
	cout<<"\nK^-1 = "<<k;

	//Step 7:
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			invMat[i][j]=k*invMat[i][j];
			//check negative value
			if(invMat[i][j]<0){
				//call function negModulus()
				int val = negModulus(invMat[i][j]);
				invMat[i][j]=val;
			}
			else{
				invMat[i][j]%=26;
			}
		}
	}

}

void inverseMatrix(int mat[N][N],int invMat[N][N],int n){
	
	/*
		Step 1: Generate the cofactor matrix for position (i,j)
		Step 2: Find determinant for above cofactor matrix 
		Step 3: Multiply the determinant with *sign and put it in coMat[i][j]
		Step 4: Follow the above Step 1 to 4 for all position of the given key matrix
		Step 5: Find Ajoint = Transpose[coFactor Matrix]
		Step 6: Find modulo inverse of 26 for determinant of mat i.e (det)*k mod 26 = 1, find k
		Step 7: Multiply the k with Ajoint to form inverse matrix then also take modulus of 26
	*/
	

	int coMat[N][N],temp[N][N],det,sign=1; 

	for(int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			//Step 1:
			getCoFactorMatrix(mat,temp,i,j,n);	
			//Step 2:
			det = determinant(temp,n-1);
			//Step 3:
			coMat[i][j]=det*(sign);
			sign =((i+j)%2 == 0)? -1:1;
		}
		//Step 4: Continue
	}
	//Step 5:
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			invMat[j][i]=coMat[i][j];
		}
	}

	
	//Step 6:
	det = determinant(mat,n);

	det = (det<0)?negModulus(det):(det%26);
	
	int k = moduloInverse(det);

	cout<<"\nK^-1 = "<<k;

	//Step 7:
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			invMat[i][j]=k*invMat[i][j];
			
			//modulus 26
			invMat[i][j] = (invMat[i][j]<0)?negModulus(invMat[i][j]):(invMat[i][j]%26);
		}
	}
}

int main(){
	int n;
	cout<<"\nDimension of key : \n1. 2 x 2\n2. 3 x 3";
	cout<<"\nEnter the choice : ";
	int choice;
	cin>>choice;
	if(choice == 1){
		n=2;
	}
	else if(choice == 2){
		n=3;
	}
	else{
		cout<<"\nInvalid choice:";
		exit(0);
	}
	
	string message;
	int key[3][3];
	int mat[3][1];
	int res[3][1];
	
	getchar();
	cout<<"\nEnter the message : ";
	getline(cin,message);

	//if the message is not a factor of n then append x at the end
	int rem = n - message.length()%n;
	
	for(int i=0;i<rem;++i){
		message+='x';
	}
	
	
	//get the key matrix
	cout<<"\nEnter the key matrix :";
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cin>>key[i][j];
		}
	}
	
	string enMsg="";

	//main logic for encrytpion
	for(int i=0;i<message.length();){
		for(int j=0;j<n;++j){
			if(message[i]==' '){
				j--;
				i++;
			}
			else{
				mat[j][0]=(message[i++]-'a') ;	
			}
		}			
		
		matrixMultiply(res,key,mat,n);

		//read the result in a string
		for(int i=0;i<n;++i){
			enMsg+=(char)((res[i][0] % 26) + 97);
		}
	}

	//Display the encrypted text
	cout<<"\n===========================================";
	cout<<"\nEncryption Process:";
    cout<<"\n===========================================";
    cout<<"\nPlain Text : "<<message;
    cout<<"\nDecrypted Text : "<<enMsg;
    cout<<"\n===========================================\n";
	
	/* Decryption Process*/

    /* find out the keyInv and then follow the same steps as we did in encryption */
    int keyInv[N][N];

    //Call the inverseMatrix()
   	if(n==2)
    	inverseMatrix2x2(key,keyInv,n);
    else
    	inverseMatrix(key,keyInv,n);

    //print the inverse matrix
    cout<<"\nInverse matrix :\n";
    for (int i = 0; i < n; ++i){
    	for (int j = 0; j < n; ++j){
    		cout<<keyInv[i][j]<<"\t";
    	}
    	cout<<"\n";
    }

    string decMsg="";
    for(int i=0;i<enMsg.length();){
		for(int j=0;j<n;++j){
			mat[j][0]=(enMsg[i++]-'a') ;	
		}	

		matrixMultiply(res,keyInv,mat,n);
		
		//read the result in a string
		for(int i=0;i<n;++i){
			decMsg+=(char)((res[i][0] % 26) + 97);
		}
	}

	//Display the encrypted text
	cout<<"\n===========================================";
	cout<<"\nDecryption Process:";
    cout<<"\n===========================================";
    cout<<"\nPlain Text : "<<enMsg;
    cout<<"\nDecrypted Text : "<<decMsg;
    cout<<"\n===========================================\n";
		
	return 0;
}
