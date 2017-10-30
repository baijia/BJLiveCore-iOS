//
//  _LPTaskQueue.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/4/13.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@class _LPTaskQueue;
@class _LPTaskItem;
@protocol _LPTaskQueueDelegate <NSObject>

@required
- (void)taskQueueWillStart:(_LPTaskQueue *)taskQueue;
- (BOOL)taskQueueShouldContinue:(_LPTaskQueue *)taskQueue currentTask:(_LPTaskItem *)taskItem;

- (void)taskQueueDidCompleted:(_LPTaskQueue *)taskQueue;
@end

@class _LPTaskItem;
@interface _LPTaskQueue : NSObject

@property (nonatomic, readonly, assign) NSInteger count;
@property (nonatomic, weak) id<_LPTaskQueueDelegate> delegate;

- (void)add:(_LPTaskItem *)task;

- (void)start;

- (void)resume;

- (void)restart;

- (void)clear;

@end
