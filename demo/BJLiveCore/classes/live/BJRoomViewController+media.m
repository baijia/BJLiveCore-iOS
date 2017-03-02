//
//  BJRoomViewController+media.m
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-18.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#import <MobileCoreServices/MobileCoreServices.h>

#import "BJRoomViewController+media.h"

#import "BJLNetworking.h"

@implementation BJRoomViewController (media)

- (void)makeMediaEvents {
    [self makeSpeakingEvents];
    [self makeRecordingEvents];
    [self makePlayingEvents];
    [self makeSlideshowAndWhiteboardEvents];
}

- (void)makeSpeakingEvents {
    weakdef(self);
    
    if (self.room.loginUser.isTeacher) {
        // 有学生请求发言
        [self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, receivedSpeakingRequestFromUser:)
                 observer:^BOOL(NSObject<BJLUser> *user) {
                     strongdef(self);
                     // 自动同意
                     [self.room.speakingRequestVM replySpeakingRequestToUserID:user.ID allowed:YES];
                     [self.console printFormat:@"%@ 请求发言、已同意", user.name];
                     return YES;
                 }];
    }
    else {
        // 发言请求被处理
        [self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, speakingRequestDidReply:)
                 observer:^BOOL(NSObject<BJLSpeakingReply> *reply) {
                     strongdef(self);
                     [self.console printFormat:@"发言申请已被%@", reply.speakingEnabled ? @"允许" : @"拒绝"];
                     if (reply.speakingEnabled) {
                         [self.room.recordingVM setRecordingAudio:YES
                                                   recordingVideo:NO];
                         [self.console printFormat:@"麦克风已打开"];
                     }
                     return YES;
                 }];
        // 发言状态被开启、关闭
        [self bjl_observe:BJLMakeMethod(self.room.speakingRequestVM, speakingDidRemoteEnabled:)
                 observer:(BJLMethodObserver)^BOOL(BOOL enabled) {
                     [self.console printFormat:@"发言状态被%@", enabled ? @"开启" : @"关闭"];
                     return YES;
                 }];
    }
}

