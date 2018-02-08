//
//  BJLSlideshowVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-07.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLDocument.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLSlidePage : NSObject

@property (nonatomic, readonly) NSInteger slidePageIndex; // slidePageNumber = slidePageIndex + 1

@property (nonatomic, readonly, copy) NSString *documentID;
@property (nonatomic, readonly) NSInteger documentPageIndex; // maybe incorrect if allDocuments changed

@property (nonatomic, readonly, copy) NSString *pageURLString; // image
@property (nonatomic, readonly) NSInteger width, height;

/**
 size:  CGSizeMake(1280.0, 720.0) || CGSizeMake(1920.0, 1080.0) || CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)
 fill:  fill, or fit
 ext:   jpg, png, webp, bmp, gif, src
 */
- (nullable NSString *)pageURLStringWithSize:(CGSize)size
                                        fill:(BOOL)fill
                                      format:(nullable NSString *)ext;

@end

#pragma mark -

/**
 ### 课件显示
 #discussion BJLDocument：课件，教室内默认至少有一个白板课件，老师可能会上传多个课件，每个课件有一页或多页，每个课件内的 pageIndex 单独计算、从 0 开始
 #discussion BJLSlidePage：幻灯片，将所有课件拆散、组成成幻灯片序列，课件的每一页对应一个幻灯片，所有幻灯片 slidePageIndex 整体计算、从 0 开始
 #discussion 参考 `loadAllDocuments`
 */
@interface BJLSlideshowVM : BJLBaseVM

/** 所有课件 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLDocument *> *allDocuments;

/** `allDocuments` 被覆盖更新
 #discussion 覆盖更新才调用，增量更新不调用
 #param allDocuments 所有课件
 */
- (BJLObservable)allDocumentsDidOverwrite:(nullable NSArray<BJLDocument *> *)allDocuments;

/** 加载所有课件
 #discussion 连接教室后、掉线重新连接后自动调用加载
 #discussion 加载成功后更新 `allDocuments`、调用 `allDocumentsDidOverwrite:`
 */
- (void)loadAllDocuments;

/** 添加课件通知
 #discussion 同时更新 `allDocuments`
 #param document 课件
 */
- (BJLObservable)didAddDocument:(BJLDocument *)document;

/** 删除课件通知
 #discussion 同时更新 `allDocuments`
 #param document 课件
 */
- (BJLObservable)didDeleteDocument:(BJLDocument *)document;

/** 课件总页数 */
@property (nonatomic, readonly) NSInteger totalPageCount;

/** 课件当前页信息 */
@property (nonatomic, readonly, nullable) BJLSlidePage *currentSlidePage;

/** 通过 documentID 获取 document
 #param documentID 课件 ID
 */
- (nullable BJLDocument *)documentWithID:(NSString *)documentID;

/** 通过 documentID、pageIndex 获取 slide page
 #param documentID 课件 ID
 #param pageIndex 目标页在课件中的序号
 */
- (nullable BJLSlidePage *)slidePageWithDocumentID:(NSString *)documentID
                                         pageIndex:(NSInteger)pageIndex;

/** 获取 slide pages */
- (NSArray<BJLSlidePage *> *)allSlidePages;

- (NSArray<BJLSlidePage *> *)slidePagesWithFillSize:(CGSize)fillSize DEPRECATED_MSG_ATTRIBUTE("use `self - allSlidePages` and `BJLSlidePage - pageURLStringWithSize:fill:format:`");

@end

NS_ASSUME_NONNULL_END
