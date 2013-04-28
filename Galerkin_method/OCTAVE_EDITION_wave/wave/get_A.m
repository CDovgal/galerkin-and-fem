function A = get_A(C,D)

	number = length(C);
	
	A = zeros(number*2, number*2);
	
	N = inv(C) * D;						 save "D:/wave/output/N.m" N;
	
	j = number+1;
	for i = 1 : number
		A(i,j++) = 1;
	endfor

	for i = number+1:number*2
		for j = 1:number
			A(i,j) = N(i-number,j);
		endfor
	endfor
end