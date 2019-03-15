function [E,X] = encoded(x,pmf,N,a)
X = rand_gen(x,pmf,N)
M = double(a);
N=length(X);
k=length(M);
E=zeros(1,N);
for i=1:N
    if i>k
        p=i-k;
    else
        p=i;
    end
    c=X(i);
    if c==1
        E(i)=M(p);
    else
        for j=1:c-1
            q=p;
            p=p+1;
            if(p>k)
                p=p-k;
            end
            if j==1
                x=M(q);
            else
                x=E(i);
            end
            E(i)=bitxor(x,M(p));      
        end
    end
end
end