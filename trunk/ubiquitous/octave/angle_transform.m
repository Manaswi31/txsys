if (input>0)
    degree = ceil(input) - 1;
elseif (input<0)
    degree = ceil(input);
endif
temp1 = abs(input-degree);
fen=ceil(temp1*60)-1;
miao=60*(temp1*60-fen);
printf("%d %d\'%f\"\n", degree, fen, miao);
