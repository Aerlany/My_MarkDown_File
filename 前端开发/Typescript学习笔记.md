# TypeScript NOTES

## 基础数据类型

TypeScript支持与JavaScript几乎相同的数据类型，数字，字符串，结构体，布尔值等。此外还提供了实用的枚举类型方便我们使用。

### **变量数据类型声明**

```ts
let name: string = "Tom";	
let age: number = 12；
```

你还可以使用*模版字符串*，它可以定义多行文本和内嵌表达式。 这种字符串是被反引号包围（```），并且以`${ expr }`这种形式嵌入表达式。

```ts
let name: string = `Gene`;
let age: number = 37;
let sentence: string = `Hello, my name is ${ name }.

I'll be ${ age + 1 } years old next month.`;
```

### **数组声明**

```ts
let list: number[] = [1,2,3];
// 数组泛型声明
let list: Array<number> = [1,2,3];
```

### **元组** 

元组类型允许表示一个已知元素数量和类型的数组，各元素的类型不必相同。 比如，你可以定义一对值分别为`string`和`number`类型的元组

```ts
let tuple: [string,number];
//Initialize
tuple = ["Tom",12];
```

### **枚举**

`enum`类型是对JavaScript标准数据类型的一个补充。 像C#等其它语言一样，使用枚举类型可以为一组数值赋予友好的名字。

枚举：定义一组命名常量。便于描述一个值，该值可以是其命名常量中的一个。

数字类型的枚举有初始值，默认第一个成员值为0，向后加1自增。

字符串的枚举没有默认值，必须手动赋值。

```ts
enum Color {red= 1, Green, Blue};
let c: Color = Color.red;
let colorName: string = Color[2];

alert(colorName);  // 显示'Green'因为上面代码里它的值是2
```

### **任意值 （any）**

我们不希望类型检查器对这些值进行检查而是直接让它们通过编译阶段的检查。 那么我们可以使用`any`类型来标记这些变量：

```ts
let notSure: any = 4;
notSure = "maybe a string instead";
notSure = false; // okay, definitely a boolean
```

### **空值**

某种程度上来说，`void`类型像是与`any`类型相反，它表示没有任何类型。 当一个函数没有返回值时，你通常会见到其返回值类型是`void`：

```ts
function warnUser(): void {
    alert("This is my warning message");
}
```

声明一个`void`类型的变量没有什么大用，因为你只能为它赋予`undefined`和`null`：

```ts
let unusable: void = undefined;
```

### **Null 和 Undefined**

TypeScript里，`undefined`和`null`两者各自有自己的类型分别叫做`undefined`和`null`。 和`void`相似，它们的本身的类型用处不是很大：

```ts
// Not much else we can assign to these variables!
let u: undefined = undefined;
let n: null = null;
```

默认情况下`null`和`undefined`是所有类型的子类型。 就是说你可以把`null`和`undefined`赋值给`number`类型的变量。

### **类型断言**

```ts
let someValue: any = "this is a string";

//使用<>
let strLength: number = (<string>someValue).length;
//使用 as 关键字
let strLength: number = (someValue as string).length;
```

### **联合类型**

```ts
//既可以有string 又可以有number
let arr:(string | number)[] = [1,2,"3"];
```

### 类型别名 type

```ts
type CustomArray = (string | number)[]

