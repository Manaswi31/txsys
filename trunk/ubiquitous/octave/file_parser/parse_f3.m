 	
function [coeff_f3, x1, x2] =  parse_f3(line)
%         if coeff_f3~=0
%                 coeff_f3 = 0;
%         end
%         if x1~=0
%                 x1 = 0;
%         end
%         if x2~=0
%                 x2 = 0;
%         end
    coeff_f3 = 0;
    x1 = 0;
    x2 = 0;
        if length(line)>5 && 1==strcmp('x0:', line(1:3))
            x1_str = line(5:end);
            x1 = str2num(x1_str);
        end

        if length(line)>5 && 1==strcmp('x1:', line(1:3))
            x2_str = line(5:end);
            x2 = str2num(x2_str);
        end

        keystr = 'ber:';
        keylen = length(keystr);
        if length(line)>keylen && 1==strcmp(keystr, line(1:keylen))
            f3_coeff_str = line(keylen+1:end);
            startpos = strfind(f3_coeff_str, ' ');
            endpos = [strfind(f3_coeff_str, ',') length(f3_coeff_str)];
            %coeff_f3 = [];
            for ii=1:length(startpos)
                    coeff_f3 (ii) = str2double(f3_coeff_str(startpos(ii):endpos(ii)));
            end
    end  %end of if

