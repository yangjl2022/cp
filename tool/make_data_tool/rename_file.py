"""
此程序用于对"pref"文件夹下的所有成对的".in"和".out"文件按字典序重命名成"1.in","1.out",..,"99.in","99.out",..
请保证文件夹下仅含有成对的成对的".in"和".out"文件，无其他无关文件
"""
import os

pref = r'C:\Users\21396\Desktop\data\\'
names = os.listdir(pref)
names.sort()
idx = 0
for name in names:
    if name[-1] == 'n':
        idx += 1
        os.rename(pref+name, pref+str(idx)+'.in')
    else:
        os.rename(pref+name, pref+str(idx)+'.out')
