snrdB_min=-3;snrdB_max=8;

snrdB=snrdB_min:1:snrdB_max;
Nsymbols=input('Enter number of symbols>');
snr=10.^(snrdB/10);
%h=waitbar(0, 'SNR Iteraction');
len_snr=length(snrdB)
for j=1:len_snr
%    waitbar(j/len_snr)
    sigma=sqrt(1/(2*snr(j)));
    error_count=0;
    for k=1:Nsymbols
        d = round(rand(1));
        %d = rand(1)
        x_d=2*d-1;
        n_d=sigma*randn(1);
        y_d=x_d+n_d;
        if y_d>0
            d_est=1;
        else
            d_est=0;
        endif
        if (d_est ~= d)
            error_count=error_count+1;
        endif
    endfor
    j
    errors(j)=error_count;
endfor
%close(h)
ber_sim=errors/Nsymbols
ber_theor=q(sqrt(2*snr));
%semilogy(snrdB, ber_theor, snrdB, ber_sim, 'o');
semilogy(snrdB, ber_sim)
%plot(snrdB, ber_theor, snrdB, ber_sim, 'o');
axis([snrdB_min snrdB_max 0.0001 1])
xlabel('SNR in dB')
ylabel('BER')
legend('Theoretical', 'Simulation')
grid on
