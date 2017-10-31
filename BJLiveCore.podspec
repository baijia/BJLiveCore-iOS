Pod::Spec.new do |s|
  s.name = "BJLiveCore"
  s.version = "0.2.4-dylib07-dylib01"
  s.summary = "BJLiveCore SDK."
  s.license = "MIT"
  s.authors = {"MingLQ"=>"minglq.9@gmail.com"}
  s.homepage = "http://www.baijiacloud.com/"
  s.description = "BJLiveCore SDK for iOS."
  s.frameworks = ["CoreGraphics", "Foundation", "UIKit"]
  s.requires_arc = true
  s.xcconfig = {"ENABLE_BITCODE"=>"NO", "CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES"=>"YES"}
  s.source = { :git => 'https://github.com/baijia/BJLiveCore-iOS.git', :tag => s.version.to_s }

  s.ios.deployment_target    = '8.0'
  s.ios.vendored_frameworks   = 'BJLiveCore/*.framework'
  
  s.dependency 'AFNetworking', '~> 3.0'
#  s.dependency 'BJHL-AVSDK-iOS', '>= 0.1.9'
  s.dependency "libextobjc/EXTScope"
  s.dependency 'LogStat', '0.6.6-dylib'
  s.dependency 'JRSwizzle'
  s.dependency 'YYModel'
  s.dependency 'BJHL-Foundation-iOS', '1.2.13-nolog'
  s.dependency 'BJHL-Websocket-iOS', '>= 0.3.4'
  s.dependency 'LTInfiniteScrollView'

  s.dependency 'SDWebImage'
  # Build Settings > Preprocessor Macros + SD_WEBP=1
  # s.dependency 'SDWebImage/WebP'
  # s.dependency  'iOS-WebP'

  s.dependency 'ReactiveCocoa', '~> 2.0'
  
end
