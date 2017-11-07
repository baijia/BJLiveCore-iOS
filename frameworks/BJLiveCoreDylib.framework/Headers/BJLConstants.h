//
//  BJLConstants.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-11-26.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/** WebSocket 请求超时时间 */
extern const NSTimeInterval BJLWebSocketTimeoutInterval;

/** 部署环境 */
typedef NS_ENUM(NSInteger, BJLDeployType){
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
    /** 小班课 */
    BJLRoomType_1toM = 3, // M: s[m]all
    /** 大班课 */
    BJLRoomType_1toN = 2
    // 小班课是 2、大班课是 3，没错
};

/** 客户端类型 */
typedef NS_ENUM(NSUInteger, BJLClientType) {
    /** PC 网页 */
    BJLClientType_PCWeb = 0,
    /** PC 客户端 */
    BJLClientType_PCApp = 1,
    /** M 站 */
    BJLClientType_MobileWeb = 2,
    /** iOS 客户端 */
    BJLClientType_iOSApp = 3,
    /** Android 客户端 */
    BJLClientType_AndroidApp = 4
};

/** 在线状态 */
typedef NS_ENUM(NSInteger, BJLOnlineState) {
    /** 在线 */
    BJLOnlineState_visible = 0,
    /** 隐身 */
    BJLOnlineState_invisible = 1,
    /** 离线 */
    BJLOnlineState_offline = 2 
};

/** 媒体类型限制 */
typedef NS_ENUM(NSInteger, BJLMediaLimit) {
    /** 无限制 */
    BJLMediaLimit_none = 0,
    /** 只支持音频 */
    BJLMediaLimit_audioOnly = 1
};

/** 链路类型 */
typedef NS_ENUM(NSInteger, BJLLinkType) {
    /** TCP */
    BJLLinkType_TCP = 0,
    /** UDP */
    BJLLinkType_UDP = 1
};
static inline BOOL BJLLinkTypeValidate(BJLLinkType linkType) {
    return linkType == BJLLinkType_TCP || linkType == BJLLinkType_UDP;
}
static inline BJLLinkType BJLLinkTypeValidify(BJLLinkType linkType) {
    return linkType == BJLLinkType_TCP ? BJLLinkType_TCP : BJLLinkType_UDP;
}

/** 视频方向 */
typedef NS_ENUM(NSInteger, BJLVideoOrientation) {
    /** 自动 - 使用设备方向 */
    BJLVideoOrientation_auto,
    /** 纵向 */
    BJLVideoOrientation_portrait,
    /** 横向 */
    BJLVideoOrientation_landscape
};

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
    BJLVideoBeautifyLevel_0,
    BJLVideoBeautifyLevel_1,
    BJLVideoBeautifyLevel_2,
    BJLVideoBeautifyLevel_3,
    BJLVideoBeautifyLevel_4,
    BJLVideoBeautifyLevel_5,
    BJLVideoBeautifyLevel_off = BJLVideoBeautifyLevel_0,
    BJLVideoBeautifyLevel_on  = BJLVideoBeautifyLevel_5,
    BJLVideoBeautifyLevel_default = BJLVideoBeautifyLevel_off
};

