//
//  BJLMessage.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-10.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BJLUser.h"
#import "BJLEmoticon.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BJLMessageContentType) {
    BJLMessageContentType_text,
    BJLMessageContentType_emoticon,
    BJLMessageContentType_image
};

@interface BJLMessage : NSObject <YYModel>

@property (nonatomic, readonly) NSString *ID, *content;
@property (nonatomic, readonly, nullable) NSString *channel;
@property (nonatomic, readonly) NSTimeInterval timeInterval; // seconds since 1970
@property (nonatomic, readonly) BJLUser *fromUser;

@property (nonatomic, readonly) BJLMessageContentType contentType;
@property (nonatomic, readonly, nullable) BJLEmoticon *emoticon; // BJLMessageContentType_emoticon
@property (nonatomic, readonly, nullable) NSString *imageURLString; // BJLMessageContentType_image

+ (NSString *)messageStringWithEmoticon:(BJLEmoticon *)emoticon;
+ (NSString *)messageStringWithImageURLString:(NSString *)imageURLString;

@end

NS_ASSUME_NONNULL_END
