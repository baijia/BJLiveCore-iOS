//
//  BJLGift.h
//  Pods
//
//  Created by MingLQ on 2016-12-06.
//
//

#import <Foundation/Foundation.h>
#import <YYModel/YYModel.h>

#import "BJLConstants.h"
#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

@protocol BJLGift <NSObject>

@property (nonatomic, readonly) BJLGiftType type;
@property (nonatomic, readonly) NSString *price, *name;

@end

@protocol BJLReceivedGift <BJLGift>

@property (nonatomic, readonly) NSObject<BJLUser> *fromUser, *toUser;

@end

#pragma mark -

@interface BJLGift : NSObject <BJLGift, YYModel>

+ (instancetype)giftWithType:(BJLGiftType)type
                       price:(NSString *)price
                        name:(NSString *)name;

@end

NS_ASSUME_NONNULL_END