/** 课件显示模式 */
typedef NS_ENUM(NSInteger, BJLContentMode) {
    /** 完整 */
    BJLContentMode_scaleAspectFit,
    /** 铺满 */
    BJLContentMode_scaleAspectFill,
    /** 拉伸 */
    BJLContentMode_scaleToFill
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

#pragma mark - AliIMG

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
 */
static inline NSString *BJLAliIMGURLParams_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSInteger scale, NSString * _Nullable ext) {
    static const NSInteger aliIMGMaxSize = 4096;
    scale = MAX(1.0, scale <= 0 ? round([UIScreen mainScreen].scale) : scale);
    NSInteger max = MAX(width, height) * scale;
    if (max > aliIMGMaxSize) {
        CGFloat maxScale = (CGFloat)aliIMGMaxSize / max;
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
}

/*
 Ali image url params
 ?x-oss-process=image/resize,m_mfit,w_100,h_100,limit_1/auto-orient,1/format,jpg
 /resize: m_lfit - aspect fit (default), m_mfit - aspect fill (no cut), w - width, h - height, limit_1 - no enlarge (default)
 /auto-orient: 1 - auto routate then resize (default?), 0 - resize without auto routate
 /format,jpg: jpg/png/webp/gif (lowercase!)
 https://help.aliyun.com/document_detail/44686.html?spm=5176.doc54739.3.2.kCK7Oh
static inline NSString *BJLAliIMGURLParams_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSInteger scale, NSString * _Nullable ext) {
    scale = MAX(1.0, scale <= 0 ? round([UIScreen mainScreen].scale) : scale);
    width *= scale;
    height *= scale;
    static const NSInteger aliIMGMaxSize = 4096;
    NSInteger max = MAX(width, height);
    if (max > aliIMGMaxSize) {
        CGFloat minify = (CGFloat)aliIMGMaxSize / max;
        width = floor(width * minify);
        height = floor(height * minify);
    }
    width = MAX(1.0, width);
    height = MAX(1.0, height);
    ext = ext.lowercaseString;
    return [NSString stringWithFormat:@
            "?x-oss-process=image"
            "/resize,m_%@,w_%td,h_%td,limit_1"
            "/auto-orient,1"
            "/format,%@",
            fill ? @"mfit" : @"lfit", width, height,
            [@[@"jpg", @"png", @"webp", @"gif"] containsObject:ext] ? ext : @"jpg"];
} */

static inline NSString *BJLAliIMGURLString_aspectScale(BOOL fill, NSInteger width, NSInteger height, NSInteger scale, NSString *urlString, NSString * _Nullable ext) {
    NSUInteger atLocation = [urlString rangeOfString:@"@"].location;
    if (atLocation != NSNotFound) {
        urlString = [urlString substringToIndex:atLocation];
    }
    NSString *params = BJLAliIMGURLParams_aspectScale(fill, width, height, scale, ext ?: [urlString pathExtension]);
    return urlString.length ? [urlString stringByAppendingString:params] : params;
}

static inline NSString *BJLAliIMG_aspectFill(CGSize size, CGFloat scale, NSString *urlString, NSString * _Nullable ext) {
    return BJLAliIMGURLString_aspectScale(YES, round(size.width), round(size.height), scale, urlString, ext);
}

static inline NSString *BJLAliIMG_aspectFit(CGSize size, CGFloat scale, NSString *urlString, NSString * _Nullable ext) {
    return BJLAliIMGURLString_aspectScale(NO, round(size.width), round(size.height), scale, urlString, ext);
}

#pragma mark - AutoLayout Constraints

static inline void BJLConstrains_edgesEqual(id item, id targetItem, UIView *superview) {
    [superview addConstraints:@[[NSLayoutConstraint constraintWithItem:item
                                                        attribute:NSLayoutAttributeTop
                                                        relatedBy:NSLayoutRelationEqual
                                                           toItem:targetItem
                                                        attribute:NSLayoutAttributeTop
                                                       multiplier:1.0
                                                         constant:0.0],
                           [NSLayoutConstraint constraintWithItem:item
                                                        attribute:NSLayoutAttributeLeft
                                                        relatedBy:NSLayoutRelationEqual
                                                           toItem:targetItem
                                                        attribute:NSLayoutAttributeLeft
                                                       multiplier:1.0
                                                         constant:0.0],
                           [NSLayoutConstraint constraintWithItem:item
                                                        attribute:NSLayoutAttributeBottom
                                                        relatedBy:NSLayoutRelationEqual
                                                           toItem:targetItem
                                                        attribute:NSLayoutAttributeBottom
                                                       multiplier:1.0
                                                         constant:0.0],
                           [NSLayoutConstraint constraintWithItem:item
                                                        attribute:NSLayoutAttributeRight
                                                        relatedBy:NSLayoutRelationEqual
                                                           toItem:targetItem
                                                        attribute:NSLayoutAttributeRight
                                                       multiplier:1.0
                                                         constant:0.0]
                           ]];
}

NS_ASSUME_NONNULL_END
