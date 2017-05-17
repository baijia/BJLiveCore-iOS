//
//  BJLEmoticon.h
//  BJLiveUI
//
//  Created by MingLQ on 2017-04-12.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <YYModel/YYModel.h>

NS_ASSUME_NONNULL_BEGIN

@interface BJLEmoticon : NSObject <YYModel, NSCopying>

@property (nonatomic, readonly, copy) NSString *key, *name, *name_en;
@property (nonatomic, readonly) NSString *urlString;

@property (nonatomic) UIImage *cachedImage;

+ (nullable instancetype)emoticonForKey:(NSString *)key;

+ (NSArray<BJLEmoticon *> *)allEmoticons;
+ (void)setAllEmoticons:(NSArray<BJLEmoticon *> *)allEmoticons;

@end

NS_ASSUME_NONNULL_END
