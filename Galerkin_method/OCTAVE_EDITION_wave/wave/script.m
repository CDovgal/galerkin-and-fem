clear number;clear count;clear delta_t;clear init_state;clear C;clear D;clear A;

number = 100;
count = 1000;
delta_t = 0.005;

init_state = get_init_state(number); save "output/init_state.m" init_state;

C = get_C(number); 					 save "output/C.m" C;
D = get_D(number); 					 save "output/D.m" D;
A = get_A(C,D);				     	 save "output/A.m" A;

result = runge(A,init_state, count, delta_t); 
									 save "output/result.m" result;
									 
for_plot = for_gnuplot(number,result);
									 save "plot/OCTAVE_RESULT.dat" for_plot;