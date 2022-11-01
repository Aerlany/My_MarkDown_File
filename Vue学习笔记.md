# Vue学习笔记

## 1.创建Vue实例

```html
<script src="../js/vue.js"></script>
<script type="text/javascript">
    var vm = new Vue({
        //第一种挂载形式
        el:"#app",
        data() {
            return {
                message: "World"
            }
        },
    })

	//第二种挂载形式
    vm.$mount('#app');

    console.log(vm);

</script>
```

## 2.了解MVVM模型

```text
M : modle

V  : View

VM : View Modle 

//每一个Vue实例都是一个VM
```

## 3.事件处理

### *vue中v-on支持的事件总结 

```text
资源事件
error	资源加载失败时。
abort	正在加载资源已经被中止时。
load	资源及其相关资源已完成加载。
beforeunload	window，document 及其资源即将被卸载。
unload	文档或一个依赖资源正在被卸载

网络事件
online	浏览器已获得网络访问
offline	浏览器已失去网络访问

焦点事件
focus	元素获得焦点（不会冒泡）
blur	元素失去焦点（不会冒泡）

键盘事件
keydown	按下任意按键。
keypress	除 Shift、Fn、CapsLock 外的任意键被按住（连续触发）
keyup	释放任意按键

鼠标事件
auxclick	A pointing device button (ANY non-primary button) has been pressed and released on an element.
click	在元素上按下并释放任意鼠标按键。
contextmenu	右键点击（在右键菜单显示前触发）。
dblclick	在元素上双击鼠标按钮。
mousedown	在元素上按下任意鼠标按钮。
mouseenter	指针移到有事件监听的元素内。
mouseleave	指针移出元素范围外（不冒泡）。
mousemove	指针在元素内移动时持续触发。
mouseover	指针移到有事件监听的元素或者它的子元素内。
mouseout	指针移出元素，或者移到它的子元素上。
mouseup	在元素上释放任意鼠标按键。
pointerlockchange	鼠标被锁定或者解除锁定发生时。
pointerlockerror	可能因为一些技术的原因鼠标锁定被禁止时。
select	有文本被选中。
wheel	滚轮向任意方向滚动。
```

### （1）基本事件处理

```html
//Vue中的@cilck 点击事件可以将本次事件作为参数传递到方法中
//并且可以通过event.target 获取当前操作的DOM元素

<body>
    <div id="app">
        <h1>{{message}}</h1>
        <button @click="showTab1">点击1</button>
        <button @click="showTab2(22,$event)">点击2</button>
    </div>

    <script src="../../js/vue.js"></script>
    <script type="text/javascript">
        var app = new Vue({
            el: "#app",
            data() {
                return {
                    message: "Hello"
                }
            },
            methods: {
                showTab1(event) {
                    console.log(event.target.innerText);
                    event.target.innerText = "Hello"
                },
                showTab2(num,event) {
                    console.log(num,event);
                    console.log(event.target.innerText);
                    event.target.innerText = "Hello"
                },

            },
        })
        console.log();
    </script>
</body>
```

### （2）键盘事件监听

```html
<!-- 
    回车: enter
    删除：delete
    退出：esc
    换行：tab
    上：up
    下：down
    左：left
    右：right
 -->

<body>
    
    <div id="app">
        <input type="text" placeholder="请输入" @keyup.enter="show"></input>
    </div>


    <script src="../../js/vue.js"></script>
    <script>
        var app = new Vue({
            el:"#app",
            methods: {
                show(e){
                    console.log(e.target.value);
                }
            },
        })
    </script>
</body>
```

### （3）事件修饰符

```html
<!-- 形如@click.prevent的prevent关键字就是修饰符
    相当于javascript中的preventdefine -->
<!-- 
        Vue中的修饰符：
        prevent：（阻止默认事件）
        stop：（阻止事件冒泡）
        once：（事件只触发一次）
		capture
		self
		passive
-->

<body>
    <div id="app">
        <h1>{{message}}</h1>
        <a href="www.baidu.com" @click="showTab1">点击1</a>
        <a href="#" @click.once="showTab1">点击1</a>
    </div>

    <script src="../../js/vue.js"></script>
    <script type="text/javascript">
        var app = new Vue({
            el: "#app",
            data() {
                return {
                    message: "Hello"
                }
            },
            methods: {
                showTab1(event) {
                    console.log(event.target.innerText);
                    event.target.innerText = "Hello"
                    alert("Hello");
                },

            },
        })
    </script>
</body>
```

## 4.计算属性（computed）

```html
<body>
    <div id="app">
        <input type="text" v-model="firstName">
        <input type="text" v-model="lastName">
        {{fullName}}
    </div>


    <script src="../../js/vue.js"></script>
    <script>
        var app = new Vue({
            el:"#app",
            data() {
                return {
                    firstName:"张",
                    lastName:"三"
                }
            },
            
            //computed函数运行在页面加载时
            //其中的属性类似data中的数据但是如果需要修改或访问则应该给该方法添加get()和set()
            computed:{
                fullName:{
                    get(){
                        return this.firstName + this.lastName
                    }
                }
            }
        })
    </script>
</body>
```

## 5.事件监听（watch）

