搜集c++项目工程用到的工具

静态代码检测工具
https://sourceforge.net/projects/cppcheck/files/cppcheck/
https://blog.csdn.net/liang19890820/article/details/52778149
使能检查规则：
默认：--enable=error
--enable=all 
--enable=unusedFuntion path
--enable=style
规则定义：
error：出现的错误
warning：为了预防bug防御性编程建议信息
style：编码格式问题（没有使用的函数、多余的代码等）
portablity：移植性警告。该部分如果移植到其他平台上，可能出现兼容性问题
performance：建议优化该部分代码的性能
information：一些有趣的信息，可以忽略不看的。

风格检测工具cpplint
https://github.com/google/styleguide/blob/gh-pages/cpplint/cpplint.py
clang-format 风格格式化工具

内存泄漏越界检测valgrind
https://blog.csdn.net/dodonei/article/details/79806931
https://blog.csdn.net/luxiuwen/article/details/7659128
https://blog.csdn.net/mishifangxiangdefeng/article/details/17657293

性能分析工具
https://blog.51cto.com/xiamachao/1857696


