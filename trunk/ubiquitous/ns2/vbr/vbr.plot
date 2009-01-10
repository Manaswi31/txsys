set title 'throughput'
set grid
set ylabel 'MBytes/s'
set xlabel 's'

plot 'cbr-sim.out' w lines title 'cbr' linetype 1, 'vbr-sim.out' w lines title 'uniform' linetype 2
