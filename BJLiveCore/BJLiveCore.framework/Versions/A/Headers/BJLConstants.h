//
//  BJLConstants.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-26.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** 毫秒 */

typedef long long BJLMilliseconds;

#define BJL_MSEC_PER_SEC            1000ull
#define BJLMillisecondsSince1970    BJLMillisecondsFromTimeInterval(NSTimeIntervalSince1970)

NS_INLINE BJLMilliseconds BJLMillisecondsFromTimeInterval(NSTimeInterval timeInterval) {
    return (BJLMilliseconds)(timeInterval * BJL_MSEC_PER_SEC);
}

NS_INLINE NSTimeInterval BJLTimeIntervalFromMilliseconds(BJLMilliseconds milliseconds) {
    return (NSTimeInterval)milliseconds / BJL_MSEC_PER_SEC;
}

/** 部署环境 */
typedef NS_ENUM (NSInteger, BJLDeployType){
    /** 正式环境 */
    BJLDeployType_www,
    BJLDeployType_test,
    BJLDeployType_beta,
    _BJLDeployType_count
};

/** 用户角色 */
typedef NS_ENUM(NSInteger, BJLUserRole) {
    /** 学生 */
    BJLUserRole_student = 0,
    /** 老师 */
    BJLUserRole_teacher = 1,
    /** 助教 */
    BJLUserRole_assistant = 2,
    /** 游客 */
    BJLUserRole_guest = 3 // 内部使用
};

/** 教室类型 */
typedef NS_ENUM(NSInteger, BJLRoomType) {
    /** 1 对 1 */
    BJLRoomType_1to1 = 1,
    /** 多人班课 */
    BJLRoomType_1toN = 2
};

/** 客户端类型 */
typedef NS_ENUM(NSUInteger, BJLClientType) {
    /** PC 网页 */
    BJLClient_PCWeb = 0,
    /** PC 客户端 */
    BJLClient_PCApp = 1,
    /** M 站 */
    BJLClient_MobileWeb = 2,
    /** iOS 客户端 */
    BJLClient_iOSApp = 3,
    /** Android 客户端 */
    BJLClient_AndroidApp = 4
};

/** 媒体类型限制 */
typedef NS_ENUM(NSInteger, BJLMediaLimit) {
    /** 无限制 */
    BJLMediaLimit_none = 0,
    /** 只支持音频 */
    BJLMediaLimit_audioOnly = 1
};

/** 学生发言方式 */
typedef NS_ENUM(NSUInteger, BJLSpeakType) {
    /** 自由模式（一般在1对1模式下） */
    BJLSpeakType_free = 0,
    /** 限制模式。 默认值， 需要举手才能发言 */
    BJLSpeakType_limit = 1
};

/** 链路类型 */
typedef NS_ENUM(NSInteger, BJLLinkType) {
    /** TCP */
    BJLLinkType_TCP = 0,
    /** UDP */
    BJLLinkType_UDP = 1
};
NS_INLINE BOOL BJL_isValidLinkType(BJLLinkType linkType) {
    return linkType == BJLLinkType_TCP || linkType == BJLLinkType_UDP;
}

/** 视频清晰度 */
typedef NS_ENUM(NSInteger, BJLVideoDefinition) {
    /** 流畅 */
    BJLVideoDefinition_low,
    /** 高清 */
    BJLVideoDefinition_high,
    /** 默认 */
    BJLVideoDefinition_default = BJLVideoDefinition_low
};

/** 美颜 */
typedef NS_ENUM(NSInteger, BJLVideoBeautifyLevel) {
    BJLVideoBeautifyLevel0,
    BJLVideoBeautifyLevel1,
    BJLVideoBeautifyLevel2,
    BJLVideoBeautifyLevel3,
    BJLVideoBeautifyLevel4,
    BJLVideoBeautifyLevel5,
    /** 默认 */
    BJLVideoBeautifyLevel_default = BJLVideoBeautifyLevel0,
    /** 关闭 */
    BJLVideoBeautifyLevel_close = BJLVideoBeautifyLevel0,
    /** 最小 */
    BJLVideoBeautifyLevel_min = BJLVideoBeautifyLevel1,
    /** 最大 */
    BJLVideoBeautifyLevel_max = BJLVideoBeautifyLevel5
};

/** 课件显示模式 */
typedef NS_ENUM(NSInteger, BJLSlideshowContentMode) {
    /** 完整 */
    BJLSlideshowContentMode_scaleAspectFit,
    /** 铺满 */
    BJLSlideshowContentMode_scaleAspectFill
    /** 拉伸 */
    // BJLSlideshowContentMode_scaleToFill
};

/** 礼物类型 */
typedef NS_ENUM(NSInteger, BJLGiftType) {
    /** 可乐 */
    BJLGiftType_cola = 1,
    /** 咖啡 */
    BJLGiftType_coffee = 2,
    /** 橙汁 */
    BJLGiftType_orangeJuice = 3,
    /** 冰红茶 */
    BJLGiftType_tea = 4,
    /** 大麦茶 */
    BJLGiftType_barleyTea = 5
};

typedef NS_ENUM(NSInteger, BJLTextMaxLength) {
    BJLTextMaxLength_chat = 140,
    BJLTextMaxLength_notice = 140
};

