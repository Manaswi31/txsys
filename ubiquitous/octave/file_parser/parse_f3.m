 	
function [coeff_f3, x1, x2] =  parse_f3(line)
    coeff_f3 = 0;
    x1 = 0;
    x2 = 0;

	key1 = 'x0: ';
	key2 = 'x1: ';
	pos1 = strfind(line, key1);
	pos2 = strfind(line, key2);
	x1_str = line(pos1+length(key1):pos2-1);
	x1 = str2num(x1_str);

	key1 = key2;
	key2 = 'ber: ';
	pos1 = strfind(line, key1);
	pos2 = strfind(line, key2);
	x2_str = line(pos1+length(key1):pos2-1);
	x2 = str2num(x2_str);

	key1 = 'ber:';
	key2 = 'end_RawBerToBler_F3';
	pos1 = strfind(line, key1);
	pos2 = strfind(line, key2);
	f3_coeff_str = line(pos1+length(key1):pos2-1);
	startpos = strfind(f3_coeff_str, ' ');
	endpos = [strfind(f3_coeff_str, ',') length(f3_coeff_str)];
	%coeff_f3 = [];
	for ii=1:length(startpos)
		coeff_f3 (ii) = str2num(f3_coeff_str(startpos(ii):endpos(ii)));
	end
    end  %end of if
