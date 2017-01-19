//
//  UIViewController+BJUtil.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-22.
//  Copyright © 2016年 Baijia Cloud. All rights reserved.
//

// #import <NBKit/NBKit.h>
#import <M9Dev/M9Dev.h>

#import "UIViewController+BJUtil.h"

#import "BJAppearance.h"

@implementation UIViewController (BJBack)

- (UIBarButtonItem *)barButtonItemWithTitle:(NSString *)title
                                     target:(id)target
                                     action:(SEL)action {
    return [[UIBarButtonItem alloc] initWithTitle:title
                                            style:UIBarButtonItemStylePlain
                                           target:target
                                           action:action];
}

- (UIBarButtonItem *)barButtonItemWithImage:(UIImage *)image
                                buttonClass:(Class)buttonClass
                                     target:(id)target
                                     action:(SEL)action {
    if (!buttonClass) {
        return [[UIBarButtonItem alloc] initWithImage:image
                                                style:UIBarButtonItemStylePlain
                                               target:target
                                               action:action];
    }
    
    NSAssert([buttonClass isSubclassOfClass:[UIButton class]],
             @"<#buttonClass#> must be a subclass of <#UIButton#>");
    if (![buttonClass isSubclassOfClass:[UIButton class]]) {
        return nil;
    }
    
    UIButton *backBarButton = ({
        UIButton *button = [[buttonClass alloc] initWithFrame:CGRectMake(0, 0, image.size.width, image.size.height)];
        button.tintColor = [UIBarButtonItem appearanceWhenContainedIn:[UINavigationBar class], nil].tintColor;
        /* if ([image respondsToSelector:@selector(imageWithRenderingMode:)]) {
            image = [image imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
        } */
        [button setImage:image forState:UIControlStateNormal];
        [button addTarget:target action:action forControlEvents:UIControlEventTouchUpInside];
        button;
    });
    return [[UIBarButtonItem alloc] initWithCustomView:backBarButton];
}

- (UIBarButtonItem *)backBarButtonItemWithTarget:(id)target action:(SEL)action {
    UIImage *image = [UIImage imageNamed:@"back-dark"];
    /* if ([image respondsToSelector:@selector(imageWithRenderingMode:)]) {
        image = [image imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    } */
    return [self barButtonItemWithImage:image
                            // buttonClass:[NBLeftBarButton class]
                            buttonClass:[UIButton class]
                                 target:target
                                 action:action];
}

- (void)setBackBarButtonItem {
    if (!self.navigationItem.leftBarButtonItem) {
        self.navigationItem.leftBarButtonItem = [self backBarButtonItemWithTarget:self
                                                                           action:@selector(popViewControllerAnimated)];
    }
}

- (UIBarButtonItem *)dismissBarButtonItemWithTarget:(id)target action:(SEL)action {
    UIImage *image = [UIImage imageNamed:@"back-dark"];
    /* if ([image respondsToSelector:@selector(imageWithRenderingMode:)]) {
        image = [image imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    } */
    return [self barButtonItemWithImage:image
                            // buttonClass:[NBLeftBarButton class]
                            buttonClass:[UIButton class]
                                 target:target
                                 action:action];
}

- (void)setDismissBarButtonItem {
    if (!self.navigationItem.leftBarButtonItem) {
        self.navigationItem.leftBarButtonItem = [self dismissBarButtonItemWithTarget:self
                                                                              action:@selector(dismissViewControllerAnimated)];
    }
}

@end

#pragma mark -

@implementation UIViewController (BJNavigation)

+ (void)showViewController:(UIViewController *)viewController
        fromViewController:(UIViewController *)fromViewController
                completion:(void (^)(void))completion {
    if (!viewController) {
        return;
    }
    UIViewController *top = fromViewController OR [UIViewController topViewController];
    UINavigationController *nav = [top as:[UINavigationController class]] OR top.navigationController;
    if (nav) {
        [nav pushViewController:viewController animated:YES completion:completion];
    }
    else {
        nav = [viewController wrapWithNavigationController]; // viewDidLoad?
        if (!viewController.viewLoaded) {
            [viewController view];
        }
        // set dismiss after viewDidLoad
        [viewController setDismissBarButtonItem];
        [top presentViewController:nav animated:YES completion:completion];
    }
}

@end
