//
//  UIKit+BJL_M9Dev.h
//  Pods
//
//  Created by MingLQ on 2016-04-21.
//
//

#import <UIKit/UIKit.h>
// #import <Masonry/Masonry.h>

static inline CGFloat bjl_screenFloor(CGFloat size) {
    CGFloat scale = [UIScreen mainScreen].scale;
    return floor(size * scale) / scale;
}

static inline CGFloat bjl_screenCeil(CGFloat size) {
    CGFloat scale = [UIScreen mainScreen].scale;
    return ceil(size * scale) / scale;
}

static inline CGRect bjl_fillFrameWithScale(CGRect frame, CGFloat scale) {
    CGFloat width = CGRectGetWidth(frame), height = CGRectGetHeight(frame);
    CGFloat innerHeight = width / scale;
    CGFloat innerWidth = height * scale;
    if (ABS(width - innerWidth) < 2
        || ABS(height - innerHeight) < 2) {
        return frame;
    }
    return CGRectMake(MIN(0, bjl_screenFloor((width - innerWidth) / 2)),
                      MIN(0, bjl_screenFloor((height - innerHeight) / 2)),
                      MAX(width, bjl_screenCeil(innerWidth)),
                      MAX(height, bjl_screenCeil(innerHeight)));
}

static inline CGRect bjl_fitFrameWithScale(CGRect frame, CGFloat scale) {
    CGFloat width = CGRectGetWidth(frame), height = CGRectGetHeight(frame);
    CGFloat innerHeight = width / scale;
    CGFloat innerWidth = height * scale;
    if (ABS(width - innerWidth) < 2
        || ABS(height - innerHeight) < 2) {
        return frame;
    }
    return CGRectMake(MAX(0, bjl_screenFloor((width - innerWidth) / 2)),
                      MAX(0, bjl_screenFloor((height - innerHeight) / 2)),
                      MIN(width, bjl_screenCeil(innerWidth)),
                      MIN(height, bjl_screenCeil(innerHeight)));
}

#pragma mark -

typedef BOOL (^BJL_M9ResponderFindingBlock)(UIResponder *responder, BOOL *stop);

@interface UIResponder (BJL_M9Dev)

- (UIResponder *)bjl_closestResponderOfClass:(Class)clazz; // NOT include self
- (UIResponder *)bjl_closestResponderOfClass:(Class)clazz includeSelf:(BOOL)includeSelf;
- (UIResponder *)bjl_findResponderWithBlock:(BJL_M9ResponderFindingBlock)enumerateBlock;

@end

#pragma mark -

@interface UIView (BJL_M9Dev)

- (__kindof UIView *)bjl_closestViewOfClass:(Class)clazz; // NOT include self
- (__kindof UIView *)bjl_closestViewOfClass:(Class)clazz includeSelf:(BOOL)includeSelf; // up to UIViewController
- (__kindof UIView *)bjl_closestViewOfClass:(Class)clazz includeSelf:(BOOL)includeSelf upToResponder:(UIResponder *)upToResponder; // not include the upToResponder, nil - up to UIViewController
- (__kindof UIViewController *)bjl_closestViewController;

- (void)bjl_removeAllConstraints;

@end

#pragma mark -

@interface UIViewController (BJL_M9Dev)

- (void)bjl_addChildViewController:(UIViewController *)childController superview:(UIView *)superview;
- (void)bjl_removeFromParentViewControllerAndSuperiew;

- (void)bjl_dismissAllViewControllersAnimated:(BOOL)animated completion:(void (^)(void))completion;

@end

#pragma mark - iOS7AutoCellSizing

@interface NSObject (bjl_iOS7AutoCellSizing)

+ (void)bjl_enable_iOS7AutoCellSizing;

@end

@protocol BJL_iOS7AutoCellSizingTableViewDelegate <UITableViewDelegate>

@property (nonatomic, strong) NSMutableDictionary *bjl_iOS7_cellsForCalculatingHeight;

- (NSString *)  bjl_iOS7_tableView:(UITableView *)tableView
  reuseIdentifierForRowAtIndexPath:(NSIndexPath *)indexPath;

/**
 *  WARNING: Don't call the table view's dequeueReusableCellWithIdentifier: method here
 *  because this will result in a memory leak as the cell is created but never returned from the
 *  tableView:cellForRowAtIndexPath: method!
 */
- (UITableViewCell *)bjl_iOS7_tableView:(UITableView *)tableView
                  cellForRowAtIndexPath:(NSIndexPath *)indexPath;

- (void)bjl_iOS7_tableView:(UITableView *)tableView
                updateCell:(UITableViewCell *)cell
         forRowAtIndexPath:(NSIndexPath *)indexPath;

@end

#pragma mark -

@interface UIColor (BJL_M9Dev)

// @"#FFFFFF"
+ (UIColor *)bjl_colorWithHexString:(NSString *)hexString;
// 0xFFFFFF
+ (UIColor *)bjl_colorWithHex:(unsigned)hex;

@end

#pragma mark -

@interface UIImage (BJL_M9Dev)

- (UIImage *)bjl_resizableImage;

+ (UIImage *)bjl_imageWithColor:(UIColor *)color;
+ (UIImage *)bjl_imageWithColor:(UIColor *)color size:(CGSize)size;

@end

/*
#pragma mark - Masonry

@interface MASConstraint (BJL_M9Dev)

- (MASConstraint *(^)(CGFloat))bjl_inset;

@end */
