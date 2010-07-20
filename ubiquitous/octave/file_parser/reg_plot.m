function [cir, sir, ber, bler] = reg_plot(limits, coeff_f4, coeff_f5, coeff_f3, line_arg)

%%%%%%%%%%%%%%%%%%%%%%%
% Dealing with F4
cir_orig=limits(1):limits(2);
coeff_f4=rot90(coeff_f4);
coeff_f4=transpose(coeff_f4);
sir_orig=polyval(coeff_f4, cir_orig);
index=[];

index_old = index;
index_new=find(sir_orig>=limits(3) & sir_orig<=limits(4));
start = max ([min(index_new) min(index_old)]);
stop = min([max(index_new) max(index_old)]);
index = start:stop;

cir_f4=cir_orig(index);
sir_f4=sir_orig(index);

sir = sir_f4;
cir = cir_f4;

%%%%%%%%%%%%%%%%%%%%%%%
% Dealing with F5
coeff_f5=rot90(coeff_f5);
coeff_f5=transpose(coeff_f5);
ber_orig=polyval(coeff_f5, sir_orig);

index_old = index;
index_new=find(ber_orig>=limits(5) & ber_orig<=limits(6));
start = max ([min(index_new) min(index_old)]);
stop = min([max(index_new) max(index_old)]);
index = start:stop;

sir_f5=sir_orig(index);
ber_f5=ber_orig(index);

ber = ber_f5;

%%%%%%%%%%%%%%%%%%%%%%%
% Dealing with F3
coeff_f3=rot90(coeff_f3);
coeff_f3=transpose(coeff_f3);
bler_orig = polyval(coeff_f3, ber_f5);
bler=bler_orig;

bler_f3=bler_orig;
ber_f3=ber_f5;
cir_f3=cir_orig(index);

%%%%%%%%%%%%%%%%%%%%%%%
subplot(221)
plot(cir_f4, sir_f4, line_arg);
title('CIR \~ SIR');
xlabel('CIR / dB');
ylabel('SIR / dB');
grid on;
hold on;

subplot(222)
plot(sir_f5, ber_f5, line_arg);
title('SIR \~ BER');
xlabel('SIR / dB');
ylabel('BER / (base10 exponent)');
axis([-Inf Inf -7 1]);
grid on;
hold on;

subplot(223)
plot(ber_f3, bler_f3, line_arg);
title('BER \~ BLER');
xlabel('BER / (base10 exponent)');
ylabel('BLER (base10 exponent)');
axis([-7 1 -5 1]);
grid on;
hold on;

subplot(224)
plot(cir_f3, bler_f3, line_arg);
hold on
