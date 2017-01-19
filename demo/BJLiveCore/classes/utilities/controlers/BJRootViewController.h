//
//  BJRootViewController.h
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-22.
//  Copyright © 2016年 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BJRootViewController : UIViewController

+ (instancetype)sharedInstance;

@property (nonatomic, readonly) UIViewController *activeViewController;

- (void)switchViewController:(UIViewController *)viewController
                  completion:(void (^)(BOOL finished))completion;

@end
