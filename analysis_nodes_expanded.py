x=open('analysis_bibfs.txt',"r")
x3=open('Nodes_Expanded_Analysis.txt',"a")
x1=x.readlines()

x2= x1[2:]
#print x2
avg=0
sum1=0

for i in range(len(x2)):
	temp=x2[i].split(" ")
	#print temp[3]
	sum1=sum1+int(temp[4])

avg=sum1/len(x2)
#print len(x2)
x3.write("Bibfs"+" "+str(avg))
x3.write('\n')
