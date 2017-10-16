//
//  BJRoomViewController+media.m
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-18.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <MobileCoreServices/MobileCoreServices.h>
#import <Masonry/Masonry.h>

#import "BJRoomViewController+media.h"
#import "UIViewController+BJUtil.h"

#import <BJLiveCore/BJLiveCore.h>

@implementation BJRoomViewController (media)

- (void)makeMediaEvents {
    [self makeSpeakingEvents];
    [self makeRecordingEvents];
    [self makePlayingEvents];
    [self makeSlideshowAndWhiteboardEvents];
}

- (void)makeSpeakingEvents {
    @weakify(self);
    
    if (self.room.loginUser.isTeacher) {
        // 有学生请求发言
        [self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, receivedSpeakingRequestFromUser:)
                 observer:^BOOL(BJLUser *user) {
                     @strongify(self);
                     // 自动同意
                     [self.room.speakingRequestVM replySpeakingRequestToUserID:user.ID allowed:YES];
                     [self.console printFormat:@"%@ 请求发言、已同意", user.name];
                     return YES;
                 }];
    }
    else {
        // 发言请求被处理
        [self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, speakingRequestDidReplyEnabled:isUserCancelled:user:)
                 observer:(BJLMethodObserver)^BOOL(BOOL speakingEnabled, BOOL isUserCancelled, BJLUser *user) {
                     @strongify(self);
                     [self.console printFormat:@"发言申请已被%@", speakingEnabled ? @"允许" : @"拒绝"];
                     if (speakingEnabled) {
                         [self.room.recordingVM setRecordingAudio:YES
                                                   recordingVideo:NO];
                         [self.console printFormat:@"麦克风已打开"];
                     }
                     return YES;
                 }];
        // 发言状态被开启、关闭
        [self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, speakingDidRemoteControl:)
                 observer:(BJLMethodObserver)^BOOL(BOOL enabled) {
                     [self.console printFormat:@"发言状态被%@", enabled ? @"开启" : @"关闭"];
                     return YES;
                 }];
    }
}