#pragma mark -

static const NSInteger BJLAliIMGMaxSize = 4096;

/**
 Ali image url params - old
 #param fill    fill, or fit
 #param width   * scale <> 1-4096
 #param height  * scale <> 1-4096
 #param scale   0 - mainScreen.scale
 #param ext     jpg, png, webp, bmp, gif, src
 #return        url params
 e.g.
 http://image-demo.img-cn-hangzhou.aliyuncs.com/example.jpg@100h_100w_0c_1e_1l_2o_2x.jpg - fill > 300*200
 http://image-demo.img-cn-hangzhou.aliyuncs.com/example.jpg@100h_100w_0c_0e_1l_2o_2x.jpg - fit  > 200*134
 @see
 whcel: https://help.aliyun.com/document_detail/32223.html?spm=5176.doc32228.6.969.IvVprX
 o:     https://help.aliyun.com/document_detail/32231.html?spm=5176.doc32223.6.977.fTzBHO
 ext:   https://help.aliyun.com/document_detail/32244.html?spm=5176.doc32223.2.2.fTzBHO

static inline NSString *BJLAliIMGURLParams_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSInteger scale, NSString * _Nullable ext) {
    scale = MAX(1.0, scale <= 0 ? round([UIScreen mainScreen].scale) : scale);
    NSInteger max = MAX(width, height) * scale;
    if (max > BJLAliIMGMaxSize) {
        CGFloat maxScale = (CGFloat)BJLAliIMGMaxSize / max;
        width = floor(width * maxScale);
        height = floor(height * maxScale);
    }
    width = MAX(1.0, width);
    height = MAX(1.0, height);
    // w: width, h: height, x: scale, c: 0 - no cut, e: 0 - fit, 1 - fill, l: 1 - no enlarge, o: 2 - auto routate then resize
    NSString *params = [NSString stringWithFormat:@"@%tdw_%tdh_%tdx_0c_%de_1l_2o",
                        width, height, scale, fill];
    ext = ext.lowercaseString;
    return ext.length ? [params stringByAppendingPathExtension:ext] : params;
} */

/**
 Ali image url params
 x-oss-process=image/resize,m_mfit,w_100,h_100,limit_1/auto-orient,1/format,jpg
 /resize: m_lfit - aspect fit (default), m_mfit - aspect fill (no cut), w - width, h - height, limit_1 - no enlarge (default)
 /auto-orient: 1 - auto routate then resize (default?), 0 - resize without auto routate
 /format,jpg: jpg/png/webp/gif (lowercase!)
 https://help.aliyun.com/document_detail/44686.html?spm=5176.doc54739.3.2.kCK7Oh
 */
static inline NSString *BJLAliIMGURLParams_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSInteger scale, NSString * _Nullable ext) {
    scale = MAX(1.0, scale <= 0 ? round([UIScreen mainScreen].scale) : scale);
    width *= scale;
    height *= scale;
    NSInteger max = MAX(width, height);
    if (max > BJLAliIMGMaxSize) {
        CGFloat minify = (CGFloat)BJLAliIMGMaxSize / max;
        width = floor(width * minify);
        height = floor(height * minify);
    }
    width = MAX(1.0, width);
    height = MAX(1.0, height);
    ext = ext.lowercaseString;
    return [NSString stringWithFormat:@"image"
            "/resize,m_%@,w_%td,h_%td,limit_1"
            "/auto-orient,1"
            "/format,%@",
            fill ? @"mfit" : @"lfit", width, height,
            [@[@"jpg", @"png", @"webp", @"gif"] containsObject:ext] ? ext : @"jpg"];
}

static inline NSString *BJLAliIMGURLString_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSInteger scale, NSString *urlString, NSString * _Nullable ext) {
    NSString * const key = @"x-oss-process";

    NSURLComponents *components = [NSURLComponents componentsWithString:urlString];
    if (!components) {
        return urlString;
    }

    NSMutableArray *queryItems = [components.queryItems mutableCopy] ?: [NSMutableArray new];
    for (NSURLQueryItem *queryItem in components.queryItems) {
        if ([queryItem.name isEqualToString:key]) {
            [queryItems removeObject:queryItem];
        }
    }

    NSString *value = BJLAliIMGURLParams_aspectScale(fill, width, height, scale, ext ?: [urlString pathExtension]);
    NSURLQueryItem *queryItem = [NSURLQueryItem queryItemWithName:key value:value];
    [queryItems addObject:queryItem];
    components.queryItems = queryItems;

    NSRange range = [components.path rangeOfString:@"@" options:NSBackwardsSearch];
    if (range.location != NSNotFound) {
        components.path = [components.path substringToIndex:range.location];
    }

    return components.string;
}

static inline NSString *BJLAliIMG_aspectFill(CGSize size, CGFloat scale, NSString *urlString, NSString * _Nullable ext) {
    return BJLAliIMGURLString_aspectScale(YES, round(size.width), round(size.height), scale, urlString, ext);
}

static inline NSString *BJLAliIMG_aspectFit(CGSize size, CGFloat scale, NSString *urlString, NSString * _Nullable ext) {
    return BJLAliIMGURLString_aspectScale(NO, round(size.width), round(size.height), scale, urlString, ext);
}

NS_ASSUME_NONNULL_END
