function N = get_C(number)
	h = 1/number;
	number -= 2;
	N = zeros(number,number);
	
	N(1,1) = 2*h/3; 			N(1,2) = h/6;
	%%
	N(number,number-1) = h/6;	N(number,number)   = 2*h/3;
	
	for i = 2:number-1
		N(i,i) = 2*h/3;
		N(i,i-1) = h/6;
		N(i,i+1) = h/6;
	endfor
end