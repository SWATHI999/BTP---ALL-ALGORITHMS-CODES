x=open('analysis_bibfs.txt',"r")
x3=open('CPU_Time_Analysis.txt',"a")
x1=x.readlines()

x2= x1[2:]
#print x2
avg=0
sum1=0

for i in range(len(x2)):
	temp=x2[i].split(" ")
	#print temp[2]
	sum1=sum1+float(temp[3])

avg=sum1/len(x2)
#print avg
x3.write("Bibfs"+" "+str(avg))
x3.write('\n')
