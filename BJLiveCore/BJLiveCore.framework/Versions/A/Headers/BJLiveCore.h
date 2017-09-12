//
//  BJLiveCore.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-18.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#if __has_include(<BJLiveCore/BJLiveCore.h>)

#import <BJLiveCore/BJLBaseVM.h>
#import <BJLiveCore/BJLBlockHelper.h>
#import <BJLiveCore/BJLChatVM.h>
#import <BJLiveCore/BJLConstants.h>
#import <BJLiveCore/BJLDocument.h>
#import <BJLiveCore/BJLEmoticon.h>
#import <BJLiveCore/BJLFeatureConfig.h>
#import <BJLiveCore/BJLGift.h>
#import <BJLiveCore/BJLHelpVM.h>
#import <BJLiveCore/BJLLoadingVM.h>
#import <BJLiveCore/BJLMediaVM.h>
#import <BJLiveCore/BJLMessage.h>
#import <BJLiveCore/BJLNotice.h>
#import <BJLiveCore/BJLOnlineUsersVM.h>
#import <BJLiveCore/BJLPlayingVM.h>
#import <BJLiveCore/BJLRecordingVM.h>
#import <BJLiveCore/BJLRoom.h>
#import <BJLiveCore/BJLRoomInfo.h>
#import <BJLiveCore/BJLRoomVM.h>
#import <BJLiveCore/BJLServerRecordingVM.h>
#import <BJLiveCore/BJLSlideVM.h>
#import <BJLiveCore/BJLSlideshowUI.h>
#import <BJLiveCore/BJLSlideshowVM.h>
#import <BJLiveCore/BJLSpeakingRequestVM.h>
#import <BJLiveCore/BJLSurvey.h>
#import <BJLiveCore/BJLUser.h>
#import <BJLiveCore/BJLWebImage.h>
#import <BJLiveCore/NSError+BJLError.h>
#import <BJLiveCore/NSObject+BJLObserving.h>
#import <BJLiveCore/NSObject+BJL_M9Dev.h>
#import <BJLiveCore/UIKit+BJL_M9Dev.h>

#else

#import "BJLBaseVM.h"
#import "BJLBlockHelper.h"
#import "BJLChatVM.h"
#import "BJLConstants.h"
#import "BJLDocument.h"
#import "BJLEmoticon.h"
#import "BJLFeatureConfig.h"
#import "BJLGift.h"
#import "BJLHelpVM.h"
#import "BJLLoadingVM.h"
#import "BJLMediaVM.h"
#import "BJLMessage.h"
#import "BJLNotice.h"
#import "BJLOnlineUsersVM.h"
#import "BJLPlayingVM.h"
#import "BJLRecordingVM.h"
#import "BJLRoom.h"
#import "BJLRoomInfo.h"
#import "BJLRoomVM.h"
#import "BJLScrollViewController.h"
#import "BJLServerRecordingVM.h"
#import "BJLSlideVM.h"
#import "BJLSlideshowUI.h"
#import "BJLSlideshowVM.h"
#import "BJLSpeakingRequestVM.h"
#import "BJLSurvey.h"
#import "BJLTableViewController.h"
#import "BJLUser.h"
#import "BJLUserAgent.h"
#import "BJLWebImage.h"
#import "BJLWebViewController.h"
#import "NSError+BJLError.h"
#import "NSObject+BJLObserving.h"
#import "NSObject+BJL_M9Dev.h"
#import "UIKit+BJL_M9Dev.h"
#import "UIKit+BJLHandler.h"

#endif

FOUNDATION_EXPORT NSString * BJLiveCoreName();
FOUNDATION_EXPORT NSString * BJLiveCoreVersion();
