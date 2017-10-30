//
//  _LPMessage.h
//  BJLiveCore
//
//  Created by 杨磊 on 16/5/3.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "_LPUser.h"
#import "_LPDataModel.h"
/**
 *  聊天 message
 */
@interface _LPMessage : _LPDataModel

@property (nonatomic, copy) NSString *messageId;
@property (nonatomic, assign) NSTimeInterval time;
@property (nonatomic, copy) NSString *content, *channel;
@property (nonatomic, strong) _LPUser *fromUser;

@end
