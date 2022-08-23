chairX = np.array([[int(values[0]),int(values[1]),int(values[2])],[int(values[3]),int(values[4]),int(values[5])],[int(values[6]),int(values[7]),int(values[8])]])
chairY = np.array([[int(values[0]),int(values[3]),int(values[6])],[int(values[1]),int(values[4]),int(values[7])],[int(values[2]),int(values[5]),int(values[8])]])
        dis = np.array([1,13,25])         
        totX= chairX*dis
        totY = chairY*dis
        meanX = np.array([])
        meanY = np.array([])
        valueX = np.array([])
        valueY = np.array([])

for i in range(3):
            
            tot = totX[[0,1,2][i]]
            X = chairX[[0,1,2][i]]
        
            p = sum(tot)/sum(X)
            v = sum(X)
            meanX = np.append(meanX,p)
            valueX = np.append(valueX,v) 
            meanXT = meanX * valueX
            FX = sum(meanXT)/sum(valueX)

        
        for i in range(3):
            
            tot = totY[[0,1,2][i]]
            Y = chairY[[0,1,2][i]]
        
            p = sum(tot)/sum(Y)
            v = sum(Y)
            
            meanY = np.append(meanY,p)
            valueY = np.append(valueY,v) 
            meanYT = meanY * valueY
            FY = sum(meanYT)/sum(valueY)    