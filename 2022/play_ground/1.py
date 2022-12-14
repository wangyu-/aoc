#!/usr/bin/env python3
#  a<b -1  a=b 0   a>b 1
def cmp1(a,b):
    if a<b:
        return -1
    if a==b:
        return 0
    if a>b:
        return 1
ll = [5,3,2,4,1]
import functools
ll=sorted(ll, key= functools.cmp_to_key(cmp1))
print(ll)
