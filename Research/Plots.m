clc;
clear;
close all;

% Read the file line by line
fid = fopen('Entropy_file.csv', 'r');

if fid == -1
    error('Could not open Entropy_file.csv');
end

figure;
hold on;

sample = 1;

while ~feof(fid)

    line = fgetl(fid);

    % Skip empty lines
    if isempty(line)
        continue;
    end

    % Convert comma-separated values into numbers
    entropy = str2double(split(line, ','));

    % Remove any NaN values
    entropy = entropy(~isnan(entropy));

    % Number of steps
    steps = 1:length(entropy);

    % Plot entropy vs steps
    plot(steps, entropy, 'DisplayName', sprintf('Sample %d', sample));

    sample = sample + 1;
end

fclose(fid);

xlabel('Number of Steps');
ylabel('Entropy');

title('Entropy vs Number of Steps');

grid on;
legend('Location', 'eastoutside');

hold off;