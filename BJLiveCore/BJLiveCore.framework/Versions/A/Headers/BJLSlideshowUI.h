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

/** 文档显示模式
 只支持 BJLContentMode_scaleAspectFit, BJLContentMode_scaleAspectFill */
@property (nonatomic) BJLContentMode contentMode;

/** 文档占位图 */
@property (nonatomic) UIImage *placeholderImage;

/** 观众本地翻页是否可以超过房间内的页数 */
@property (nonatomic) BOOL studentCanPreviewForward;
/** 观众本地翻页是否可以同步到房间内的页数
 设置为 YES 时忽略 `studentCanPreviewForward` 的值、当 YES 处理 */
@property (nonatomic) BOOL studentCanRemoteControl;

/** 本地当前页、可能与房间内的页数不同
 参考 `BJLSlideshowVM` 的 `currentSlidePage.documentPageIndex` */
@property (nonatomic) NSInteger localPageIndex;
/** 是否空白
 只有一页白板、并且没有画笔 */
@property (nonatomic, readonly) BOOL isBlank;

/** 开启、关闭画笔（白板）
 开启画笔时，如果本地页数与服务端页数不同步的话无法绘制 */
@property (nonatomic) BOOL drawingEnabled;
/** 清除白板 */
- (void)clearDrawing;

@property (nonatomic) BOOL whiteboardEnabled DEPRECATED_MSG_ATTRIBUTE("use `drawingEnabled` instead");
- (void)clearWhiteboard DEPRECATED_MSG_ATTRIBUTE("use `clearDrawing` instead");

@end

NS_ASSUME_NONNULL_END
