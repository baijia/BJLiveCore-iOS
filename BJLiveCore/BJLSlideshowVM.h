//
//  BJLSlideshowVM.h
//  Pods
//
//  Created by MingLQ on 2016-12-07.
//
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
 */
@interface BJLSlideshowVM : BJLBaseVM

/** 所有课件
 参考 `- loadAllDocuments` */
@property (nonatomic, readonly, nullable, copy) NSArray<NSObject<BJLDocument> *> *allDocuments;

/** 通过 documentID 获取 document */
- (nullable NSObject<BJLDocument> *)documentWithID:(NSString *)documentID;
/** 通过 documentID、pageIndex 获取 slide page */
- (nullable BJLSlidePage *)slidePageWithDocumentID:(NSString *)documentID pageIndex:(NSInteger)pageIndex;

/** 加载所有课件
 加载成功后更新 `allDocuments`，内部不主动调用此方法 TODO: MingLQ - 主动调用，但 BJLSlideshowUI 可能会调用 */
- (void)loadAllDocuments;

/** 添加课件通知
 同时更新 `allDocuments` */
- (BJLOEvent)didAddDocument:(NSObject<BJLDocument> *)document;

/** 删除课件通知
 同时更新 `allDocuments` */
- (BJLOEvent)didDeleteDocument:(NSObject<BJLDocument> *)document;

/** 翻页课件通知 */
- (BJLOEvent)didTurnToSlidePage:(BJLSlidePage *)slidePage;

@end

NS_ASSUME_NONNULL_END
