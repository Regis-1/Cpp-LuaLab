x = {}
y = {}

for i=1,5,0.1 do
	x[#x+1] = i
	y[#y+1] = -math.sin(i)
end

H_Plot(x,y)