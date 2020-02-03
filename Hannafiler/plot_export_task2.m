%% Example data
%t = linspace(0,5,200);
load travelrate.mat
load pitchrate.mat
load elevationrate.mat
load pitch.mat
load elevation.mat

t1 = tr(1, :);
y1 = tr(2:3, :); 
t2 = pr(1, :);
y2 = pr(2:3, :);
t3 = er(1, :);
y3 = er(2:3, :);
t4 = pitch(1, :);
p = pitch(2:3, :);
t5 = pitch(1, :);
e = elev(2:3, :);


%% Define figure size
width = 10; % cm
height = 10; % cm
fontsize = 20; % points
x = 20; y = 20; % Where on the screen the plot will appear, not important.

set(0,'DefaultTextInterpreter', 'latex') % Interpret (most) text as LaTeX.

%% Set up the figure
fig1 = figure(1);
fig1.Units = 'centimeters';
fig1.Position = [x y width height];

%% Plot the data
subplot(3,2,1);
plot(t1, y1);
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
ylabel('$Travel rate$ [rad/s]')
legend('Encoder', 'Estimate', 'Location','NorthEast')
title('Travel rate')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts

subplot(3,2,2);
plot(t2, y2);
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
ylabel('$Pitch rate$ [rad/s]')
legend('Encoder', 'Estimate', 'Location','NorthEast')
title('Pitch rate')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
%%
subplot(3,2,3);
plot(t3, y3);
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
ylabel('$Elevation rate$ [rad/s]')
legend('Encoder', 'Estimate', 'Location','NorthEast')
title('Elevation rate')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
%%
subplot(3,2,4);
plot(t4, p);
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
ylabel('$Pitch$ [rad]')
legend('Encoder', 'Estimate', 'Location','NorthEast')
title('Pitch')
ax.TitleFontSizeMultiplier = 1.1; %Set title to be 1.1 times larger than other fonts
%%
subplot(3,2,5);
plot(t5, e);
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
ylabel('$Elevation$ [rad]')
legend('Encoder', 'Estimate', 'Location','NorthEast')
title('Elevation')
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

