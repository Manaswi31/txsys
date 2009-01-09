set title 'throughput'
set grid
set ylabel 'MBytes/s'
set xlabel 's'

plot 'cbr-sim.out' w lines title 'LAN' linetype 1, 'vbr-sim.out' w lines title '802.11b' linetype 2
