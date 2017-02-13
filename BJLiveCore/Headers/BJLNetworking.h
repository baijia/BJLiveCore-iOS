//
//  BJNetworking.h
//  LivePlayerApp
//
//  Created by MingLQ on 2016-08-20.
//  Copyright © 2016年 Baijia Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>

@protocol BJLResponse;

#define BJLNetworking    [AFHTTPSessionManager bj_manager]

extern NSString * const BJAnonymousAuthTokenURL;

// copied from AFURLRequestSerialization.m
static inline NSString * BJMimeTypeForPathExtension(NSString *extension) {
    NSString *UTI = (__bridge_transfer NSString *)UTTypeCreatePreferredIdentifierForTag(kUTTagClassFilenameExtension, (__bridge CFStringRef)extension, NULL);
    NSString *contentType = (__bridge_transfer NSString *)UTTypeCopyPreferredTagWithClass((__bridge CFStringRef)UTI, kUTTagClassMIMEType);
    if (!contentType) {
        return @"application/octet-stream";
    }
    else {
        return contentType;
    }
}

#pragma mark -

@interface AFHTTPSessionManager (BJLNetworkingExt)

+ (AFHTTPSessionManager *)bj_manager;

// Class MUST conforms to protocol <BJLResponse>, use @class BJLResponse if nil.
@property (nonatomic) Class responseClass;

- (NSURLSessionDataTask *)bj_GET:(NSString *)pathString
                      parameters:(NSDictionary *)parameters
                         success:(void (^)(NSURLSessionDataTask *task, __kindof NSObject<BJLResponse> *response))success
                         failure:(void (^)(NSURLSessionDataTask *task, __kindof NSObject<BJLResponse> *response))failure;

- (NSURLSessionDataTask *)bj_POST:(NSString *)pathString
                       parameters:(NSDictionary *)parameters
                          success:(void (^)(NSURLSessionDataTask *task, __kindof NSObject<BJLResponse> *response))success
                          failure:(void (^)(NSURLSessionDataTask *task, __kindof NSObject<BJLResponse> *response))failure;

- (NSURLSessionDataTask *)bj_HTTPWithMethod:(NSString *)method
                                  urlString:(NSString *)urlString
                                 parameters:(NSDictionary *)parameters
                                    success:(void (^)(NSURLSessionDataTask *task, __kindof NSObject<BJLResponse> *response))success
                                    failure:(void (^)(NSURLSessionDataTask *task, __kindof NSObject<BJLResponse> *response))failure;

/**
 * !!!: Call `failure` if an error occurs when constructing the HTTP body, but `AFNetworking` DOESNOT.
 * @param constructing  Different from `AFNetworking`.
 *  - @param error      Pass it directly to the method `[formData appendPartWith...:error]`.
 *  - @return           The value returned from the method `[formData appendPartWith...]`.
 */
- (NSURLSessionUploadTask *)bj_upload:(NSString *)urlString
                           parameters:(NSDictionary *)parameters
                         constructing:(BOOL (^)(id <AFMultipartFormData> formData, NSError * __autoreleasing *error))constructing
                             progress:(void (^)(NSProgress *uploadProgress))progress
                              success:(void (^)(NSURLSessionUploadTask *task, __kindof NSObject<BJLResponse> *response))success
                              failure:(void (^)(NSURLSessionUploadTask *task, __kindof NSObject<BJLResponse> *response))failure;

- (NSURLSessionDownloadTask *)bj_download:(NSString *)urlString
                               parameters:(NSDictionary *)parameters
                                 progress:(void (^)(NSProgress *uploadProgress))progress
                              destination:(NSURL *(^)(NSURL *targetPath, NSURLResponse *response))destination
                                  success:(void (^)(NSURLSessionDownloadTask *task, __kindof NSObject<BJLResponse> *response))success
                                  failure:(void (^)(NSURLSessionDownloadTask *task, __kindof NSObject<BJLResponse> *response))failure;

- (__kindof NSURLSessionTask *)bj_makeRequest:(NSMutableURLRequest *(^)(NSString *urlString, NSDictionary *parameters, NSError *__autoreleasing *serializationError))makeRequest
                                     makeTask:(__kindof NSURLSessionTask *(^)(NSURLRequest *request, void (^completionHandler)(NSURLResponse *response, id responseObject, NSError *error)))makeTask
                                    urlString:(NSString *)urlString
                                   parameters:(NSDictionary *)parameters
                                      success:(void (^)(__kindof NSURLSessionTask *task, __kindof NSObject<BJLResponse> *response))success
                                      failure:(void (^)(__kindof NSURLSessionTask *task, __kindof NSObject<BJLResponse> *response))failure;

@end

#pragma mark -

@protocol BJLResponse <NSObject>

+ (instancetype)responseWithObject:(id)responseObject;
+ (instancetype)responseWithError:(NSError *)error;

@property (nonatomic, readonly) BOOL isSuccess;

@end

#pragma mark -

typedef NS_ENUM(NSInteger, BJLResponseCode) {
    BJLResponseCodeSuccess = 0,
    BJLResponseCodeFailure = 1
};

@interface BJLResponse : NSObject <BJLResponse>

@property (nonatomic, readonly) BJLResponseCode code;

@property (nonatomic, readonly) NSString *message;
@property (nonatomic, readonly) NSTimeInterval timestamp;
@property (nonatomic, readonly) NSDictionary *data;
@property (nonatomic, readonly) NSError *error;

@end

@interface BJMutableResponse : BJLResponse

@property (nonatomic, readwrite) BJLResponseCode code;
@property (nonatomic, readwrite) NSString *message;
@property (nonatomic, readwrite) NSTimeInterval timestamp;
@property (nonatomic, readwrite) NSDictionary *data;
@property (nonatomic, readwrite) NSError *error;

@end
