//
//  BJRoomViewController.m
//  BJLiveCore
//
//  Created by MingLQ on 2016-12-18.
//  Copyright © 2016 BaijiaYun. All rights reserved.
//

#import <BJLIveBase/BJLYYModel.h>
#import <BJLiveCore/BJLiveCore.h>

#import <Masonry/Masonry.h>

#import "UIViewController+BJUtil.h"

#import "BJRoomViewController.h"
#import "BJRoomViewController+media.h"
#import "BJRoomViewController+users.h"

#import "BJAppearance.h"
#import "BJAppConfig.h"

static CGFloat const margin = 10.0;
static NSInteger const playingViewCount = 4;

@interface BJRoomViewController ()

@property (nonatomic) UIView *topBarGroupView;
@property (nonatomic) BJPlayingView *backButton, *doneButton;
@property (nonatomic) UITextField *textField;

@property (nonatomic) UIView *dashboardGroupView;
@property (nonatomic) UIScrollView *scrollView;

@end

@implementation BJRoomViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor bj_grayBackgroundColor];
    [self setupSubviews];
    [self makeEvents];
}

- (void)dealloc {
    [NSObject cancelPreviousPerformRequestsWithTarget:self];
}

- (void)enterRoomWithSecret:(NSString *)roomSecret
                   userName:(NSString *)userName {
    self.room = [BJLRoom roomWithSecret:roomSecret
                               userName:userName
                             userAvatar:nil];
    
    @weakify(self);
    
    [self bjl_observe:BJLMakeMethod(self.room, enterRoomSuccess)
             observer:^BOOL() {
                 @strongify(self);
                 if (self.room.loginUser.isTeacher) {
                     [self.room.roomVM sendLiveStarted:YES]; // 上课
                 }
                 [self didEnterRoom];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room, roomWillExitWithError:)
             observer:^BOOL(BJLError *error) {
                 @strongify(self);
                 if (self.room.loginUser.isTeacher) {
                     [self.room.roomVM sendLiveStarted:NO]; // 下课
                 }
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(self.room, roomDidExitWithError:)
             observer:^BOOL(BJLError *error) {
                 @strongify(self);
                 
                 if (!error) {
                     [self goBack];
                     return YES;
                 }
                 
                 NSString *message = error ? [NSString stringWithFormat:@"%@ - %@",
                                              error.localizedDescription,
                                              error.localizedFailureReason] : @"错误";
                 UIAlertController *alert = [UIAlertController
                                             alertControllerWithTitle:@"错误"
                                             message:message
                                             preferredStyle:UIAlertControllerStyleAlert];
                 [alert addAction:[UIAlertAction
                                   actionWithTitle:@"退出"
                                   style:UIAlertActionStyleDestructive
                                   handler:^(UIAlertAction * _Nonnull action) {
                                       [self goBack];
                                   }]];
                 [alert addAction:[UIAlertAction
                                   actionWithTitle:@"知道了"
                                   style:UIAlertActionStyleCancel
                                   handler:nil]];
                 [self presentViewController:alert animated:YES completion:nil];
                 
                 return YES;
             }];
    
    [self bjl_kvo:BJLMakeProperty(self.room, loadingVM)
                       filter:^BOOL(id old, id now) {
                           // @strongify(self);
                           return !!now;
                       }
                     observer:^BOOL(id old, BJLLoadingVM *now) {
                         @strongify(self);
                         [self makeEventsForLoadingVM:now];
                         return YES;
                     }];
    
    [self.room setReloadingBlock:^(BJLLoadingVM * _Nonnull reloadingVM, void (^ _Nonnull callback)(BOOL)) {
        @strongify(self);
        [self.console printLine:@"网络连接断开"];
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"网络连接断开"
                                                                       message:@"重连 或 退出？"
                                                                preferredStyle:UIAlertControllerStyleAlert];
        [alert addAction:[UIAlertAction
                          actionWithTitle:@"重连"
                          style:UIAlertActionStyleDefault
                          handler:^(UIAlertAction * _Nonnull action) {
                              [self.console printLine:@"网络连接断开，正在重连 ..."];
                              [self makeEventsForLoadingVM:reloadingVM];
                              [self.console printLine:@"网络连接断开：重连"];
                              callback(YES);
                          }]];
        [alert addAction:[UIAlertAction
                          actionWithTitle:@"退出"
                          style:UIAlertActionStyleDestructive
                          handler:^(UIAlertAction * _Nonnull action) {
                              [self.console printLine:@"网络连接断开：退出"];
                              callback(NO);
                          }]];
        [self presentViewController:alert animated:YES completion:nil];
    }];
    
    [self.room enter];
}

