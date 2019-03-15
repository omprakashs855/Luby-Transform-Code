#include <SPI.h>
#include <RH_NRF24.h>
RH_NRF24 nrf24;

#define N 10
#define n 3
char a1[20] = "Brother";
int x[] = {1,2,3};
float pmf[] = {0.33,0.33,0.33};

void setup() 
{
  int i,j,m,b[10][10],X[10],k,M[20],E[20],p,q,x1,c;
  float r1,r[20],d[20],a[10][10];
  
  Serial.begin(9600);

  randomSeed(analogRead(0));
  for(i=0;i<N;i++)
  {
    delay(10);
    r1 = random(1,11);
    r[i] = r1/10;
  }
  
  for(i=1;i<n;i++)
  {
    delay(10);
    pmf[i] = pmf[i]+pmf[i-1];
  }
  m = n+1;
  d[0] = 0;
  for(i=1;i<n;i++)
  {
    delay(10);
    d[i] = 5*pmf[i-1];
  }
  d[n] = 10;
  
  for(i=0;i<m;i++)
    for(j=0;j<N;j++)
    {
      delay(10);
      a[i][j]=d[i]*r[j];
    }

  for(i=0;i<m;i++)
    for(j=0;j<N;j++)
    {
      delay(10);
      if(a[i][j]>=1)
        b[i][j] = 1;
      else
        b[i][j] = 0;
    }

  for(j=0;j<N;j++)
    for(i=0;i<N;i++)
        if(b[i][j]==1)
        {
            delay(10);
            X[j]=i;
            break;
        }
  Serial.println("Generated Random Sequence : ");
  for(i=0;i<N;i++)
  {
    delay(500);
    Serial.print(X[i]);
    Serial.print(" ");
  }

  k = strlen(a1);

  for(i=0;i<k;i++)
    M[i] = a1[i];

  for(i=0;i<N;i++)
    E[i] = 0;

  for(i=0;i<N;i++)
  {
    p = i%k;
    c = X[i];
    if(c==1)
      E[i] = M[p];
    else
    {
      for(j=0;j<(c-1);j++)
      {
        q = p;
        p = p+1;
        if(p==k)
          p = p-k;
        
        if(j==0)
          x1 = M[q];
        else
          x1 = E[i];

        E[i] = x1^M[p];
      }
    }
  }
  delay(200);
  Serial.println("\nEncoded Data : ");

  for(i=0;i<N;i++)
  {
    delay(500);
    Serial.print(E[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  while (!Serial); 
  if (!nrf24.init())
    Serial.println("init failed");
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");

  char C[20];
  int temp = 0;
  for(i=0;i<N;i++)
  {
    C[temp++] = E[i];
    delay(10);
  }
  delay(500);
  for(i=0;i<N;i++)
  {
    C[temp++] = X[i];
    delay(10);
  }
  delay(500);
  
  Serial.println(C);
  while(1)
  {
    nrf24.send(C, sizeof(C));
    delay(1000);
  }
}

void loop(){}
