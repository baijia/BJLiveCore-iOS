//
//  BJAppConfig.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 Baijia Cloud. All rights reserved.
//

#import <ReactiveObjC/ReactiveObjC.h>

#import "BJAppConfig.h"

static NSString * const BJAppConfig_deployType = @"BJAppConfig_deployType";

@implementation BJAppConfig

+ (instancetype)sharedInstance {
    static BJAppConfig *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [BJAppConfig new];
    });
    return sharedInstance;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _deployType = BJLDeployType_www;
#if DEBUG
        id deployType = [[NSUserDefaults standardUserDefaults] stringForKey:BJAppConfig_deployType];
        _deployType = ([deployType respondsToSelector:@selector(integerValue)]
                       ? [deployType integerValue]
                       : BJLDeployType_test);
#endif
        [self makeSignals];
    }
    return self;
}

- (void)makeSignals {
#if DEBUG
    @weakify(self);
    [[[RACObserve(self, deployType) skip:1] distinctUntilChanged] subscribeNext:^(id x) {
        @strongify(self);
        
        NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
        [userDefaults setInteger:self.deployType forKey:BJAppConfig_deployType];
        [userDefaults synchronize];
        
        exit(0);
    }];
#endif
}

@end
