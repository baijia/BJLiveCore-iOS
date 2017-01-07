Pod::Spec.new do |s|
  s.name = 'BJLiveCore'
  s.version = '0.1.0'
  s.summary = 'BJLiveCore SDK.'
  s.license = 'MIT'
  s.authors = {"MingLQ"=>"minglq.9@gmail.com"}
  s.homepage = 'http://www.baijiacloud.com/'
  s.description = 'BJLiveCore SDK for iOS.'
  s.requires_arc = true

  s.ios.deployment_target    = '7.0'
  # s.frameworks = ['AssetsLibrary', 'CoreGraphics', 'Foundation', 'UIKit', 'Photos']
  s.frameworks = ['CoreGraphics', 'Foundation', 'UIKit']

  # s.ios.vendored_frameworks  = 'BJLiveCore-#{s.version}/BJLiveCore.framework'

  # http
  # s.source = { :http => 'http://file.gsxservice.com/0baijiatools/09b9807a96075f6247fd08ea48cab16b/BJLiveCore-0.0.1.zip' }
  # s.public_header_files = 'BJLiveCore-#{s.version}/**/*.h'
  # s.source_files = 'BJLiveCore-#{s.version}/**/*.h'
  # s.vendored_libraries = 'BJLiveCore-#{s.version}/**/*.a'
  # # s.resources = 'BJLiveCore-#{s.version}/**/*.bundle'

  # git
  s.source = { :git => 'https://github.com/baijia/BJLiveCore-iOS.git', :tag => s.version.to_s }
  s.public_header_files = 'BJLiveCore/**/*.h'
  s.source_files = 'BJLiveCore/**/*.h'
  s.vendored_libraries = 'BJLiveCore/**/*.a'
  # s.resources = 'BJLiveCore/**/*.bundle'

  s.dependency 'BJHL-AVSDK-iOS', '>= 0.1.9'
  s.dependency 'BJHL-Foundation-iOS'
  s.dependency 'BJHL-Websocket-iOS', '>= 0.3.2'
  s.dependency "libextobjc/EXTScope"
  s.dependency 'LogStat'
  s.dependency 'JRSwizzle'
  s.dependency 'YYModel'

  # DEPRECATED
  s.dependency 'LKDBHelper'
  s.dependency 'LTInfiniteScrollView'
  s.dependency 'Masonry'
  s.dependency 'SDWebImage'
  s.dependency 'ReactiveCocoa', '~> 2.0'

end
