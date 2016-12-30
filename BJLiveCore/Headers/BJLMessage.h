//
//  BJLMessage.h
//  Pods
//
//  Created by MingLQ on 2016-12-10.
//
//

#import <Foundation/Foundation.h>

#import "BJLUser.h"

NS_ASSUME_NONNULL_BEGIN

@protocol BJLMessage <NSObject>

@property (nonatomic, readonly) NSString *ID, *content;
@property (nonatomic, readonly) NSTimeInterval timeInterval; // seconds since 1970
@property (nonatomic, readonly) NSObject<BJLUser> *fromUser;

@end

NS_ASSUME_NONNULL_END
