 	
function [coeff_f3, coeff_f4, coeff_f5, f4_x1, f4_x2, f5_x1, f5_x2, f3_x1, f3_x2] = lls_file_parse(fp_source)

line_counter = 0;

        inblock_f4 = 0;
        inblock_f5 = 0;
        inblock_f3 = 0;
	block = [];

while(1)
        line = fgetl(fp_source);
        line_counter = line_counter + 1;

        if line==-1
                break
        end

        if 0==inblock_f4
            if 0==isempty(strfind (line, 'start_CirToSnr_F4'))
                inblock_f4 = 1;
            else
                %continue;
            end
        end

        if 1==inblock_f4
                if 0==isempty(strfind (line, 'end_CirToSnr_F4'))
                        inblock_f4 = 0;
                        [coeff_f4_temp, f4_x1_inter_temp, f4_x2_inter_temp] = parse_f4(block);
                        if coeff_f4_temp~=0
                                coeff_f4 = coeff_f4_temp;
                        end

                        if f4_x1_inter_temp~=0
                                f4_x1 = f4_x1_inter_temp;
                        end

                        if f4_x2_inter_temp~=0
                                f4_x2 = f4_x2_inter_temp;
                        end

                       continue;
                else
		    block = [block line]; %%%contaminate to be a long line
                end
        end

        %%%%%
	if 0==inblock_f5
            if 0==isempty(strfind (line, 'start_SirToRawBer_F5'))
                inblock_f5 = 1;
		block = line;
		continue;
            else
                %continue;
            end
        end
        
        if 1==inblock_f5
		block = [block line] %%%contaminate to be a long line
                if 0==isempty(strfind (line, 'end_SirToRawBer_F5'))
                        inblock_f5 = 0;
                        [coeff_f5_temp, f5_x1_inter_temp, f5_x2_inter_temp] = parse_f5(block);
                        if coeff_f5_temp~=0
                                coeff_f5 = coeff_f5_temp;
                        end

                        if f5_x1_inter_temp~=0
                                f5_x1 = f5_x1_inter_temp;
                        end

                        if f5_x2_inter_temp~=0
                                f5_x2 = f5_x2_inter_temp;
                        end

                       continue;
                end
	end

        %%%%%%%%%%%%%%%%%%%
        %Parsing F3%
        %%%%%%%%%%%%%%%%%%%

	if 0==inblock_f3
            if 0==isempty(strfind (line, 'start_RawBerToBler_F3'))
                inblock_f3 = 1;
		block = [];
            else
                %continue;
            end
        end
        
          if 1==inblock_f3
                if 0==isempty(strfind (line, 'end_RawBerToBler_F3'))
                        inblock_f3 = 0;
                        [coeff_f3_temp, f3_x1_inter_temp, f3_x2_inter_temp] = parse_f3(block);
                        if coeff_f3_temp~=0
                                coeff_f3 = coeff_f3_temp;
                        end

                        if f3_x1_inter_temp~=0
                                f3_x1 = f3_x1_inter_temp;
                        end

                        if f3_x2_inter_temp~=0
                                f3_x2 = f3_x2_inter_temp;
                        end

                       continue;
                else
		    block = [block line]; %%%contaminate to be a long line
                end
	end

end %end of outer while(1)