let arr1: CustomArray = [1,2,"3"];
let arr2: CustomArray = [3,"a",3];
```

### 类型推论(type inference)

TypeScript里，在有些没有明确指出类型的地方，类型推论会帮助提供类型

```ts
let x = 3;
```

变量`x`的类型被推断为数字。 这种推断发生在初始化变量和成员，设置默认参数值和决定函数返回值时。

大多数情况下，类型推论是直截了当地。

**最佳通用类型**

当需要从几个表达式中推断类型时候，会使用这些表达式的类型来推断出一个最合适的通用类型。例如，

```ts
let x = [0, 1, null];
```

为了推断`x`的类型，我们必须考虑所有元素的类型。 这里有两种选择：`number`和`null`。 计算通用类型算法会考虑所有的候选类型，并给出一个兼容所有候选类型的类型。

由于最终的通用类型取自候选类型，有些时候候选类型共享相同的通用类型，但是却没有一个类型能做为所有候选类型的类型。例如：

```ts
let zoo = [new Rhino(), new Elephant(), new Snake()];
```

这里，我们想让zoo被推断为`Animal[]`类型，但是这个数组里没有对象是`Animal`类型的，因此不能推断出这个结果。 为了更正，当候选类型不能使用的时候我们需要明确的指出类型：

```ts
let zoo: Animal[] = [new Rhino(), new Elephant(), new Snake()];
```

如果没有找到最佳通用类型的话，类型推断的结果为联合数组类型，`(Rhino | Elephant | Snake)[]`。

**上下文类型**

TypeScript类型推论也可能按照相反的方向进行。 这被叫做“按上下文归类”。按上下文归类会发生在表达式的类型与所处的位置相关时。比如：

```ts
window.onmousedown = function(mouseEvent) {
    console.log(mouseEvent.button);  //<- Error
};
```

这个例子会得到一个类型错误，TypeScript类型检查器使用`Window.onmousedown`函数的类型来推断右边函数表达式的类型。 因此，就能推断出`mouseEvent`参数的类型了。 如果函数表达式不是在上下文类型的位置，`mouseEvent`参数的类型需要指定为`any`，这样也不会报错了。

如果上下文类型表达式包含了明确的类型信息，上下文的类型被忽略。 重写上面的例子：

```ts
window.onmousedown = function(mouseEvent: any) {
    console.log(mouseEvent.button);  //<- Now, no error is given
};
```

这个函数表达式有明确的参数类型注解，上下文类型被忽略。 这样的话就不报错了，因为这里不会使用到上下文类型。

上下文归类会在很多情况下使用到。 通常包含函数的参数，赋值表达式的右边，类型断言，对象成员和数组字面量和返回值语句。 上下文类型也会做为最佳通用类型的候选类型。比如：

```ts
function createZoo(): Animal[] {
    return [new Rhino(), new Elephant(), new Snake()];
}
```

这个例子里，最佳通用类型有4个候选者：`Animal`，`Rhino`，`Elephant`和`Snake`。 当然，`Animal`会被做为最佳通用类型。



### typeof 类型属性

**类型推论实现简化类型书写**

```ts
type p = { x: number, y: number }

let point: p = { x: 1, y: 2 }

function formate(params: typeof point) {
    return params.x + params.y;
}

let formate1 = formate({ x: 1, y: 3 });

console.log(formate1);
```

1. 使用 `typeof` 操作符来获取变量的类型，结果与字面形式的一致。

2. `typeof`出现在类型注解的位置所处环境就是类型上下文。

3. `typeof`只能用来查询变量或对象的类型，无法查询函数返回值的类型。

   

-----

## 函数

### 定义函数参数类型

TypeScript里的类型注解是一种轻量级的为函数或变量添加约束的方式。 在这个例子里，我们希望`greeter`函数接收一个字符串参数。 然后尝试把`greeter`的调用改成传入一个数组：

```ts
function greeter(person: string) {
    return "Hello, " + person;
}

let user = "TOM";

document.body.innerHTML = greeter(user);
```

### 定义函数返回值类型

```ts
function add(x: number, y: number): number {
    return x + y;
}

let myAdd = function(x: number, y: number): number { return x + y; };
```

### **完整函数类型**

函数类型包含两部分：参数类型和返回值类型。 当写出完整函数类型的时候，这两部分都是需要的。

只要参数类型是匹配的，那么就认为它是有效的函数类型，而不在乎参数名是否正确。

```ts
let myAdd: (x:number, y:number) => number =
    function(x: number, y: number): number { return x + y; };
```



### **可选参数和默认参数**

TypeScript里的每个函数参数都是必须的。 这不是指不能传递`null`或`undefined`作为参数，而是说编译器检查用户是否为每个参数都传入了值。 编译器还会假设只有这些参数会被传递进函数。 简短地说，传递给一个函数的参数个数必须与函数期望的参数个数一致。

```ts
function buildName(firstName: string, lastName?: string) {
    if (lastName)
        return firstName + " " + lastName;
    else
        return firstName;
}

