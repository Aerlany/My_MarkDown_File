# Double和double 区别

**1、Double是java定义的类，而double是预定义数据类型（8种中的一种）**

**2、Double就好比是对double类型的封装，内置很多方法可以实现String到double的转换，以及获取各种double类型的属性值（MAX_VALUE、SIZE等等）**

基于上述两点，如果你在普通的定义一个[浮点](https://so.csdn.net/so/search?q=浮点&spm=1001.2101.3001.7020)类型的数据，两者都可以，但是Double是类所以其对象是可以为NULL的，而double定义的不能为NULL，如果你要将一些数字字符串，那么就应该使用Double类型了，其内部帮你实现了强转。