clear
n=-0.01:0.005:0.015
n1=-0.012:0.00001:0.018
y=cos(2*3.14*83*n);
y1=cos(2*3.14*83*n1);
stem(n,y,'r+'),hold on,plot(n1,y1,'b'),hold off;