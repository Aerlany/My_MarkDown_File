
<center><h1>C# 学习笔记</h1></center>

## 一、程序结构

C# 中的组织结构的关键概念是**程序 (program)**、**命名空间 (namespace)**、类型 (type)、**成员 (member)** 和**程序集 (assembly)**。C# 程序由一个或多个源文件组成。

程序中声明类型，类型包含成员，并且可按命名空间进行组织。类和接口就是类型的示例。字段 (field)、方法、属性和事件是成员的示例。在编译 C# 程序时，它们被物理地打包为程序集。程序集通常具有文件扩展名 .exe 或 .dll，具体取决于它们是实现应用程序 (application) 还是实现库 (library)。

```c#
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleHelloWord.lenarnCode
{
    public class Stack
    {
        //栈顶指针
        Entry top;
        public void Push(object data)
        {
            //将新对象的Next指向top，新对象就变为top
            top = new Entry(top, data);
        }
        public object Pop()
        {
            if (top == null) throw new InvalidOperationException();
            object result = top.data;
            top = top.next;
            return result;
        }
        class Entry
        {
            public Entry next;
            public object data;
            public Entry(Entry next, object data)
            {
                this.next = next;
                this.data = data;
            }
        }

    }
}

```



