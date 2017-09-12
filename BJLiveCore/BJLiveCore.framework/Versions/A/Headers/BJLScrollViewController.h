//
//  BJLScrollViewController.h
//  BJLiveCore
//
//  Created by MingLQ on 2017-03-06.
//  Copyright © 2017 Baijia Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BJLScrollViewController : UIViewController {
@protected
    UIScrollView *_scrollView;
}

@property (nonatomic, readonly) UIScrollView *scrollView;

@property (nonatomic, nullable) UIRefreshControl *refreshControl;

@end

NS_ASSUME_NONNULL_END
