
mac-control-volume
macOS 下控制系统音量。
others：[windows 下控制系统音量](https://github.com/houchaowei/win-control-volume)

done：
- [x] 获取扬声器音量：执行命令 volume-mac -o
- [x] 设置扬声器音量：执行命令 volume-mac -s 50
- [x] 获取麦克风音量：执行命令 volume-mac -mo
- [x] 设置麦克风音量：执行命令 volume-mac -ms 50
- [x] 获取静音状态：执行命令 volume-mac -mute
- [x] 设置静音状态：执行命令 volume-mac -mt [true/false]
- [x] 监听系统输出音量变化，当音量变化时，会输出当前音量
- [x] 监听系统输入音量变化，当音量变化时，会输出当前音量


Usage:
```sh
$ ./volume-mac -o
```

Releases:
https://github.com/houchaowei/mac-control-volume/releases/tag/v1.0.0