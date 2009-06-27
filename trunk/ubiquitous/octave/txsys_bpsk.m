NSymbols=1E5;
EbvsN0=-10:0.38:10;
snr=10.^(EbvsN0/10);

len_snr = length(EbvsN0);

for it=1:len_snr
    sigma=sqrt(1/(2*snr(it)));
    errorCount = 0;
    d = round(rand(1, NSymbols));
    s = 2*d-1;
    n = sigma*randn(1, NSymbols);
    r=s+n;
    d_est=r>0;
    errors(it) = size(find(d_est-d), 2);
end
theoryBer = 0.5*erfc(sqrt(10.^(EbvsN0/10)));
berSim=errors/NSymbols
figure(1);
semilogy(EbvsN0, theoryBer, 'b.-', EbvsN0, berSim, 'o');
legend('theory', 'simulation');
xlabel('Eb/No, dB');
ylabel('Bit Error Rate');
title('Bit error probability curve for BPSK modulation');
axis([-10 10 10^-5 0.5])
grid on 

figure(2);
plot(EbvsN0, theoryBer, 'b.-', EbvsN0, berSim, 'o');
legend('theory', 'simulation');
xlabel('Eb/No, dB');
ylabel('Bit Error Rate');
title('Bit error probability curve for BPSK modulation');
axis([-10 10 10^-5 0.5])
grid on 

