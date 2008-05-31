m = input('Enter M, number of experiments >')
n = input('Enter N, number of trials / experiment >')
z = zeros(1, m);
data = zeros(n,m);
for j=1:m
    x=rand(1,n);
    y=rand(1,n);
    k=0;
    for i=1:n
	if x(i)^2+y(i)^2<=1
	    k=k+1
	end
	data(i,j)=4*(k/i);
    end
    z(j)=data(n,j);
end
plot(data, 'k')
xlabel('Number of Trials')
ylabel('Estimate of pi')
