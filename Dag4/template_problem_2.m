% TTK4135 - Helicopter lab
% Hints/template for problem 2.
% Updated spring 2018, Andreas L. Flï¿½ten
 
%% Initialization and model definition
init06; % Change this to the init file corresponding to your helicopter
 
% Discrete time system model. x = [lambda r p p_dot]'

 

 

%  
% % Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
% %Q1 = zeros(mx,mx);
% %Q1(1,1) = 2;                            % Weight on state x1
% Q1(2,2) = 0;                            % Weight on state x2
% Q1(3,3) = 0;                            % Weight on state x3
% Q1(4,4) = 0;                            % Weight on state x4
% P1 = 1;                                % Weight on input
% Q = gen_q(Q1,P1,N,M);                                  % Generate Q, hint: gen_q
% c = 0;    %TROR DENNE ER 0 MEN IKKE SIKKER    % Generate c, this is the linear constant term in the QP
%  
% %% Generate system matrixes for linear model
% Aeq = gen_aeq(A1,B1,N,mx,mu);   % Generate A, hint: gen_aeq
% beq = zeros(400,1);
% tempM = A1*x0;
% for i = 1:4
%     beq(i) = tempM(i);
% end
%  
% %[(A1*x0)' 0]'        % Generate b
%  
% %% Solve QP problem with linear model
% tic
% [z,lambda] = quadprog(Q, [], [], [], Aeq, beq, vlb, vub, z0); % hint: quadprog. Type 'doc quadprog' for more info 
% t1=toc;
%  
%  
% % Calculate objective value
% phi1 = 0.0;
% PhiOut = zeros(N*mx+M*mu,1);
% for i=1:N*mx+M*mu
%   phi1=phi1+Q(i,i)*z(i)*z(i);
%   PhiOut(i) = phi1;
% end
%  
% %% Extract control inputs and states
% u_star  = [z(N*mx+1:N*mx+M*mu);z(N*mx+M*mu)]; % Control input from solution
%  
% x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
% x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
% x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
% x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution
%  
% num_variables = 5/delta_t;
% zero_padding = zeros(num_variables,1);
% unit_padding  = ones(num_variables,1);
% 
% u_star   = [zero_padding; u_star; zero_padding];
% x1  = [pi*unit_padding; x1; zero_padding];
% x2  = [zero_padding; x2; zero_padding];
% x3  = [zero_padding; x3; zero_padding];
% x4  = [zero_padding; x4; zero_padding];
% x_star = [x1 x2 x3 x4];
% t = [0:delta_t:delta_t*(length(u_star)-1)]';
% x2model =[t x_star];
% u2model = [t u_star];
% 
% %% Plotting
% fontsize = 20;
% 
% figure(2)
% subplot(511)
% stairs(t,u_star),grid
% ylabel('u')
% ax = gca; %get the axes handle of the current axes
% ax.FontSize = fontsize;
% ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
% subplot(512)
% plot(t,x1,'m',t,x1,'mo'),grid
% ax = gca; %get the axes handle of the current axes
% ax.FontSize = fontsize;
% ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
% ylabel('lambda')
% subplot(513)
% plot(t,x2,'m',t,x2','mo'),grid
% ylabel('r')
% ax = gca; %get the axes handle of the current axes
% ax.FontSize = fontsize;
% ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
% subplot(514)
% plot(t,x3,'m',t,x3,'mo'),grid
% ylabel('p')
% ax = gca; %get the axes handle of the current axes
% ax.FontSize = fontsize;
% ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
% subplot(515)
% plot(t,x4,'m',t,x4','mo'),grid
% xlabel('tid (s)'),ylabel('pdot')
% ax = gca; %get the axes handle of the current axes
% ax.FontSize = fontsize;
% ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
% 

%%

%dag 3
% delta_t = 0.25; % sampling time
% 
% diagQ = ones(4, 1);
% diagR = ones(1,1);
% 
% diagQ(1) = 10; % travel
% diagQ(2);
% diagQ(3);
% diagQ(4);
% 
% diagR(1) = 2.5; %input pitch ref
% 
% Q = diag(diagQ);
% R = diag(diagR);
% 
% [K, S, e] = dlqr(A1, B1, Q, R);
% 
% 
% K_transpose = K.';

%%

%Dag 4
N=320;
M=N;
delta_t = 1; % sampling time

A_ext = [0 1 0 0 0 0;
        0 0 -K_2 0 0 0;
        0 0 0 1 0 0;
        0 0 -K_1*K_pp -K_1*K_pd 0 0;
        0 0 0 0 0 1;
        0 0 0 0 -K_3*K_ep -K_3*K_ed];
    
B_ext = [0 0;
         0 0;
         0 0;
         K_1*K_pp 0;
         0 0;
         0 K_3*K_ep];

A_disc = eye(6) + A_ext*delta_t;
B_disc = B_ext*delta_t;
x_0 = [pi;
       0;
       0;
       0;
       0;
       0];
   
mx = size(A_disc,2); % Number of states (number of columns in A)
mu = size(B_disc,2);
A_ext_eq = gen_aeq(A_disc, B_disc, N, mx, mu);
b_ext_eq = zeros(N*mx,1);
tempM = A_disc*x_0;
for i = 1:6
    b_ext_eq(i) = tempM(i);
end




% Bounds
ul_ext      = -Inf*ones(mu,1);              % Lower bound on input2 (no bound)
uu_ext      = Inf*ones(mu,1);               % Upper bound on input2 (no bound)
ul_ext(1)      = -pi/6;                  % Lower bound on control
uu_ext(1)      = pi/6;                   % Upper bound on control
%elev_r_l = -2*pi/180;
%elev_r_u = 2*pi/180;
%travel_r_l = -15*pi/180;
%travel_r_u = 15*pi/180;

xl_ext      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu_ext      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl_ext(3)   = ul_ext(1);                           % Lower bound on state x3
xu_ext(3)   = uu_ext(1);                           % Upper bound on state x3
%xl_ext(6) = elev_r_l;
%xu_ext(6) = elev_r_u;
%xl_ext(2) = travel_r_l;
%xu_ext(2) = travel_r_u;
% Generate constraints on measurements and inputs
[vlb_ext,vub_ext]       = gen_constraints(N,M,xl_ext,xu_ext,ul_ext,uu_ext); % hint: gen_constraints
vlb_ext(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub_ext(N*mx+M*mu)  = 0;                    % We want the last input to be zero






c = @mycon;

Q_ext = zeros(mx,mx);
Q_ext(1,1) = 2;                            % Weight on state x1
Q_ext(2,2) = 0;                            % Weight on state x2
Q_ext(3,3) = 0;                            % Weight on state x3
Q_ext(4,4) = 0; 
Q_ext(5,5) = 0; 
Q_ext(6,6) = 0; 

% Weight on state x4
P1 = 2*[1 0;
      0 1];                                % Weight on input
Q = gen_q(Q_ext,P1,N,M); 

obj = @(z) 1/2*z'*Q*z;
% options = optimoptions('fmincon', 'Display', 'iter', 'Algorithm', 'sqp');
% Time horizon and initialization
                                % Time horizon for inputs
z  = [x_0; zeros((N-1)*mx+M*mu,1)];        % Initialize z for the whole horizon %SKAL DENNE LIGGE ELLER STÃ…???
z_0 = z;                        % Initial value for optimization   
test = mycon(z);


tic
[z_ext,lambda] = fmincon(obj, z_0, [], [], A_ext_eq, b_ext_eq, vlb_ext, vub_ext, c);%, options); 
t1=toc;

%% Extract control inputs and states
u1_star  = [z_ext(N*mx+1:2:N*mx+M*mu);z_ext(N*mx+M*mu-1)]; % Control input from solution
u2_star  = [z_ext(N*mx+2:2:N*mx+M*mu);z_ext(N*mx+M*mu)]; % Control input from solution

x1 = [x_0(1);z_ext(1:mx:N*mx)];              % State x1 from solution
x2 = [x_0(2);z_ext(2:mx:N*mx)];              % State x2 from solution
x3 = [x_0(3);z_ext(3:mx:N*mx)];              % State x3 from solution
x4 = [x_0(4);z_ext(4:mx:N*mx)];              % State x4 from solution
x5 = [x_0(5);z_ext(5:mx:N*mx)];  
x6 = [x_0(6);z_ext(6:mx:N*mx)];  
 
num_variables = 5/delta_t;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u1_star   = [zero_padding; u1_star; zero_padding];

u2_star   = [zero_padding; u2_star; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

x_star = [x1 x2 x3 x4 x5 x6];
t = [0:delta_t:delta_t*(length(u1_star)-1)]';
x2model =[t x_star];
u_1_2model = [t u1_star];
u_2_2model = [t u2_star];

%% Plotting
fontsize = 20;

figure(2)
subplot(421)
stairs(t,u1_star),grid
ylabel('u')
ax = gca; %get the axes handle of the current axes
ax.FontSize = fontsize;
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
subplot(422)
plot(t,x1,'m',t,x1,'mo'),grid
ax = gca; %get the axes handle of the current axes
ax.FontSize = fontsize;
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
ylabel('lambda')
subplot(423)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
ax = gca; %get the axes handle of the current axes
ax.FontSize = fontsize;
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
subplot(424)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
ax = gca; %get the axes handle of the current axes
ax.FontSize = fontsize;
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
subplot(425)
plot(t,x4,'m',t,x4','mo'),grid
xlabel('tid (s)'),ylabel('pdot')
ax = gca; %get the axes handle of the current axes
ax.FontSize = fontsize;
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
subplot(426)
plot(t,x5,'m',t,x5','mo'),grid
xlabel('tid (s)'),ylabel('elevation')
ax = gca; %get the axes handle of the current axes
ax.FontSize = fontsize;
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
subplot(427)
plot(t,x6,'m',t,x6','mo'),grid
xlabel('tid (s)'),ylabel('e_rate')
ax = gca; %get the axes handle of the current axes
ax.FontSize = fontsize;
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
subplot(428)
stairs(t,u2_star),grid
ylabel('u2')
ax = gca; %get the axes handle of the current axes
ax.FontSize = fontsize;
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts

%%Feedback

% 
diagQ = ones(6, 1);
diagR = ones(2,1);
% 
diagQ(1) = pi; % travel
diagQ(2);
diagQ(3);
diagQ(4);
diagQ(5) = 100; %elev
diagQ(6);

diagR(1) = 1; %input pitch ref
diagR(2) = 1;
Q = diag(diagQ);
R = diag(diagR);
% 
[K, S, e] = dlqr(A_disc, B_disc, Q, R);

% K_transpose = K.';
