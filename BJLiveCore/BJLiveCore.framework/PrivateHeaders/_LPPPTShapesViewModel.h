//
//  _LPPPTBrushViewModel.h
//  BJLiveCore
//
//  Created by Randy on 16/4/27.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

#import "_BJLContext.h"
#import "_LPDocContext.h"

@class _LPLayer;

@interface _LPPPTShapesViewModel : NSObject

/**
 *  只有在获取时生成最新的数据，所以不能观察此变化
 */
@property (copy, readonly, nonatomic) NSArray<_LPLayer *> *layers;

@property (strong, readonly, nonatomic) RACSignal *shapesAddedSignal;
@property (strong, readonly, nonatomic) RACSignal *shapesDeletedSignal;

- (instancetype)initWithPageIndex:(NSUInteger)pageIndex context:(BJLContext *)context docContext:(_LPDocContext *)docContext;

- (void)updateShowSize:(CGSize)showSize;

@end
