//
//  _LPRoomServer+LPBrush.h
//  BJLiveCore
//
//  Created by Randy on 16/4/28.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import "_LPBaseKit.h"

NS_ASSUME_NONNULL_BEGIN

@class _LPShape;

@interface _LPRoomServer (_LPBrush)

/**
 *  获取某一页的所有标注
 */
- (BOOL)requestAllShapeWithDocId:(NSString *)docId page:(NSUInteger)pageIndex;
/**
 *  _LPResAllShapes
 *
 *  @return
 */
- (RACSignal *)signalOfAllShapes;

/**
 *  添加标注
 */
- (BOOL)requestAddShape:(_LPShape *)shape docId:(NSString *)docId page:(NSUInteger)pageIndex;

/**
 *  自己发送标注触发 —— 避免从服务器走一遍回来再显示导致不能实时绘制
 *
 *  @return _LPResAddShape
 */
- (RACSignal *)signalOfMyAddShape;

/**
 *  添加标注触发
 *
 *  @return _LPResAddShape
 */
- (RACSignal *)signalOfAddShape;

/**
 *  移除标注
 *
 *  @param shapeId   shape 的标识 为空字符串时表示删除所有
 */
- (BOOL)requestDelShapeWithId:(NSString *)shapeId docId:(NSString *)docId page:(NSUInteger)pageIndex;

/**
 *  删除标注触发
 *
 *  @return _LPResDelShape
 */
- (RACSignal *)signalOfDelShape;

/**
 *  更新标注，批量更新
 */

- (BOOL)requestUpdateShapes:(NSArray<_LPShape *> *)list docId:(NSString *)docId page:(NSUInteger)pageIndex;

/**
 *  更新标注触发，多个标注
 *
 *  @return _LPResUpdateShape
 */
- (RACSignal *)signalOfUpdateShapes;

@end

NS_ASSUME_NONNULL_END
