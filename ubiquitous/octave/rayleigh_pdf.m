variance=1;
r=linspace(0,3,100);
rayleigh_pdf=2*r/variance.*exp(-r.^2/variance);
plot(r, rayleigh_pdf);
