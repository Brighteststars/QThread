# QThread
## 多线程:生产者,消费者问题实现
### 解决项目中,20万日志写入数据库,协调文件 读取-写入
unique<mutex> lock 用类管理锁 局部变量析构时,调用lock.unlock();  
condition-variable 信号量 用于解决死锁
