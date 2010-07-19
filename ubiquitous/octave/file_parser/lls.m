clear all;
fp_source = fopen('lls.txt', 'r');
inblock = 0;

group_index = 0;

cirmin = [];
cirmax = [];
sirmin = [];
sirmax = [];

x1_flag = 0;
line_counter = 0;

while(1) 
	line = fgetl(fp_source);
	line_counter = line_counter + 1;

	if line==-1
		break
	end

	if 0==inblock 
	    if 0==isempty(strfind (line, 'start_CirToSnr_F4'))
		inblock = 1;
	    else
		continue;
	    end
	end


	if 0==strcmp('x1_inter', line(1:8))
	    x1_inter = line(11:end);
	end




end