let result1 = buildName("Bob");  // works correctly now
let result2 = buildName("Bob", "Adams", "Sr.");  // error, too many parameters
let result3 = buildName("Bob", "Adams");  // ah, just right
```

### **剩余参数**

必要参数，默认参数和可选参数有个共同点：它们表示某一个参数。 有时，你想同时操作多个参数，或者你并不知道会有多少参数传递进来。 在JavaScript里，你可以使用`arguments`来访问所有传入的参数。

在TypeScript里，你可以把所有参数收集到一个变量里：

```ts
function buildName(firstName: string, ...restOfName: string[]) {
  return firstName + " " + restOfName.join(" ");
}

let employeeName = buildName("Joseph", "Samuel", "Lucas", "MacKinzie");
```

剩余参数会被当做个数不限的可选参数。 可以一个都没有，同样也可以有任意个。 编译器创建参数数组，名字是你在省略号（`...`）后面给定的名字，你可以在函数体内使用这个数组。





### **`this`和箭头函数**

JavaScript里，`this`的值在函数被调用的时候才会指定。 这是个既强大又灵活的特点，但是你需要花点时间弄清楚函数调用的上下文是什么。 但众所周知，这不是一件很简单的事，尤其是在返回一个函数或将函数当做参数传递的时候。

**this指向问题**

this 的指向取决于函数的调用方式。

```ts
const user = {
    name: 'KinWen',
    age: 18,
    sayHello(){
        console.log(`你好,我是${this.name}`);
    }
}
```

- 如果直接调用函数(全局调用), this 指向全局或 undefined (启用严格模式)

```ts
const sayHello = user.sayHello;
sayHello(); // this指向全局对象
```

- 如果使用`对象.方法`调用, this 指向对象本身。

```ts
user.sayHello(); // this指向user对象
```

- 如果是 dom 事件的处理函数, this 指向事件处理对象。

```ts
document.body.addEventListener('click',function () {
    console.log(this); //this === body
})
```

**正确使用this和箭头函数**

```ts
let deck = {
    suits: ["hearts", "spades", "clubs", "diamonds"],
    cards: Array(52),
    createCardPicker: function() {
        // NOTE: the line below is now an arrow function, allowing us to capture 'this' right here
        return () => {
            let pickedCard = Math.floor(Math.random() * 52);
            let pickedSuit = Math.floor(pickedCard / 13);

            return {suit: this.suits[pickedSuit], card: pickedCard % 13};
        }
    }
}

let cardPicker = deck.createCardPicker();
let pickedCard = cardPicker();

alert("card: " + pickedCard.card + " of " + pickedCard.suit);
```



### **函数重载**

JavaScript本身是个动态语言。 JavaScript里函数根据传入不同的参数而返回不同类型的数据是很常见的。

```ts
let suits = ["hearts", "spades", "clubs", "diamonds"];

function pickCard(x): any {
    // Check to see if we're working with an object/array
    // if so, they gave us the deck and we'll pick the card
    if (typeof x == "object") {
        let pickedCard = Math.floor(Math.random() * x.length);
        return pickedCard;
    }
    // Otherwise just let them pick the card
    else if (typeof x == "number") {
        let pickedSuit = Math.floor(x / 13);
        return { suit: suits[pickedSuit], card: x % 13 };
    }
}

let myDeck = [{ suit: "diamonds", card: 2 }, { suit: "spades", card: 10 }, { suit: "hearts", card: 4 }];
let pickedCard1 = myDeck[pickCard(myDeck)];
alert("card: " + pickedCard1.card + " of " + pickedCard1.suit);

let pickedCard2 = pickCard(15);
alert("card: " + pickedCard2.card + " of " + pickedCard2.suit);
```

`pickCard`方法根据传入参数的不同会返回两种不同的类型。 如果传入的是代表纸牌的对象，函数作用是从中抓一张牌。 如果用户想抓牌，我们告诉他抓到了什么牌。 但是这怎么在类型系统里表示呢。



### 函数自调用

```js
const functionA = function () {
    var x = "Hello A";
    console.log(x);
    return 3;
}

console.log(functionA);

const functionB = function () {
    var x = "Hello B";
    console.log(x);
    return 3;
}();

console.log(functionB);

(function functionC() {
    var x = "Hello C";
    console.log(x);
    return 3;
})();

