function D = get_D(number)
	h = 1/number;
	number -= 2;
	D = zeros(number,number);
	
	D(1,1) = -2/h;
	D(1,2) = 1/h;
	
	D(number,number-1) = 1/h;
	D(number,number)   = -2/h;
	
	for i = 2:number-1
		D(i,i) =  -2/h;
		D(i,i-1) = 1/h;
		D(i,i+1) = 1/h;
	endfor
	
endfunction