//
//  DTXSocketConnection.h
//  DTXSocketConnection
//
//  Created by Leo Natan (Wix) on 18/07/2017.
//  Copyright © 2017 LeoNatan. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DTXSocketConnection;

@protocol DTXSocketConnectionDelegate <NSObject>

@optional

- (void)readClosedForSocketConnection:(DTXSocketConnection*)socketConnection;
- (void)writeClosedForSocketConnection:(DTXSocketConnection*)socketConnection;

@end

@interface DTXSocketConnection : NSObject

- (instancetype)initWithInputStream:(NSInputStream*)inputStream outputStream:(NSOutputStream*)outputStream queue:(nullable dispatch_queue_t)queue;
- (instancetype)initWithHostName:(NSString*)hostName port:(NSInteger)port queue:(nullable dispatch_queue_t)queue;

@property (nonatomic, nullable, weak) id<DTXSocketConnectionDelegate> delegate;

- (void)open;
- (void)closeRead;
- (void)closeWrite;

- (void)readDataWithCompletionHandler:(void (^)(NSData* __nullable data, NSError* __nullable error))completionHandler;
- (void)writeData:(NSData*)data withCompletionHandler:(void (^)(NSError* __nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