// ReferenceError: functionC is not defined
//console.log(functionC);
```

 

## interface 接口

让我们开发这个示例应用。这里我们使用接口来描述一个拥有`firstName`和`lastName`字段的对象。 在TypeScript里，只在两个类型内部的结构兼容那么这两个类型就是兼容的。 这就允许我们在实现接口时候只要保证包含了接口要求的结构就可以，而不必明确地使用`implements`语句。

```ts
interface Person {
    firstName: string;
    lastName: string;
}
  
function greeter(person: Person) {
    return "Hello, " + person.firstName + " " + person.lastName;
}

let user = { firstName: "Jane", lastName: "User" };

document.body.innerHTML = greeter(user);
```

### **可选属性**

带有可选属性的接口与普通的接口定义差不多，只是在可选属性名字定义的后面加一个`?`符号。

可选属性的好处之一是可以对可能存在的属性进行预定义，好处之二是可以捕获引用了不存在的属性时的错误。

```ts
interface SquareConfig {
  color?: string;
  width?: number;
}
```

### **只读属性**

一些对象属性只能在对象刚刚创建的时候修改其值。 你可以在属性名前用`readonly`来指定只读属性:

```ts
interface Point {
    readonly x: number;
    readonly y: number;
}
```

### **函数类型**

接口能够描述JavaScript中对象拥有的各种各样的外形。 除了描述带有属性的普通对象外，接口也可以描述函数类型。为了使用接口表示函数类型，我们需要给接口定义一个调用签名。 它就像是一个只有参数列表和返回值类型的函数定义。参数列表里的每个参数都需要名字和类型。

```ts
interface SearchFunc {
  (source: string, subString: string): boolean;
}

let mySearch: SearchFunc;
mySearch = function(source: string, subString: string) {
  let result = source.search(subString);
  return result > -1;
}
```

### **可索引的类型**

可索引类型具有一个*索引签名*，它描述了对象索引的类型，还有相应的索引返回值类型。

```ts
//这个索引签名表示了当用number去索引StringArray时会得到string类型的返回值。
interface StringArray {
    //(索引值)      (返回值)
  [index: number]: string;
}

let myArray: StringArray;
myArray = ["Bob", "Fred"];

let myStr: string = myArray[0];
//共有支持两种索引签名：字符串和数字。 可以同时使用两种类型的索引，但是数字索引的返回值必须是字符串索引返回值类型的子类型。 这是因为当使用number来索引时，JavaScript会将它转换成string然后再去索引对象。 
```

### **实现接口**

TypeScript也能够用它来明确的强制一个类去符合某种契约。

```ts
interface ClockInterface {
    currentTime: Date;
    setTime(d, Date);
}

class Clock implements ClockInterface {
    currentTime: Date;
    //构造方法
    constructor(h: number, m: number) { }
    //在实现一个接口时要实现接口中的所有抽象方法
    setTime(d: Date){
        this.currentTime = d;
    }
}
```

### 接口继承

当使用接口继承关键字`extends`声明并继承一个接口时，其拥有其父接口中所有的属性和方法。

```ts
interface Point2D {
    x: number,
    y: number
}

interface Point3D extends Point2D {
    z: number;
}

let position: Point2D = { x: 12, y: 12 }
let position2: Point3D = { x: 12, y: 12, z: 2 }
```



### **接口继承类**

当接口继承了一个类类型时，它会继承类的成员但不包括其实现。 就好像接口声明了所有类中存在的成员，但并没有提供具体实现一样。 接口同样会继承到类的private和protected成员。 这意味着当你创建了一个接口继承了一个拥有私有或受保护的成员的类时，这个接口类型只能被这个类或其子类所实现（implement）。

```ts
class Control {
    private state: any;
}
interface SelectableControl extends Control {
    select(): void;
}
class Button extends Control implements SelectableControl {
    select() { }
}
class TextBox extends Control {}
// Error: Property 'state' is missing in type 'Image'.
class Image implements SelectableControl {
    select() { }
}

