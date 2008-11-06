BEGIN {
    node = 1;
    recv_bytes_sec = 0;
    recv_sflag = 0;
    recv_start=0.0;
    recv_end=0.0;

    sent_sflag = 0;
    sent_start=0.0;
    sent_end=0.0;
    }
    {
	if ($1=="r" && $4==node && $5=="cbr") {
	    if (recv_sflag==0) {
		recv_sflag=1;
		recv_start = $2
	    }
	    recv_end=$2;
	    recv_bytes_sec+=$6;
	}
	if ($1=="+" && $3==node && $5=="cbr") {
	    if (sent_sflag==0) {
		sent_sflag=1;
		sent_start = $2
	    }
	    sent_end=$2;
	    sent_bytes_sec+=$6;
	}   }
END {
    recv_bytes_sec = recv_bytes_sec / (recv_end-recv_start);
    sent_bytes_sec = sent_bytes_sec / (sent_end-sent_start);
    #printf("%f-%f\n", end, start);
    printf("NODE%d.CBR: \n", node);
    printf( "\ttraffic received (bytes/sec): %.2f\n", recv_bytes_sec );
    printf("\ttraffic sent (bytes/sec): %.2f\n", sent_bytes_sec);
    }
