Pod::Spec.new do |s|

    s.name          = 'BJLiveCore'
    s.version       = '1.3.0'
    s.summary       = 'BJLiveCore SDK.'
    s.description   = 'BJLiveCore SDK for iOS.'

    s.homepage      = 'http://www.baijiayun.com/'
    s.license       = 'MIT'
    s.author        = { 'MingLQ' => 'minglq.9@gmail.com' }

    s.platform      = :ios
    s.ios.deployment_target = '8.0'

    s.source = {
        :git => 'http://git.baijiashilian.com/open-ios/BJLiveCore.git',
        :tag => s.version.to_s
    }

    s.default_subspecs = ['static']

    s.subspec 'static' do |ss|
        ss.ios.preserve_paths       = 'frameworks/BJLiveCore.framework'
        ss.ios.source_files         = 'frameworks/BJLiveCore.framework/Versions/A/Headers/**/*.h'
        ss.ios.public_header_files  = 'frameworks/BJLiveCore.framework/Versions/A/Headers/**/*.h'
        # ss.ios.resource             = 'frameworks/BJLiveCore.framework/Versions/A/Resources/**/*'
        ss.ios.vendored_frameworks  = 'frameworks/BJLiveCore.framework'
        ss.frameworks               = ['CoreGraphics', 'CoreTelephony', 'Foundation', 'UIKit', 'WebKit']
        ss.dependency 'BJLiveCore/BJHLMediaPlayer'
        ss.dependency 'BJLLogStat', '~> 0.9.0'
    end

    # TODO: Assets.car
    # s.subspec 'dynamic' do |ss|
    #     ss.ios.preserve_paths       = 'frameworks/dylib/BJLiveCore.framework'
    #     ss.ios.source_files         = 'frameworks/dylib/BJLiveCore.framework/Headers/**/*.h'
    #     ss.ios.public_header_files  = 'frameworks/dylib/BJLiveCore.framework/Headers/**/*.h'
    #     # ss.ios.resource             = 'frameworks/dylib/BJLiveCore.framework/Resources/**/*'
    #     ss.ios.vendored_frameworks  = 'frameworks/dylib/BJLiveCore.framework'
    #     ss.frameworks               = ['CoreGraphics', 'Foundation', 'UIKit', 'WebKit']
    #     ss.dependency 'BJLiveCore/BJHLMediaPlayer'
    #     ss.dependency 'BJLLogStat', '0.9.0'
    # end

    s.subspec 'BJHLMediaPlayer' do |ss|
        ss.xcconfig = {
            'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES',
            "ENABLE_BITCODE" => "NO"
        }
        ss.vendored_frameworks = "frameworks/BJHLMediaPlayer.framework"
        ss.frameworks = ['AVFoundation', 'GLKit', 'VideoToolbox']
        ss.libraries = ['icucore', 'c++', 'stdc++.6', 'z']
    end

    s.dependency "BJLiveBase", "~> 1.3.0"
    s.dependency "BJLiveBase/Base"
    s.dependency "BJLiveBase/Ext"
    s.dependency "BJLiveBase/Networking"
    s.dependency "BJLiveBase/PocketSocket/Client"
    s.dependency "BJLiveBase/WebImage/AFNetworking"
    s.dependency "BJLiveBase/YYModel"

end
