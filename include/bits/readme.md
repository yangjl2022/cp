# Setting
预编译头文件
```
g++ -std=c++20 -x c++-header -o include/bits/stdc++.h.gch -c include/bits/stdc++.h
```
下次编译指令使用会自动识别
```
g++ -std=c++20 -include D:\CPPCODE\include\bits\stdc++.h test.cpp
```