class Location {

}
```





## class 类

TypeScript支持持基于类的面向对象编程。

让我们创建一个`Student`类，它带有一个构造函数和一些公共字段。 注意类和接口可以一起共作，程序员可以自行决定抽象的级别。

1、在构造函数的参数上使用`public`等同于创建了同名的成员变量。

2、使用`constructor`创建一个类的构造函数。

### class构造函数和实例方法

```ts
class Student {
    fullName: string;
    //构造函数
    constructor(public firstName: string, public middleInitial: string, public lastName: string) {
        this.fullName = firstName + " " + middleInitial + " " + lastName;
    }
    
    //实例方法
    function fun1(public action: string){
        this.action = action;
    }
}

interface Person {
    firstName: string;
    lastName: string;
}

function greeter(person : Person) {
    return "Hello, " + person.firstName + " " + person.lastName;
}

let user = new Student("Jane", "M.", "User");

document.body.innerHTML = greeter(user);
```

### class继承（extents）

子类继承父类，则子类的实例对象就具有了父类和子类的所有`public`属性和方法

```ts
class Animal {
    private name: string;
    protected age: string;
    protected move() {
        console.log("Walk 1 step");
    };
    private say() {
        console.log("Hello");
    };
}

class Panda extends Animal {
    test() {
        this.move();
    }
}

let animal = new Panda();
animal.test()
```



### class实现（implements）

当一个类想要实现一个接口，就必须要实现接口中的所有抽象方法

```ts
interface Animal {
    walk(): void;
    say(): void;
}

class Panda implements Animal {
    walk(): void {
        //code
    }
    say(): void {
        //code
    }
}
```



### **公共，私有与受保护的修饰符**

**public**

```ts
class Animal {
    public name: string;
    public constructor(theName: string) { this.name = theName; }
    public move(distanceInMeters: number) {
        console.log(`${this.name} moved ${distanceInMeters}m.`);
    }
}
```

**private** ***仅在其声明所在类中可见，实例对象也不可见***

```ts
class Animal {
    private name: string;
    constructor(theName: string) { this.name = theName; }
}

new Animal("Cat").name; // 错误: 'name' 是私有的.
```

TypeScript使用的是结构性类型系统。 当我们比较两种不同的类型时，并不在乎它们从何处而来，如果所有成员的类型都是兼容的，我们就认为它们的类型是兼容的。

然而，当我们比较带有`private`或`protected`成员的类型的时候，情况就不同了。 如果其中一个类型里包含一个`private`成员，那么只有当另外一个类型中也存在这样一个`private`成员， 并且它们都是来自同一处声明时，我们才认为这两个类型是兼容的。 对于`protected`成员也使用这个规则。

下面来看一个例子，更好地说明了这一点：

```ts
class Animal {
    private name: string;
    constructor(theName: string) { this.name = theName; }
}

class Rhino extends Animal {
    constructor() { super("Rhino"); }
}

class Employee {
    private name: string;
    constructor(theName: string) { this.name = theName; }
}

let animal = new Animal("Goat");
let rhino = new Rhino();
let employee = new Employee("Bob");

animal = rhino;
animal = employee; // 错误: Animal 与 Employee 不兼容.
```

**protected**	***仅在其声明所在类和其子类中可见，实例对象也不可见***

```ts
class Person {
    protected name: string;
    constructor(name: string) { this.name = name; }
}

class Employee extends Person {
    private department: string;

    constructor(name: string, department: string) {
        super(name)
        this.department = department;
    }

    public getElevatorPitch() {
        return `Hello, my name is ${this.name} and I work in ${this.department}.`;
    }
}

let howard = new Employee("Howard", "Sales");
console.log(howard.getElevatorPitch());
console.log(howard.name); // 错误
```

注意，我们不能在`Person`类外使用`name`，但是我们仍然可以通过`Employee`类的实例方法访问，因为`Employee`是由`Person`派生而来的。

构造函数也可以被标记成`protected`。 这意味着这个类不能在包含它的类外被实例化，但是能被继承。比如，

```ts
class Person {
    protected name: string;
    protected constructor(theName: string) { this.name = theName; }
}

// Employee 能够继承 Person
class Employee extends Person {
    private department: string;

    constructor(name: string, department: string) {
        super(name);
        this.department = department;
    }

    public getElevatorPitch() {
        return `Hello, my name is ${this.name} and I work in ${this.department}.`;
    }
}

