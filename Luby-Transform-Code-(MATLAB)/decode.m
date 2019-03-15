clc;
clear all;
close all;
X = [1,3,2,3,2,1,3,2,3,3];
E = [72,101,0,75,39,72,101,0,75,66];
N =length(X);
k = 5; %Length of the Message;
G = zeros(N,k);
for i=1:N
    if i>k
        p=i-k;
    else
        p=i;
    end
    c=X(i);
    if c==1
        G(i,p)=1;
    else
        for j=1:c
            G(i,p)=1;
            p=p+1;
            if(p>k)
                p=p-k;
            end
        end
    end
end
G
M1 = zeros(1,k);
for i=1:k
    for j=1:N
       if sum(G(j,:))==1
            [m,n] = max(G(j,:));
            m=j;
            M1(n)=E(m);
            G(m,n)=0;
            break;
       end
    end
    for j=1:N
        if G(j,n)==1
            E(j)=bitxor(E(j),M1(n));
            G(j,n)=0;
        end        
    end
end     
char(M1)