//
//  BJLWhiteboardVM.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-08.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "BJLBaseVM.h"

/** NOTE: 如果改为 public
 - vm 内 _LP 开头的 model 等需要重新封装，参考
    BJLGiftVM.h、BJLGift.h、LPGift+BJLGift.h
    BJLDocumentVM.h、BJLDocument.h、LPDocument+BJLDocument.h
*/
#import "_LPShape.h"
#import "_LPResAllShapes.h"
#import "_LPResAddShape.h"
#import "_LPResDelShape.h"
#import "_LPResUpdateShapes.h"

NS_ASSUME_NONNULL_BEGIN

@interface BJLWhiteboardVM : BJLBaseVM

/** 请求某一页所有标注 */
- (nullable BJLError *)loadShapesWithDocumentID:(NSString *)documentID
                                      pageIndex:(NSUInteger)pageIndex;
/** 某一页所有标注加载完成通知 */
- (BJLObservable)didLoadShapes:(_LPResAllShapes *)loadShapesRes;

/** 添加标注 */
- (nullable BJLError *)addShape:(_LPShape *)shape
                     documentID:(NSString *)documentID
                      pageIndex:(NSUInteger)pageIndex;
/** 添加标注通知 */
- (BJLObservable)didAddShape:(_LPResAddShape *)addShapeRes;

/** 删除标注 */
- (nullable BJLError *)deleteShapeWithID:(NSString *)shapeID
                              documentID:(NSString *)documentID
                               pageIndex:(NSUInteger)pageIndex;
/** 删除标注通知 */
- (BJLObservable)didDeleteShape:(_LPResDelShape *)deleteShapeRes;

/** 修改标注 */
- (nullable BJLError *)updateShapes:(NSArray<_LPShape *> *)shapes
                         documentID:(NSString *)documentID
                          pageIndex:(NSUInteger)pageIndex;
/** 修改标注通知 */
- (BJLObservable)didUpdateShape:(_LPResUpdateShapes *)updateShapeRes;

@end

NS_ASSUME_NONNULL_END