- (void)makeRecordingEvents {
    weakdef(self);
    
    self.room.recordingView.userInteractionEnabled = NO;
    [self.recordingView addSubview:self.room.recordingView];
    [self.room.recordingView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.recordingView);
    }];
    
    [[self.recordingView rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(id x) {
         strongdef(self);
         
         if (!self.room.loginUser.isTeacher
             && !self.room.speakingRequestVM.speakingEnabled) {
             BOOL hasTeacher = !!self.room.onlineUsersVM.onlineTeacher;
             UIAlertController *actionSheet = [UIAlertController
                                               alertControllerWithTitle:self.recordingView.currentTitle
                                               message:hasTeacher ? @"要发言先举手" : @"老师没在教室，不能举手"
                                               preferredStyle:UIAlertControllerStyleActionSheet];
             if (hasTeacher) {
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
                                             [self.room.speakingRequestVM stopSpeaking];
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
                                         [self.room.speakingRequestVM stopSpeaking];
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
                                         [self.room.speakingRequestVM stopSpeaking];
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
             
             BOOL isClose = recordingVM.videoBeautifyLevel == BJLVideoBeautifyLevel_close;
             [actionSheet addAction:[UIAlertAction
                                     actionWithTitle:isClose ? @"打开美颜" : @"关闭美颜"
                                     style:UIAlertActionStyleDefault
                                     handler:^(UIAlertAction * _Nonnull action) {
                                         recordingVM.videoBeautifyLevel = isClose ? BJLVideoBeautifyLevel_max : BJLVideoBeautifyLevel_close;
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
    self.room.playingView.userInteractionEnabled = NO;
    [self.playingView addSubview:self.room.playingView];
    [self.room.playingView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.playingView);
    }];
    
    weakdef(self);
    
    [self bjl_observe:BJLMakeMethod(self.room.playingVM, playingUserDidUpdate:)
             observer:^BOOL(BJLTuple *tuple) {
                 BJLTupleUnpack(tuple) = ^(NSObject<BJLOnlineUser> *old,
                                           NSObject<BJLOnlineUser> *now) {
                     strongdef(self);
                     [self.console printFormat:@"playingUserDidUpdate: %@ >> %@", old, now];
                 };
                 return YES;
             }];
    [self bjl_observe:BJLMakeMethod(self.room.playingVM, playingUserDidUpdate:old:)
             observer:^BOOL(NSObject<BJLOnlineUser> *now,
                            NSObject<BJLOnlineUser> *old) {
                 strongdef(self);
                 [self.console printFormat:@"playingUserDidUpdate:old: %@ >> %@", old, now];
                 return YES;
             }];
    
    [[self.playingView rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(id x) {
         strongdef(self);
         
         BJLPlayingVM *playingVM = self.room.playingVM;
         if (!playingVM) {
             return;
         }
         
         NSObject<BJLOnlineUser> *videoPlayingUser = playingVM.videoPlayingUser;
         NSArray<NSObject<BJLOnlineUser> *> *playingUsers = playingVM.playingUsers;
         BOOL noBody = !videoPlayingUser && !playingUsers.count;
         
         UIAlertController *actionSheet = [UIAlertController
                                           alertControllerWithTitle:self.playingView.currentTitle
                                           message:noBody ? @"现在没有人在发言" : nil
                                           preferredStyle:UIAlertControllerStyleActionSheet];
         
         if (videoPlayingUser) {
             [actionSheet addAction:[UIAlertAction
                                     actionWithTitle:[NSString stringWithFormat:@"关闭视频 %@", videoPlayingUser.name]
                                     style:UIAlertActionStyleDefault
                                     handler:^(UIAlertAction * _Nonnull action) {
                                         [playingVM updateVideoPlayingUserWithID:nil];
                                     }]];
             if (self.room.loginUser.isTeacher) {
                 [actionSheet addAction:[UIAlertAction
                                         actionWithTitle:([NSString stringWithFormat:@"关闭发言 %@", videoPlayingUser.name])
                                         style:UIAlertActionStyleDestructive
                                         handler:^(UIAlertAction * _Nonnull action) {
                                             [playingVM remoteUpdatePlayingUserWithID:videoPlayingUser.ID
                                                                              audioOn:NO
                                                                              videoOn:NO];
                                         }]];
             }
         }
         for (NSObject<BJLOnlineUser> *user in playingVM.playingUsers) {
             if (videoPlayingUser && [user.ID isEqualToString:videoPlayingUser.ID]) {
                 continue;
             }
             if (user.videoOn) {
                 [actionSheet addAction:[UIAlertAction
                                         actionWithTitle:[NSString stringWithFormat:@"打开视频 %@", user.name]
                                         style:UIAlertActionStyleDefault
                                         handler:^(UIAlertAction * _Nonnull action) {
                                             [playingVM updateVideoPlayingUserWithID:user.ID];
                                         }]];
             }
             if (self.room.loginUser.isTeacher) {
                 [actionSheet addAction:[UIAlertAction
                                         actionWithTitle:([NSString stringWithFormat:@"关闭发言 %@", user.name])
                                         style:UIAlertActionStyleDestructive
                                         handler:^(UIAlertAction * _Nonnull action) {
                                             [playingVM remoteUpdatePlayingUserWithID:user.ID
                                                                              audioOn:NO
                                                                              videoOn:NO];
                                         }]];
                 NSInteger seconds = 1;
                 [actionSheet addAction:[UIAlertAction
                                         actionWithTitle:([NSString stringWithFormat:@"禁言 %td 分钟 %@", seconds, user.name])
                                         style:UIAlertActionStyleDestructive
                                         handler:^(UIAlertAction * _Nonnull action) {
                                             [self.room.chatVM sendForbidUser:user
                                                                     duration:seconds * 60.0];
                                         }]];
                 [actionSheet addAction:[UIAlertAction
                                         actionWithTitle:([NSString stringWithFormat:@"解除禁言 %@", user.name])
                                         style:UIAlertActionStyleDestructive
                                         handler:^(UIAlertAction * _Nonnull action) {
                                             [self.room.chatVM sendForbidUser:user
                                                                     duration:0.0];
                                         }]];
             }
         }
         
         BJLMediaVM *mediaVM = self.room.mediaVM;
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:(mediaVM.downLinkType == BJLLinkType_TCP
                                                  ? @"TCP > UDP" : @"UDP > TCP")
                                 style:UIAlertActionStyleDefault
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     mediaVM.downLinkType = (mediaVM.downLinkType == BJLLinkType_TCP
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

- (void)makeSlideshowAndWhiteboardEvents {
    weakdef(self);
    
    self.room.slideshowViewController.studentCanPreviewForward = YES;
    self.room.slideshowViewController.studentCanRemoteControl = YES;
    self.room.slideshowViewController.placeholderImage = [UIImage imageWithColor:[UIColor lightGrayColor]];
    
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
         strongdef(self);
         
         UIAlertController *actionSheet = [UIAlertController
                                           alertControllerWithTitle:@"课件&画板"
                                           message:nil
                                           preferredStyle:UIAlertControllerStyleActionSheet];
         
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:@"上传课件"
                                 style:UIAlertActionStyleDefault
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     [self.room.slideVM addDocument:({
                                         BJLDocumentPageInfo *pageInfo = [BJLDocumentPageInfo new];
                                         pageInfo.isAlbum = NO;
                                         pageInfo.pageCount = 0;
                                         pageInfo.pageURLString = @"https://img.genshuixue.com/baijiacloud/25760197_xg3ypq77.png";
                                         pageInfo.width = 550;
                                         pageInfo.height = 280;
                                         BJLDocument *document = [BJLDocument new];
                                         document.fileID = @"25760197";
                                         document.fileName = @"1482134071749";
                                         document.fileExtension = @".png";
                                         document.pageInfo = pageInfo;
                                         document;
                                     })];
                                     [self.room.slideVM addDocument:({
                                         BJLDocumentPageInfo *pageInfo = [BJLDocumentPageInfo new];
                                         pageInfo.isAlbum = NO;
                                         pageInfo.pageCount = 0;
                                         pageInfo.pageURLString = @"https://img.genshuixue.com/baijiacloud/25760479_kypu8tvk.png";
                                         pageInfo.width = 627;
                                         pageInfo.height = 830;
                                         BJLDocument *document = [BJLDocument new];
                                         document.fileID = @"25760479";
                                         document.fileName = @"1482134268462";
                                         document.fileExtension = @".png";
                                         document.pageInfo = pageInfo;
                                         document;
                                     })];
                                 }]];
         
         BOOL isFit = self.room.slideshowViewController.contentMode == BJLSlideshowContentMode_scaleAspectFit;
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:isFit ? @"完整显示" : @"铺满显示"
                                 style:UIAlertActionStyleDefault
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     self.room.slideshowViewController.contentMode = isFit ? BJLSlideshowContentMode_scaleAspectFill : BJLSlideshowContentMode_scaleAspectFit;
                                 }]];
         
         BOOL whiteboardEnabled = self.room.slideshowViewController.whiteboardEnabled;
         if (whiteboardEnabled) {
             [actionSheet addAction:[UIAlertAction
                                     actionWithTitle:@"擦除标记"
                                     style:UIAlertActionStyleDefault
                                     handler:^(UIAlertAction * _Nonnull action) {
                                         [self.room.slideshowViewController clearWhiteboard];
                                     }]];
         }
         [actionSheet addAction:[UIAlertAction
                                 actionWithTitle:whiteboardEnabled ? @"结束标记" : @"开始标记"
                                 style:UIAlertActionStyleDefault
                                 handler:^(UIAlertAction * _Nonnull action) {
                                     self.room.slideshowViewController.whiteboardEnabled = !whiteboardEnabled;
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

@end
