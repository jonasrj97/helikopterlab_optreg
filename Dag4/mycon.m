function [c, ceq] = mycon(x)
    
   N = 80;
   
   %c = 0.2*exp(-20*(x(1:6:N*6)-2*pi/3).^2)-x(5:6:N*6);
   %c = 1000*exp(((x(1:6:N*6)-2*pi/3).^2))-x(5:6:N*6);
   vect = 1:N;
    vect = vect';
   c = [7*sin((vect)/5)-x(5:6:N*6); x(5:6:N*6) - 7*sin((vect)/5)+0.02];
       
   ceq = [];
end