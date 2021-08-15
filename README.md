# HTTPserver
缺个项目

第一次写Socket，照着别人的写成精神分裂。头文件凑合着看，凑合着改，传上去才改成hpp的。 

git443 所以代码~~可能~~大概缺胳膊少腿。
## 参考资料
一直照着写的↓
* CSDN云英[https://blog.csdn.net/u014530704/article/details/78920612?spm=1001.2014.3001.5501]  
* 以及百度上的静态html页面
------------------
## 已实现
* 基本的通信
* 静态Get、一半动态
* http报文解析（状态机需要化简，可能根本不对）
## 待实现
* cgi
* POST等方法
* 多线程
* 日志
* 不屎的代码（重新写）
* 等功能
----------------------
## 编译
```
$ cd /build
$ cmake ..
$ make
```
## 运行
WSL1的UBUNTU上能运行
```
$ cd {PROJECT_SOURCE_DIR}/bin
$ ./server
```
