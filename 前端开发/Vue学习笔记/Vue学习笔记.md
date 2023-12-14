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



# vue.config.js文件相关配置

```js
const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  lintOnSave: false, //关闭语法检查
  
  //公共请求路径
  publicPath: "",

  // 配置代理服务器
  devServer: {
    //路由跨域问题
    proxy: "http://localhost:8080"
  }
})
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



# Vue3学习笔记

## 一、vue-cli创建项目

```sh
# 检查vue/cli版本
vue -V
# 如果版本过低则重新安装
npm install -g @vue/cli

# 创建vue3项目
vue create <项目名>
```

## 二、vite创建项目

```sh
# vite创建项目
npm create vite@latest my-vue-app -- --template vue

## 进入工程目录
cd <project-name>
## 安装依赖
npm install
## 运行
npm run dev
```

##  三、常用 Composition API

官方文档: [https://v3.cn.vuejs.org/guide/composition-api-introduction.html](https://gitee.com/link?target=https%3A%2F%2Fv3.cn.vuejs.org%2Fguide%2Fcomposition-api-introduction.html)

### 1.拉开序幕的setup

1. 理解：Vue3.0中一个新的配置项，值为一个函数。
2. setup是所有**Composition API（组合API）***“ 表演的舞台 ”*。
3. 组件中所用到的：数据、方法等等，均要配置在setup中。
4. setup函数的两种返回值：
   1. 若返回一个对象，则对象中的属性、方法, 在模板中均可以直接使用。（重点关注！）
   2. 若返回一个渲染函数：则可以自定义渲染内容。（了解）
5. 注意点：
   1. 尽量不要与Vue2.x配置混用
      - Vue2.x配置（data、methos、computed...）中**可以访问到**setup中的属性、方法。
      - 但在setup中**不能访问到**Vue2.x配置（data、methos、computed...）。
      - 如果有重名, setup优先。
   2. setup不能是一个async函数，因为返回值不再是return的对象, 而是promise, 模板看不到return对象中的属性。（后期也可以返回一个Promise实例，但需要Suspense和异步组件的配合）

###  2.ref函数

- 作用: 定义一个响应式的数据

- 语法:

  ```js
  const xxx = ref(initValue);
  ```

  - 创建一个包含响应式数据的**引用对象（reference对象，简称ref对象）**。
  - JS中操作数据： `xxx.value`
  - 模板中读取数据: 不需要.value，直接：`<div>{{xxx}}</div>`

- 备注：

  - 接收的数据可以是：基本类型、也可以是对象类型。
  - 基本类型的数据：响应式依然是靠`Object.defineProperty()`的`get`与`set`完成的。
  - 对象类型的数据：内部 *“ 求助 ”* 了Vue3.0中的一个新函数—— `reactive`函数。

### 3.reactive函数

- 作用: 定义一个**对象类型**的响应式数据（基本类型不要用它，要用`ref`函数）

- 语法：

  ```js
  const 代理对象 = reactive(源对象);
  ```

  接收一个对象（或数组），返回一个**代理对象（Proxy的实例对象，简称proxy对象）**

- reactive定义的响应式数据是“深层次的”。

- 内部基于 ES6 的 Proxy 实现，通过代理对象操作源对象内部数据进行操作。

### 4.Vue3.0中的响应式原理

#### vue2.x的响应式

- 实现原理：

  - 对象类型：通过`Object.defineProperty()`对属性的读取、修改进行拦截（数据劫持）。

  - 数组类型：通过重写更新数组的一系列方法来实现拦截。（对数组的变更方法进行了包裹）。

    ```js
    Object.defineProperty(data, 'count', {
        get () {}, 
        set () {}
    })
    ```

- 存在问题：

  - 新增属性、删除属性, 界面不会更新。
  - 直接通过下标修改数组, 界面不会自动更新。

####  Vue3.X的响应式

- 实现原理:

  - 通过Proxy（代理）: 拦截对象中任意属性的变化, 包括：属性值的读写、属性的添加、属性的删除等。

  - 通过Reflect（反射）: 对源对象的属性进行操作。

  - MDN文档中描述的Proxy与Reflect：

    - Proxy：[https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Proxy](https://gitee.com/link?target=https%3A%2F%2Fdeveloper.mozilla.org%2Fzh-CN%2Fdocs%2FWeb%2FJavaScript%2FReference%2FGlobal_Objects%2FProxy)

    - Reflect：[https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Reflect](https://gitee.com/link?target=https%3A%2F%2Fdeveloper.mozilla.org%2Fzh-CN%2Fdocs%2FWeb%2FJavaScript%2FReference%2FGlobal_Objects%2FReflect)

      ```js
      new Proxy(data, {
      	// 拦截读取属性值
          get (target, prop) {
          	return Reflect.get(target, prop)
          },
          // 拦截设置属性值或添加新属性
          set (target, prop, value) {
          	return Reflect.set(target, prop, value)
          },
          // 拦截删除属性
          deleteProperty (target, prop) {
          	return Reflect.deleteProperty(target, prop)
          }
      })
      
      proxy.name = 'tom'   
      ```



###  5.reactive对比ref

- 从定义数据角度对比：
  - ref用来定义：**基本类型数据**。
  - reactive用来定义：**对象（或数组）类型数据**。
  - 备注：ref也可以用来定义**对象（或数组）类型数据**, 它内部会自动通过`reactive`转为**代理对象**。
- 从原理角度对比：
  - ref通过`Object.defineProperty()`的`get`与`set`来实现响应式（数据劫持）。
  - reactive通过使用**Proxy**来实现响应式（数据劫持）, 并通过**Reflect**操作**源对象**内部的数据。
- 从使用角度对比：
  - ref定义的数据：操作数据**需要**`.value`，读取数据时模板中直接读取**不需要**`.value`。
  - reactive定义的数据：操作数据与读取数据：**均不需要**`.value`。

### 6.setup的两个注意点

- setup执行的时机
  - 在beforeCreate之前执行一次，this是undefined。
- setup的参数
  - props：值为对象，包含：组件外部传递过来，且组件内部声明接收了的属性。
  - context：上下文对象
    - attrs: 值为对象，包含：组件外部传递过来，但没有在props配置中声明的属性, 相当于 `this.$attrs`。
    - slots: 收到的插槽内容, 相当于 `this.$slots`。
    - emit: 分发自定义事件的函数, 相当于 `this.$emit`。

### 7.计算属性与监视

#### 1.computed函数

- 与Vue2.x中computed配置功能一致

- 写法

  ```js
  import {computed} from 'vue'
  
  setup(){
      ...
  	//计算属性——简写
      let fullName = computed(()=>{
          return person.firstName + '-' + person.lastName
      })
      //计算属性——完整
      let fullName = computed({
          get(){
              return person.firstName + '-' + person.lastName
          },
          set(value){
              const nameArr = value.split('-')
              person.firstName = nameArr[0]
              person.lastName = nameArr[1]
          }
      })
  }
  ```

#### 2.watch函数

- 与Vue2.x中watch配置功能一致

- 两个小“坑”：

  - 监视reactive定义的响应式数据时：oldValue无法正确获取、强制开启了深度监视（deep配置失效）。
  - 监视reactive定义的响应式数据中某个属性时：deep配置有效。

  ```
  //情况一：监视ref定义的响应式数据
  watch(sum,(newValue,oldValue)=>{
  	console.log('sum变化了',newValue,oldValue)
  },{immediate:true})
  
  //情况二：监视多个ref定义的响应式数据
  watch([sum,msg],(newValue,oldValue)=>{
  	console.log('sum或msg变化了',newValue,oldValue)
  }) 
  
  /* 情况三：监视reactive定义的响应式数据
  			若watch监视的是reactive定义的响应式数据，则无法正确获得oldValue！！
  			若watch监视的是reactive定义的响应式数据，则强制开启了深度监视 
  */
  watch(person,(newValue,oldValue)=>{
  	console.log('person变化了',newValue,oldValue)
  },{immediate:true,deep:false}) //此处的deep配置不再奏效
  
  //情况四：监视reactive定义的响应式数据中的某个属性
  watch(()=>person.job,(newValue,oldValue)=>{
  	console.log('person的job变化了',newValue,oldValue)
  },{immediate:true,deep:true}) 
  
  //情况五：监视reactive定义的响应式数据中的某些属性
  watch([()=>person.job,()=>person.name],(newValue,oldValue)=>{
  	console.log('person的job变化了',newValue,oldValue)
  },{immediate:true,deep:true})
  
  //特殊情况
  watch(()=>person.job,(newValue,oldValue)=>{
      console.log('person的job变化了',newValue,oldValue)
  },{deep:true}) //此处由于监视的是reactive素定义的对象中的某个属性，所以deep配置有效
  ```

#### 3.watchEffect函数

- watch的套路是：既要指明监视的属性，也要指明监视的回调。

- watchEffect的套路是：不用指明监视哪个属性，监视的回调中用到哪个属性，那就监视哪个属性。

- watchEffect有点像computed：

  - 但computed注重的计算出来的值（回调函数的返回值），所以必须要写返回值。
  - 而watchEffect更注重的是过程（回调函数的函数体），所以不用写返回值。

  ```
  //watchEffect所指定的回调中用到的数据只要发生变化，则直接重新执行回调。
  watchEffect(()=>{
      const x1 = sum.value
      const x2 = person.age
      console.log('watchEffect配置的回调执行了')
  })
  ```

### 8.生命周期

- Vue3.0中可以继续使用Vue2.x中的生命周期钩子，但有有两个被更名：
  - `beforeDestroy`改名为 `beforeUnmount`
  - `destroyed`改名为 `unmounted`
- Vue3.0也提供了 Composition API 形式的生命周期钩子，与Vue2.x中钩子对应关系如下：
  - `beforeCreate`===>`setup()`
  - `created`=======>`setup()`
  - `beforeMount` ===>`onBeforeMount`
  - `mounted`=======>`onMounted`
  - `beforeUpdate`===>`onBeforeUpdate`
  - `updated` =======>`onUpdated`
  - `beforeUnmount` ==>`onBeforeUnmount`
  - `unmounted` =====>`onUnmounted`

### 9.自定义hook函数

- 什么是hook？—— 本质是一个函数，把setup函数中使用的Composition API进行了封装。
- 类似于vue2.x中的mixin。
- 自定义hook的优势: 复用代码, 让setup中的逻辑更清楚易懂。

### 10.toRef

- 作用：创建一个 ref 对象，其value值指向另一个对象中的某个属性。
- 语法：`const name = toRef(person,'name')`
- 应用: 要将响应式对象中的某个属性单独提供给外部使用时。
- 扩展：`toRefs` 与`toRef`功能一致，但可以批量创建多个 ref 对象，语法：`toRefs(person)`

## 四、其它 Composition API

### 1.shallowReactive 与 shallowRef

- shallowReactive：只处理对象最外层属性的响应式（浅响应式）。
- shallowRef：只处理基本数据类型的响应式, 不进行对象的响应式处理。
- 什么时候使用?
  - 如果有一个对象数据，结构比较深, 但变化时只是外层属性变化 ===> shallowReactive。
  - 如果有一个对象数据，后续功能不会修改该对象中的属性，而是生新的对象来替换 ===> shallowRef。

### 2.readonly 与 shallowReadonly

- readonly: 让一个响应式数据变为只读的（深只读）。
- shallowReadonly：让一个响应式数据变为只读的（浅只读）。
- 应用场景: 不希望数据被修改时。

### 3.toRaw 与 markRaw

- toRaw：
  - 作用：将一个由`reactive`生成的**响应式对象**转为**普通对象**。
  - 使用场景：用于读取响应式对象对应的普通对象，对这个普通对象的所有操作，不会引起页面更新。
- markRaw：
  - 作用：标记一个对象，使其永远不会再成为响应式对象。
  - 应用场景:
    1. 有些值不应被设置为响应式的，例如复杂的第三方类库等。
    2. 当渲染具有不可变数据源的大列表时，跳过响应式转换可以提高性能。

### 4.customRef

- 作用：创建一个自定义的 ref，并对其依赖项跟踪和更新触发进行显式控制。

- 实现防抖效果：

  ```
  <template>
  	<input type="text" v-model="keyword">
  	<h3>{{keyword}}</h3>
  </template>
  
  <script>
  	import {ref,customRef} from 'vue'
  	export default {
  		name:'Demo',
  		setup(){
  			// let keyword = ref('hello') //使用Vue准备好的内置ref
  			//自定义一个myRef
  			function myRef(value,delay){
  				let timer
  				//通过customRef去实现自定义
  				return customRef((track,trigger)=>{
  					return{
  						get(){
  							track() //告诉Vue这个value值是需要被“追踪”的
  							return value
  						},
  						set(newValue){
  							clearTimeout(timer)
  							timer = setTimeout(()=>{
  								value = newValue
  								trigger() //告诉Vue去更新界面
  							},delay)
  						}
  					}
  				})
  			}
  			let keyword = myRef('hello',500) //使用程序员自定义的ref
  			return {
  				keyword
  			}
  		}
  	}
  </script>
  ```

### 5.provide 与 inject

- 作用：实现**祖与后代组件间**通信

- 套路：父组件有一个 `provide` 选项来提供数据，后代组件有一个 `inject` 选项来开始使用这些数据

- 具体写法：

  1. 祖组件中：

     ```
     setup(){
     	......
         let car = reactive({name:'奔驰',price:'40万'})
         provide('car',car)
         ......
     }
     ```

  2. 后代组件中：

     ```
     setup(props,context){
     	......
         const car = inject('car')
         return {car}
     	......
     }
     ```

### 6.响应式数据的判断

- isRef: 检查一个值是否为一个 ref 对象
- isReactive: 检查一个对象是否是由 `reactive` 创建的响应式代理
- isReadonly: 检查一个对象是否是由 `readonly` 创建的只读代理
- isProxy: 检查一个对象是否是由 `reactive` 或者 `readonly` 方法创建的代理

## 五、Composition API 的优势

### 1.Options API 存在的问题

使用传统OptionsAPI中，新增或者修改一个需求，就需要分别在data，methods，computed里修改 。

### 2.Composition API 的优势

我们可以更加优雅的组织我们的代码，函数。让相关功能的代码更加有序的组织在一起。

## 六、新的组件

### 1.Fragment

- 在Vue2中: 组件必须有一个根标签
- 在Vue3中: 组件可以没有根标签, 内部会将多个标签包含在一个Fragment虚拟元素中
- 好处: 减少标签层级, 减小内存占用

### 2.Teleport

- 什么是Teleport？—— `Teleport` 是一种能够将我们的**组件html结构**移动到指定位置的技术。

  ```
  <teleport to="移动位置">
  	<div v-if="isShow" class="mask">
  		<div class="dialog">
  			<h3>我是一个弹窗</h3>
  			<button @click="isShow = false">关闭弹窗</button>
  		</div>
  	</div>
  </teleport>
  ```

### 3.Suspense

- 等待异步组件时渲染一些额外内容，让应用有更好的用户体验

- 使用步骤：

  - 异步引入组件

    ```
    import {defineAsyncComponent} from 'vue'
    const Child = defineAsyncComponent(()=>import('./components/Child.vue'))
    ```

  - 使用`Suspense`包裹组件，并配置好`default` 与 `fallback`

    ```
    <template>
    	<div class="app">
    		<h3>我是App组件</h3>
    		<Suspense>
    			<template v-slot:default>
    				<Child/>
    			</template>
    			<template v-slot:fallback>
    				<h3>加载中.....</h3>
    			</template>
    		</Suspense>
    	</div>
    </template>
    ```

## 七、其他

### 1.全局API的转移

- Vue 2.x 有许多全局 API 和配置。

  - 例如：注册全局组件、注册全局指令等。

    ```
    //注册全局组件
    Vue.component('MyButton', {
      data: () => ({
        count: 0
      }),
      template: '<button @click="count++">Clicked {{ count }} times.</button>'
    })
    
    //注册全局指令
    Vue.directive('focus', {
      inserted: el => el.focus()
    }
    ```

- Vue3.0中对这些API做出了调整：

  - 将全局的API，即：`Vue.xxx`调整到应用实例（`app`）上

    | 2.x 全局 API（`Vue`）    | 3.x 实例 API (`app`)        |
    | ------------------------ | --------------------------- |
    | Vue.config.xxxx          | app.config.xxxx             |
    | Vue.config.productionTip | **移除**                    |
    | Vue.component            | app.component               |
    | Vue.directive            | app.directive               |
    | Vue.mixin                | app.mixin                   |
    | Vue.use                  | app.use                     |
    | Vue.prototype            | app.config.globalProperties |

### 2.其他改变

- data选项应始终被声明为一个函数。

- 过度类名的更改：

  - Vue2.x写法

    ```
    .v-enter,
    .v-leave-to {
      opacity: 0;
    }
    .v-leave,
    .v-enter-to {
      opacity: 1;
    }
    ```

  - Vue3.x写法

    ```
    .v-enter-from,
    .v-leave-to {
      opacity: 0;
    }
    
    .v-leave-from,
    .v-enter-to {
      opacity: 1;
    }
    ```

- **移除**keyCode作为 v-on 的修饰符，同时也不再支持`config.keyCodes`

- **移除**`v-on.native`修饰符

  - 父组件中绑定事件

    ```
    <my-component
      v-on:close="handleComponentEvent"
      v-on:click="handleNativeClickEvent"
    />
    ```

  - 子组件中声明自定义事件

    ```
    <script>
      export default {
        emits: ['close']
      }
    </script>
    ```

- **移除**过滤器（filter）

  > 过滤器虽然这看起来很方便，但它需要一个自定义语法，打破大括号内表达式是 “只是 JavaScript” 的假设，这不仅有学习成本，而且有实现成本！建议用方法调用或计算属性去替换过滤器。

























