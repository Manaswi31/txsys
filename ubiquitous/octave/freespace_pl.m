f=30E6 % Hz
d=10E6 % m
N=4E-14 % mW
SNR=6.2
Gp=9.67 % procss gain
c=3E8

Pt=N*10^((SNR-Gp)/10)*(4*pi*f*d/c)^2
Pt=20*log10(f)-147.56+10*log10(N)+SNR-Gp+20*log10(d)
