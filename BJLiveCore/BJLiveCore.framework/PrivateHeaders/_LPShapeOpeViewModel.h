//
//  _LPShapeGatherViewModel.h
//  BJLiveCore
//
//  Created by Randy on 16/4/22.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ReactiveCocoa/ReactiveCocoa.h>

#import "_BJLContext.h"
#import "_LPDocContext.h"

@interface _LPShapeOpeViewModel : NSObject

- (instancetype)initWithContext:(BJLContext *)context docContext:(_LPDocContext *)docContext;

@property (assign, nonatomic) NSInteger opeType;

@property (strong, readonly, nonatomic) RACSignal *opeInterruptSignal;

@property (strong, readonly, nonatomic) RACCommand *addShapeCommand;
@property (strong, readonly, nonatomic) RACCommand *clearShapesCommand;

@end