- (void)makeRecordingEvents {
    @weakify(self);
    
    self.room.recordingView.userInteractionEnabled = NO;
    
    [self bjl_kvo:BJLMakeProperty(self.room.recordingVM, recordingVideo)
           filter:^BOOL(NSNumber *old, NSNumber *now) {
               // @strongify(self);
               return old.integerValue != now.integerValue;
           }
         observer:^BOOL(id old, id now) {
             @strongify(self);
             BOOL recordingVideo = [now boolValue];
             if (!recordingVideo && !self.room.recordingVM.recordingAudio) { // 音视频采集都被关闭
                 [self hideRecordingView];
             }
             else if (recordingVideo && !self.room.recordingVM.recordingAudio){ // 之前处于音视频都关闭的状态
                 [self showRecordingView];
             }
             [self.console printFormat:@"recordingVideo: %@", self.room.recordingVM.recordingVideo ? @"YES" : @"NO"];
             return YES;
         }];
    
    [self bjl_kvo:BJLMakeProperty(self.room.recordingVM, recordingAudio)
           filter:^BOOL(NSNumber *old, NSNumber *now) {
               // @strongify(self);
               return old.integerValue != now.integerValue;
           }
         observer:^BOOL(id old, id now) {
             @strongify(self);
             BOOL recordingAudio = [now boolValue];
             if (!recordingAudio && !self.room.recordingVM.recordingVideo) { // 音视频采集都被关闭
                 [self hideRecordingView];
             }
             else if (recordingAudio && !self.room.recordingVM.recordingVideo){ // 之前处于音视频都关闭的状态
                 [self showRecordingView];
             }
             [self.console printFormat:@"recordingAudio: %@", self.room.recordingVM.recordingAudio ? @"YES" : @"NO"];
             return YES;
         }];
    
    [[self.recordingView rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(id x) {
         @strongify(self);
         
         if (!self.room.loginUser.isTeacher
             && !self.room.speakingRequestVM.speakingEnabled) {
             BOOL liveStarted = self.room.roomVM.liveStarted;
             UIAlertController *actionSheet = [UIAlertController
                                               alertControllerWithTitle:self.recordingView.currentTitle
                                               message:liveStarted ? @"要发言先举手" : @"非上课状态，不能举手"
                                               preferredStyle:UIAlertControllerStyleActionSheet];
             if (liveStarted) {
                 [actionSheet addAction:[UIAlertAction
                                         actionWithTitle:@"举手"
                                         style:UIAlertActionStyleDefault
                                         handler:^(UIAlertAction * _Nonnull action) {
                                             [self.room.speakingRequestVM sendSpeakingRequest];
                                         }]];
             }
             [actionSheet addAction:[UIAlertAction
                                     actionWithTitle:@"取消"
                                     style:UIAlertActionStyleCancel
                                     handler:nil]];
             [self presentViewController:actionSheet
                                animated:YES
                              completion:nil];
             return;
         }
         
         BJLRecordingVM *recordingVM = self.room.recordingVM;
         if (!recordingVM) {
             return;
         }
         
         BOOL recordingAudio = recordingVM.recordingAudio, recordingVideo = recordingVM.recordingVideo;
         
         UIAlertController *actionSheet = [UIAlertController
                                           alertControllerWithTitle:self.recordingView.currentTitle
                                           message:nil
                                           preferredStyle:UIAlertControllerStyleActionSheet];
         
         if (recordingAudio == recordingVideo) {
             BOOL recording = recordingAudio;
             [actionSheet addAction:[UIAlertAction
                                     actionWithTitle:recording ? @"全部关闭" : @"全部打开"
                                     style:UIAlertActionStyleDefault
                                     handler:^(UIAlertAction * _Nonnull action) {
                                         [recordingVM setRecordingAudio:!recording
                                                         recordingVideo:!recording];
                                         if (!self.room.loginUser.isTeacher
                                             && !recordingVM.recordingAudio
                                             && !recordingVM.recordingVideo) {
                                             [self.room.speakingRequestVM stopSpeakingRequest];
                                             [self.console printLine:@"同时关闭音视频，发言结束"];
                                         }
                                     }]];
         }
         
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:recordingAudio ? @"关闭麦克风" : @"打开麦克风"
                                 style:UIAlertActionStyleDefault
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     [recordingVM setRecordingAudio:!recordingAudio
                                                     recordingVideo:recordingVideo];
                                     if (!self.room.loginUser.isTeacher
                                         && !recordingVM.recordingAudio
                                         && !recordingVM.recordingVideo) {
                                         [self.room.speakingRequestVM stopSpeakingRequest];
                                         [self.console printLine:@"同时关闭音视频，发言结束"];
                                     }
                                 }]];
         
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:recordingVideo ? @"关闭摄像头" : @"打开摄像头"
                                 style:UIAlertActionStyleDefault
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     [recordingVM setRecordingAudio:recordingAudio
                                                     recordingVideo:!recordingVideo];
                                     if (!self.room.loginUser.isTeacher
                                         && !recordingVM.recordingAudio
                                         && !recordingVM.recordingVideo) {
                                         [self.room.speakingRequestVM stopSpeakingRequest];
                                         [self.console printLine:@"同时关闭音视频，发言结束"];
                                     }
                                 }]];
         
         if (recordingVideo) {
             [actionSheet addAction:[UIAlertAction
                                     actionWithTitle:@"切换摄像头"
                                     style:UIAlertActionStyleDefault
                                     handler:^(UIAlertAction * _Nonnull action) {
                                         recordingVM.usingRearCamera = !recordingVM.usingRearCamera;
                                     }]];
             
             BOOL isLow = recordingVM.videoDefinition == BJLVideoDefinition_low;
             [actionSheet addAction:[UIAlertAction
                                     actionWithTitle:isLow ? @"高清模式" : @"流畅模式"
                                     style:UIAlertActionStyleDefault
                                     handler:^(UIAlertAction * _Nonnull action) {
                                         recordingVM.videoDefinition = isLow ? BJLVideoDefinition_high : BJLVideoDefinition_low;
                                     }]];
             
             BOOL isClose = recordingVM.videoBeautifyLevel == BJLVideoBeautifyLevel_off;
             [actionSheet addAction:[UIAlertAction
                                     actionWithTitle:isClose ? @"打开美颜" : @"关闭美颜"
                                     style:UIAlertActionStyleDefault
                                     handler:^(UIAlertAction * _Nonnull action) {
                                         recordingVM.videoBeautifyLevel = isClose ? BJLVideoBeautifyLevel_on : BJLVideoBeautifyLevel_off;
                                     }]];
         }
         
         BJLMediaVM *mediaVM = self.room.mediaVM;
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:(mediaVM.upLinkType == BJLLinkType_TCP
                                                  ? @"TCP > UDP" : @"UDP > TCP")
                                 style:UIAlertActionStyleDefault
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     mediaVM.upLinkType = (mediaVM.upLinkType == BJLLinkType_TCP
                                                           ? BJLLinkType_UDP : BJLLinkType_TCP);
                                 }]];
         
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:@"取消"
                                 style:UIAlertActionStyleCancel
                                 handler:nil]];
         
         [self presentViewController:actionSheet
                            animated:YES
                          completion:nil];
     }];
}

