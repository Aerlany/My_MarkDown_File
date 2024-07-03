
<center><h1>C# 学习笔记</h1></center>

## 一、程序结构

C# 中的组织结构的关键概念是**程序 (program)**、**命名空间 (namespace)**、类型 (type)、**成员 (member)** 和**程序集 (assembly)**。C# 程序由一个或多个源文件组成。

程序中声明类型，类型包含成员，并且可按命名空间进行组织。类和接口就是类型的示例。字段 (field)、方法、属性和事件是成员的示例。在编译 C# 程序时，它们被物理地打包为程序集。程序集通常具有文件扩展名 .exe 或 .dll，具体取决于它们是实现应用程序 (application) 还是实现库 (library)。

```c#
using System;
namespace StudyCode.Program
{
        
    public class Stack
    {
        //相当于栈顶指针
        Entry top;
        public void Push(Object data) {
            //赋值，将top指针置为一个新的Entry，新的Entry的Next指向原来的top
            top = new Entry(top, data);     
        }

        public object Pop()
        {
            if (top == null) throw new InvalidOperationException();
            object result = top.data;
            top = top.next;
            return result;
        }

    }

    class Entry
    {
        public Entry next;
        public Object data;
        public Entry(Entry entry,Object data)
        {
            this.next = entry;
            this.data = data;
        }
    }
}
```

```sh
# 编译成库文件
csc /t:library acme.cs
```



```c#
using StudyCode.Program;
using System;
class Test
{
    static void Main()
    {
        Stack s = new Stack();
        s.Push(1);
        s.Push(2);
        s.Push(3);

        Console.WriteLine(s.Pop());
        Console.WriteLine(s.Pop());
        Console.WriteLine(s.Pop());

    }
}
```

```sh
# 编译时引用程序集
 csc /r:Program.dll Test.cs
 
 ./Test.exe
```



## 二、类型和变量

C# 中的类型有两种：**值类型 (value type)** 和**引用类型 (reference type)**。

值类型的变量直接包含它们的数据，而引用类型的变量存储对它们的数据的引用，后者称为对象。

对于引用类型，两个变量可能引用同一个对象，因此对一个变量的操作可能影响另一个变量所引用的对象。对于值类型，每个变量都有它们自己的数据副本（除 ref 和 out 参数变量外），因此对一个变量的操作不可能影响另一个变量。

C# 的**值类型**进一步划分为简单类型 (simple type)、枚举类型 (enum type)、结构类型 (struct type) 和可以为 null 的类型 (nullable type)，C# 的**引用类型**进一步划分为类类型 (class type)、接口类型 (interfacetype)、数组类型 (array type) 和委托类型 (delegate type)。



```C#
public static bool Getdevicestate8(byte data2, int postion) => 0 != (data2 & (byte)(1 << postion));
```

