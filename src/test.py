import numpy as np
v = np.array([200,1,1,1,1,1,1,1,1])
chairY = np.array([[int(v[0]),int(v[3]),int(v[6])],[int(v[1]),int(v[4]),int(v[7])],[int(v[2]),int(v[5]),int(v[8])]])
dis = np.array([1,13,25])         
totY= chairY*dis
meanY = np.array([])
valueY = np.array([])
for i in range(3):  
            tot = totY[[0,1,2][i]]
            Y = chairY[[0,1,2][i]]
            p = sum(tot)/sum(Y)
            v2 = sum(Y)
            p2 = (sum(tot)/sum(Y))*sum(Y)
            print(p2)
            meanY = np.append(meanY,p)
            valueY = np.append(valueY,v2) 

meanYT = meanY * valueY
FY_old = sum(meanYT)/sum(valueY)  
print(FY_old)

FY = (
    dis[0]*v[0]+dis[1]*v[3]+dis[2]*v[6]+
    dis[0]*v[1]+dis[1]*v[4]+dis[2]*v[7]+
    dis[0]*v[2]+dis[1]*v[5]+dis[2]*v[8]
    )/sum(v)

print(FY)

