Set WshShell = CreateObject("Wscript.Shell")
WshShell.CurrentDirectory="dosbox"
WshShell.Run "dosbox.exe -conf bc31.conf -noconsole"
