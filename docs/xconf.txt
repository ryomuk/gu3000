# フレームバッファ/dev/fb0をVFDに表示するための設定

(1) /dev/fb0 を作成 (HDMI出力は外す)
/boot/config.txtに以下を追加
---ここから--
framebuffer_height=128	
framebuffer_width=256
hdmi_cvt=256 128 60 3 0 0 0
hdmi_group=2
hdmi_mode=87
hdmi_force_hotplug=1
---ここまで--

(2)/dev/fb0 をVFDに逐次表示するコマンド
examples/showfb
examples/showfb.sh
を/usr/local/binにコピー

(3)上記コマンドをサービスとして起動
/etc/systemd/system/showfb.service を作成、下記を記述。
---ここから--
[Unit]
Description=Show /dev/fb0 on VFD module
After=console-setup.service

[Service]
ExecStart=/usr/local/bin/showfb.sh
#ExecStart=/usr/local/bin/showfb
WorkingDirectory=/tmp
#StandardOutput=null
#StandardInput=null
Restart=always

[Install]
WantedBy=multi-user.target
---ここまで--
sudo systemctrl enable showfb.service
で、サービスを有効化。


#Xorg用設定
/etc/X11/にxorg.confが無い
/usr/shar/X11/xorg.conf.dがある

下記内容のxorg.confを/etc/X11/xorg.confに置く

---ここから--
Section "Device"
Identifier "testdevice"
Driver  "fbdev"
Option "fbdev" "/dev/fb0"
EndSection

Section "Monitor"
Identifier "testmonitor"
EndSection

Section "Screen"
Identifier "screen"
Device "testdevice"
Monitor "testmonitor"
EndSection

Section "ServerLayout"
Identifier "default"
Screen 0 "screen" 0 0
EndSection
---ここまで--

