import math
x=open('a*_LatLonInformation.txt','r')
h=open('target_heuristics.txt','r')
t=open('complete_file.txt','w')

x1=x.readlines()
x2=h.readlines()

for i in range(0,len(x1)):
	lat,lon=x1[i].split(" ")
	heuristic=x2[i]
	t.write(str(lat+" "+lon+" "+heuristic))
	t.write('\n')
