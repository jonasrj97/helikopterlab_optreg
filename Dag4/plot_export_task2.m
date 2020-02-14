%% Example data
%t = linspace(0,5,200);
close all
load travel.mat
load travelrate.mat
load pitch.mat
load pitchrate.mat
load elevationrate.mat
load elevation.mat


t1 = tra(1, :);
travel = tra(2, :);
t2 = tr(1, :);
travelrate = tr(2, :);
t3 = p(1, :);
pitch = p(2, :);
t4 = pr(1, :);
pitchrate = pr(2, :);
t5 = e(1, :);
elevation = e(2, :);
t6 = er(1, :);
elevationrate = er(2, :);


%% Define figure size
width = 10; % cm
height = 10; % cm
fontsize = 18; % points
x = 20; y = 20; % Where on the screen the plot will appear, not important.

set(0,'DefaultTextInterpreter', 'latex') % Interpret (most) text as LaTeX.

%% Set up the figure
fig1 = figure(1);
fig1.Units = 'centimeters';
fig1.Position = [x y width height];

%% Plot the data
subplot(3,2,2);
plot(t2, travelrate);
hold on
plot(t, x2*180/pi);
%% Set up the properties of the axes
% One figure can have multiple axes, for example if we use subplot
ax = gca; %get the axes handle of the current axes
% Set the fontsize and units correctly
ax.FontUnits = 'points';
ax.FontSize = fontsize;
% (not important) Change the 'ticks' on the y label
%ax.YTick = -pi:(pi/2):pi;
%ax.YTickLabel = {'$-\pi$', '$-\frac{\pi}{2}$','$0$','$\frac{\pi}{2}$','$\pi$'};
ax.TickLabelInterpreter = 'latex'; %Interpret Tick labels as latex
% Label the axes, set up legend and title
xlabel('Time [s]')
ylabel('$Travel rate$ [deg/s]')
legend('Travel rate','Optimal', 'Location','best')
title('Travel rate')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts

subplot(3,2,1);
plot(t1, travel);
hold on
plot(t, x1*180/pi);
%% Set up the properties of the axes
% One figure can have multiple axes, for example if we use subplot
ax = gca; %get the axes handle of the current axes
% Set the fontsize and units correctly
ax.FontUnits = 'points';
ax.FontSize = fontsize;
% (not important) Change the 'ticks' on the y label
%ax.YTick = -pi:(pi/2):pi;
%ax.YTickLabel = {'$-\pi$', '$-\frac{\pi}{2}$','$0$','$\frac{\pi}{2}$','$\pi$'};
ax.TickLabelInterpreter = 'latex'; %Interpret Tick labels as latex
% Label the axes, set up legend and title
xlabel('Time [s]')
ylabel('$Travel$ [deg]')
legend('Travel','Optimal', 'Location','best')
title('Travel')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
%%
subplot(3,2,4);
plot(t6, elevationrate);
hold on;
plot(t, x6*180/pi);
% One figure can have multiple axes, for example if we use subplot
ax = gca; %get the axes handle of the current axes
% Set the fontsize and units correctly
ax.FontUnits = 'points';
ax.FontSize = fontsize;
% (not important) Change the 'ticks' on the y label
%ax.YTick = -pi:(pi/2):pi;
%ax.YTickLabel = {'$-\pi$', '$-\frac{\pi}{2}$','$0$','$\frac{\pi}{2}$','$\pi$'};
ax.TickLabelInterpreter = 'latex'; %Interpret Tick labels as latex
% Label the axes, set up legend and title
xlabel('Time [s]')
ylabel('$Elevation rate$ [deg/s]')
legend('Elevation rate', 'Optimal', 'Location','NorthEast')
title('Elevation rate')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
%%
subplot(3,2,5);
plot(t3, pitch);
hold on
plot(t, x3*180/pi);
hold on;
plot(t, u1_star*180/pi, 'black--');
% One figure can have multiple axes, for example if we use subplot
ax = gca; %get the axes handle of the current axes
% Set the fontsize and units correctly
ax.FontUnits = 'points';
ax.FontSize = fontsize;
% (not important) Change the 'ticks' on the y label
%ax.YTick = -pi:(pi/2):pi;
%ax.YTickLabel = {'$-\pi$', '$-\frac{\pi}{2}$','$0$','$\frac{\pi}{2}$','$\pi$'};
ax.TickLabelInterpreter = 'latex'; %Interpret Tick labels as latex
% Label the axes, set up legend and title
xlabel('Time [s]')
ylabel('$Pitch$ [deg]')
legend('Pitch', 'Optimal', 'u_{star}', 'Location','best')
title('Pitch')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
%%
subplot(3,2,3);
plot(t5, elevation);
hold on;
plot(t, x5*180/pi + 30 );
hold on;
plot(t, u2_star*180/pi,'black--');

% One figure can have multiple axes, for example if we use subplot
ax = gca; %get the axes handle of the current axes
% Set the fontsize and units correctly
ax.FontUnits = 'points';
ax.FontSize = fontsize;
% (not important) Change the 'ticks' on the y label
%ax.YTick = -pi:(pi/2):pi;
%ax.YTickLabel = {'$-\pi$', '$-\frac{\pi}{2}$','$0$','$\frac{\pi}{2}$','$\pi$'};
ax.TickLabelInterpreter = 'latex'; %Interpret Tick labels as latex
% Label the axes, set up legend and title
xlabel('Time [s]')
ylabel('$Elevation$ [deg]')
legend('Elevation', 'Optimal','u_{star}', 'Location','NorthEast')
title('Elevation')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
%%
subplot(3,2,6);
plot(t4, pitchrate);
hold on
plot(t, x3*180/pi);
% One figure can have multiple axes, for example if we use subplot
ax = gca; %get the axes handle of the current axes
% Set the fontsize and units correctly
ax.FontUnits = 'points';
ax.FontSize = fontsize;
% (not important) Change the 'ticks' on the y label
%ax.YTick = -pi:(pi/2):pi;
%ax.YTickLabel = {'$-\pi$', '$-\frac{\pi}{2}$','$0$','$\frac{\pi}{2}$','$\pi$'};
ax.TickLabelInterpreter = 'latex'; %Interpret Tick labels as latex
% Label the axes, set up legend and title
xlabel('Time [s]')
ylabel('$Pitch rate$ [deg/s]')
legend('Pitch rate', 'Optimal', 'Location','NorthEast')
title('Pitch rate')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts

%% Export the figure
hgexport(fig1,'heading_plot.eps')
% optional: save the fig, for later customization: 
% saveas(fig1,'heading_plot.fig')
% optional: save the data, for later plot reproduction:
% save('myAwesomeData.mat','t','y1','y2');

%% (not important) Uncomment these lines if you want to set up different settings for the exported figure than for the figure plotted in matlab
% plotStyle = hgexport('factorystyle');
% plotStyle.Format = 'eps';
% plotStyle.Width = 10;
% plotStyle.Height = 10;
% plotStyle.FontMode = 'Fixed';
% plotStyle.FixedFontSize = 10;
% hgexport(fig1,'heading_plot.eps', plotStyle)

