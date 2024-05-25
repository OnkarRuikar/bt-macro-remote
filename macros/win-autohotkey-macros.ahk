#Requires AutoHotkey v2.0

; uncomment following line to debug key presses
InstallKeybdHook true

; run your favorite text editor
^+F1::Run "Notepad++"

; shutdown command
^+F2::Run "shutdown.exe /s /t 5"

; restart command
^+F3::Run "shutdown.exe /r /t 5"

; move mouse
^+F6::Run "nircmd movecursor 10 10"

; turn off the monitor
^+F7::Run "nircmd.exe monitor off"

; mute default mic
^+F8::Run "nircmd.exe mutesysvolume 2"

; set volume to 40%. max volume is 65535
^+F10::Run "nircmd.exe setvolume 0 6214 6214"

; set voluem to 85%
^+F11::Run "nircmd.exe setvolume 0 55705 55705"
