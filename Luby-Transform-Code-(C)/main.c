#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void encode(int X[],int N);
void decode(int N,int k,int E[100],int X[100]);

int main(){
int b,x[10],m,n,i,j,N,X[100];
float r1,pmf[10],r[100],a[100][100];
srand(time(NULL));
printf("Enter the N : ");
scanf("%d",&N);
for (b=0;b<N;b++){
        r1 = rand();
        r[b]=RAND_MAX/r1;
        }
printf("Enter the no. of x and pmf (same) :");
scanf("%d",&n);
printf("Enter the x : ");
for(i=0;i<n;i++)
    scanf("%d",&x[i]);
printf("Enter the pmf : ");
for(i=0;i<n;i++)
    scanf("%f",&pmf[i]);
for(i=1;i<n;i++)
    pmf[i] = pmf[i]+pmf[i-1];
m=n+1;
for(i=0;i<N;i++)
    a[0][i]=0;
for(i=1;i<m;i++)
    for(j=0;j<N;j++){
        if(pmf[i-1]*r[j]>1)
            a[i][j] = 1;
        else
            a[i][j] = 0;
    }
for(j=0;j<N;j++)
    for(i=0;i<N;i++)
        if(a[i][j]>0){
            X[j]=i;
            break;
        }
for(i=0;i<N;i++)
    printf("%d ",X[i]);
encode(X,N);
return 0;
}
//----------------------------------------------------------------
//Encode
void encode(int X[100],int N)
{
    char a[100];
    int i,j,k,M[100],E[100],p,q,x,c;
    printf("\n-------------------------------");
    printf("\nEnter the Message : ");
    scanf("%s",a);
    k=strlen(a);

    for(i=0;i<k;i++)
        M[i] = a[i];

    for(i=0;i<N;i++)
        E[i]=0;

    for(i=0;i<N;i++)
    {
        p = i%k;
        c=X[i];
        if(c==1)
            E[i] = M[p];
        else
        {
            for(j=0;j<(c-1);j++)
            {
                q = p;
                p = p+1;
                if(p==k)
                    p=p-k;
                if(j==0)
                    x=M[q];
                else
                    x=E[i];
                E[i] = x^M[p];
            }
        }
    }
 for(i=0;i<N;i++)
        printf("%d ",E[i]);

 decode(N,k,E,X);
}
//------------------------------------------------------------
//Decode
void decode(int N,int k,int E[100],int X[100])
{
    printf("\n");
    int M1[100],G[20][20];
    int i,j,m,n,p,c,s,l;

    for(i=0;i<N;i++)
        for(j=0;j<k;j++)
            G[i][j] = 0;

    for(i=0;i<N;i++)
    {
        p = i%k;
        c = X[i];
        if(c==1)
            G[i][p] = 1;
        else
        {
            for(j=0;j<c;j++)
            {
                G[i][p] = 1;
                p = p+1;
                if(p==k)
                    p=0;
            }
        }
    }

    for(i=0;i<N;i++){
        for(j=0;j<k;j++)
            printf("%d ",G[i][j]);
        printf("\n");
    }

    for(i=0;i<k;i++)
        M1[i] = 0;

    for(i=0;i<k;i++)
    {
        for(j=0;j<N;j++)
        {
            s=0;
            for(l=0;l<k;l++)
                s = s+G[j][l];
            if(s==1)
            {
                for(l=0;l<k;l++)
                {
                    if(G[j][l]==1)
                        break;
                }
                m=j;
                n=l;
                M1[n] = E[m];
                G[m][n] = 0;
                break;
            }
        }
        for(j=0;j<N;j++)
        {
            if(G[j][n]==1)
            {
                E[j] = E[j]^M1[n];
                G[j][n] = 0;
            }
        }
    }
    printf("\nThe Message Retrieved : ");
    for(i=0;i<k;i++)
        printf("%c ",M1[i]);
}

