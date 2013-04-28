function P = for_gnuplot(number, R)
	h = 1/number;
		
	[size1, size2] = size(R);
	P = zeros(size1/2,size2+1);
	
	for i = 1:size1/2
		P(i,1) = i*h;
		for j = 2:size2+1
			P(i,j) = R(i,j-1);
		endfor
	endfor
end