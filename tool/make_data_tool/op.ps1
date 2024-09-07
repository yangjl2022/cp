cd 'D:\CPPCODE\tool\make_data_tool'
python -u "gen.py"
pyjudge std.cpp -s

# 展示答案
Get-Content data/*.out