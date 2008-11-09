BEGIN {
    node = 3;
   }

    {
	if (time2 - time1 > 0.050) {
	    thru = bytes_counter / (time2-time1);
	    printf("%f %f\n", time2, thru) > "example4_pre";
	    time1=$2;
	    bytes_counter=0;
	}
	

	if ($1=="+" && $3!=node && $5=="exp") {
	    bytes_counter += $6;
	}   
    }

END {
}
