BJLiveCore
==========

详细的文档、示例、常见问题等请访问 百家云官方网站 [http://www.baijiayun.com/](http://www.baijiayun.com/)

- [官方文档](http://dev.baijiayun.com/default/wiki/index)
- [API 文档](https://baijia.github.io/BJLiveCore-iOS/)
- [版本记录](./wiki/CHANGELOG.md)
- [更多 SDK](https://github.com/baijia)

## 迁移

- **所有项目现已迁移到 http://git.baijiashilian.com/open-ios/**

- **引入 1.0 以上版本 SDK 需要修改 Podfile 中的 source**

```ruby
source 'https://github.com/CocoaPods/Specs.git'
source 'http://git.baijiashilian.com/open-ios/specs.git'
```

- **引入 1.0 以前版本继续保持原有的 Podfile 中的 source**

```ruby
source 'https://github.com/CocoaPods/Specs.git'
source 'https://github.com/baijia/specs.git'
```

## 集成 SDK

BJLiveCore 会依赖一些第三方库，建议使用 CocoaPods 方式集成；
- Podfile 中设置 source
```ruby
source 'https://github.com/CocoaPods/Specs.git'
source 'https://github.com/baijia/specs.git'
```
- Podfile 中引入 BJLiveCore
```ruby
pod 'BJLiveCore', '~> 1.0'
```

## 工程设置

- 隐私权限：在 `Info.plist` 中添加麦克风、摄像头、相册访问描述；
```
Privacy - Microphone Usage Description       用于语音上课、发言
Privacy - Camera Usage Description           用于视频上课、发言，拍照上传课件、聊天发图
Privacy - Photo Library Usage Description    用于上传课件、聊天发图
```
- 后台任务：在 `Project > Target > Capabilities` 中打开 `Background Modes` 开关、选中 `Audio, AirPlay, and Picture in Picture`；

## 版本升级

版本号格式为 `大版本.中版本.小版本[-alpha(测试版本)/beta(预览版本)]`：

- 测试版本和预览版本可能很不稳定，请勿随意尝试；

- 小版本升级只改 BUG、UI 样式优化，不会影响功能；

- 中版本升级、修改功能，更新 UI 风格、布局，会新增 API、标记 API 即将废弃，但不会导致现有 API 不可用；

- 大版本任何变化都是有可能的；

首次集成建议选择最新正式版本(版本号中不带有 `alpha`、`beta` 字样)，**版本升级后请仔细阅读 [ChangeLog](./wiki/CHANGELOG.md)**，指定版本的方式有一下几种：

- 固执型：`pod update` 时不会做任何升级，但可能无法享受到最新的 BUG 修复，建议用于 0.x 版本；
```ruby
pod 'BJLiveCore', '1.0.0'
```
- 稳妥型(**推荐**)：`pod update` 时只会升级到更稳定的小版本，而不会升级中版本和大版本，不会影响功能和产品特性，升级后需要 **适当测试**；
```ruby
pod 'BJLiveCore', '~> 1.0.0'
```
- 积极型：`pod update` 时会升级中版本，但不会升级大版本，及时优化，但不会导致编译出错不可用，升级后需要 **全面测试**；
```ruby
pod 'BJLiveCore', '~> 1.0'
```
- 激进型(**不推荐**)：`pod update` 时会升级大版本，可能导致编译出错、必须调整代码，升级后需要 **严格测试**；
```ruby
pod 'BJLiveCore'
```

