#!/usr/bin/env python3
input=open("input.txt")

lines= input.read().split('\n');

n = len(lines)

#  a<b -1  a=b 0   a>b 1
def cmp1(a,b):
    if type(a)!=list and type(b)!=list:
        if a<b:
            return -1
        if a==b:
            return 0
        if a>b:
            return 1
    if type(a)==list and type(b)!= list:
        b = [b]
    if type(a)!=list and type(b)== list:
        a = [a]
    len_a= len(a)
    len_b= len(b)
    mlen= min(len_a,len_b)
    for i in range(0,mlen):
        r=cmp1(a[i],b[i])
        if(r!=0):
            return r;
    return cmp1(len_a,len_b)
        

sum=0
ll=[]
for i in range(0,n,3):
    #print(lines[i])
    #print(lines[i+1])
    a =eval (lines[i])
    b=eval(lines[i+1])
    r= cmp1(a,b)
    if(r!=1):
        sum+=i//3+1
    #print(r)
    ll.append(eval(lines[i]))
    ll.append(eval(lines[i+1]))
    #print(lines[i+2])
print(sum)
ll.append([[2]])
ll.append([[6]])

import functools
ll=sorted(ll, key= functools.cmp_to_key(cmp1))

for i in range(0,len(ll)):
    if(str(ll[i])=="[[2]]"):
        print (i+1)
    if(str(ll[i])=="[[6]]"):
        print (i+1)
