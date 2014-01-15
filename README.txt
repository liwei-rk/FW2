准备:
    make 生成libwritedoc.so ；//移到/usr/lib下?
编写源码：
    可参照example.cpp
编译:
    g++ -o example  example.cpp -lwritedoc
运行：需要加载libwritedoc.so
    ./example
结果：
在当前目录下生成mongodb文件和ct文件，其中mongodb存储GatherDoc的快照,ct存储GatherDoc的JSON表达式