### （1）事件监听

```html
<body>
    <div id="app">
        <h1>今天天气很{{info}}</h1>
        <button @click="show()">点击</button>
    </div>


    <script src="../../js/vue.js"></script>
    <script>
        var app = new Vue({
            el: "#app",
            data() {
                return {
                    isHot: true
                }
            },
            methods: {
                show() {
                    this.isHot = !this.isHot
                }
            },

            //计算
            computed: {
                info: {
                    get() {
                        return this.isHot ? "炎热" : "凉爽"
                    }
                }
            },

            watch:{
                info:{
                    //初始化时就让handler调用
                    immediate:true,
                    //handler当监视值改变时调用
                    handler(newValue,oldValue){
                        console.log(newValue, oldValue);
                    }
                }
                //写法二
                //info(val){
         			//console.log(val);
                //}
            }

        })

		//第二种写法
        // app.$watch("isHot", {
        //     handler(newValue, oldValue) {
        //         //newValue 和 oldValue 支持返回新旧数据
        //         console.log(newValue, oldValue);
        //     }
        // })

    </script>
</body>
```

### （2）深度监听

```html
<body>
    <div id="app">
        <h1>{{numbers.a}}</h1>
        <button @click="changeNuma()">点击a+1</button>
 		<button @click="changeNumb()">点击b+1</button>
    </div>
    <script src="../../js/vue.js"></script>
    <script>
        var app = new Vue({
            el: "#app",
            data() {
                return {
                    numbers:{
                        a:"1",
                        b:"1"
                    }
                }
            },
            methods: {
                changeNum(a){
                    this.numbers.a ++;
                },
                changeNumb() {
                    this.numbers.b++;
                }
            },
            watch: {
                
                //监听的对象原本就是String
                //但是简单的支持简写
                
                //监听多结构中的某个数据变化
                "numbers.a":{
                    handler(){
                        console.log("a改变了");
                    }
                },
            	
                //监听多结构中的所有数据变化
                numbers: {
                    //开启深度监视
                    deep: true,
                    handler() {
                        console.log("numbers改变了");
                    }
                }

            }
        })

    </script>
</body>
```

### （3）简写形式

```javascript
app.$watch("isHot", {
       handler(newValue, oldValue) {
       //newValue 和 oldValue 支持返回新旧数据
       console.log(newValue, oldValue);
       }
})
```

## 6.watch 比较 computed

 （1）watch函数用于监听data中定义的数据的变化且watch函数中可以调用异步函数（setTimeout）

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <div id="app">
        <p><input type="text" v-model="firstName"></p>
        <p></input><input type="text" v-model="lastName"></p>
        <P>{{fullName}}</P>
    </div>
    <script src="../../js/vue.js"></script>
    <script>
        var app = new Vue({
            el: "#app",
            data() {
                return {
                    firstName: "张",
                    lastName: "三",
                    fullName: ""
                }
            },
            mounted() {
                this.fullName = this.firstName + this.lastName
            },

            watch: {
                firstName(newValue) {
                    setTimeout(() => {
                        this.fullName = newValue + this.lastName
                    }, 2000);
                },
                lastName(newValue) {
                    this.fullName = this.firstName + newValue
                }
            }
        })
    </script>
</body>

</html>
```

（2）computed使用data中的数据进行计算后支持插值访问 但是computed不支持使用异步函数（因为其每一个计算属性都需要返回值）

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>

    <div id="app">
        <p><input type="text" v-model="firstName"></p>
        <p></input><input type="text" v-model="lastName"></p>
        <P>{{fullName}}</P>

    </div>


    <script src="../../js/vue.js"></script>
    <script>
        var app = new Vue({
            el: "#app",
            data() {
                return {
                    firstName: "张",
                    lastName: "三",
                }
            },
            computed: {
                fullName() {
                    return this.firstName + this.lastName
                }
            },
        })

    </script>
</body>

</html>
```

## 7.class样式绑定

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>

    <style>
        .basic{
            padding: 100px;
        }

        .one {
            background-color: rgb(165, 0, 0);
        }

        .two {
            border-radius: 20%;
        }

        .three{
            text-align: center;
        }
    </style>
</head>

<body>
    <div id="app">

        <!-- 方法一 使用字符串 -->
        <div class="basic one" :class="change" @click="button">
            <p>HelloWorld</p>
        </div>

        <!-- 方法二 数组 -->
        <div class="basic" :class="arr" @click="button2">
            <p>HelloWorld</p>
        </div>

        <!-- 方法三 对象 -->
        <div class="basic" :class="obj" @click="button3">
            <p>HelloWorld</p>
        </div>
    </div>


    <script src="../../js/vue.js"></script>
    <script>
        var vm = new Vue({
            el: "#app",
            data() {
                return {
                    change: "",
                    arr:["three","two", "one"],
                    obj:{
                        one:true,
                        three:false
                    }
                }
            },
            methods: {
                button() {
                    this.change = "two"
                },
                button2(){
                    //shift函数用于移除数组顶元素
                    this.arr.shift();
                },
                button3() {
                    //shift函数用于移除数组顶元素
                    this.obj.one = !this.obj.one 
                    this.obj.three = !this.obj.three 
                },

            },
        })
    </script>
