BEGIN {
    node = 1;
    time1 = 0.0;
    time2 = 0.0;
   }

    {
	time2 = $2;
	if (time2 - time1 > 0.050) {
	    thru = bytes_counter / (time2-time1);
	    printf("%f %f\n", time2, thru) > "example1_dataset";
	    time1=$2;
	    bytes_counter=0;
	}
	

	if ($1=="r" && $4==node && $5=="cbr") {
	    bytes_counter += $6;
	}   
}

END {
}
