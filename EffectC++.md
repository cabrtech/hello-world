Effective C++

copy 构造函数定义了一个类如何pass by value

### 1.  构造和析构中不要使用虚函数，调用的函数也不要使用虚函数。	

- reson 

  ABBA，B构造时调用A构造，此时对象是A，

- 改进方式

  将 此函数 改为 non-virtual，传递参数调用

  ```c++
  class Transaction{
      public:
      explicit Transaction(const std::string& logInfo);
      void logTransaction(const std::string& logInfo) const; // 此函数修改为 non-virtual 函数
  };
  
  Transaction::Transaction(const std::string& logInfo)
  {
      logTransaction(logInfo);
  }
  
  class BuyTransaction: public Transaction
  {
      public:
      BuyTransaction(parameters) : Transaction(createLogString(parameters))
      { ... }
      
      private:
      static std::string createlogString(parameters);
  }
  ```

   

### 2. 自写的赋值函数，需要检查是否赋值自身

### 3. 自写的赋值函数

 1. 赋值所有成员变量

 2. 赋值基类

    ```c++
    DerivedClass& DerivedClass:: operator=(const DerivedClass& rhs)
    {
        BaseClass:: operator=(rhs);
        return *this;
    }
    ```

3. 可以写一个init成员函数，同时使用在copy-assingment和copy构造函数

### 4. 析构要避免抛出异常，避免不正常的析构。

​	最好在析构中catch捕获异常

