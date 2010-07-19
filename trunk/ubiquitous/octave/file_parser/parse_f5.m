 	
function [coeff_f5, x1, x2] =  parse_f5(line)
%         if coeff_f5~=0
%                 coeff_f5 = 0;
%         end
%         if x1~=0
%                 x1 = 0;
%         end
%         if x2~=0
%                 x2 = 0;
%         end
    coeff_f5 = 0;
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

        keystr = 'sir:';
        keylen = length(keystr);
        if length(line)>keylen && 1==strcmp(keystr, line(1:keylen))
            f5_coeff_str = line(keylen+1:end);
            startpos = strfind(f5_coeff_str, ' ');
            endpos = [strfind(f5_coeff_str, ',') length(f5_coeff_str)];
            %coeff_f5 = [];
            for ii=1:length(startpos)
                    coeff_f5 (ii) = str2num(f5_coeff_str(startpos(ii):endpos(ii)));
            end
    end  %end of if