#pragma mark - subviews

- (void)setupSubviews {
    [self makeTopBar];
    [self makeScrollView];
}

- (void)makeTopBar {
    self.topBarGroupView = ({
        UIView *view = [UIView new];
        view.clipsToBounds = YES;
        view;
    });
    [self.view addSubview:self.topBarGroupView];
    [self.topBarGroupView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.view);
        make.top.equalTo(self.mas_topLayoutGuide).offset(margin);
        make.height.equalTo(@32);
    }];
    
    UIImage *backImage = [UIImage imageNamed:@"back-dark"];
    self.backButton = ({
        BJPlayingView *button = [[BJPlayingView alloc] initWithFrame:CGRectMake(0, 0, backImage.size.width, backImage.size.height)];
        button.tintColor = [UIBarButtonItem appearanceWhenContainedIn:[UINavigationBar class], nil].tintColor;
        [button setImage:backImage forState:UIControlStateNormal];
        button;
    });
    [self.topBarGroupView addSubview:self.backButton];
    
    self.textField = ({
        UITextField *textField = [UITextField new];
        textField.backgroundColor = [UIColor whiteColor];
        textField.layer.cornerRadius = 2.0;
        textField.layer.masksToBounds = YES;
        textField.returnKeyType = UIReturnKeySend;
        textField.delegate = self;
        textField;
    });
    [self.topBarGroupView addSubview:self.textField];
    
    self.doneButton = ({
        BJPlayingView *button = [BJPlayingView new];
        button.backgroundColor = [UIColor bj_brandColor];
        button.layer.cornerRadius = 2.0;
        button.layer.masksToBounds = YES;
        button.titleLabel.font = [UIFont systemFontOfSize:16.0];
        [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [button setTitleColor:[UIColor colorWithWhite:1.0 alpha:0.5] forState:UIControlStateDisabled];
        [button setTitle:@"发送" forState:UIControlStateNormal];
        button;
    });
    [self.topBarGroupView addSubview:self.doneButton];
    
    [self.backButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.topBarGroupView).offset(margin);
        make.top.bottom.equalTo(self.topBarGroupView);
        make.width.equalTo(self.backButton.mas_height);
    }];
    
    [self.doneButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(self.topBarGroupView).offset(- margin);
        make.width.equalTo(@64.0);
        make.top.bottom.equalTo(self.topBarGroupView);
    }];
    
    [self.textField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.backButton.mas_right).offset(margin);
        make.right.equalTo(self.doneButton.mas_left).offset(- margin);
        make.top.bottom.equalTo(self.topBarGroupView);
    }];
}

- (void)makeScrollView {
    self.scrollView = ({
        UIScrollView *scrollView = [[UIScrollView alloc] init];
        scrollView.showsVerticalScrollIndicator = NO;
        scrollView;
    });
    [self.view addSubview:self.scrollView];
    [self.scrollView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.bottom.equalTo(self.view);
        make.top.equalTo(self.topBarGroupView.mas_bottom).offset(margin);
    }];
    [self makeDashboard];
    [self makeConsole];
}