</body>

</html>
```

## 8.条件渲染

条件渲染（当满足特定条件时显示部分代码）

（1）v-show

底层是控制display属性进行渲染

（2）v-if

原理：当boolean值为false时直接不加载HTML代码 

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <div id="app">
        <p>{{message}}</p>
        <button @click="button">点击+1</button>

        <p v-show="message == 1">打撒比阿达</p>
        <p v-show="message == 2">撒乏味的大赛</p>
        <p v-show="message == 3">啊发达万恶</p>

        <p v-if="message == 1">打撒比阿达</p>
        <p v-if="message == 2">撒乏味的大赛</p>
        <p v-if="message == 3">啊发达万恶</p>
    </div>


    <script src="../../js/vue.js"></script>
    <script>
        var vm = new Vue({
            el:"#app",
            data() {
                return {
                    message:0,
                }
            },
            methods: {
                button(){
                    this.message = this.message + 1;
                }
            },
        })
    </script>
</body>
</html>
```

## 9.列表渲染

列表渲染

（1）v-for 指令

​	1.用于展示列表数据

​	2.语法：v-for="(item,index) in Array" :key="index"

​	3.可遍历：数组、对象、字符串、指定次数

:key是用于对每一个遍历出来的结构进行单独的数据绑定

:key最好使用惟一的值 一般为数组索引值index 或为 id值 

（2）v-for中 :Key属性的内部原理（面试常考）

 	1.虚拟DOM中key的作用：

​			key是虚拟DOM对象的标识，当状态中的数据发生变化时，Vue会根据<新数据>生成<新的虚拟DOM>

​			随后Vue进行《新旧DOM的差异比较》，比较规则如下：



​	2.比对规则：

​		（1）旧虚拟DOM中找到了与新虚拟DOM相同的key：

​				若虚拟DOM中的数据内容没变，直接使用原来的真实DOM；

​				若虚拟DOM中的数据内容变了，则生成新的真实DOM替换掉页面中的真实DOM

​		（2）旧虚拟DOM中未找到了与新虚拟DOM相同的key：

​				创建新的真实DOM，渲染到页面上



​	3.使用index（遍历数组索引值）可能引发的问题：

​		（1）若对数据进行：逆序添加，逆序删除等破坏数组顺序的操作：

​				会产生没必要的真实DOM更新 ==》界面效果没问题，但是效率低

​		（2）遍历的结构中如果包含	input输入框之类的DOM

​				会产生DOM对应错误 ==》界面有问题



​	4.一般使用遍历数组中的唯一数值来作为key值	如id,	手机号，	学号等；

​		如果数据不存在逆序添加，逆序删除等破坏数组顺序的操作	使用index作为key也可以；

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <div id="root">
        <div>
            <!-- 数组遍历 -->
            <ul>
                <!-- :key是用于对每一个遍历出来的结构进行单独的数据绑定 -->
                <!-- ：key最好使用惟一的值 一般为数组索引值index 或为 id值 -->
                <li v-for="(item,index) in Data" ::key="item.id">
                    第{{index + 1}}个--{{item.name}}
                </li>
            </ul>

            <!-- 对象遍历 -->
            <ul>
                <!-- 两个参数为值和键 -->
                <li v-for="(value,key) in obj">
                    {{key}}=={{value}}
                </li>
            </ul>
        </div>
    </div>
    <script src="../../js/vue.js"></script>
    <script>
        var vm = new Vue({
            el: "#root",
            data() {
                return {
                    message: 0,
                    Data: [{
                        id: 1,
                        name: "张三"
                    },
                    {
                        id: 2,
                        name: "张三"
                    }, {
                        id: 3,
                        name: "张三"
                    }]
                    ,
                    obj: {
                        name: "张三",
                        age: 190,
                        sex: "man"
                    }
                }
            },
            methods: {

            },
        })
    </script>
</body>

</html>
```

## 10.列表过滤

列表过滤使用Js原生数组方法filter对目标数组进行过滤操作

**参数是一个函数，所有数组成员依次执行该函数，返回结果为`true`的成员组成一个新数组返回。该方法不会改变原数组。**

该方法原理是对整个数组进行遍历
i为数组中的每一个元素
return 值为-1 则将该数据过滤掉

```

Arrary.filter((i) => {
      return i.name.indexOf(value) !== -1;
})
```

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <div id="root">
        <div>
            <input v-model="keyword"></input>
            <!-- 数组 -->
            <ul>
                <!-- :key是用于对每一个遍历出来的结构进行单独的数据绑定 -->
                <!-- ：key最好使用惟一的值 一般为数组索引值index 或为 id值 -->
                <li v-for="(item,index) in filmessage" ::key="item.id">
                    第{{index + 1}}个--{{item.name}}
                </li>
            </ul>
        </div>
    </div>
    <script src="../../js/vue.js"></script>
    <script>
        var vm = new
            Vue({
                el: "#root",
                data() {
                    return {
                        keyword: "",
                        message: [{
                            id: "1",
                            name: "张三"
                        },
                        {
                            id: "2",
                            name: "李四"
                        }, {
                            id: "3",
                            name: "王武"
                        }]
                        ,

                        filmessage: []
                    }
                },
                mounted() {
                    this.filmessage = this.message;

                },
                watch: {
                    keyword(value) {
                        this.filmessage = this.message.filter((i) => {
                            return i.name.indexOf(value) !== -1;
                        });

                    }
                }
            })
    </script>
</body>

</html>
```

