netsh interface ip set address name="�ϰ�s�u" source=static addr=192.168.11.83 mask=255.255.255.0
netsh interface ip set address name="�ϰ�s�u" gateway=192.168.11.254 gwmetric=0
netsh interface ip set dns name="�ϰ�s�u" source=static addr=61.67.112.11 register=PRIMARY
netsh interface ip add dns name="�ϰ�s�u" addr=61.67.112.12 index=2
exit
