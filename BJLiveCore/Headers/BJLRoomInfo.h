//
//  BJLRoomInfo.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-05.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BJLConstants.h"

NS_ASSUME_NONNULL_BEGIN

@protocol BJLRoomInfo <NSObject>

@property (nonatomic, readonly) NSString *ID, *title;
@property (nonatomic, readonly) NSTimeInterval startTimeInterval, endTimeInterval;

@property (nonatomic, readonly) BJLRoomType roomType;
@property (nonatomic, readonly) BJLMediaLimit mediaLimit;

@property (nonatomic, readonly) NSString *partnerID;
@property (nonatomic, readonly, nullable) NSString *customerSupportMessage;

@end

NS_ASSUME_NONNULL_END
