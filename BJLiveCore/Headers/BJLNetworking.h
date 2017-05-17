//
//  BJLNetworking.h
//  BJLiveCore
//
//  Created by MingLQ on 2016-08-20.
//  Copyright © 2016年 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>

NS_ASSUME_NONNULL_BEGIN

@protocol BJLResponse;

extern NSString * const BJAnonymousAuthTokenURL;

// copied from AFURLRequestSerialization.m
static inline NSString * BJMimeTypeForPathExtension(NSString *extension) {
    NSString *UTI = (__bridge_transfer NSString *)UTTypeCreatePreferredIdentifierForTag(kUTTagClassFilenameExtension, (__bridge CFStringRef)extension, NULL);
    NSString *contentType = (__bridge_transfer NSString *)UTTypeCopyPreferredTagWithClass((__bridge CFStringRef)UTI, kUTTagClassMIMEType);
    return contentType ?: @"application/octet-stream";
}

#pragma mark -

#define BJLNETWORKING [BJLNetworking bjl_defaultManager]

/*
@interface BJLNetworking <BJLResponseType: id<BJLResponse>> : AFHTTPSessionManager
@end */
@compatibility_alias BJLNetworking AFHTTPSessionManager;

/**
 TODO: MingLQ - set baseURL etc. via config block?
 */
@interface AFHTTPSessionManager (BJLNetworkingExt)

+ (instancetype)bjl_defaultManager;
+ (instancetype)bjl_managerWithDefaultConfiguration;

// Class MUST conforms to protocol <BJLResponse>, use @class BJLResponse if nil.
@property (nonatomic, null_resettable) Class<BJLResponse> responseClass;

- (NSURLSessionDataTask *)bjl_GET:(NSString *)urlString
                       parameters:(nullable NSDictionary *)parameters
                          success:(nullable void (^)(NSURLSessionDataTask *task, __kindof NSObject<BJLResponse> *response))success
                          failure:(nullable void (^)(NSURLSessionDataTask * _Nullable task, __kindof NSObject<BJLResponse> *response))failure;

- (NSURLSessionDataTask *)bjl_POST:(NSString *)urlString
                        parameters:(nullable NSDictionary *)parameters
                           success:(nullable void (^)(NSURLSessionDataTask *task, __kindof NSObject<BJLResponse> *response))success
                           failure:(nullable void (^)(NSURLSessionDataTask * _Nullable task, __kindof NSObject<BJLResponse> *response))failure;

- (NSURLSessionDataTask *)bjl_HTTPWithMethod:(NSString *)method
                                   urlString:(NSString *)urlString
                                  parameters:(nullable NSDictionary *)parameters
                                     success:(nullable void (^)(NSURLSessionDataTask *task, __kindof NSObject<BJLResponse> *response))success
                                     failure:(nullable void (^)(NSURLSessionDataTask * _Nullable task, __kindof NSObject<BJLResponse> *response))failure;

/**
 *  @param constructing Different from `AFNetworking` - Call `failure` if an error occurs when constructing the HTTP body.
 *  - @param error      Pass it directly to the method `[formData appendPartWith...:error]`.
 *  - @return           The value returned from the method `[formData appendPartWith...]`.
 *  @param progress     Note this block is called on the session queue, not the main queue.
 */
- (NSURLSessionUploadTask *)bjl_upload:(NSString *)urlString
                            parameters:(nullable NSDictionary *)parameters
                          constructing:(nullable BOOL (^)(id <AFMultipartFormData> formData, NSError * _Nullable __autoreleasing *error))constructing
                              progress:(nullable void (^)(NSProgress *uploadProgress))progress
                               success:(nullable void (^)(NSURLSessionUploadTask *task, __kindof NSObject<BJLResponse> *response))success
                               failure:(nullable void (^)(NSURLSessionUploadTask * _Nullable task, __kindof NSObject<BJLResponse> *response))failure;

/**
 *  @param progress     Note this block is called on the session queue, not the main queue.
 */
- (NSURLSessionDownloadTask *)bjl_download:(NSString *)urlString
                                parameters:(nullable NSDictionary *)parameters
                                  progress:(nullable void (^)(NSProgress *uploadProgress))progress
                               destination:(nullable NSURL *(^)(NSURL *targetPath, NSURLResponse *response))destination
                                   success:(nullable void (^)(NSURLSessionDownloadTask *task, __kindof NSObject<BJLResponse> *response))success
                                   failure:(nullable void (^)(NSURLSessionDownloadTask * _Nullable task, __kindof NSObject<BJLResponse> *response))failure;

- (__kindof NSURLSessionTask *)bjl_makeRequest:(NSMutableURLRequest *(^)(NSString *urlString, NSDictionary * _Nullable parameters, NSError *_Nullable __autoreleasing *serializationError))makeRequest
                                      makeTask:(__kindof NSURLSessionTask *(^)(NSURLRequest *request, void (^completionHandler)(NSURLResponse *response, id responseObject, NSError * _Nullable error)))makeTask
                                     urlString:(NSString *)urlString
                                    parameters:(nullable NSDictionary *)parameters
                                       success:(nullable void (^)(__kindof NSURLSessionTask *task, __kindof NSObject<BJLResponse> *response))success
                                       failure:(nullable void (^)(__kindof NSURLSessionTask * _Nullable task, __kindof NSObject<BJLResponse> *response))failure;

@end

#pragma mark -

@protocol BJLResponse <NSObject>

/**
 *  @param responseObject   JSON object, or NSURL for NSURLSessionDownloadTask
 */
+ (instancetype)responseWithObject:(nullable id)responseObject;
+ (instancetype)responseWithError:(nullable NSError *)error;

@property (nonatomic, readonly) BOOL isSuccess;

@end

#pragma mark -

typedef NS_ENUM(NSInteger, BJLResponseCode) {
    BJLResponseCodeSuccess = 0,
    BJLResponseCodeFailure = 1
};

@interface BJLResponse : NSObject <BJLResponse>

@property (nonatomic, readonly) BJLResponseCode code;
@property (nonatomic, readonly, nullable ) NSString *message;

@property (nonatomic, readonly) NSTimeInterval timestamp;
@property (nonatomic, readonly, nullable ) NSDictionary *data;
@property (nonatomic, readonly, nullable ) NSError *error;

@end

@interface BJLMutableResponse : BJLResponse

@property (nonatomic, readwrite) BJLResponseCode code;
@property (nonatomic, readwrite, nullable ) NSString *message;

@property (nonatomic, readwrite) NSTimeInterval timestamp;
@property (nonatomic, readwrite, nullable ) NSDictionary *data;
@property (nonatomic, readwrite, nullable ) NSError *error;

@end

NS_ASSUME_NONNULL_END
