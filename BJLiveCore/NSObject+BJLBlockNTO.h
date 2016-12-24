//
//  NSObject+BJLBlockNTO.h
//  M9Dev
//
//  Created by MingLQ on 2015-12-14.
//  Copyright © 2015年 MingLQ <minglq.9@gmail.com>. All rights reserved.
//

#import <Foundation/Foundation.h>

#define BJLOEvent void

#define BJLOEventType_isSEL 1
#if BJLOEventType_isSEL
    typedef SEL BJLOEventType;
    #define BJLOEventSend(DATA) [self bjl_notifyObserversWithEvent:_cmd data:DATA]
#else
    typedef NSString *BJLOEventType NS_EXTENSIBLE_STRING_ENUM;
    #define BJLOEventSend(DATA) [self bjl_notifyObserversWithEvent:NSStringFromSelector(_cmd) data:DATA]
#endif

typedef void (^BJLObserverBlock)(id data, id object, BJLOEventType event);

/**
 *  BJLBlock Observation implemented via a special NSNotificationCenter
 */

@interface NSObject (BJLBlockObserver)

- (void)bjl_observe:(id)object event:(BJLOEventType)event usingBlock:(BJLObserverBlock)block;

// auto called when dealloc
- (void)bjl_stopObserving:(id)object event:(BJLOEventType)event;
- (void)bjl_stopAllObserving;

@end

@interface NSObject (BJLBlockObservable)

- (void)bjl_notifyObserversWithEvent:(BJLOEventType)event;
- (void)bjl_notifyObserversWithEvent:(BJLOEventType)event data:(id)data;

@end
