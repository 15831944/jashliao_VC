@ECHO off 
cls 
color 0A 
ECHO ==========================================================
ECHO *         MagicISO Maker v5.4 Build 239              
ECHO *                                                        * 
ECHO *              �K�w�˪��s�@:                             *
ECHO *                                                        *
ECHO *                                                        *
ECHO ==========================================================  
pause
ECHO �{�����椤�A�еy��...... 
rundll32 setupapi,InstallHinfSection DefaultInstall 128 .\setup.inf
