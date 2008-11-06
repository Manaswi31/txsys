BEGIN {
    bytes_sec = 0;
    sflag = 0;
    eflag = 0;
    start=0.0;
    end=0.0;
    }
    {
	if ($1=="r" && $4=="5" && $5=="cbr") {
	    if (sflag==0) {
		sflag=1;
		start = $2
	    }
	    end=$2;
	    bytes_sec+=$6;
	}
    }
END {
    bytes_sec = bytes_sec / (end-start);
    #printf("%f-%f\n", end, start);
    printf( "NODE1.CBR traffic received (bytes/sec): %f\n", bytes_sec );
    }
