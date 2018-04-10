import math

print ("Sonia")
source=input("Enter the source node ")
dest=input("Enter the destination ")

x=open('a*_LatLonInformation.txt','r')
x1=x.readlines()
#print x1

x2F=open('heuristics_MM.txt'+" "+str(source),'w')
x2B=open('heuristics_MM.txt'+" "+str(dest),'w')

goal=x1[dest-1]
goal_lat,goal_lon=goal.split(" ")

for i in range(0,len(x1)):
	lat,lon=x1[i].split(" ")
	d=math.sqrt((float(goal_lat)-float(lat))**2+(float(goal_lon)-float(lon))**2)
	x2F.write(str(d))
	x2F.write('\n')


goal=x1[source-1]
goal_lat,goal_lon=goal.split(" ")

for i in range(0,len(x1)):
	lat,lon=x1[i].split(" ")
	d=math.sqrt((float(goal_lat)-float(lat))**2+(float(goal_lon)-float(lon))**2)
	x2B.write(str(d))
	x2B.write('\n')
