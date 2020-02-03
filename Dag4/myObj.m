function f = myObj(z)
mx = 6;
mu = 2;
Q_ext = zeros(mx,mx);
Q_ext(1,1) = 2;                            % Weight on state x1
Q_ext(2,2) = 0;                            % Weight on state x2
Q_ext(3,3) = 0;                            % Weight on state x3
Q_ext(4,4) = 0; 
Q_ext(5,5) = 0; 
Q_ext(6,6) = 0; 

% Weight on state x4
P1 = [1 0;
      0 1];                                % Weight on input
Q = gen_q(Q_ext,P1,40,40); 
    f = Q*z;
end