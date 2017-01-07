Blocks
======

为了开发方便，这里大量的使用了 `block`（`RAC` 本是个很好的选择，但为避免依赖过多的第三方库而被放弃）；

##### 1. Block KVO

- KVO 调用方式，支持 filter - 可选：
```objc
weakdef(self);
[self bjl_kvo:BJLMakeProperty(self.room.roomVM, // 对象
                              liveStarted) // 属性名，支持代码自动完成
       filter:^BOOL(NSNumber *old, NSNumber *now) { // 过滤
           return old.boolValue != now.boolValue;  // 返回 NO 丢弃
       }
     observer:^BOOL(NSNumber *old, NSNumber *now) { // 处理
       strongdef(self);
       [self.console printFormat:@"liveStarted: %@", NSStringFromBOOL(now.boolValue)];
       return YES; // 返回 NO 停止监听
   }];
```

- 支持两种方式取消某次 KVO；
```objc
weakdef(self);
id<BJLObservation> observation =
    [self bjl_kvo:BJLMakeProperty(self.room.roomVM, liveStarted)
         observer:^BOOL(NSNumber *old, NSNumber *now) {
           strongdef(self);
           [self.console printFormat:@"liveStarted: %@", NSStringFromBOOL(now.boolValue)];
           return YES; // 1. 返回 NO 取消 KVO
       }];
[observation stopObserving]; // 2. 取消 KVO
```

##### 2. Block 监听方法调用

- 监听方法调用，支持 filter - 可选：
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room, // 对象
                                roomWillExitWithError:) // 方法
           filter:(BJLMethodFilter)^BOOL(BJLError *error) { // 过滤
               return !!error; // 返回 NO 丢弃
           }];
         observer:(BJLMethodObserver)^BOOL(BJLError *error) { // 处理
             strongdef(self);
             [self.console printFormat:@"roomWillExitWithError: %@", error];
             return YES; // 返回 NO 停止监听
         }];
```

- 支持 **简单类型参数**：
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, speakingBeRemoteEnabled:)
         observer:(BJLMethodObserver)^BOOL(BOOL enabled) {
             [self.console printFormat:@"发言状态被%@", enabled ? @"开启" : @"关闭"];
             return YES;
         }];
```

- 支持 **多个参数**：
```objc
weakdef(self);
[self bjl_observe:BJLMakeMethod(self.room.playingVM, playingUserDidUpdate:old:)
         observer:^BOOL(NSObject<BJLOnlineUser> *old,
                        NSObject<BJLOnlineUser> *now) {
             strongdef(self);
             [self.console printFormat:@"playingUserDidUpdate:old: %@ >> %@", old, now];
         }];
```

- 支持两种方式取消某次监听；
```objc
weakdef(self);
id<BJLObservation> observation =
    [self bjl_observe:BJLMakeMethod(self.room, roomWillExitWithError:)
             observer:(BJLMethodObserver)^BOOL(BJLError *error) {
                 strongdef(self);
                 [self.console printFormat:@"roomWillExitWithError: %@", error];
                 return YES; // 1. 返回 NO 取消监听
             }];
[observation stopObserving]; // 2. 取消监听
```

##### 3. Block 模拟元组

- 支持使用 **简单类型参数** 和 **多个参数**；
```objc
// 定义: 此方法返回一个包含两个 BOOL 型变量的元组
- (BJLTuple<void (^)(BOOL state1, BOOL state2> *)states;
```
```objc
// 拆包: 这个 block 会被立即执行，因此这里不需要 weakify&strongify
BJLTupleUnpack(tuple) = ^(BOOL state1, BOOL state2) {
    NSLog(@"state1: %d, state2: %d", state1, state2);
};
```

