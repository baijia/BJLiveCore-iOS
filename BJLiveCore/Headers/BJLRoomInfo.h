//
//  BJLRoomInfo.h
//  Pods
//
//  Created by MingLQ on 2016-12-05.
//
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

@end

NS_ASSUME_NONNULL_END
