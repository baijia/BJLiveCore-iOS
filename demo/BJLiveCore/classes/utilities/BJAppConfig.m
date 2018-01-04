//
//  BJAppConfig.m
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-19.
//  Copyright © 2016年 BaijiaYun. All rights reserved.
//

#import <ReactiveObjC/ReactiveObjC.h>

#import "BJAppConfig.h"

static NSString * const BJAppConfig_deployType = @"BJAppConfig_deployType";

@implementation BJAppConfig

+ (instancetype)sharedInstance {
    static BJAppConfig *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [self new];
    });
    return sharedInstance;
}

+ (void)initializeInstance {
    [self sharedInstance];
}

- (instancetype)init {
    self = [super init];
    if (self) {
        id deployType = [[NSUserDefaults standardUserDefaults] stringForKey:BJAppConfig_deployType];
        _deployType = ([deployType respondsToSelector:@selector(integerValue)]
                       ? [deployType integerValue]
                       : BJLDeployType_www);
        [self makeSignals];
    }
    return self;
}

- (void)makeSignals {
    bjl_weakify(self);
    [[[RACObserve(self, deployType) skip:1] distinctUntilChanged] subscribeNext:^(id x) {
        bjl_strongify(self);
        
        NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
        [userDefaults setInteger:self.deployType forKey:BJAppConfig_deployType];
        [userDefaults synchronize];
        
        exit(0);
    }];
}

@end
