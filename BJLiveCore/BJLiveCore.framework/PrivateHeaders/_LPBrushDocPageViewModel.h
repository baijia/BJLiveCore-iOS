//
//  _LPBrushDocPageViewModel.h
//  BJLiveCore
//
//  Created by Randy on 16/4/27.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

#import "_BJLContext.h"
#import "_LPDocContext.h"

@interface _LPBrushDocPageViewModel : NSObject

- (instancetype)initWithContext:(BJLContext *)context docContext:(_LPDocContext *)docContext;

@property (assign, readonly, nonatomic) NSUInteger curPageIndex;
@property (assign, readonly, nonatomic) NSUInteger maxPageIndex;

@property (strong, readonly, nonatomic) RACCommand *backPageCommand;
@property (strong, readonly, nonatomic) RACCommand *nextPageCommand;

@end