## 11.列表排序

sort方法对数组成员进行排序，默认是按照字典顺序排序。排序后，原数组将被改变

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <div id="root">
        <div>
            <button @click="sortType = 1">升序</button>
            <button @click="sortType = 2">降序</button>
            <button @click="sortType = 0">原序</button>
            <input v-model="keyword"></input>
            <!-- 数组 -->
            <ul>
                <!-- :key是用于对每一个遍历出来的结构进行单独的数据绑定 -->
                <!-- ：key最好使用惟一的值 一般为数组索引值index 或为 id值 -->
                <li v-for="(item,index) in filmessage" ::key="item.id">
                    第{{index + 1}}个--{{item.name}}--{{item.id}}
                </li>
            </ul>
        </div>
    </div>
    <script src="../../js/vue.js"></script>
    <script>
        var vm = new
            Vue({
                el: "#root",
                data() {
                    return {
                        keyword: "",
                        message: [{
                            id: "1",
                            name: "张三"
                        },
                        {
                            id: "3",
                            name: "王武"
                        }, {
                            id: "2",
                            name: "李四"
                        }, {
                            id: "4",
                            name: "阿三打"
                        }, {
                            id: "6",
                            name: "阿三打树的"
                        }, {
                            id: "5",
                            name: "阿达屎的地方的"
                        }, {
                            id: "7",
                            name: "反倒是方式"
                        }, {
                            id: "8",
                            name: "发射的发送"
                        }],
                        sortType: 0,
                        filmessage: []
                    }
                },
                mounted() {
                    this.filmessage = this.message;

                },
                watch: {
                    keyword: {
                        immediate: true,
                        handler(value) {
                            const arr = this.filmessage = this.message.filter((i) => {
                                return i.id >= value;
                            });

                            if (this.sortType) {
                                arr.sort((p1, p2) => {
                                    return this.sortType === 1 ? p1.id - p2.id : p2.id - p1.id
                                })
                            }
                        }
                    },

                    // keyword(value) {
                    //     const arr = this.filmessage = this.message.filter((i) => {
                    //         return i.id >= value;
                    //     });

                    //     if (this.sortType) {
                    //         arr.sort((p1, p2) => {
                    //             return this.sortType === 1 ? p1.id - p2.id : p2.id - p1.id
                    //         })
                    //     }

                    //     return arr

                    // }
                }

            })
    </script>
</body>

</html>
```

## 12.Vue检测数据改变的原理 $set()

数据劫持 或 数据代理

原理方法			ObjectdefineProperty()

1.vue会监视data中所有层级的数据

2.如何监测对象中的数据？

​		通过setter实现监视，且要在new Vue时就传入要检测的数据。

​		（1）对象中后追加的属性，Vue默认不做响应式处理

​		（2）如需给后添加的的属性添加响应式，需要使用如下API

​				<1>	Vue.set(target,propertyName/index,value)

​				<2> 	Vue.$set(target,propertyName/index,value)

3.如何检测数组中的数据？

​		通过包裹数组更新元素的方法实现，本质为：

​		（1）调用原生对应的方法对数组进行更新

​		（2）重新更新模板，进而更新页面

4.在Vue中修改数组的某个元素要使用如下方法：

​		（1）API:	push()	pop()	shift()	unshift()	splice()	sort()	reverse()

​		（2）Vue.set() 或 Vue.$set



注意：Vue.set() 和 Vue.$set不能给VM跟数据对象修改属性

```

```

## 13.内置指令

（1）v-text	（用于往所在标签插入文本）注：会替换原有的标签文本信息

（2）v-html	(向指定节点中渲染包含HTML结构的内容)

（3）v-cloak 

（4）v-once	（所在节点只渲染一次）

（5）v-pre	（跳过所在节点的编译过程	提高效率）

## 14.自定义指令

## 15.生命周期函数

### （1）mounted()	

Vue完成模板解析并将真实DOM元素放入页面后调用mounted

### （2）beforeDestroy()

销毁Vm之前	清除定时器、解除自定义事件等

```HTML
//一个动态变化的字体
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <div id="app">
        <h2 :style="{opacity}">{{message}}</h2>
    </div>
    <script src="../../js/vue.js"></script>
    <script>
        var vm = new Vue({
            el: "#app",
            data() {
                return {
                    message: "Hello World",
                    opacity: 1
                }
            },
            methods: {

            },
        })

        //定时器
        setInterval(() => {
            vm.opacity -= 0.01
            if (vm.opacity <= 0) {
                vm.opacity = 1;
            }
        }, 16);
    </script>
</body>

</html>
```



# vue脚手架基本操作

## 1.Project setup

```
npm install
```

Compiles and hot-reloads for development

```
npm run serve
```

Compiles and minifies for production

```
npm run build
```

Lints and fixes files

```
npm run lint
```

Customize configuration

See [Configuration Reference](https://cli.vuejs.org/config/).

## 2.Render函数

```
render函数用于runtime版本下的Vue