- (void)makePlayingEvents {
    @weakify(self);
    
    [self bjl_observe:BJLMakeMethod(self.room.playingVM, playingUserDidUpdate:old:)
             observer:^BOOL(BJLOnlineUser *now,
                            BJLOnlineUser *old) {
                 @strongify(self);
                 if (!now.videoOn) {
                     [self stopPlayingForUser:now];
                 }
                 [self.console printFormat:@"playingUserDidUpdate:old: %@ >> %@", old, now];
                 return YES;
             }];
}

- (void)makeSlideshowAndWhiteboardEvents {
    @weakify(self);
    
    self.room.slideshowViewController.studentCanPreviewForward = YES;
    self.room.slideshowViewController.studentCanRemoteControl = YES;
    // self.room.slideshowViewController.placeholderImage = [UIImage imageWithColor:[UIColor lightGrayColor]];
    
    [self addChildViewController:self.room.slideshowViewController
                       superview:self.slideshowAndWhiteboardView];
    [self.room.slideshowViewController.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.slideshowAndWhiteboardView);
    }];
    
    UIButton *infoButton = [UIButton buttonWithType:UIButtonTypeInfoLight];
    [self.slideshowAndWhiteboardView addSubview:infoButton];
    [infoButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.bottom.equalTo(self.slideshowAndWhiteboardView).offset(- 5);
    }];
    
    [[infoButton rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(id x) {
         @strongify(self);
         
         UIAlertController *actionSheet = [UIAlertController
                                           alertControllerWithTitle:@"课件&画板"
                                           message:nil
                                           preferredStyle:UIAlertControllerStyleActionSheet];
         
         BOOL wasFit = self.room.slideshowViewController.contentMode == BJLContentMode_scaleAspectFit;
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:wasFit ? @"铺满显示" : @"完整显示"
                                 style:UIAlertActionStyleDefault
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     self.room.slideshowViewController.contentMode = wasFit ? BJLContentMode_scaleAspectFill : BJLContentMode_scaleAspectFit;
                                 }]];
         
         BOOL drawingEnabled = self.room.slideshowViewController.drawingEnabled;
         if (drawingEnabled) {
             [actionSheet addAction:[UIAlertAction
                                     actionWithTitle:@"擦除标记"
                                     style:UIAlertActionStyleDefault
                                     handler:^(UIAlertAction * _Nonnull action) {
                                         [self.room.slideshowViewController clearDrawing];
                                     }]];
         }
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:drawingEnabled ? @"结束标记" : @"开始标记"
                                 style:UIAlertActionStyleDefault
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     self.room.slideshowViewController.drawingEnabled = !drawingEnabled;
                                 }]];
         
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:@"取消"
                                 style:UIAlertActionStyleCancel
                                 handler:nil]];
         
         [self presentViewController:actionSheet
                            animated:YES
                          completion:nil];
     }];
}

#pragma mark - private

- (void)stopPlayingForUser:(BJLUser *)user {
    BJLUser *playingUser;
    for (BJPlayingView *playingView in self.playingViews) {
        playingUser = [playingView currentPlayingUser];
        if (playingUser && [playingUser.ID isEqualToString:user.ID]) {
            [playingView stopPlaying];
        }
    }
}

- (void)showRecordingView {
    if (self.room.recordingView.superview) {
        return;
    }
    [self.recordingView addSubview:self.room.recordingView];
    [self.room.recordingView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.recordingView);
    }];
}

- (void)hideRecordingView {
    [self.room.recordingView removeFromSuperview];
}

@end
