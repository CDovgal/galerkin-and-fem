function R = runge(A, init_state, count, delta_time)
	R = zeros(length(init_state),count+1);
	
	R(:,1) = init_state;
	curr_state = init_state;
	
	for i = 1:count
		curr_state = R(:,i);
		k1 = A * (curr_state);
		
		k2 = A * (curr_state + k1/2);
		
		k3 = A * (curr_state + k2/2);
		
		k4 = A * (curr_state + k3 );
		
		new_state = curr_state + delta_time*( k1 + 2*k2 + 2*k3 + k4)/6;
		R(:,i+1) = new_state;
	endfor
	
end