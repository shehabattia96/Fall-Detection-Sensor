clear;
clc;
R_ldr_light = 2e4;
R_ldr_dark = 2e6;
R_n = 1:100:1e6;
Vs = 5; %Volts
% V_light = [];
% V_dark = [];
V_range = [];
% for Rn = R_n
v_light = R_ldr_light./(R_ldr_light+R_n) .* Vs;
%     V_light = [V_light v];
v_dark = R_ldr_dark./(R_ldr_dark+R_n) .* Vs;
%     V_dark = [V_dark v];
V_range = v_dark - v_light;
% end
plot(R_n,V_range)
title('Optimal series resistance for maximum LDR sensitivity.')
xlabel('Series Resistor (Ohm)')
ylabel('V_d - V_l (Volts)')
display('Max range at voltage:')
[~,ind] = max(V_range);
max_range_resistance = R_n(ind)
display(max_range_resistance)

% plot(R_n,V_dark,'r')
% hold on;
% plot(R_n,V_light,'g')