Pod::Spec.new do |s|

    s.name          = 'BJLiveCore'
    s.version       = '1.0.2'
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

    # # framework
    s.ios.preserve_paths       = 'frameworks/BJLiveCore.framework'
    s.ios.source_files         = 'frameworks/BJLiveCore.framework/Versions/A/Headers/**/*.h'
    s.ios.public_header_files  = 'frameworks/BJLiveCore.framework/Versions/A/Headers/**/*.h'
    s.ios.resource             = 'frameworks/BJLiveCore.framework/Versions/A/Resources/**/*'
    s.ios.vendored_frameworks  = 'frameworks/BJLiveCore.framework'
    s.frameworks    = ['CoreGraphics', 'Foundation', 'UIKit', 'WebKit']

    s.subspec 'BJHLMediaPlayer' do |ss|
        ss.xcconfig = {
            'ENABLE_BITCODE' => 'NO',
            'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES'
        }
        ss.vendored_frameworks = "frameworks/BJHLMediaPlayer.framework"
        ss.frameworks = ['AVFoundation', 'GLKit', 'VideoToolbox']
        ss.libraries = ['icucore', 'c++', 'stdc++.6', 'z']
    end

    s.dependency 'BJLiveBase', '~> 1.0.1'
    s.dependency 'BJLiveBase/Base'
    s.dependency 'BJLiveBase/Ext'
    s.dependency 'BJLiveBase/Networking'
    s.dependency 'BJLiveBase/WebImage/AFNetworking'

    s.dependency 'AFNetworking', '~> 3.0'
    s.dependency 'PocketSocket'
    s.dependency 'YYModel'

    ## DEPRECATED
    s.dependency 'LogStat', '~> 0.7.3'
    s.dependency 'ReactiveObjC'

end
