BEGIN {
    node1_cbr_sent_bytes_sec = 0.0;
    node1_cbr_sent_start_flag = 0;
    node1_cbr_sent_start = 0.0;
    node1_cbr_sent_end = 0.0
    
    node2_cbr_sent_bytes_sec = 0.0;
    node2_cbr_sent_start_flag = 0;
    node2_cbr_sent_start = 0.0;
    node2_cbr_sent_end = 0.0
    
    node0_cbr_sent_bytes_sec = 0.0;
    node0_cbr_sent_start_flag = 0;
    node0_cbr_sent_start = 0.0;
    node0_cbr_sent_end = 0.0
    
    node4_cbr_rcv_bytes_sec = 0.0;
    node4_cbr_rcv_start_flag = 0;
    node4_cbr_rcv_start = 0.0;
    node4_cbr_rcv_end = 0.0;

    traffic_loss = 0.0;
    
}
{
	if ($1~/r/ && $4~/4/) {
		if (node4_cbr_rcv_start_flag == 0) {
			node4_cbr_rcv_start = $2;
			node4_cbr_rcv_start_flag=1;
		}
		node4_cbr_rcv_end = $2;
		node4_cbr_rcv_bytes_sec += $6;
	}
	
	if ($1~/\+/) {
		if ($3~/1/) {
			if (node1_cbr_sent_start_flag == 0) {
				node1_cbr_sent_start = $2;
				node1_cbr_sent_start_flag = 1;
			}
			node1_cbr_sent_end = $2;
			node1_cbr_sent_bytes_sec += $6;
		}
		else if ($3~/2/) {
			if (node2_cbr_sent_start_flag == 0) {
				node2_cbr_sent_start = $2;
				node2_cbr_sent_start_flag = 1;
			}
			node2_cbr_sent_end = $2;
			node2_cbr_sent_bytes_sec += $6;
		}
		else if ($3~/0/) {
			if (node0_cbr_sent_start_flag == 0) {
				node0_cbr_sent_start = $2;
				node0_cbr_sent_start_flag = 1;
			}
			node0_cbr_sent_end = $2;
			node0_cbr_sent_bytes_sec += $6;			
		}
	}
		
}

END {
	traffic_loss = node0_cbr_sent_bytes_sec + node1_cbr_sent_bytes_sec  + node2_cbr_sent_bytes_sec - node4_cbr_rcv_bytes_sec ;
	if(node4_cbr_rcv_end-node4_cbr_rcv_start) {
		node4_cbr_rcv_bytes_sec = node4_cbr_rcv_bytes_sec/(node4_cbr_rcv_end-node4_cbr_rcv_start);
		traffic_loss = traffic_loss /(node4_cbr_rcv_end-node4_cbr_rcv_start); 
	}

	if (node1_cbr_sent_end-node1_cbr_sent_start) {
		node1_cbr_sent_bytes_sec = node1_cbr_sent_bytes_sec/(node1_cbr_sent_end-node1_cbr_sent_start);
	}
	
	if (node2_cbr_sent_end-node2_cbr_sent_start) {
		node2_cbr_sent_bytes_sec = node2_cbr_sent_bytes_sec/(node2_cbr_sent_end-node2_cbr_sent_start);
	}
	
	if (node0_cbr_sent_end-node0_cbr_sent_start) {
		node0_cbr_sent_bytes_sec = node0_cbr_sent_bytes_sec/(node0_cbr_sent_end-node0_cbr_sent_start);
	}	
	printf("Node 0.Traffic sent (bytes/sec): %f\n", node0_cbr_sent_bytes_sec);	
	printf("Node 1.Traffic sent (bytes/sec): %f\n", node1_cbr_sent_bytes_sec);
	printf("Node 2.Traffic sent (bytes/sec): %f\n", node2_cbr_sent_bytes_sec);
	printf("Node 4.Traffic received (bytes/sec): %f\n", node4_cbr_rcv_bytes_sec); 
	if (traffic_loss > 0) {
		printf("CBR.Traffic loss (bytes/sec): %f\n" , traffic_loss );
	}
    }
