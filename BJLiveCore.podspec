Pod::Spec.new do |s|

    s.name          = 'BJLiveCore'
    s.version       = '1.1.0-alpha'
    s.summary       = 'BJLiveCore SDK.'
    s.description   = 'BJLiveCore SDK for iOS.'

    s.homepage      = 'http://www.baijiayun.com/'
    s.license       = 'MIT'
    s.author        = { 'MingLQ' => 'minglq.9@gmail.com' }

    s.platform      = :ios
    s.ios.deployment_target = '8.0'

    s.source = {
        :git => 'https://github.com/baijia/BJLiveCore-iOS.git',
        :tag => s.version.to_s
    }

    s.default_subspecs = ['static']

    s.subspec 'static' do |ss|
        ss.ios.preserve_paths       = 'frameworks/BJLiveCore.framework'
        ss.ios.source_files         = 'frameworks/BJLiveCore.framework/Versions/A/Headers/**/*.h'
        ss.ios.public_header_files  = 'frameworks/BJLiveCore.framework/Versions/A/Headers/**/*.h'
        ss.ios.resource             = 'frameworks/BJLiveCore.framework/Versions/A/Resources/**/*'
        ss.ios.vendored_frameworks  = 'frameworks/BJLiveCore.framework'
        ss.frameworks               = ['CoreGraphics', 'Foundation', 'UIKit', 'WebKit']
        ss.dependency 'BJLiveCore/BJHLMediaPlayer'
        ss.dependency 'LogStat', '~> 0.7.3'
    end

    s.subspec 'dynamic' do |ss|
        ss.ios.preserve_paths       = 'frameworks/BJLiveCore-dylib.framework'
        ss.ios.source_files         = 'frameworks/BJLiveCore-dylib.framework/Versions/A/Headers/**/*.h'
        ss.ios.public_header_files  = 'frameworks/BJLiveCore-dylib.framework/Versions/A/Headers/**/*.h'
        ss.ios.resource             = 'frameworks/BJLiveCore-dylib.framework/Versions/A/Resources/**/*'
        ss.ios.vendored_frameworks  = 'frameworks/BJLiveCore-dylib.framework'
        ss.frameworks               = ['CoreGraphics', 'Foundation', 'UIKit', 'WebKit']
        ss.dependency 'BJLiveCore/BJHLMediaPlayer'
        ss.dependency 'LogStat', '0.7.3-dylib'
    end

    s.subspec 'BJHLMediaPlayer' do |ss|
        ss.xcconfig = {
            'ENABLE_BITCODE' => 'NO',
            'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES'
        }
        ss.vendored_frameworks = "frameworks/BJHLMediaPlayer.framework"
        ss.frameworks = ['AVFoundation', 'GLKit', 'VideoToolbox']
        ss.libraries = ['icucore', 'c++', 'stdc++.6', 'z']
    end

    s.dependency 'BJLiveBase', '~> 1.1.0'
    s.dependency 'BJLiveBase/Base'
    s.dependency 'BJLiveBase/Ext'
    s.dependency 'BJLiveBase/Networking'
    s.dependency 'BJLiveBase/WebImage/AFNetworking'

    s.dependency 'AFNetworking', '~> 3.0'
    s.dependency 'PocketSocket'
    s.dependency 'YYModel'

    ## DEPRECATED
    s.dependency 'ReactiveObjC'

end