let howard = new Employee("Howard", "Sales");
let john = new Person("John"); // 错误: 'Person' 的构造函数是被保护的.
```

**readonly** ***只读修饰符，外部不可直接访问，自能通过GetSet方法访问***

你可以使用`readonly`关键字将属性设置为只读的。 只读属性必须在声明时或构造函数里被初始化。

```ts
class Octopus {
    readonly name: string;
    readonly numberOfLegs: number = 8;
    constructor (theName: string) {
        this.name = theName;
    }
}
let dad = new Octopus("Man with the 8 strong legs");
dad.name = "Man with the 3-piece suit"; // 错误! name 是只读的.
```





## TypeScript 高级特性

### 类型兼容性

两种类型系统：

1. Structural Type System（结构化类型系统）
2. Nominal Type System（标明类型系统）

Ts采用的是结构化类型系统，类型检查关注的是值所具有的形状，也就是说，在结构化类型系统中，如果两个对象具有相同的形状，则他们就属于一种类型。

#### **类之间的类型兼容性**

对于对象类型来说，a 的成员和b的至少相同，则b兼容a（成员多的可以赋值给成员少的）

```ts
class a {
    x: number; y: number
    say() { }
}
class b extends a {
    z: number;
    walk() { }
}

let p: a = new b();
```

#### **接口之间的类型兼容性**

```ts
interface a {
    x: number; y: number
}
interface a1 {
    x: number; y: number
}
let x1: a;
let x2: a1 = x1;

console.log(x2 == x1);//ture

```

#### 函数之间的类型兼容性



### 交叉类型

交叉类型（&）：类似于接口继承，用于组合多个类型为一个类型（常用于对象类型）

```ts
interface a {
    x: number;
    y: number
}
interface b {
    z: number;
}

type unixType = a & b;
let x: unixType = {
    x: 1,
    y: 2,
    z: 1
};

console.log(x);
console.log(typeof (x));
```

**注意：**接口继承和交叉类型的差异比较

```ts
//接口继承时
//重新声明一个变量或函数时
//如果声明时类型不一致，会报错‘类型不兼容’
interface a {
    fn1(p: string): void
}
interface b extends a {
    fn1(p: number): void
}
```

```ts
//采用交叉类型时则不会出现
interface a {
    fn1(p: string): void
}
interface b extends a {
    fn1(p: number): void
}

type c = a & b
//相当于
//fn1: (p: string | number): void
```



### 泛型

**泛型**可以保证类型安全的前提下，让函数实现多种类型兼容，从而实现复用，常用于函数、接口、类中。

#### 泛型函数

**创建泛型函数**

```ts
function id<Type>(value: Type): Type { return value }
```

**注意：**

- 类型变量Type，是一种特殊类型的变量，它处理类型而不是值。
- 该类型变量相当于一个类型容器，能够捕获用户提供的类型（具体是什么类型由用户调用该函数时指定）
- 因为Type是类型，因此可以将其作为函数参数和返回值的类型，表示参数和返回值具有相同的类型。类型变量Type，可以是任意合法的变量名称。



**泛型函数的调用**

```ts
let a = id<string>("10");
let b = id<number>(10);
```

- 语法：在函数名称的后面添加＜＞（尖括号），尖括号中指定具体的类型，比如，此处的number。
- 当传入类型number后，这个类型就会被函数声明时指定的类型变量Type捕获到。
- 此时，Type的类型就是number，所以，函数id参数和返回值的类型也都是number。同样，如果传入类型string，函数id参数和返回值的类型就都是string。

这样，通过泛型就做到了让id函数与多种不同的类型一起工作，实现了复用的同时保证了类型安全。



**简化泛型函数的调用**

根据TypeScript类型推论，在有些没有明确指出类型的地方，类型推论会帮助提供类型，所以泛型函数在调用时也可以省略类型

```ts
let a = id(10);
```



**泛型函数类型约束**

添加泛型约束收缩类型，主要有以下两种方式

1. 指定更加具体的类型

   ```ts
   function id<Type>(value:Type[]):Type { 
       console.log(value.length)
       return value
   }
   ```

2. 添加约束

   ```ts
   interface ILength { length: number}
   
   function id<Type extends ILength>(value:Type):Type { 
       console.log(value.length)
       return value
   }
   ```

**解释：**

- 创建描述约束的接口ILength，该接口要求提供length属性。
- 通过extends关键字使用该接口，为泛型（类型变量）添加约束。
- 该约束表示：传入的类型必须具有length属性。

注意：传入的实参（比如，数组）只要有length属性即可，这也符合前面讲到的接口的类型兼容性。



**多个泛型类型参数**

泛型的类型变量可以有多个，并且类型变量之间还可以约束（比如，第二个类型变量受第一个类型变量约束）。

比如，创建一个函数来获取对象中属性的值：

```ts
function id<Type, Key extends keyof Type>(target: Type, name: Key) {
    return target[name];
}

