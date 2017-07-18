//
//  BJLSlideshowVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-07.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

#import "BJLDocument.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLSlidePage : NSObject

@property (nonatomic, readonly) NSInteger slidePageIndex; // slidePageNumber = slidePageIndex + 1

@property (nonatomic, readonly, copy) NSString *documentID;
@property (nonatomic, readonly) NSInteger documentPageIndex;

@property (nonatomic, readonly, copy) NSString *pageURLString; // image
@property (nonatomic, readonly) NSInteger width, height;

@end

#pragma mark -

/**
 BJLDocument: 文档，主讲可能会上传多个文档，每个文档有一页或多页，每个文档内的 pageIndex 单独计算、从 0 开始
 BJLSlidePage: 幻灯片，将所有文档拆散、组成成幻灯片序列，文档的每一页对应一个幻灯片，所有幻灯片 slidePageIndex 整体计算、从 0 开始
 参考 `loadAllDocuments`
 */
@interface BJLSlideshowVM : BJLBaseVM

/** 所有文档 */
@property (nonatomic, readonly, copy, nullable) NSArray<BJLDocument *> *allDocuments;

/** `allDocuments` 被覆盖更新
 覆盖更新才调用，增量更新不调用
 */
- (BJLObservable)allDocumentsDidOverwrite:(nullable NSArray<BJLDocument *> *)allDocuments;

/** 加载所有文档
 连接房间后、掉线重新连接后自动调用加载
 加载成功后更新 `allDocuments`、调用 `allDocumentsDidOverwrite:`
 */
- (void)loadAllDocuments;

/** 添加文档通知
 同时更新 `allDocuments` */
- (BJLObservable)didAddDocument:(BJLDocument *)document;

/** 删除文档通知
 同时更新 `allDocuments` */
- (BJLObservable)didDeleteDocument:(BJLDocument *)document;

/** 文档总页数 */
@property (nonatomic, readonly) NSInteger totalPageCount;
/** 文档当前页信息 */
@property (nonatomic, readonly, nullable) BJLSlidePage *currentSlidePage;
/** 通过 documentID 获取 document */
- (nullable BJLDocument *)documentWithID:(NSString *)documentID;
/** 通过 documentID、pageIndex 获取 slide page */
- (nullable BJLSlidePage *)slidePageWithDocumentID:(NSString *)documentID pageIndex:(NSInteger)pageIndex;
/** 指定 fillSize，获取 slide pages */
- (NSArray<BJLSlidePage *> *)slidePagesWithFillSize:(CGSize)fillSize;

/** 翻页文档通知 */
- (BJLObservable)didTurnToSlidePage:(BJLSlidePage *)slidePage DEPRECATED_MSG_ATTRIBUTE("KVO `currentSlidePage` instead");

@end

NS_ASSUME_NONNULL_END
