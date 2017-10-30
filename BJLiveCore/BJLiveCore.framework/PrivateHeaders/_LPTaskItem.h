//
//  _LPTaskItem.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/4/13.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "_LPError.h"

@class _LPTaskQueue;

typedef NS_ENUM(NSUInteger, _LPTaskItemState) {
    _LP_TaskItem_state_Init = 0,
    _LP_TaskItem_state_Started  = 1,
    _LP_TaskItem_state_Completed  = 2,
    _LP_TaskItem_state_Cancelled  = 3,
};

@interface _LPTaskItem : NSObject

@property (nonatomic, strong, readonly) id result;
@property (nonatomic, strong, readonly) _LPError *error;

@property (nonatomic, assign, readonly) _LPTaskItemState state;

@property (nonatomic, weak) _LPTaskQueue *parent;
@property (nonatomic, weak) _LPTaskItem  *previous;
@property (nonatomic, strong) _LPTaskItem  *next;

- (void)execute NS_REQUIRES_SUPER;

/**
 *  执行成功
 *
 *  @param result <#result description#>
 */
- (void)setResult:(id)result;

/**
 *  执行失败
 *
 *  @param error <#error description#>
 */
- (void)setError: (_LPError *)error;

/**
 *  执行取消
 */
- (void)setCancel;

@end