let targetObj = {
    name: "Tom",
    age: 21
}

let a = id(targetObj, "age")
console.log(a);
```

**注意：**

1．添加了第二个类型变量Key，两个类型变量之间使用（）逗号分隔。

2．keyof关键字接收一个对象类型，生成其键名称（可能是字符串或数字）的联合类型。

`keyof` is a keyword in TypeScript which is used to extract the key type from an object type.

3．本示例中keyof Type 实际上获取的是person对象所有键的联合类型，也就是：＇name＇｜＇age＇。

4．类型变量Key受Type约束，可以理解为：Key只能是Type所有键中的任意一个，或者说只能访问对象中存在的属性。



#### 泛型接口

泛型接口：接口也可以配合泛型来使用，以增加其灵活性，增强其复用性。

```ts
//泛型接口
interface Animal<Type> {
    Walk: (param: Type) => Type
}
//泛型接口继承时要指定父泛型接口的类型
interface aquatic<Type> extends Animal<string> {
    swim: (param: Type) => Type;
}
//实现泛型接口
class Panda implements Animal<string> {
    Walk(param: string) {
        return param;
    }
}

let a: Animal<string> = {
    Walk(param) {
        return param
    }
}
console.log(a.Walk("Tom"));

let b = new Panda()
console.log(b.Walk("Jery"));


let c: aquatic<string> = {
    swim(param) {
        return param
    },

    Walk(param) {
        return param
    },
}
console.log(c.swim("Aerlany"));
```

解释：

1. 在接口名称的后面添加<类型变量>，那么，这个接口就变成了泛型接口

2. 接口的类型变量，对接口中所有其他成员可见，也就是接口中所有成员都可以使用类型变量

3. 使用泛型接口时，需要显式指定具体的类型（比如，此处的`Animal<string>`）。
4. 数组就是泛型接口



#### 泛型类

```ts
class Animal<T> {
    defalutName: T;
    add: (param: T) => T
}

let a = new Animal<string>()
a.defalutName = "100";
console.log(a.defalutName);

```

**注意：**在创建泛型类时，如果指定构造函数中的参数为泛型参数，那么该类实例化时可以不写`<Type>`泛型。

**泛型工具**

- **`Partial<Type>`**用来构造（创建）一个类型，将Type的所有属性设置为可选	

```ts
interface Animal<T> {
    defalutName: T
}

type AnimalA = Partial<Animal<string>>

/*
type AnimalA = {
    defalutName?: string | undefined;
}
*/
```

- **`Readonly<Type>`**用来构造（创建）一个类型，将Type的所有属性设置为readonly（只读）

```ts
interface Animal<T> {
    defalutName: T
}

type AnimalA = Readonly<Animal<string>>

/*
 type AnimalA = {
    readonly defalutName: string;
}
 */
```

- **`Pick<Type，Keys>`**从Type中选择一组属性来构造新类型。

```ts
interface Props {
    id: string
    title: string
    chiLdren: number
}

type PickProps = Pick<Props, 'id' | 'title'>

/*
 type PickProps = {
    id: string;
    title: string;
}
 */
```

- **`Record<keys,Type>`**构造一个对象类型，属性键为Keys，属性类型为Type。

```ts
type Records = Record<"a" | "b", string>
/*
type Records = {
    a: string;
    b: string;
}
 */
```



### 索引签名类型

当无法确定对象中存在那些属性（或者说对象中可以出现任意个属性），就可以使用到索引签名属性

```ts
interface AnyObject {
    [Key: string]: number
}

