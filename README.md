# FT_IRC

## Server configuration:

[Website wich helped me](https://ncona.com/2019/04/building-a-simple-server-with-cpp/)

### ```int	socket(int domain, int type, int protocol);```

We'll use the **socket** function to create a socket. A socket can be seen as a file
descriptor that can be used for communication.

> **"domain"** refers to the protocol the socket will use for communication
here we use IPv4 Internet protocols, so we need **AF_INET** arg.

> **"type"** specifies if the communication will be connectionless or persistent
not all ***types*** are compatible with all ***domains***.

> Normally there is only one **protocol** available for eache **type**,
so the value **0** can be used.

### ```int	bind(int sockfd, const sockaddr *addr, socklen_t addrlen);```

Once we have the socket, we need to use **bind** to assign an IP address
and port to the socket.

> Similar to **socket**, the function returns **-1** in case of error.
In case of success, it returns **0**.

> **sockfd** refers to the file descriptor we want to assign an adress to.
For us, it will be the file descriptor returned by **socket**.

> **addr** is a struct to specify the address we want to assign to the socket.
The exact struct that needs to be used to define the address, varies by protocol.
Since we are going to use IP for this server, we will use ***sockaddr_in***:

```
	struct sockaddr_in
	{
		sa_family_t		sin_family; /* address family: AF_INET for IPv4 */
		in_port_t		sin_port; /* port in network byte order */
		struct in_addr	sin_addr; /* internet address */
	};
```

> **addrlen** is just the **size()** of **addr**.

### ```int	listen(int sockfd, int backlog);```

Listen marks a socket as passive. The socket will be used to accept connections.

> Returns **-1** in case of error. In case of success, it returns 0.

> **sockfd** is the file descriptor of the socket.

> **backlog** is the maximum number of connections that will be queued before
connections start being refused.

### ```int	accept(int sockfd, sockaddr *addr, socklen_t *addrlen);```

**accept** extracts an element from a queue of connections (The queue created by listen)
for a socket.

> The function will return **-1** if there is an error. On success, it will return
a file descriptor for the connection.

> The argument list is similar to the one for **bind**, with one difference.
**addrlen** is now a value-result argument. It expects a pointer to an int
that will be the size of **addr**. After the function is executed, the int
refered by **addrlen** will be set to the size of the peer address.


Client:
	A client is anything connecting to a server that is not another
	server.  Each client is distinguished from other clients by a unique
	nickname having a maximum length of nine (9) characters.  See the
	protocol grammar rules for what may and may not be used in a
	nickname.  In addition to the nickname, all servers must have the
	following information about all clients: the real name of the host
	that the client is running on, the username of the client on that
	host, and the server to which the client is connected.

Channels:
	A channel is a named group of one or more clients which will all
	receive messages addressed to that channel.  The channel is created
	implicitly when the first client joins it, and the channel ceases to
	exist when the last client leaves it.  While channel exists, any
	client can reference the channel using the name of the channel.
	
	Channels names are strings (beginning with a '&' or '#' character) of
	length up to 200 characters.  Apart from the requirement that the
	first character being either '&' or '#'; the only restriction on a
	channel name is that it may not contain any spaces (' '), a control G
	(^G or ASCII 7), or a comma (',' which is used as a list item
	separator by the protocol).

	To create a new channel or become part of an existing channel, a user
	is required to JOIN the channel.  If the channel doesn't exist prior
	to joining, the channel is created and the creating user becomes a
	channel operator.  If the channel already exists, whether or not your
	request to JOIN that channel is honoured depends on the current modes
	of the channel. For example, if the channel is invite-only, (+i),
	then you may only join if invited.  As part of the protocol, a user
	may be a part of several channels at once, but a limit of ten (10)
	channels is recommended as being ample for both experienced and
	novice users.

	