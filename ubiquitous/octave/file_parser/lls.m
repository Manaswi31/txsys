clear all;
dirn=dir('*.txt');
dirc=length(dirn);

line_args = [
            'b.-',
            'go-',
            'rx-',
            'c+-',
            'm*-',
            'bs-',
            'gd-',
            'rv-',
            'c^-',
            'm<-'
] ;

curve_counter = 1;

for jj=1:dirc

        file_struct = dirn(jj);
        filename = file_struct.name;
        fp_source = fopen(filename, 'r');

        group_index = 0;

        cirmin = [];
        cirmax = [];
        sirmin = [];
        sirmax = [];

        [coeff_f3, coeff_f4, coeff_f5, f4_x1, f4_x2, f5_x1, f5_x2, f3_x1, f3_x2] = lls_file_parse(fp_source);

limits = [f4_x1 f4_x2 f5_x1 f5_x2 f3_x1 f3_x2];
[cir, sir, ber ,bler] = reg_plot(limits, coeff_f4, coeff_f5, coeff_f3, line_args(:, jj));


end %for


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%curve 1 cr=0.5
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%coeff_f4 = [1.621642667841940e+001, 4.869510663780906e-001, 1.062202390609047e-002 0 0 0 0 0 0 0];
%
%coeff_f5 = [-1.387657093128833e+004, 7.007391413752364e+003, -1.546051422232924e+003, 1.956337132108143e+002, -1.565164543603494e+001, 8.214390494742501e-001, -2.829683477558478e-002, 6.173289077423715e-004, -7.744221301713878e-006, 4.258692786738095e-008];
%
%coeff_f3 = [8.453085105749641e-001, 2.212612996582892e+000, 2.187293961324546e-001 0 0 0 0 0 0 0];

%limits = [-20, 34, 1.084650e+001, 2.824850e+001, -3.586000e+000, -3.012900e-001];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

title_str = 'HSPDSCH 64QAM OTIA3';

legends = [
'CodeRate=0.5'
'CodeRate=0.6'
'CodeRate=0.7'
'CodeRate=0.8'
'CodeRate=0.9'
'CodeRate=1.0'
] ;

title (title_str);
xlabel('CIR per SF16 VRU [dB]');
ylabel('BLER (base10 exponent)');
legend(legends, 3);
axis([-20 20 -6 1])
grid on