- (void)makeDashboard {
    self.dashboardGroupView = ({
        UIView *view = [UIView new];
        view.clipsToBounds = YES;
        view;
    });
    [self.scrollView addSubview:self.dashboardGroupView];
    [self.dashboardGroupView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(@[self.view, self.scrollView]);
        make.top.equalTo(self.scrollView);
    }];
    
    // 采集视图
    self.recordingView = ({
        BJPlayingView *button = [BJPlayingView new];
        button.clipsToBounds = YES;
        button;
    });
    [self.recordingView setTitle:@"采集" forState:UIControlStateNormal];
    self.recordingView.backgroundColor = [[UIColor redColor] colorWithAlphaComponent:0.2];
    [self.dashboardGroupView addSubview:self.recordingView];
    [self.recordingView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.top.equalTo(self.dashboardGroupView);
        make.right.equalTo(self.dashboardGroupView.mas_centerX);
        make.height.equalTo(self.recordingView.mas_width).multipliedBy(3.0 / 4.0);
    }];
    
    // PPT 视图
    self.slideshowAndWhiteboardView = ({
        UIView *view = [UIView new];
        view.clipsToBounds = YES;
        UILabel *label = [UILabel new];
        label.text = @"白板";
        label.textColor = [UIColor whiteColor];
        label.textAlignment = NSTextAlignmentCenter;
        [view addSubview:label];
        [label mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(view);
        }];
        view;
    });
    self.slideshowAndWhiteboardView.backgroundColor = [[UIColor blueColor] colorWithAlphaComponent:0.2];
    [self.dashboardGroupView addSubview:self.slideshowAndWhiteboardView];
    [self.slideshowAndWhiteboardView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.bottom.equalTo(self.recordingView);
        make.left.equalTo(self.recordingView.mas_right);
        make.right.equalTo(self.dashboardGroupView);
    }];
    
    // 播放视图
    int maxColCount = 2;
    int maxRowCount = (playingViewCount - 1) / maxColCount + 1;
    UIView *targetView = self.recordingView;
    for (int i = 0; i < playingViewCount; i ++) {
        int row = i / maxColCount;
        int col = i % maxColCount;
        BJPlayingView *playingView = ({
            BJPlayingView *button = [BJPlayingView new];
            button.clipsToBounds = YES;
            [button setTitle:[NSString stringWithFormat:@"播放%d", i + 1] forState:UIControlStateNormal];
            button.backgroundColor = [[UIColor greenColor] colorWithAlphaComponent:0.2];
            [[button rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(id x) {
                [self showAlertWithPlayingView:button];
            }];
            [button addTarget:self action:@selector(showAlertWithPlayingView:) forControlEvents:UIControlEventTouchUpInside];
            button;
        });
        [self.dashboardGroupView addSubview:playingView];
        [self.playingViews addObject:playingView];
        
        if (col % maxColCount == 0) {
            [playingView mas_makeConstraints:^(MASConstraintMaker *make) {
                make.top.equalTo(targetView.mas_bottom).offset(1.0);
                make.left.equalTo(targetView);
                make.right.equalTo(targetView).offset(-1.0);
                make.height.equalTo(playingView.mas_width).multipliedBy(3.0 / 4.0);
                if (row == maxRowCount - 1) {
                    make.bottom.equalTo(self.dashboardGroupView);
                }
            }];
            targetView = playingView;
        } else {
            [playingView mas_makeConstraints:^(MASConstraintMaker *make) {
                make.left.equalTo(targetView.mas_right).offset(1.0);
                make.top.bottom.equalTo(targetView);
                make.right.equalTo(self.dashboardGroupView);
            }];
        }
    }
}

- (void)makeConsole {
    self.console = [BJConsoleViewController new];
    [self addChildViewController:self.console superview:self.scrollView];
    [self.console.view mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.dashboardGroupView.mas_bottom);
        make.left.right.equalTo(@[self.view, self.scrollView]);
        make.bottom.equalTo(self.scrollView);
        make.height.greaterThanOrEqualTo(@140.0);
        make.height.lessThanOrEqualTo(@300.0);
        make.bottom.equalTo(self.view).priorityHigh();
    }];
}

#pragma mark - VM

- (void)didEnterRoom {
    [self.console printFormat:@"roomInfo ID: %@, title: %@",
     self.room.roomInfo.ID,
     self.room.roomInfo.title];
    
    [self.console printFormat:@"loginUser ID: %@, number: %@, name: %@",
     self.room.loginUser.ID,
     self.room.loginUser.number,
     self.room.loginUser.name];
    
    // if (!self.room.loginUser.isTeacher) {
    @weakify(self);
    [self bjl_kvo:BJLMakeProperty(self.room.roomVM, liveStarted)
                       filter:^BOOL(NSNumber *old, NSNumber *now) {
                           // @strongify(self);
                           return old.integerValue != now.integerValue;
                       }
                     observer:^BOOL(id old, id now) {
                         @strongify(self);
                         [self.console printFormat:@"liveStarted: %@", self.room.roomVM.liveStarted ? @"YES" : @"NO"];
                         return YES;
                     }];
    // }
    
    [self makeUserEvents];
    [self makeMediaEvents];
    [self makeChatEvents];
}

