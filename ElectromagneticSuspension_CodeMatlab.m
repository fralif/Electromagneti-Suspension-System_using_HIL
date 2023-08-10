m1 = 250; %Body mass (kg)
m2 = 50; %Suspension mass (kg)
k1 = 16812; %Spring Suspension (N/m)
k2 = 190000; %Spring Tire (N/m)
b1 = 500; %Damping Suspension (N.s/m)
b2 = 1050; %Damping Tire (N.s/m)

s = tf('s');
G = ((m1+m2)*s^2+b2*s+k2)/((m1*s^2+b1*s+k1)*(m2*s^2+(b1+b2)*s+(k1+k2))-(b1*s+k1)*(b1*s+k1));
s1 = ss(G); %state-space

step(G); %Menampilkan step response dari sistem
rlocus(G); %menampilkan root locus yang didapat