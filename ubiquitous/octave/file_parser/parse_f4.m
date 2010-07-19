 	
function [coeff_f4, x1_inter, x2_inter] =  parse_f4(line)
%         if coeff_f4~=0
%                 coeff_f4 = 0;
%         end
%         if x1_inter~=0
%                 x1_inter = 0;
%         end
%         if x2_inter~=0
%                 x2_inter = 0;
%         end
    coeff_f4 = 0;
    x1_inter = 0;
    x2_inter = 0;
    key = 'x1_inter';
    pos = strfind(line, key);
            x1_inter_str = line(pos+lengthkey:pos+8)
            x1_inter = str2num(x1_inter_str);
        end

        if length(line)>8 && 1==strcmp('x2_inter', line(1:8))
            x2_inter_str = line(11:end);
            x2_inter = str2num(x2_inter_str);
        end

        if length(line)>8 && 1==strcmp('x2_inter', line(1:8))
            x2_inter_str = line(11:end);
            x2_inter = str2num(x2_inter_str);
        end

        keystr = 'CIR_Inter:';
        keylen = length(keystr);
        if length(line)>keylen && 1==strcmp(keystr, line(1:keylen))
            f4_coeff_str = line(keylen+1:end);
            startpos = strfind(f4_coeff_str, ' ');
            endpos = [strfind(f4_coeff_str, ',') length(f4_coeff_str)];
            %coeff_f4 = [];
            for ii=1:length(startpos)
                    coeff_f4 (ii) = str2num(f4_coeff_str(startpos(ii):endpos(ii)));
            end
    end  %end of if