因为缺少tempate模板解析器所以

不可以使用component来引入App.vue
```

## 3.Vue不同版本

```
关于不同版本的Vue

1.Vue.js 与 Vue.runtime.js 相比后者没有模板解析器只含有核心功能   

2.因为vue.runtime.js没有模板解析器所以不能使用template配置项，需要使用render函数接收createElement函数来实现组件的注册
```

## 4.ref属性

```
1.用于给元素或子组件注册引用信息（id的替代品）
2.应用在HTML元素上获取的是真实DOM元素，应用在组件标签上获取组件的事例对象（VueComponent）
3.使用方式：
	打标签：<h1 ref="XXX">...</h1> 或 <school ref="XXX">...</School>
	获取：this.$refs.XXX
```

## 5._props配置

让组件接收外部传进来的数据（通常情况下是父传子）

（1）传递数据

```html
<Demo name="Xxx"></Demo>
```

（2）接收数据

```html
//只接收
props:["xxx","xxx"]
```

```vue
//限制类型、限制必要性、限制默认值
props: {
    myname: {
       type: String,
       require: true
    },
    other: {
       typeof: String,
       default: "无"
    }
```

注：props属性是只读的，如果要进行props的修改会出现一些不必要的错误，如若需要修改则需要新声明一个变量来存储和展示，

然后对新变量进行修改操作。

## 6.mixin混入

可以将多个组件共用的配置提取成为一个混入对象

（1）混入的创建：

创建文件	mixin.js

```javascript
export const mixin = {
    mounted() {
        //如果引入的.vue文件中mounted存在则两个mounted中的函数都存在
        //且mixin文件中的函数先调用
        console.log("Hello");
    },
    data() {
        return {
            //如果引入的.vue文件中data数据存在则则以.vue文件中的数据为准
            name: "张三"
        }
    },
}
```

（2）混入的使用

```html
//局部混入
//在.vue文件中
<script>
import { mixin } from "../mixin";

export default {
    name: 'School',
    data() {
        return {
            school: {
                name: "希腊大赛",
                address: "大东村"
            }
        }
    },
    //该配置项为一个数组
    mixins: [mixin],
}
</script>
```

```javascript
//全局混入
//在main.js中

import { mixin } from "./mixin";

vue.mixin(mixin);
```

## 7.vue插件

用于增强vue

本质：包含install方法的一个对象。install方法的第一个参数是Vue，支持多个参数

```javascript
//创建插件
export default {
    install(Vue) {
        //全局过滤器
        Vue.filter("mySlice", function (value) {
            return value.slice(0, 4)
        })

        //全局指令
        //定义混入
        Vue.mixins({
            mounted() {
                console.log("Hello");
            },
        })

        //给Vue原型添加一个方法
        Vue.prototype.hello = () => {
            alert("Hello");
        }
    }
}
```

```javascript
//使用
//在mian.js中

import { plugins } from "./plugin";

Vue.use(plugins);
```

## 8.scoped样式

让style样式局部生效

```html
<style scoped>
	.class{
        backgroundcolor: orange
    }
</style>
```

## 9.组件的自定义事件

（1）组件间的通行方式，适用于：子组件 ==> 父组件	的参数传递

（2）子组件想要传递参数给父组件，要在父组件中给子组件标签绑定自定义事件（即事件的回调在父组件中）

（3）用法：

```vue
<!-- 通过父组件给子组件绑定函数类型的自定义事件实现：子给父传递数据 （写法一 v-on）-->
<Student @getStudentName="getStudentName"></Student>
<Student @getStudentName.once="getStudentName"></Student>
<Student v-on:getStudentName="getStudentName"></Student>
```

```vue
<template>
  <div id="app">
    <!-- 通过父组件给子组件绑定函数类型的自定义事件实现：子给父传递数据 （写法二 ref）-->
    <Student ref="student"></Student>
  </div>
</template>

<script>
import Student from './components/Student'

export default {
  name: 'App',
  components: {
    Student,
  },
  methods: {
    getStudentName(e) {
      console.log(e);
    },
  },
  mounted() {
    this.$refs.student.$on("getStudentName", this.getStudentName)
    this.$refs.student.$once("getStudentName", this.getStudentName) //触发一次
  },
}
</script>

```

注：若想要事件只触发一次可以用	*once* 修饰	或 	*$once*方法

（4）触发自定义事件：

```
this.$emit("自定义事件名",参数)
```

（5）解绑自定义事件

```
this.$off("自定义事件名")
```

（6）组件上使用的事件修饰符Vue默认为自定义事件，如果需要使用原生DOM事件，需要使用	*.native*	修饰符

```vue
<school @click.native="xxx"></school>
```

（7）通过	*`this.$refs.xxx.$on("自定义事件名",回调函数)`*	绑定自定义事件时，回调函数要求使用`箭头函数` 或 `配置在method`中，否则函数体中的this指向会存在问题

## 10.全局事件总线 （GlobalEventBus）

（1）组件间的通信方式，适用于任意组件间的通信

（2）注册全局事件总线

注：一个重要的内置关系

<img src="/home/user/Documents/Vue_study/03_进阶/2022-08-07 20-14-27 的屏幕截图.png" alt="2022-08-07 20-14-27 的屏幕截图" style="zoom: 200%;" />

```javascript
//在main.js
new Vue(){
    beforeCreate(){
        Vue.prototype.$bus = this; //安装全局事件总线，$bus相当于vm
    }
}
```

（3）使用事件总线

```vue
//接收数据
<script>
methods(){
	Demo(data){
		//回调函数
	}
},
mounted(){
    this.$bus.$on("自定义事件名",this.Demo());
}
</script>
```

```vue
//传输数据
//调用自定义事件
<script>
	this.$bus.$emit("自定义事件名",参数)
</script>
```

（4）为了防止总线占用，最好在beforeDestroy() 中用 *$off* 解绑改组件用到的自定义事件

## 11.消息订阅与发布（pubsub）

publish and subscribe

（1）一种组件间的通信方式，适用于任意组件之间通信

（2）第三方库

```js
//安装
npm -i pubsub-js
```

```js
//引入
import pubsub from 'pubsub-js'
```

（3）接收数据

```js
mounted(){
	this.pid = pubsub.subscribe("xxx",()=>{
		//回调
	})
}
```

（4）传输数据

```js
pubsub.publish("xxx",data)
```

（5）取消订阅

```js
pubsub.unsubscribe(this.pid)
```

## 12.nextTick()

（1）用法

```
this.nextTick(()=>{
	//回调
})
```

（2）作用：在下一次DOM更新结束后执行其指定的回调函数

（3）使用时机：当数据改变后要立即进行界面改变的操作时，可以使用setTimeout()延时器 也可以使用nextTick

## 13.Vue动画效果

### （1）基本使用

<transition></transition>

关键帧 keyframes

```vue
<template>
    <div>
        <button @click="isShow = !isShow">点击</button>
        <transition name="biaoti" :appear="true">
            <h2 v-show="isShow">Hello</h2>
        </transition>
    </div>
</template>

<script>
export default {
    name: "MyHeader",
    data() {
        return {
            msg: "",
            isShow: true,
        }
    },
    methods: {
        show() {

        }
    },
}
</script>

<style scoped>
h2 {
    background-color: rgb(245, 26, 26);
}

.biaoti-enter-active {
    animation: showtrasform 1s;
}

.biaoti-leave-active {
    animation: showtrasform 1s reverse;
}

@keyframes showtrasform {
    from {
        transform: translateX(-100%);
    }

    to {
        transform: translateX(0px);
    }
}
</style>
```

### （2）集成第三方库 （Animate.css）

```vue
<template>
    <div>
        <button @click="isShow = !isShow">点击</button>
        <transition 
           appear 
           name="animate__animated animate__bounce" 
           enter-active-class="animate__heartBeat"
           leave-active-class="animate__fadeOutDown"
        >
            <h2 v-show="isShow" style="text-align:center">Hello</h2>
        </transition>
    </div>
</template>

<script>
import 'animate.css';
    
export default {
    name: "MyHeader",
    data() {
        return {
            msg: "",
            isShow: true,
        }
    },
    methods: {
        show() {

        }
    },
}
</script>

<style scoped>
h2 {
    background-color: rgb(130, 50, 50);
}
</style>
```

## 14.Vue解决请求跨域

（1）方法一

​		在vue.config.js中添加如下配置

```js
  devServer: {
    proxy: 'http://localhost:4000'
  }
```

缺点：不能配置多个代理，当前端资源public中有，优先匹配前端资源



（2）方法二

```javascript
module.exports = {
  devServer: {
    proxy: {
        //代理一
      '/url1': {
        target: 'http://localhost:4000',
          //替换请求路径中的 /url1 为空字符串
          //再转发给目标服务器
        pathRewite:{'^/url1':''}
        ws: true,
        changeOrigin: true
      },
        //代理二
      '/url2': {
        target: 'http://localhost:5000',
        ws: true,
        changeOrigin: true
      },
      
    }
  }
}
```

## 15.Vue插槽

```vue
//App.vue
<template>
  <div class="root">
    <MyHeader title="美食">
      <ul>
        <li v-for="(item, index) in foods" :key="index">{{ item }}</li>
      </ul>
    </MyHeader>
    <MyHeader title="商品">
      <img src="https://tse3-mm.cn.bing.net/th/id/OIP-C.gEhrPM_QgCe_J7C4vHmMDQHaEK?pid=ImgDet&rs=1" />
    </MyHeader>
    <MyHeader title="锻炼"></MyHeader>
  </div>
</template>

<script>
import MyHeader from "./components/MyHeader.vue";
export default {
  name: "App",
  components: {
    MyHeader,
  },
  data() {
    return {
      foods: ['啊撒', 'as', 'aadasd'],
      goods: ['啊撒', '是大势的', 'aadasd'],
      excese: ['asdasdad', 'as', 'aadasd'],
    }
  },
}
</script>

<style scoped>
.root {
  display: flex;
  justify-content: space-around;
}
</style>
```

```vue
//MyHeader.vue
<template>
    <div>
        <h2>{{ title }}</h2>
        <slot></slot>
    </div>
</template>

<script>
import 'animate.css';
export default {
    name: "MyHeader",
    data() {
        return {
        }
    },
    props: ["title"],
    methods: {
    },
}
</script>

<style scoped>
div {

    background-color: rgb(203, 187, 187);
    width: 500px;
    height: 800px;
}

h2 {
    text-align: center;
    background-color: rgb(185, 218, 19);
}

img {
    width: 100%;
}
</style>
```

## 16.Vuex

### （1）Vuex 是什么？

Vuex 是一个专为 Vue.js 应用程序开发的**状态管理模式 + 库**。它采用集中式存储管理应用的所有组件的状态，并以相应的规则保证状态以一种可预测的方式发生变化。

![vuex](https://vuex.vuejs.org/vuex.png)

### （2）什么情况下我应该使用 Vuex？

Vuex 可以帮助我们管理共享状态，并附带了更多的概念和框架。（需要进行多组件之间通信）

### （3）Vuex环境搭建

1.创建store/index.js

```javascript
//Vuex核心搭建
//引入Vue核心
import Vue from 'vue'
//引入Vuex
import Vuex from 'vuex'
//注册
Vue.use(Vuex);

//用于响应组件中的动作
const actions = {}
//用于操作数据
const mutations = {}
//用于储存数据
const state = {}

export default new Vuex.Store({
    actions,
    mutations,
    state,
})
```

2.在main.js中传入store

```javascript
import Vue from 'vue'
import App from './App.vue'

import store from './store'

//关闭Vue生产提示
Vue.config.productionTip = false
new Vue({
  render: h => h(App),
  store,
  beforeCreate() {
    Vue.prototype.$bus = this;
  }
}).$mount('#app')
```

### （4）基本使用

```javascript
//Vuex核心搭建
//引入Vue核心
import Vue from 'vue'
//引入Vuex
import Vuex from 'vuex'
//注册
Vue.use(Vuex);

const actions = {
    //无业务逻辑的可以在$store中直接调用.commit
    // jia(context, value) {
    //     console.log("hello", context, value);
    //     context.commit("JIA", value);
    // },
    // jian(context, value) {
    //     console.log("hello", context, value);
    //     context.commit("JIAN", value);
    // },
    jianOdd(context, value) {
        console.log("hello", context, value);
        if (state.sum % 2) {
            context.commit("JIA", value);
        }
    },
    jianWait(context, value) {
        console.log("hello", context, value);
        setTimeout(() => {
            context.commit("JIA", value);
        }, 500);
    },
}
const mutations = {
    JIA(state, value) {
        console.log("hello", state, value);
        state.sum += value;
    },
    JIAN(state, value) {
        console.log("hello", state, value);
        state.sum -= value;
    },
}
const state = {
    sum: 0,
}

export default new Vuex.Store({
    actions,
    mutations,
    state,
})
```

读取state中的数据：this.$store.state.xxx

修改数据：this.$store.dispatch("action中的方法名",data) 或 this.$store.commit("mutation方法名",data)

### （5）getters 配置项

相当于Vue中的配置属性 

取值：this.$store.getters.bigSum

```javascript
//Vuex核心搭建
//引入Vue核心
import Vue from 'vue'
//引入Vuex
import Vuex from 'vuex'
//注册
Vue.use(Vuex);

const actions = {}
const mutations = {}
const state = {
    sum: 0,
}
const getters = {
    bigSum(state) {
        return state.sum * 10
    }
}
export default new Vuex.Store({
    actions,
    mutations,
    state,
    getters,
})
```

### （6）四个map方法的使用

#### 1.mapState	

用于映射state中的数据为计算属性

```javascript
computed:{
    //借助mapState方法生成计算属性
    ...mapState({ sum: "sum" }), //对象写法 可以改名字
    ...mapState(["sum"]), //数组写法 方法名必须一致
}
```

#### 2.mapState	

用于映射getters中的数据为计算属性

```javascript
computed:{
    //借助mapGetters方法生成计算属性
    ...mapGetters({ bigSum: "bigSum" }),
    ...mapGetters(["bigSum"]),
}
```

####  3.mapActions	

用于生成与actions对话的方法。即：this.$store.dispatch()

```javascript
methods:{
    ...mapActions({ increment: "jia",decrement:"jian" }),
    ...mapActions(["jia","jian"]),
}
```

####  4.mapMutations	

用于生成与mutations对话的方法。即：this.$store.commit()

```javascript
methods:{
    ...mapMutations({ increment: "JIA",decrement:"JIAN" }),
    ...mapMutations(["JIA","JIAN"]),
}
```

 注：借助mapActions and mapMutations方法生成的方法需要在具体使用时传递参数

### （7）Vuex 模块化 + namespace

1.使用模块化

```javascript
const CountAbout = {
    namespaced: true,
    actions: {
        jianOdd(context, value) {
            console.log("hello", context, value);
            if (context.state.sum % 2) {
                context.commit("JIA", value);
            }
        },
        jianWait(context, value) {
            console.log("hello", context, value);
            setTimeout(() => {
                context.commit("JIA", value);
            }, 500);
        },
    },
    mutations: {
        JIA(state, value) {
            state.sum += value;
        },
        JIAN(state, value) {
            console.log("hello", state, value);
            state.sum -= value;
        },
    },
    state: {
        sum: 0,
    },
    getters: {
        bigSum(state) {
            return state.sum * 10
        }
    },
}

export default new Vuex.Store({
    modules: {
        CountAbout,
    }
})
```

2.读取state数据

```javascript
//直接读取
this.$store.state.CountAbout.sum

//组件读取
...mapState("CountAbout",{sum:"sum"})
```

3.读取getters数据

```javascript
//直接读取
this.$store.getters["CountAbout/bigSum"]

//组件读取
...mapGetters("CountAbout",["bigSum"])
```

4.调用dispatch

```javascript
//直接读取
this.$store.dispatch("CountAbout/jianOdd",data)

//组件读取
...mapActions("CountAbout",{increment:"jianOdd",decrement:"jianWait"})
```

5.调用commit

```javascript
//直接读取
this.$store.commite("CountAbout/JIA",data)

//组件读取
...mapActions("CountAbout",{increment:"JIA",decrement:"JIAN"})
```

## 17.路由

#### （1）基本使用

​	（1）安装 

```shell
npm i vue-router@3
```

​	（2）应用插件

```javascript
import VueRouter from 'vue-router'
import router from './router'
Vue.use(VueRouter)


Vue.config.productionTip = false
const vm = new Vue({
  render: h => h(App),
  router, //
}).$mount('#app')

console.log(vm);
```

​	（3）配置环境

创建router/index.js

```js
//用于创建路由器
import VueRouter from "vue-router";

//引入组件
import About from '../components/About'
import Message from '../components/Message'

export default new VueRouter({
    routes: [
        {
            path: "/About",
            component: About
        },
        {
            path: "/Message",
            component: Message
        },
    ]
})
```

​	（4）切换路由

```html
<router-link to="/About" active-class="active">Goto About</router-link>
```

​	（5）指定位置展现

```html
<router-view></router-view>
```

注意：

路由组件存放在 pages 文件夹里

通过切换路由隐藏的组件默认被销毁了，需要时再去挂载

每个组件都有一个 $route 属性，其中存放着自己的路由信息

整个应用只有一个 $router



#### （2）嵌套路由

```js
//用于创建路由器
import VueRouter from "vue-router";
//引入组件
import About from '../pages/About'
import Home from '../pages/Home'
import Message from '../pages/Message'
export default new VueRouter({
    routes: [
        {
            path: "/About",
            component: About
        },
        {
            path: "/Home",
            component: Home,
            children: [
                {
                    path: 'Message', //  此处不能写/
                    component: Message
                }
            ]
        },
    ]
})
```

```html
//跳转时写完整路径
<router-link to="/Home/Message" active-class="active">Goto Message</router-link>
```

#### （3）路由传递参数

1.传递参数

```html
//字符串
<router-link :to="/home/message/detail?id=888&titli=你好"></router-link>
```

```html
//对象
<router-link :to="{
     path: '/home/message/detail',
     query: {
         id: 111,
         title: 'asa'
	}
}"></router-link>

