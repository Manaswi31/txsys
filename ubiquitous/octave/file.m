EOF=-1;

s_fid = fopen('test','r');
d_fid = fopen('out','w');

i=1;

while (true)
    str=fgets(s_fid);
    if(str==EOF)
	break;
    end
    if (mod(i, 2)==0) 
	fwrite(d_fid, str);
    end
    i++;
end

fclose(s_fid);
fclose(d_fid);
