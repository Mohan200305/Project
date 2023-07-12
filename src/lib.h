//Function declration 
double **createMat(int m, int n); 
void readMat(double **p, int m,int n); 
double **loadtxt(char *str,int m,int n); 
void print(double **p, int m,int n); 
double** scalarProduct(double scalar, double **mat); 
double **linalg_inv(double **mat, int m, int n); 
double **matmul(double **a, double **b, int m, int n, int p); 
void save_q(double **a, int rows, int cols); 
//End function declaration 
 
 
 
//defining the function for matrix creation 
double **createMat(int m, int n) {  
    int i, j;  
    double **a;  
      
    // Allocate memory to the pointer  
    a = (double **)malloc(m * sizeof(*a));  
      
    for (i = 0; i < m; i++) {  
        a[i] = (double *)malloc(n * sizeof(*a[i]));  
        for (j = 0; j < n; j++) {  
            a[i][j] = 0.0;  
        }  
    }  
      
    return a;  
}  
 
//end function for the matrix creation 
 
//Defining the function for reading matrix  
void readMat(double **p, int m,int n) 
{ 
 int i,j; 
 for(i=0;i<m;i++) 
 { 
  for(j=0;j<n;j++) 
  { 
   scanf("%lf",&p[i][j]); 
  } 
 } 
} 
//End function for reading matrix 
 
//Read  matrix from file 
double **loadtxt(char *str,int m,int n) 
{ 
FILE *fp; 
double **a; 
int i,j; 
} 
//end function for reading of matrix 
 
 
//defining th funcion for printing of matrix  
void print(double **p, int m,int n)   
{   
 int i,j;   
   
 for(i=0;i<m;i++)   
 {   
  for(j=0;j<n;j++){  
         printf("%lf ",p[i][j]);  
  }  
 printf("\n");   
 }   
}   
//end function for print matrix 
 
 
 
//defining the function for multiplying a scalar value with the matrix 
double** scalarProduct(double scalar, double **mat) {  
    double **product = (double**)malloc(2 * sizeof(*product));  
    for(int i = 0; i < 3; i++) {  
     for(int j=0;j<1;j++){  
        product[i] = (double*)malloc(sizeof(product));  
             }  
    }  
  
    product[0][0] = mat[0][0] * scalar;  
    product[1][0] = mat[1][0] * scalar;  
    product[2][0] = mat[2][0] * scalar;  
  
    return product;  
}  
 
//end function for scalar multiplication 
 
 
 
 
 
//defining the function for 3x3 inverse of a matrix 
double **linalg_inv(double **mat, int m, int n) {  
    double **inv;  
    double det;  
  
    inv = createMat(m, n);  
      
    det = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) -   
          mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +   
          mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);  
  
    // Calculate the adjoint matrix  
    inv[0][0] = (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) / det;  
    inv[0][1] = (mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2]) / det;  
    inv[0][2] = (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]) / det;  
    inv[1][0] = (mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2]) / det;  
    inv[1][1] = (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]) / det;  
    inv[1][2] = (mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2]) / det;  
    inv[2][0] = (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]) / det;  
    inv[2][1] = (mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1]) / det;  
    inv[2][2] = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) / det;  
  
    return inv;  
}  
//end function for inverse of matrix 
 
 
//defining the function for multiplication of two matrices 
double **matmul(double **a, double **b, int m, int n, int p)  
{  
int i, j, k;  
double **c, temp =0;  
c = createMat(m,p);  
  
 for(i=0;i<m;i++)  
 {  
  for(k=0;k<p;k++)  
  {  
    for(j=0;j<n;j++)  
    {  
 temp= temp+a[i][j]*b[j][k];  
    }  
 c[i][k]=temp;  
 temp = 0;  
  }  
 }  
return c;  
  
} 
//end functon for martrix multiplication 
 
 
 
//defining the function for saving the values of q(output values) 
void save_q(double **a, int rows, int cols)  
{ 
 FILE *fp; 
  fp = fopen("q.dat", "w");   
  //fprintf(fp, "The result of the multiplication is:\n"); 
  int i, j;  
  for (i = 0; i < rows; i++) { 
    //fprintf(fp, "[");   
    for (j = 0; j < cols; j++) { 
      fprintf(fp, "%lf", a[i][j]);    
      if (j < cols - 1) { 
        //fprintf(fp, ", ");      
 } 
    }


}
}
double **load_ser(AsyncWebServerRequest *request,const char* matrix1[3])
{
	double **a;
	int m=3,n=1;
	a = createMat(m,n);
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			a[i][j]=request->getParam(matrix1[i])->value().toDouble();
		}
	}
	return a;
}

double **load_serv(AsyncWebServerRequest *request,const char* matrix2[9])
{
	double **a;
	int m=3,n=3,k=0;
	a = createMat(m,n);
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			a[i][j]=request->getParam(matrix2[k])->value().toDouble();
			k+=1;
		}
	}
	return a;
}

