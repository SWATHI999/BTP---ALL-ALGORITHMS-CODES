x=open('Analysis_of_MM.txt',"r")
x3=open('analysis__cputime.txt',"a")
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
x3.write("MM"+" "+str(avg))
x3.write('\n')
