//
//  BJPlayingView.m
//  BJLiveCore
//
//  Created by HuangJie on 2017/9/11.
//  Copyright © 2017年 BaijiaYun. All rights reserved.
//

#import "BJPlayingView.h"

#import <Masonry/Masonry.h>

@interface BJPlayingView ()

@property (nonatomic, strong) BJLUser *user;

@end

@implementation BJPlayingView

- (void)playWithUser:(BJLUser *)user videoView:(UIView *)videoView {
    // user
    self.user = user;
    
    // videoView;
    videoView.userInteractionEnabled = NO;
    [self addSubview:videoView];
    [videoView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self);
    }];
}

- (void)stopPlaying {
    self.user = nil;
}

- (BJLUser *)currentPlayingUser {
    return self.user;
}

@end
