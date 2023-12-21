
mac-control-volume
macOS 下控制系统音量。

done：

 获取扬声器音量：执行命令 volume.exe -o
 设置扬声器音量：执行命令 volume.exe -s 50
 获取麦克风音量：执行命令 volume.exe -mo
 设置麦克风音量：执行命令 volume.exe -ms 50
 获取静音状态：执行命令 volume.exe -mute
 设置静音状态：执行命令 volume.exe -mt [true/false]
 监听系统输出音量变化，当音量变化时，会输出当前音量
 监听系统输入音量变化，当音量变化时，会输出当前音量