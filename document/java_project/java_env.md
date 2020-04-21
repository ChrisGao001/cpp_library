## maven编译环境

1. 环境设置

   ```shell
   # package download from https://maven.apache.org/download.cgi
   yum install -y java
   wget http://apache.fayea.com/maven/maven-3/3.3.9/binaries/apache-maven-3.3.9-bin.tar.gz
   # install maven
   tar vxf apache-maven-3.2.3-bin.tar.gz
   mv apache-maven-3.2.3 /usr/local/maven3
   # set env
   在/etc/profile中添加以下几行
   MAVEN_HOME=/usr/local/maven3
   export MAVEN_HOME
   export PATH=${PATH}:${MAVEN_HOME}/bin
   
   source /etc/profile
   # 验证maven是否安装成功
   mvn -v
   ```

2. mvn命令

   ```shell
   mvn compile  #编译
   mvn package  #编包
   mvn exec:java -Dexec.mainClass="hello.HelloWorld" #运行类
   java -jar target/gs-maven-0.1.0.jar #运行jar包
   mvn install #安装
   ```

3. 案例

   Refer:https://www.cnblogs.com/mafeng/p/8405364.html

   + 无外部依赖

     1. 创建pom.xml

        ```xml
        <?xml version="1.0" encoding="UTF-8"?>
        <project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/maven-v4_0_0.xsd">
            <modelVersion>4.0.0</modelVersion>
            <groupId>org.springframework</groupId>
            <artifactId>gs-maven</artifactId>
            <packaging>jar</packaging>
            <version>0.1.0</version>
        
            <build>
                <plugins>
                    <plugin>
                        <groupId>org.apache.maven.plugins</groupId>
                        <artifactId>maven-shade-plugin</artifactId>
                        <version>2.1</version>
                        <executions>
                            <execution>
                                <phase>package</phase>
                                <goals>
                                    <goal>shade</goal>
                                </goals>
                                <configuration>
                                    <transformers>
                                        <transformer
                                            implementation="org.apache.maven.plugins.shade.resource.ManifestResourceTransformer">
                                            <mainClass>hello.HelloWorld</mainClass>
                                        </transformer>
                                    </transformers>
                                </configuration>
                            </execution>
                        </executions>
                    </plugin>
                </plugins>
            </build>
        </project>
        ```

        

     2. 编写程序

        ```java
        cat src/main/java/hello/HelloWorld.java
        package hello;
        
        public class HelloWorld {
            public static void main(String[] args) {
                System.out.println("hello world");
            }
        
        }
        ```

        

     3. 编译

        ```shell
        mvn compile  #编译
        mvn package  #编包
        ```

     4. 运行

        ```shell
        java -jar target/gs-maven-0.1.0.jar #运行jar包
        ```

        

   + 有外部依赖

     1. 修改pom.xml增加dependency

        ```xml
        <dependencies>
            <dependency>
                <groupId>joda-time</groupId>
                <artifactId>joda-time</artifactId>
                <version>2.2</version>
            </dependency>
        </dependencies>
        
        <groupId> ： 该依赖库所属的组织名称
        <artifactId> ： 依赖的库名
        <version> ： 依赖的库版本
        ```

        ```java
        package hello;
        
        import org.joda.time.LocalTime;
        
        public class HelloWorld {
            public static void main(String[] args) {
                LocalTime currentTime = new LocalTime();
                System.out.println("The current local time is: " + currentTime);
                Greeter greeter = new Greeter();
                System.out.println(greeter.sayHello());
            }
        }
        ```

        

     2. 编译

     3. 运行