- (void)makeEventsForLoadingVM:(BJLLoadingVM *)loadingVM {
    @weakify(self/* , loadingVM */);
    
    loadingVM.suspendBlock = ^(BJLLoadingStep step,
                               BJLLoadingSuspendReason reason,
                               BJLError *error,
                               void (^continueCallback)(BOOL isContinue)) {
        @strongify(self/* , loadingVM */);
        
        if (reason == BJLLoadingSuspendReason_stepOver) {
            [self.console printFormat:@"loading step over: %td", step];
            continueCallback(YES);
            return;
        }
        [self.console printFormat:@"loading step suspend: %td", step];
        
        NSString *message = nil;
        if (reason == BJLLoadingSuspendReason_errorOccurred) {
            message = error ? [NSString stringWithFormat:@"%@ - %@",
                               error.localizedDescription,
                               error.localizedFailureReason] : @"错误";
        }
        if (message) {
            UIAlertController *alert = [UIAlertController
                                        alertControllerWithTitle:reason != BJLLoadingSuspendReason_errorOccurred ? @"提示" : @"错误"
                                        message:message
                                        preferredStyle:UIAlertControllerStyleAlert];
            [alert addAction:[UIAlertAction
                              actionWithTitle:reason != BJLLoadingSuspendReason_errorOccurred ? @"继续" : @"重试"
                              style:UIAlertActionStyleDefault
                              handler:^(UIAlertAction * _Nonnull action) {
                                  continueCallback(YES);
                              }]];
            [alert addAction:[UIAlertAction
                              actionWithTitle:@"取消"
                              style:UIAlertActionStyleCancel
                              handler:^(UIAlertAction * _Nonnull action) {
                                  continueCallback(NO);
                              }]];
            [self presentViewController:alert animated:YES completion:nil];
        }
    };
    
    [self bjl_observe:BJLMakeMethod(loadingVM, loadingUpdateProgress:)
             observer:(BJLMethodObserver)^BOOL(CGFloat progress) {
                 @strongify(self/* , loadingVM */);
                 [self.console printFormat:@"loading progress: %f", progress];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(loadingVM, loadingSuccess)
             observer:^BOOL() {
                 @strongify(self/* , loadingVM */);
                 [self.console printLine:@"loading success"];
                 return YES;
             }];
    
    [self bjl_observe:BJLMakeMethod(loadingVM, loadingFailureWithError:)
             observer:^BOOL(BJLError *error) {
                 @strongify(self/* , loadingVM */);
                 [self.console printLine:@"loading failure"];
                 return YES;
             }];
}

- (void)makeChatEvents {
    @weakify(self);
    
    [self bjl_observe:BJLMakeMethod(self.room.chatVM, didReceiveMessage:)
             observer:^BOOL(BJLMessage *message) {
                 @strongify(self);
                 [self.console printFormat:@"chat %@: %@", message.fromUser.name, message.text];
                 return YES;
             }];
}

- (void)startPrintAVDebugInfo {
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:_cmd object:nil];
    
    [self.console printFormat:@"---- av - %f ----", [NSDate timeIntervalSinceReferenceDate]];
    for (NSString *info in [self.room.mediaVM avDebugInfo]) {
        [self.console printLine:info];
    }
    
    [self performSelector:_cmd withObject:nil afterDelay:1.0];
}

- (void)stopPrintAVDebugInfo {
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(startPrintAVDebugInfo) object:nil];
}

#pragma mark - events

