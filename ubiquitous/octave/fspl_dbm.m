function out_dBm = fspl_dbm(f, d)
out_dBm = 20*log10(f) + 20*log10(d) - 147.56;
