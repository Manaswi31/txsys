d_max = 100;
f = 2.4e9;
d = 10:10:d_max;
pl_dBm = fspl_dbm(f, d);

rcv_thrshld_dBm = -90; %dBm
xmt_pwr_dBm = rcv_thrshld_dBm + fspl_dbm(f, d_max)
xmt_pwr_mW = 10^(xmt_pwr_dBm/10)
rcv_prw_dBm = xmt_pwr_dBm - pl_dBm ;
plot(d, rcv_prw_dBm, 'b.-');
title('Free-space path loss for a 2.4GHz WLAN signal');
ylabel('Mininum recvied power (dBm)');
xlabel('Tx-Rx distance (m)' );
grid on
