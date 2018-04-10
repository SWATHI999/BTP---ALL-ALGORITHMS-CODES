import matplotlib.pyplot as plt
x=open('analysis_cputime.txt',"r")
x1=x.readlines()
algo=[]
cpu=[]

for i in range(len(x1)):
	temp=x1[i].split(" ")
	algo.append(temp[0])
	cpu.append(temp[1])

plt.plot(algo, cpu,'ro')

#plt.axis([0, 6, 0, 20])

plt.xlabel('Algorithms')
plt.ylabel('Average CPU times')
plt.show()
