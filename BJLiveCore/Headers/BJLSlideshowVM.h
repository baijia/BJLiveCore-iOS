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
 BJLDocument: 课件，老师可能会上传多个课件，每个课件有一页或多页，每个课件内的 pageIndex 单独计算、从 0 开始
 BJLSlidePage: 幻灯片，将所有课件拆散、组成成幻灯片序列，课件的每一页对应一个幻灯片，所有幻灯片 slidePageIndex 整体计算、从 0 开始
 参考 `loadAllDocuments`
 */
@interface BJLSlideshowVM : BJLBaseVM

/** 所有课件 */
@property (nonatomic, readonly, nullable, copy) NSArray<NSObject<BJLDocument> *> *allDocuments;

/** `allDocuments` 被覆盖更新
 覆盖更新才调用，增量更新不调用
 */
- (BJLObservable)allDocumentsDidOverwrite:(nullable NSArray<NSObject<BJLDocument> *> *)allDocuments;

/** 通过 documentID 获取 document */
- (nullable NSObject<BJLDocument> *)documentWithID:(NSString *)documentID;
/** 通过 documentID、pageIndex 获取 slide page */
- (nullable BJLSlidePage *)slidePageWithDocumentID:(NSString *)documentID pageIndex:(NSInteger)pageIndex;

/** 加载所有课件
 连接教室后、掉线重新连接后自动调用加载
 加载成功后更新 `allDocuments`、调用 `allDocumentsDidOverwrite:`
 */
- (void)loadAllDocuments;

/** 添加课件通知
 同时更新 `allDocuments` */
- (BJLObservable)didAddDocument:(NSObject<BJLDocument> *)document;

/** 删除课件通知
 同时更新 `allDocuments` */
- (BJLObservable)didDeleteDocument:(NSObject<BJLDocument> *)document;

/** 翻页课件通知 */
- (BJLObservable)didTurnToSlidePage:(BJLSlidePage *)slidePage;

@end

NS_ASSUME_NONNULL_END
