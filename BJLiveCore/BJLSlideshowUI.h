//
//  BJLSlideshowUI.h
//  Pods
//
//  Created by MingLQ on 2016-12-19.
//
//

#import <Foundation/Foundation.h>

@protocol BJLSlideshowUI <NSObject>

/** 课件显示模式 */
@property (nonatomic) BJLSlideshowContentMode contentMode;
/** 开启、关闭白板（画笔） */
@property (nonatomic) BOOL whiteboardEnabled;

/** 学生本地翻页是否可以超过老师的进度 */
@property (nonatomic) BOOL studentCanPreviewForward;
/** 学生本地翻页是否可以同步到其他人
 设置为 YES 时将忽略 `studentCanPreviewForward` */
@property (nonatomic) BOOL studentCanRemoteControl;

/** 课件占位图 */
@property (nonatomic) UIImage *placeholderImage;

/** 清除白板 */
- (void)clearWhiteboard;

@end
