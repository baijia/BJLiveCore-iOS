//
//  BJLGift.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-06.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BJLConstants.h"
#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

@protocol BJLGift <NSObject>

@property (nonatomic, readonly) BJLGiftType type;
@property (nonatomic, readonly) NSString *price, *name;

@end

@protocol BJLReceivedGift <BJLGift>

@property (nonatomic, readonly) BJLUser *fromUser, *toUser;

@end

#pragma mark -

@interface BJLGift : NSObject <BJLGift>

+ (instancetype)giftWithType:(BJLGiftType)type
                       price:(NSString *)price
                        name:(NSString *)name;

@end

NS_ASSUME_NONNULL_END
