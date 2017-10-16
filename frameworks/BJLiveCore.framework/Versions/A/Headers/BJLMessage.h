//
//  BJLMessage.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-10.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BJLUser.h"
#import "BJLEmoticon.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BJLMessageType) {
    BJLMessageType_text,
    BJLMessageType_emoticon,
    BJLMessageType_image
};

@interface BJLMessage : NSObject

@property (nonatomic, readonly) NSString *ID;
@property (nonatomic, readonly, nullable) NSString *channel;
@property (nonatomic, readonly) NSTimeInterval timeInterval; // seconds since 1970
@property (nonatomic, readonly) BJLUser *fromUser;

@property (nonatomic, readonly) BJLMessageType type;
@property (nonatomic, readonly, nullable) NSString *text; // BJLMessageType_text
@property (nonatomic, readonly, nullable) BJLEmoticon *emoticon; // BJLMessageType_emoticon
@property (nonatomic, readonly, nullable) NSString *imageURLString; // BJLMessageType_image
@property (nonatomic, readonly) CGFloat imageWidth, imageHeight; // BJLMessageType_image

+ (NSDictionary *)messageDataWithEmoticonKey:(NSString *)emoticonKey;
+ (NSDictionary *)messageDataWithImageURLString:(NSString *)imageURLString imageSize:(CGSize)imageSize;

+ (nullable NSString *)displayingStringWithData:(NSDictionary *)data;

@end

NS_ASSUME_NONNULL_END
