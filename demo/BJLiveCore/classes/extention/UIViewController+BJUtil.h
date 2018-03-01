//
//  UIViewController+BJUtil.h
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-22.
//  Copyright © 2016年 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIViewController (BJBack)

- (UIBarButtonItem *)barButtonItemWithTitle:(NSString *)title
                                     target:(id)target
                                     action:(SEL)action;
- (UIBarButtonItem *)barButtonItemWithImage:(UIImage *)image
                                buttonClass:(Class)buttonClass
                                     target:(id)target
                                     action:(SEL)action;

// self.navigationItem.<#left#>BarButtonItem = ...
- (UIBarButtonItem *)backBarButtonItemWithTarget:(id)target action:(SEL)action;
- (void)setBackBarButtonItem;

// self.navigationItem.<#left#>BarButtonItem = ...
- (UIBarButtonItem *)dismissBarButtonItemWithTarget:(id)target action:(SEL)action;
- (void)setDismissBarButtonItem;

@end

@interface UIViewController (BJNavigation)

+ (void)showViewController:(UIViewController *)viewController
        fromViewController:(UIViewController *)fromViewController
                completion:(void (^)(void))completion;

@end
