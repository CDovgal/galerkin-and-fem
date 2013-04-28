plot "OCTAVE_RESULT.dat" using 1:i title sprintf("t=%i",i) with lines
i = i+1
if (i < 1002) reread;