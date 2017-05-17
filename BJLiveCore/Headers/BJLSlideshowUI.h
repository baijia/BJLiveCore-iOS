//
//  BJLSlideshowUI.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-19.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol BJLSlideshowUI <NSObject>

/** 课件显示模式
 只支持 BJLContentMode_scaleAspectFit, BJLContentMode_scaleAspectFill */
@property (nonatomic) BJLContentMode contentMode;

/** 本地当前页、可能与教室内的页数不同，参考 `BJLSlideshowVM` 的 `currentSlidePage.documentPageIndex` */
@property (nonatomic, readonly) NSInteger localPageIndex;
/** 学生本地翻页是否可以超过教室内的页数 */
@property (nonatomic) BOOL studentCanPreviewForward;
/** 学生本地翻页是否可以同步到教室内的页数
 设置为 YES 时忽略 `studentCanPreviewForward` 的值、当 YES 处理 */
@property (nonatomic) BOOL studentCanRemoteControl;

/** 课件占位图 */
@property (nonatomic) UIImage *placeholderImage;

/** 开启、关闭白板（画笔）
 开启画笔时，如果本地页数与服务端页数不同步的话无法绘制 */
@property (nonatomic) BOOL drawingEnabled;
@property (nonatomic) BOOL whiteboardEnabled DEPRECATED_MSG_ATTRIBUTE("use `drawingEnabled` instead");
/** 清除白板 */
- (void)clearDrawing;
- (void)clearWhiteboard DEPRECATED_MSG_ATTRIBUTE("use `clearDrawing` instead");

@end

NS_ASSUME_NONNULL_END
