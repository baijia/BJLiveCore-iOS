//
//  BJPlayingView.h
//  BJLiveCore
//
//  Created by HuangJie on 2017/9/11.
//  Copyright © 2017年 BaijiaYun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <BJLiveCore/BJLiveCore.h>

@interface BJPlayingView : UIButton

- (void)playWithUser:(BJLUser *)user videoView:(UIView *)videoView;
- (void)stopPlaying;
- (BJLUser *)currentPlayingUser;

@end