let a: AnyObject = {
    "a": 1,
    as: 12,
    sas: 12
}
```

解释：
1.使用`[key:string]`来约束该接口中允许出现的属性名称。表示只要是string类型的属性名称，都可以出现在对象中。
2.这样，对象obj中就可以出现任意多个属性（比如，a、b等）
3.key只是一个占位符，可以换成任意合法的变量名称。

隐藏的前置知识：**JS中对象的键是string类型的**。



### 映射类型

映射类型只能在`type`关键字，也就是类型别名中使用。

基于旧类型创建新类型，减少重复、提高开发效率。

```ts
//映射只能接收 string | number | symbol
//
type obj = 'x' | 'y' | 'z'
    
type type2 = {
    [Key in obj]: number
}
```

```

```



解释：

1. 映射类型是基于索引签名类型的，所以，该语法类似于索引签名类型，也使用了口。

2. KeyinPropkeys表示Key可以是Propkeys联合类型中的任意一个，类似于forin
3. 使用映射类型创建的新对象类型Type2和类型Type1结构完全相同。
4. 注意：映射类型只能在类型别名中使用，不能在接口中使用。



## 模块化	

### 导出

**导出声明**

任何声明（比如变量，函数，类，类型别名或接口）都能够通过添加`export`关键字来导出。

**Validation.ts**

```ts
export interface StringValidator {
    isAcceptable(s: string): boolean;
}
```

**ZipCodeValidator.ts**

```ts
export const numberRegexp = /^[0-9]+$/;

export class ZipCodeValidator implements StringValidator {
    isAcceptable(s: string) {
        return s.length === 5 && numberRegexp.test(s);
    }
}
```

**导出语句**

导出语句很便利，因为我们可能需要对导出的部分重命名，所以上面的例子可以这样改写：

```ts
class ZipCodeValidator implements StringValidator {
    isAcceptable(s: string) {
        return s.length === 5 && numberRegexp.test(s);
    }
}
export { ZipCodeValidator };
export { ZipCodeValidator as mainValidator };
```

**重新导出**

我们经常会去扩展其它模块，并且只导出那个模块的部分内容。 重新导出功能并不会在当前模块导入那个模块或定义一个新的局部变量。

**ParseIntBasedZipCodeValidator.ts**

```ts
export class ParseIntBasedZipCodeValidator {
    isAcceptable(s: string) {
        return s.length === 5 && parseInt(s).toString() === s;
    }
}

// 导出原先的验证器但做了重命名
export {ZipCodeValidator as RegExpBasedZipCodeValidator} from "./ZipCodeValidator";
```

或者一个模块可以包裹多个模块，并把他们导出的内容联合在一起通过语法：`export * from "module"`。

**AllValidators.ts**

```ts
export * from "./StringValidator"; // exports interface StringValidator
export * from "./LettersOnlyValidator"; // exports class LettersOnlyValidator
export * from "./ZipCodeValidator";  // exports class ZipCodeValidator
```

**默认导出**

每个模块都可以有一个`default`导出。 默认导出使用`default`关键字标记；并且一个模块只能够有一个`default`导出。 需要使用一种特殊的导入形式来导入`default`导出。







### 导入

模块的导入操作与导出一样简单。 可以使用以下`import`形式之一来导入其它模块中的导出内容。

```ts
import { ZipCodeValidator } from "./ZipCodeValidator";
let myValidator = new ZipCodeValidator();
```

可以对导入内容重命名

```ts
import { ZipCodeValidator as ZCV } from "./ZipCodeValidator";
let myValidator = new ZCV();
```

将整个模块导入到一个变量，并通过它来访问模块的导出部分

```ts
import * as validator from "./ZipCodeValidator";
let myValidator = new validator.ZipCodeValidator();
```

**别名**

另一种简化命名空间操作的方法是使用`import q = x.y.z`给常用的对象起一个短的名字。 不要与用来加载模块的`import x = require('name')`语法弄混了，这里的语法是为指定的符号创建一个别名。 你可以用这种方法为任意标识符创建别名，也包括导入的模块中的对象。

```ts
namespace Shapes {
    export namespace Polygons {
        export class Triangle { }
        export class Square { }
    }
}

import polygons = Shapes.Polygons;
let sq = new polygons.Square(); // Same as "new Shapes.Polygons.Square()"
```