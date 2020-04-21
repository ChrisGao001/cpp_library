### Go Study

### demo

```go
package main
import "fmt"

func main() {
  fmt.Println("hello world!")
}
```

### 库

| fmt     | 格式化输出 fmt.Println  fmt.Printf                   |
| ------- | ---------------------------------------------------- |
| strconv | 字符串转换   Atoi                                    |
| os      | os.Args获取输入参数                                  |
| testing | UT  func** TestSqrt1(t *testing.T) { t.Errorf("xxx") |

   

### 顺序编程

#### 变量

var** v1 int = 10 // 正确的使用方式1
var** v2 = 10 // 正确的使用方式2，编译器可以自动推导出v2的类型 v3 := 10 // 正确的使用方式3，编译器可以自动推导出v3的类型

**const** Pi float64 = 3.14159265358979323846  // 常量

#### 类型

Go语言内置以下这些基础类型:
  布尔类型:bool。
  整型:int8、byte、int16、int、uint、uintptr等。 

 浮点类型:float32、float64。

 复数类型:complex64、complex128。  字符串:string。
  字符类型:rune。
  错误类型:error。

此外，Go语言也支持以下这些复合类型:  指针(pointer)
  数组(array)
  切片(slice)

 字典(map)
 通道(chan)
 结构体(struct)  接口(interface)

#### 强制转换

fvalue1 = float32(fvalue2)

#### 字符串

\+ 拼接     len  长度   str[i]

#### 数组

```go
package main
import "fmt"

func main() {
  // arr := make([]int, 5, 10)  cap len
  var arr [5]int = [5]int{ 1, 2, 3, 4, 5} 
  for i:=0; i<len(arr); i+=1 {
    fmt.Println(i, arr[i])
  }
  for i,k in range arr {
    fmt.Println(i, k)
  }
}
```



#### map

```go
// create
id2age := make(map[int]int, 20)
// insert
id2age[2] = 3
// get
v,ok = id2age[5]
// delete
delete(id2age, 2)
```

### 面向对象编程

Go语言和C语言一样，类型都是基于值传递的。要想修改变量的值，只能 传递指针

```go
type Interger int
func (a *Integer) Add(b Integer) {
  *a += b
}
```

### 结构体

Go语言的结构体(struct)和其他语言的类(class)有同等的地位，但Go语言放弃了包括继 承在内的大量面向对象特性，只保留了组合(composition)这个最基础的特性。

要使某个符号对其他包(package)可见(即可以访问)，需要将该符号定义为以大写字母 开头



```go
type Rect struct { 
  x, y float64
  width, height float64 
}
// 类方法
func (rect *Rect)Area() float64 {
  return (rect.width * rect.height)
}
// 初始化
rect1 := new(Rect)
rect2 := &Rect{}
rect3 := &Rect{0, 0, 100, 200}
rect4 := &Rect{width: 100, height: 200}
```

### 并发编程

goroutine:协程并行化

channal：

渠道协程通信,channel是类型相关的。也就是说，一个channel只能传递一种类型的值.向channel写入数据通常会导致程序阻塞，直到有其他goroutine从这个channel中读取数据

```go
// create
ch := make(chan int)
// read
value := <-ch
select {
case <-ch:
// 从ch中读取到数据
case <-timeout:
// 一直没有从ch中读取到数据，但从timeout中读取到了数据
}
```

#### 同步

```go
var l sync.Mutex func foo() {
        l.Lock()
        defer l.Unlock()
        //...
}
```





 