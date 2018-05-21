@echo off
:start
python C:\Users\Abhishek\Desktop\project\human-detection\check.py
python C:\Users\Abhishek\Desktop\project\human-detection\detect.py --image %C:\Users\Abhishek\Desktop\project\human-detection
goto start
pause