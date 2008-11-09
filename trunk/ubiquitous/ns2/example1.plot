set title 'ns2 live demo 1'
set grid
set ylabel 's'
set xlabel 's'

plot 'example1_dataset' w lines title 'sink.e2e delay' linetype 1, 'example1_dataset_random2' w lines title 'sink.e2e delay' linetype 2
#plot 'example1_dataset_random2' w lines title 'sink.e2e delay' linetype 2
