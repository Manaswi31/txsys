N = 0:10:100;
%
y1 = log(N); %logN 
%y2 = (log(N))^2; %log2N 
y3 = N;
y4 = N.*log(N);
y5 = N.^2;
y6 = N.^3;
y7= 2.^N;

%semilogy(N, y4, '-', N, y5);
plot(N, y4, '-', N, y5);
xlabel('Input Size')
ylabel('Running Time')
legend('NlogN', 'Quadratic')
