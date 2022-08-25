int calculateCOG(int v[], int arrSize){
    int dis[3]= {1,13,25};
    int sumV = 0;
    for (int i = 0; i <arrSize; i++) {
        sumV += v[i];
    }
    int FX = (dis[0]*v[0]+dis[1]*v[3]+dis[2]*v[6]+
              dis[0]*v[1]+dis[1]*v[4]+dis[2]*v[7]+
              dis[0]*v[2]+dis[1]*v[5]+dis[2]*v[8]
             )/sumV;
    int FY = (dis[0]*v[0]+dis[1]*v[3]+dis[2]*v[6]+
              dis[0]*v[1]+dis[1]*v[4]+dis[2]*v[7]+
              dis[0]*v[2]+dis[1]*v[5]+dis[2]*v[8]
             )/sumV;
return {FX, FY};
}