function [X] = rand_gen(x,pmf,N);
d = cumsum(pmf(:));
a = [0;d]*(1./rand(1,N));
b = a>ones(length(pmf)+1,N);
[c,index] = max(b);
x = x(:);
X = x(index-1).';
end
