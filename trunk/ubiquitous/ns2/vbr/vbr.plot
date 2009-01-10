set grid
set ylabel 'traffic received (Bytes/sec)'
set xlabel 'time(s)'

plot 'cbr-sim.out' w lines title 'cbr' linetype 1, \
    'vbr-uniform.out' w lines title 'uniform' linetype 2, \
    'vbr-normal.out' w lines title 'normal' linetype 3, \
    'vbr-expo.out' w lines title 'exponential' linetype 4
