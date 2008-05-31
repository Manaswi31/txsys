snrdB_min = 0; snrdB_max = 10;
snrdB = snrdB_min:1:snrdB_max;
Nsymbols = input('Enter number of symbols > ');
snr = 10.^(snrdB/10);
len_snr = length(snrdB);
for j = 1:len_snr
    sigma = sqrt(1/(2*snr(j))); %noise standard deviation
    error_count = 0;
    for k = 1:Nsymbols
	d = round(rand(1));
	if d==0
	    x_d=1;
	    x_q=0;
	else
	    x_d=0;
	    x_q=1;
	end
	n_d=sigma*randn(1);
	n_q=sigma*randn(1);
	y_d = x_d+n_d;
	y_q = x_q+n_q;
	if y_d>y_q
	    d_est=0;
	else
	    d_est=1;
	end
	if (d_est ~= d)
	    error_count=error_count+1;
	end
    end
    errors(j)=error_count;
end
ber_sim=errors/Nsymbols;
ber_bfsk_theor=q(sqrt(snr));
ber_bpsk_theor=q(sqrt(2*snr));
semilogy(snrdB,ber_bfsk_theor,snrdB,ber_bpsk_theor,'g', snrdB,ber_sim,'o')
axis([snrdB_min snrdB_max 0.0001 1])
xlabel('SNR in dB')
ylabel('BER')
%legend('Theoretical', 'Simulation')
