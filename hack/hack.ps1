# "input"生成数据，用"std"来hack: "hacked.cpp"
cd d:/CPPCODE/hack

# hack --std
python "..\tool\pyjudge.py" hack "./hacked.cpp" -s "./std.cpp" -g "./input.cpp" -t 2
# pyjudge hack "./hacked.cpp" -s "./std.py" -g "./input.cpp" -t 2
# pyjudge hack "./hacked.py" -s "./std.cpp" -g "./input.cpp" -t 2

# hack --spj
# pyjudge hack "./hacked.cpp" --spj "./spj.cpp" -g "./input.cpp" -t 1

# judge
# pyjudge judge "./hacked.cpp" -t 2