- (void)makeEvents {
    @weakify(self);
    
    [[self.textField.rac_textSignal
      map:^id(NSString *text) {
          return @(!!text.length);
      }]
     subscribeNext:^(NSNumber *enabled) {
         @strongify(self);
         self.doneButton.enabled = enabled.boolValue;
     }];
    
    [[self.backButton rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(id x) {
         @strongify(self);
         [self goBack];
     }];
    
    [[self.doneButton rac_signalForControlEvents:UIControlEventTouchUpInside]
     subscribeNext:^(id x) {
         @strongify(self);
         [self sendMessage];
     }];
}

- (void)goBack {
    [self.room exit];
    [self dismissViewControllerAnimated:YES completion:^{
        self.room = nil;
    }];
}

- (void)sendMessage {
    [self.view endEditing:YES];
    if (!self.textField.text.length) {
        return;
    }
    if ([self.textField.text isEqualToString:@"-av"]) {
        self.textField.text = nil;
        [self startPrintAVDebugInfo];
        return;
    }
    if (!self.room.chatVM.forbidAll && !self.room.chatVM.forbidMe) {
        [self.room.chatVM sendMessage:self.textField.text];
    }
    else {
        [self.console printLine:@"禁言状态不能发送消息"];
    }
    self.textField.text = nil;
}

- (void)showAlertWithPlayingView:(BJPlayingView *)playingView {
    BJLPlayingVM *playingVM = self.room.playingVM;
    if (!playingVM) {
        return;
    }
    
    NSArray<BJLUser *> *videoPlayingUsers = playingVM.videoPlayingUsers;
    NSArray<BJLOnlineUser *> *playingUsers = playingVM.playingUsers;
    BOOL noBody = !videoPlayingUsers.count && !playingUsers.count;
    
    UIAlertController *actionSheet = [UIAlertController
                                      alertControllerWithTitle:self.room.roomInfo.title
                                      message:noBody ? @"现在没有人在发言" : nil
                                      preferredStyle:UIAlertControllerStyleActionSheet];
    
    BJLUser *currentUser = [playingView currentPlayingUser];
    if (currentUser) {
        [actionSheet addAction:[UIAlertAction
                                actionWithTitle:[NSString stringWithFormat:@"关闭视频 %@", currentUser.name]
                                style:UIAlertActionStyleDefault
                                handler:^(UIAlertAction * _Nonnull action) {
                                    UIView *videoView = [playingVM playingViewForUserWithID:currentUser.ID];
                                    [videoView removeFromSuperview];
                                    [playingView stopPlaying];
                                    [playingVM updatePlayingUserWithID:currentUser.ID videoOn:NO];
                                }]];
        if (self.room.loginUser.isTeacher) {
            [actionSheet addAction:[UIAlertAction
                                    actionWithTitle:([NSString stringWithFormat:@"关闭发言 %@", currentUser.name])
                                    style:UIAlertActionStyleDestructive
                                    handler:^(UIAlertAction * _Nonnull action) {
                                        [self.room.recordingVM remoteChangeRecordingWithUser:currentUser
                                                                                     audioOn:NO
                                                                                     videoOn:NO];
                                    }]];
        }
    }
    
    for (BJLOnlineUser *user in playingUsers) {
        if (currentUser && [user.ID isEqualToString:currentUser.ID]) {
            continue;
        }
        BOOL isVideoPlayingUser = NO;
        for (BJLUser *videoPlayingUser in videoPlayingUsers) {
            if ([user.ID isEqualToString:videoPlayingUser.ID]) {
                isVideoPlayingUser = YES;
            }
        }
        if (isVideoPlayingUser) {
            continue;
        }
        
        if (user.videoOn) {
            [actionSheet addAction:[UIAlertAction
                                    actionWithTitle:[NSString stringWithFormat:@"打开视频 %@", user.name]
                                    style:UIAlertActionStyleDefault
                                    handler:^(UIAlertAction * _Nonnull action) {
                                        UIView *videoView = [playingVM playingViewForUserWithID:user.ID];
                                        [playingView playWithUser:user videoView:videoView];
                                        [playingVM updatePlayingUserWithID:user.ID videoOn:YES];
                                    }]];
        }
        if (self.room.loginUser.isTeacher) {
            [actionSheet addAction:[UIAlertAction
                                    actionWithTitle:([NSString stringWithFormat:@"关闭发言 %@", user.name])
                                    style:UIAlertActionStyleDestructive
                                    handler:^(UIAlertAction * _Nonnull action) {
                                        [self.room.recordingVM remoteChangeRecordingWithUser:user
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
}

#pragma mark - <UITextFieldDelegate>

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [self sendMessage];
    return NO;
}

#pragma mark - getters

- (NSMutableArray<BJPlayingView *> *)playingViews {
    if (!_playingViews) {
        _playingViews = [NSMutableArray array];
    }
    return _playingViews;
}

@end
