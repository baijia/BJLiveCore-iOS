Pod::Spec.new do |s|
  s.name = 'BJLiveCore'
  s.version = '0.2.4-dylib13-sd'
  s.summary = 'BJLiveCore SDK.'
  s.description = 'BJLiveCore SDK for iOS.'
  s.license = 'MIT'
  s.authors = { "MingLQ"=>"minglq.9@gmail.com" }
  s.homepage = 'http://www.baijiacloud.com/'

  s.platform = :ios, "8.0"

  # git
  s.source = { :git => 'https://github.com/baijia/BJLiveCore-iOS.git', :tag => s.version.to_s }

  # # framework
  s.ios.preserve_paths       = 'BJLiveCore/BJLiveCore.framework'
  s.ios.public_header_files  = 'BJLiveCore/BJLiveCore.framework/Versions/A/Headers/**/*.h'
  s.ios.source_files         = 'BJLiveCore/BJLiveCore.framework/Versions/A/Headers/**/*.h'
  # s.ios.resource             = 'BJLiveCore/BJLiveCore.framework/Versions/A/Resources/**/*'
  s.ios.vendored_frameworks  = 'BJLiveCore/BJLiveCore.framework'

  # # library
  # s.public_header_files = 'BJLiveCore/**/*.h'
  # s.source_files = 'BJLiveCore/**/*.h'
  # s.vendored_libraries = 'BJLiveCore/**/*.a'
  # # s.resources = 'BJLiveCore/**/*.bundle'

  # # http
  # s.source = { :http => 'http://file.gsxservice.com/0baijiatools/09b9807a96075f6247fd08ea48cab16b/BJLiveCore-0.0.1.zip' }
  # s.public_header_files = 'BJLiveCore-#{s.version}/**/*.h'
  # s.source_files = 'BJLiveCore-#{s.version}/**/*.h'
  # s.vendored_libraries = 'BJLiveCore-#{s.version}/**/*.a'
  # # s.resources = 'BJLiveCore-#{s.version}/**/*.bundle'

  s.subspec 'BJHLMediaPlayer' do |ss|
    ss.frameworks = ['AVFoundation', 'VideoToolbox', 'GLKit']
    ss.libraries  = ['icucore', 'c++', 'stdc++.6', 'z']
    ss.vendored_frameworks = "BJLiveCore/BJHLMediaPlayer.framework"
  end

  # s.frameworks = ['AssetsLibrary', 'CoreGraphics', 'Foundation', 'UIKit', 'Photos']
  s.frameworks = ['CoreGraphics', 'Foundation', 'UIKit']
  # s.ios.vendored_frameworks  = 'BJLiveCore-#{s.version}/BJLiveCore.framework'

  s.requires_arc = true
  # s.xcconfig = { "ENABLE_BITCODE" => "NO" }
  s.xcconfig = { "CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES" => "YES", "ENABLE_BITCODE" => "NO" }

  s.dependency 'AFNetworking', '~> 3.0'
  s.dependency "libextobjc/EXTScope"
  s.dependency 'LogStat', '0.6.6'
  s.dependency 'JRSwizzle'
  s.dependency 'YYModel'

  # DEPRECATED
  s.dependency 'BJHL-Foundation-iOS', '1.2.13-nolog'
  s.dependency 'BJHL-Websocket-iOS', '>= 0.3.4'
  s.dependency 'LTInfiniteScrollView'
  s.dependency "libextobjc/EXTScope"
  s.dependency 'SDWebImage'
  s.dependency 'ReactiveCocoa', '~> 2.0'

end
