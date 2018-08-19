import math
x=open('a*_LatLonInformation.txt','r')
print "Enter the destination node"
dest = input()
x1 = x.readlines()
print x1[0]
x2B=open('target_heuristics.txt','w')

goal=x1[dest-1]
goal_lat,goal_lon=goal.split(" ")

for i in range(0,len(x1)):
	lat,lon=x1[i].split(" ")
	d=math.sqrt((float(goal_lat)-float(lat))**2+(float(goal_lon)-float(lon))**2)
	x2B.write(str(d))
	x2B.write('\n')
