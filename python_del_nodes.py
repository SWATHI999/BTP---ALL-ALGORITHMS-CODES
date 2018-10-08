node = input('Enter node ')
x=open('/home/sonia/Graph_Data_Edges_cpy.txt', 'r')
new_file=open('/home/sonia/Graph_Data_Edges_'+str(node)+'.txt', 'w')

g=x.readlines()

for i in range(0, len(g)):
	t=g[i].split(' ')
	x1=int(t[0])
	x2=t[1]
	z=x2.split('e')
	z1=int(z[0])
	if x1!=node:
		if z1!=node:
			new_file.write(g[i])