```

2.接收参数

```
$route.query.id
$route.query.title
```

（4）路由命名

简化路由跳转

1.命名

```js
//用于创建路由器
import VueRouter from "vue-router";
//引入组件
import About from '../pages/About'
import Home from '../pages/Home'
import Message from '../pages/Message'
export default new VueRouter({
    routes: [
        {
            path: "/About",
            component: About
        },
        {
            path: "/Home",
            component: Home,
            children: [
                {
                    path: 'Message',
                    name: 'Message',//命名
                    component: Message
                }
            ]
        },
    ]
})
```

2.简化跳转

```
//前
<router-link :to="/home/message/detail?id=888&titli=你好"></router-link>

//后
<router-link :to="{name:'xxx'}"></router-link>
```



# 前端知识拓展

## 1.浏览器本地存储 WebStorage

（1）localStorage

注：两个方法都是window的API使用时直接调用

```javascript
//存储
localStorage.setItem("key","value");

//两个参数都是String类型
//若输入非String类型会进行强制类型转换 toString()
//所以在存储JSON或Object时需要使用 JSON.stringify()
```

```javascript
//读取
localStorage.getItem("key");

//使用存储时的Key进行读取
//在读取不存在的Key值时返回值为null
//在读取JSON或Object时需使用  JSON.parse() 解析字符串
```

```javascript
//删除
localStorage.removeItem("key");
```

```javascript
//清空
localStroage.clear();
```



（2）sessionStorage

注：该方法的方法名与localStorage一致使用方法一致

区别：

​	（1）sessionStorage储存的内容，会随着浏览器的窗口关闭而关闭。

​	（2）localStorage 储存的内容，需要手动清除。

## 2.Vue  Axios 封装

```
//axios用法
axios({
	method:"get",
	url:"xxx"，
	data:'',
	paramData:'',
	....
}).then((resp)=>{
	//回调
})
```

# 有趣API

随机生成一句有趣的话

https://api.uixsj.cn/hitokoto/get?type=social

https://api.mcloc.cn/love/



















































