# DTXSocketConnection
A simple socket connection framework for two–way peer–to–peer communication.

The framework is intended to be used in conjunction with [`NSNetService`](https://developer.apple.com/documentation/foundation/nsnetservice?language=objc) and [`NSNetServiceBrowser`](https://developer.apple.com/documentation/foundation/nsnetservicebrowser?language=objc) to create communication between two peers.

### Using

Add `DTXSocketConnection.xcodeproj` to your project. In your target's settings, add `DTXSocketConnection ` to embedded binaries.

Import the framework's umbrella header:

```objc
#import <DTXSocketConnection/DTXSocketConnection.h>
```

#### Opening Connection

##### Server

```objc
- (void)netService:(NSNetService *)sender didAcceptConnectionWithInputStream:(NSInputStream *)inputStream outputStream:(NSOutputStream *)outputStream
{
	_socketConnection = [[DTXSocketConnection alloc] initWithInputStream:inputStream outputStream:outputStream queue:_socketQueue];
	_socketConnection.delegate = self;
	[_socketConnection open];
}
```

##### Client

```objc
- (void)netServiceDidResolveAddress:(NSNetService *)sender
{
	_socketConnection = [[DTXSocketConnection alloc] initWithHostName:sender.hostName port:sender.port queue:_socketQueue];
	_socketConnection.delegate = self;
	[_socketConnection open];
}
```

#### Reading Data

```objc
[_socketConnection readDataWithCompletionHandler:^(NSData * _Nullable data, NSError * _Nullable error) {
	if(error)
	{
		NSLog(@"Read error: %@", error);
		return;
	}
		
	NSLog(@"Read data: %@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
}];
```

#### Writing Data

```objc
NSString* str = [NSString stringWithFormat:@"The time is: %@", [NSDateFormatter localizedStringFromDate:[NSDate date] dateStyle:NSDateFormatterShortStyle timeStyle:NSDateFormatterShortStyle]];
NSData* data = [str dataUsingEncoding:NSUTF8StringEncoding];
[_socketConnection writeData:data completionHandler:^(NSError * _Nullable error) {	
	if(error)
	{
		NSLog(@"Write error: %@", error);
		return;
	}
	
	NSLog(@"Successfully wrote data");
}];

```

