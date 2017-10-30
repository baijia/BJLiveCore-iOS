//
//  _LPLogConstants.h
//  BJLiveCore
//
//  Created by Randy on 16/5/25.
//  Copyright © 2016 Baijia Cloud. All rights reserved.
//

#ifndef _LPLogConstants_h
#define _LPLogConstants_h

typedef NS_ENUM(NSInteger, _LPLogClickOptType){
    _LP_CLICK_OPT_CHAT                 = 1,  //点击“聊天”
    _LP_CLICK_OPT_SEND_MESSAGE         = 2,  //点击“发送文字&表情”
    _LP_CLICK_OPT_USER_LIST            = 3,  //点击“在线名单”
    _LP_CLICK_OPT_AGREE_APPLY_SPEAK    = 4,  //点击“同意举手”
    _LP_CLICK_OPT_REFUSE_APPLE_SPEAK   = 5,  //点击“拒绝举手”
    _LP_CLICK_OPT_SWITCH_STUDENT_MEDIA = 6,  //切换学生视频
    _LP_CLICK_OPT_ZOOMIN_TEACHER_MEDIA = 7,  //放大老师视频
    _LP_CLICK_OPT_ZOOMIN_STUDENT_MEDIA = 8,  //放大学生视频
    _LP_CLICK_OPT_ZOOMIN_PPT           = 9,  //放大课件
    _LP_CLICK_OPT_ADD_PPT              = 10, //点击“添加课件
    _LP_CLICK_OPT_ADD_DOC              = 11, //点击“资料库”
    _LP_CLICK_OPT_ADD_PIC              = 12, //点击“图片”
    _LP_CLICK_OPT_ADD_CAMERA           = 13, //点击“拍照”
    _LP_CLICK_OPT_ADD_SUC              = 14, //课件添加成功
    _LP_CLICK_OPT_OPEN_BLUSH           = 15, //点击“开启画笔”
    _LP_CLICK_OPT_CLOSE_BLUSH          = 16, //点击“关闭画笔”
    _LP_CLICK_OPT_OPEN_CLOUD           = 17, //点击“开启录课”
    _LP_CLICK_OPT_CLOSE_CLOUD          = 18, //点击“关闭录课”
    _LP_CLICK_OPT_GIFT_HISTORY         = 19, //点击“打赏记录”
    _LP_CLICK_OPT_SCORE                = 20, //点击“评价记录” 还没添加
    _LP_CLICK_OPT_SETTING              = 21, //点击“设置”
    _LP_CLICK_OPT_OPEN_CHAT            = 22, //开启“聊天消息”
    _LP_CLICK_OPT_CLOSE_CHAT           = 23, //关闭“聊天消息”
    _LP_CLICK_OPT_OPEN_SPEAK_LIST      = 24, //开启“发言列表”
    _LP_CLICK_OPT_CLOSE_SPEAK_LIST     = 25, //关闭“发言列表”
    _LP_CLICK_OPT_OPEN_CAMERA          = 26, //开启“摄像头”
    _LP_CLICK_OPT_CLOSE_CAMERA         = 27, //关闭“摄像头”
    _LP_CLICK_OPT_OPEN_MIC             = 28, //开启“麦克风”
    _LP_CLICK_OPT_CLOSE_MIC            = 29, //关闭“麦克风”
    _LP_CLICK_OPT_OPEN_LIMIT           = 30, //开启“全体禁言”
    _LP_CLICK_OPT_CLOSE_LIMIT          = 31, //关闭“全体禁言”
    _LP_CLICK_OPT_FILL_SCREEEN         = 32, //选择“铺满”
    _LP_CLICK_OPT_FIT_SCREEN           = 33, //选择“全屏”
    _LP_CLICK_OPT_HELP                 = 34, //点击“求助”
    _LP_CLICK_OPT_EVALUATE             = 35, //点击“评论”
    _LP_CLICK_OPT_EVALUATE_SEND        = 36, //点击"发送评论"
    
};

/**
 *  CDN 类型
 */
typedef NS_ENUM(NSInteger, _LPLogCDNType) {
    /**
     *  百家
     */
    _LPLOGCDNType_BJ = 0,
    /**
     *  A系统
     */
    _LPLOGCDNType_A = 1,
    /**
     *  帝联
     */
    _LPLOGCDNType_DL = 2,
    /**
     *  网宿
     */
    _LPLOGCDNType_WS = 3,
    /**
     *  腾讯
     */
    _LPLOGCDNType_TX = 4,
    /**
     *  蓝汛
     */
    _LPLOGCDNType_LX = 5
};

#endif /* _LPLogConstants_h */
