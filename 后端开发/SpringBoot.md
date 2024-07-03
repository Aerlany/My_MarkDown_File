# SpringBoot从入门到放弃

## 热部署

​	SpringBoot为我们提供了一个方便于开发测试的工具`dev-tools`。使用后实现热部署的效果。当我们运行程序后对程序进行了修改，程序就会自动重启。

​	原理就是使用了两个`classLoder`，一个负责加载那些不会改变的类（第三方`Jar`

包），另一个名叫`Restart ClassLoder`负责加载会改变的类，当有代码变更时，将`Restart classLoder`丢弃，重新创建，所以实现了较快的重启时间。

