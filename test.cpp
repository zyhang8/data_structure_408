//
// Created by Mr. Roy Z. on 2020-06-10.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// test.cpp
//

#include <cstdio>
#include <cstdlib>

int bei(int x,int y){
    for(int i=x; i>0; i++)  /*从大数开始寻找满足条件的自然数*/
        if(i%x==0 && i%y==0)
        {
            return i;
        }
    return 0;
}

int main()
{
    int m, n, temp;
    printf("Input m & n:");
    scanf("%d%d", &m, &n);
    if(m<n)
    {
        temp = m;
        m = n;
        n = temp;
    }
    printf("%d",bei(m,n));


    return 0;
}