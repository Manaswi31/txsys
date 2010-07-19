 	
function [coeff_f4, x1_inter, x2_inter] =  parse_f4(line)
    coeff_f4 = 0;
    x1_inter = 0;
    x2_inter = 0;

	key1 = 'x1_inter: ';
	key2 = 'x2_inter: ';
	pos1 = strfind(line, key1);
	pos2 = strfind(line, key2);
	x1_inter_str = line(pos1+length(key1):pos2-1);
	x1_inter = str2num(x1_inter_str);

	key1 = key2;
	key2 = 'x0_intra: ';
	pos1 = strfind(line, key1);
	pos2 = strfind(line, key2);
	x2_inter_str = line(pos1+length(key1):pos2-1);
	x2_inter = str2num(x2_inter_str);

	key1 = 'CIR_Inter:';
	key2 = 'CIR_Intra:';
	pos1 = strfind(line, key1);
	pos2 = strfind(line, key2);
	f4_coeff_str = line(pos1+length(key1):pos2-1);
	startpos = strfind(f4_coeff_str, ' ');
	endpos = [strfind(f4_coeff_str, ',') length(f4_coeff_str)];
	%coeff_f4 = [];
	for ii=1:length(startpos)
		coeff_f4 (ii) = str2num(f4_coeff_str(startpos(ii):endpos(ii)));
	end
%	x1_inter
%	x2_inter
%	coeff_f4
    end  %end of if
