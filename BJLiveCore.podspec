Pod::Spec.new do |s|
    s.name          = 'BJLiveCore'
    s.version       = '0.6.0-alpha'
    s.summary       = 'BJLiveCore SDK.'
    s.description   = 'BJLiveCore SDK for iOS.'

    s.homepage      = 'http://www.baijiacloud.com/'
    s.license       = 'MIT'
    s.author        = { 'MingLQ' => 'minglq.9@gmail.com' }

    s.deployment_target = '8.0'

    s.source = {
        :git => 'https://github.com/baijia/BJLiveCore-iOS.git',
        :tag => s.version.to_s
    }

    # # framework
    s.preserve_paths       = 'BJLiveCore/BJLiveCore.framework'
    s.public_header_files  = 'BJLiveCore/BJLiveCore.framework/Versions/A/Headers/**/*.h'
    s.source_files         = 'BJLiveCore/BJLiveCore.framework/Versions/A/Headers/**/*.h'
    s.resource             = 'BJLiveCore/BJLiveCore.framework/Versions/A/Resources/**/*'
    s.vendored_frameworks  = 'BJLiveCore/BJLiveCore.framework'

    s.requires_arc = true
    s.xcconfig      = {
        'GCC_PREPROCESSOR_DEFINITIONS' => '$(inherited) PODSPEC_NAME=#{s.name} PODSPEC_VERSION=#{s.version}'
    }

    s.default_subspecs = ['Core']

    s.subspec 'Core' do |ss|

        ss.frameworks = ['CoreGraphics', 'Foundation', 'UIKit']

        ss.dependency 'BJLiveBase', '~> 0.1.0-alpha'
        ss.dependency 'BJLiveBase/Base'
        ss.dependency 'BJLiveBase/Ext'
        ss.dependency 'BJLiveBase/Networking'
        ss.dependency 'BJLiveBase/WebImage/AFNetworking'

        ss.dependency 'BJLiveCore/BJHLMediaPlayer'

        ss.dependency 'AFNetworking', '~> 3.0'
        ss.dependency 'PocketSocket'
        ss.dependency 'YYModel'

        ## DEPRECATED
        ss.dependency 'LogStat', '~> 0.7.0'
        ss.dependency 'ReactiveObjC'

    end

    s.subspec 'BJHLMediaPlayer' do |ss|
        ss.xcconfig = {
            'ENABLE_BITCODE' => 'NO',
            'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES'
        }
        ss.frameworks = ['AVFoundation', 'VideoToolbox', 'GLKit']
        ss.libraries  = ['icucore', 'c++', 'stdc++.6', 'z']
        ss.vendored_frameworks = "BJLiveCore/BJHLMediaPlayer.framework"
    end

end
