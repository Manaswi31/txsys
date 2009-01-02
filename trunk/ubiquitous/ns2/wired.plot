set title 'throughput'
set grid
set ylabel 'MBytes/s'
set xlabel 's'

plot 'wired-thru.out' w lines title 'LAN' linetype 1, 'wireless.data' w lines title '802.11b' linetype 2
