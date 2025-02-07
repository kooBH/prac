close all
clear

[x_orig,fs] = audioread("../data/male_1.wav");

%sound(x,16000);

n_hop = 128;
prob_loss = 0.1;


n_frame = int16(length(x_orig)/n_hop);
x = x_orig;

flag_loss = zeros(n_frame,1);

% random stream loss

for i = 1:n_frame
    if rand < prob_loss
        x(1+(i-1)*n_hop:i*n_hop) = 0;
        flag_loss(i) = 1;
    end
end
x_rec = x;


% filling
n_landing = double(int16(n_hop/2));
knee_width = 5;

for i = 1:n_frame
    if i == 1
        continue
    end

    if flag_loss(i) == 1
        
        % copy previous buffer
         %       x_rec(1+(i-1)*n_hop:i*n_hop) =flip(x(1+(i-2)*n_hop:(i-1)*n_hop),1);

        % falling
        base_value = x_rec((i-1)*n_hop);
        for j = 1:n_landing
            x_rec((i-1)*n_hop+j) = base_value*(1 - j/n_landing);
        end
        %disp(["target " + num2str(i) + " | " + num2str(size(x_rec((i-1)*n_hop+1:(i-1)*n_hop+n_hop)))])
        %x_rec(1+(i-1)*n_hop:i*n_hop) = func_celp(x_rec(1+(i-2)*n_hop:(i-1)*n_hop),zeros(n_hop,1),fs);
    end
    % rising
    if flag_loss(i-1) == 1
        base_value = x_rec((i-1)*n_hop + n_landing);
        for j = 1:n_landing
            x_rec((i-1)*n_hop+j) = base_value*(j/n_landing);
        end
       
    end
end




subplot(3,1,1);
plot(x_orig);
title("Original")

subplot(3,1,2);
plot(x)
title("Lossed")

subplot(3,1,3);
plot(x_rec)
title("recovered");

render = [x_orig;x;x_rec];

sound(render,16000)



