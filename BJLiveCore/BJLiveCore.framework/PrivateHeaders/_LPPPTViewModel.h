//
//  _LPPPTViewModel.h
//  BJLiveCore
//
//  Created by Randy on 16/4/11.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

#import "_LPConstants.h"
#import "_BJLContext.h"
#import "_LPDocContext.h"

@class _LPPPTImageViewModel;
@class _LPPPTShapesViewModel;

@class _LPDocPageItem;

@interface _LPPPTViewModel : NSObject

- (instancetype)initWithContext:(BJLContext *)context docContext:(_LPDocContext *)docContext;

/**
 *  先有shapes，再有imageUrls，添加观察者的时候请观察imageUrls
 */
@property (copy, readonly, nonatomic) NSArray<_LPPPTImageViewModel *> *imageUrls;
@property (copy, readonly, nonatomic) NSArray<_LPPPTShapesViewModel *> *shapes;
@property (assign, nonatomic) NSUInteger curPageIndex; // 学生可以更改 pageIndex。
@property (assign, readonly, nonatomic) _LPPPTMode showMode;
@property (assign, nonatomic) CGSize showSize;

@property (strong, readonly, nonatomic) RACCommand *changePageIndexCommand;

- (void)requestChangePageIndex:(NSUInteger)pageIndex;

- (CGRect)calculateImageFrameWithShowSize:(CGSize)showSize
                                imageSize:(CGSize)imageSize;
@end
