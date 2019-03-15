#include <SPI.h>
#include <RH_NRF24.h>
#define k 6 //Length of the message

RH_NRF24 nrf24;

void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  if (!nrf24.init())
    Serial.println("init failed");
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    

  int i,E1[30],M,key = 64;
  char X1[30];  
  while(1)
  {
      if (nrf24.available())
      {
        char buf1[30];
        uint8_t len1 = sizeof(buf1);
        if (nrf24.recv(buf1, &len1))
        {
          Serial.print("got request: ");
          Serial.println(buf1);
          M = len1;
          for(i=0;i<M;i++)
          {
            delay(10); 
            X1[i] = buf1[i];
          }
          delay(700);
          for(i=0;i<M;i++)
          {
            E1[i] = X1[i];
            delay(10);
          }   
        }
        break;
      }
    }
  Serial.print("Encoded and Random Sequence : ");
  for(i=0;i<M;i++)
  {
     Serial.print(E1[i]);
     Serial.print(" ");
     delay(500);
  }
  Serial.println();  

  int M1[100],G[20][20];
    int j,m,n,p,c,s,l;
    char M2[100];
    int E[10],X[10],N,temp=0;
    N = M/2;
    for(i=0;i<N;i++)
      E[i] = E1[temp++];
    for(i=0;i<N;i++)
      X[i] = E1[temp++];

    Serial.print("Random Sequence : ");
    for(i=0;i<N;i++)
    {
      X[i] = X[i];
      Serial.print(X[i]);
      Serial.print(" ");
    }
    Serial.println();

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
    for(i=0;i<k;i++)
      M2[i] = M1[i];
    Serial.print("\nThe Message Retrieved : ");
    for(i=0;i<k;i++){
        Serial.print(M2[i]);
        delay(100); 
    }
}

void loop(){}
