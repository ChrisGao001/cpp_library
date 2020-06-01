# 使用方法
1. 引用class_registy.h
2. 在基类中定义RegistyHelper和创建宏
3. 在继承类source文件中注册类

备注：
使用__COUNTER__来去重
宏__COUNTER__实质上是一个int，并且是具体的数，初值是0，每预编译一次其值自己加1
