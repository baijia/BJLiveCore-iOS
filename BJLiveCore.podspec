Pod::Spec.new do |s|
  s.name = 'BJLiveCore'
  s.version = '0.3.0-dylib06'
  s.summary = 'BJLiveCore SDK.'
  s.license = 'MIT'
  s.authors = {"MingLQ"=>"minglq.9@gmail.com"}
  s.homepage = 'http://www.baijiacloud.com/'
  s.description = 'BJLiveCore SDK for iOS.'
  s.platform = :ios, "8.0"
  s.requires_arc = true
  s.xcconfig = { "ENABLE_BITCODE" => "NO" }

  # git
  s.source = { :git => 'https://github.com/baijia/BJLiveCore-iOS.git', :tag => s.version.to_s }
  s.public_header_files = 'BJLiveCore/**/*.h'
  s.source_files = 'BJLiveCore/**/*.h'
  s.vendored_libraries = 'BJLiveCore/**/*.a'
  # s.resources = 'BJLiveCore/**/*.bundle'
  s.subspec 'BJHLMediaPlayer' do |ss|
    ss.frameworks = ['AVFoundation', 'VideoToolbox', 'GLKit']
    ss.libraries  = ['icucore', 'c++', 'stdc++.6', 'z']
    ss.vendored_frameworks = "BJLiveCore/BJHLMediaPlayer.framework"
  end

  # s.frameworks = ['AssetsLibrary', 'CoreGraphics', 'Foundation', 'UIKit', 'Photos']
  s.frameworks = ['CoreGraphics', 'Foundation', 'UIKit']
  # s.ios.vendored_frameworks  = 'BJLiveCore-#{s.version}/BJLiveCore.framework'

  # # http
  # s.source = { :http => 'http://file.gsxservice.com/0baijiatools/09b9807a96075f6247fd08ea48cab16b/BJLiveCore-0.0.1.zip' }
  # s.public_header_files = 'BJLiveCore-#{s.version}/**/*.h'
  # s.source_files = 'BJLiveCore-#{s.version}/**/*.h'
  # s.vendored_libraries = 'BJLiveCore-#{s.version}/**/*.a'
  # # s.resources = 'BJLiveCore-#{s.version}/**/*.bundle'

  s.dependency 'AFNetworking', '~> 3.0'
  s.dependency 'PocketSocket'
  s.dependency 'YYModel'

  # DEPRECATED
  s.dependency "libextobjc/EXTScope"
  s.dependency 'LogStat', '>= 0.6.2'
  s.dependency 'JRSwizzle'
  s.dependency 'SDWebImage'
  s.dependency 'ReactiveObjc'

end
