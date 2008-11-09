set title 'example4'
set grid
set ylabel 'Mbit/s'
set xlabel 's'

plot 'out0.tr' w lines title 'LAN.throughput' linetype 1, 'out1.tr' w lines title 'LAN.throughput' linetype 2
#plot 'example1_dataset_random2' w lines title 'sink.e2e delay' linetype 2
