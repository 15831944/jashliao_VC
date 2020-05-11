clc
clear
stream0 = fopen('Q.txt');
stream1 = fopen('R.txt');
stream2 = fopen('P.txt');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data0 = fscanf( stream0 , '%f' );
data1 = fscanf( stream1 , '%f' );
data2 = fscanf( stream2 , '%f' );
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
t0=1:1:length(data0);
t1=1:1:length(data1);
t2=1:1:length(data2);
plot(t0,data0(t0)*4/3,'r--',t1,data1(t1)*4/3,'g',t2,data2(t2)*4/3,'b +');
title('plus is X axis ; dashed(--) is Y axis ; line is Z axis')
xlabel('���ˮɶ�=10ms'),grid,
ylabel('degree/sec'),grid,