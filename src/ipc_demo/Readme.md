**Unix domain socket 又叫 IPC(inter-process communication 进程间通信) socket，用于实现同一主机上的进程间通信。**socket 原本是为网络通讯设计的，但后来在 socket 的框架上发展出一种 IPC 机制，就是 UNIX domain socket。虽然网络 socket 也可用于同一台主机的进程间通讯(通过 loopback 地址 127.0.0.1)，但是 UNIX domain socket 用于 IPC 更有效率：不需要经过网络协议栈，不需要打包拆包、计算校验和、维护序号和应答等，只是将应用层数据从一个进程拷贝到另一个进程。这是因为，IPC 机制本质上是可靠的通讯，而网络协议是为不可靠的通讯设计的。
UNIX domain socket 是全双工的，API 接口语义丰富，相比其它 IPC 机制有明显的优越性，目前已成为使用最广泛的 IPC 机制，比如 X Window 服务器和 GUI 程序之间就是通过 UNIX domain socket 通讯的。
Unix domain socket 是 POSIX 标准中的一个组件，所以不要被名字迷惑，linux 系统也是支持它的。

通过一个简单的 demo 来理解相关概念。程序分为服务器端和客户端两部分，它们之间通过 unix domain socket 进行通信。

server.c

使用 UNIX domain socket 的过程和网络 socket 十分相似，也要先调用 socket() 创建一个 socket 文件描述符.
**family** 指定为 AF_UNIX，使用 AF_UNIX 会在系统上创建一个 socket 文件，不同进程通过读写这个文件来实现通信。
**type** 可以选择 SOCK_DGRAM 或 SOCK_STREAM。SOCK_STREAM 意味着会提供按顺序的、可靠、双向、面向连接的比特流。SOCK_DGRAM 意味着会提供定长的、不可靠、无连接的通信。
**protocol** 参数指定为 0 即可。
UNIX domain socket 与网络 socket 编程最明显的不同在于地址格式不同，用结构体 sockaddr_un 表示，网络编程的 socket 地址是 IP 地址加端口号，而 UNIX domain socket 的地址是一个 socket 类型的文件在文件系统中的路径，这个 socket 文件由 bind() 调用创建，如果调用 bind() 时该文件已存在，则 bind() 错误返回。因此，一般在调用 bind() 前会检查 socket 文件是否存在，如果存在就删除掉。
网络 socket 编程类似，在 bind 之后要 listen，表示通过 bind 的地址（也就是 socket 文件）提供服务。
接下来必须用 accept() 函数初始化连接。accept() 为每个连接创立新的套接字并从监听队列中移除这个连接。

client.c

与网络 socket 编程不同的是，UNIX domain socket 客户端一般要显式调用 bind 函数，而不依赖系统自动分配的地址。客户端 bind 一个自己指定的 socket 文件名的好处是，该文件名可以包含客户端的 pid 等信息以便服务器区分不同的客户端。

Run:

```
$ gcc server.c -o server
$ gcc client.c -o client
```