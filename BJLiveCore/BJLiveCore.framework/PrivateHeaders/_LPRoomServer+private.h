//
//  _LPRoomServer+private.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/3/30.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPRoomServer.h"
@class RACSignal;

@interface _LPRoomServer (private)
- (RACSignal *)signalWithRegisterModelClass:(Class)modelClass
                                   selector:(SEL)selector
                                     resKey:(NSString *)resKey;
@end
