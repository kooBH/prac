function [restored] = func_celp(x_prev,x_next,fs)
%FUNC_CELP 이 함수의 요약 설명 위치
%   자세한 설명 위치
%% CELP 기반 오류 은닉 예제 (128 샘플 버퍼)
% 가정:
%  - x_prev: 이전 프레임 (128 샘플)
%  - x_next: 이후 프레임 (128 샘플)
%  - 손실된 프레임은 주변 프레임 정보를 이용해 복원함

% 예시용으로 임의의 신호 생성 (실제에서는 실제 음성 프레임 사용)
frameLen = length(x_prev);
t = (0:frameLen-1)'/fs;

disp(["x_prev " + num2str(size(x_prev))])

%% 1. LPC 분석: 이전 프레임을 이용해 LPC 계수 추정
lpcOrder = 10;  % LPC 차수 (실제 시스템에서는 최적 차수 선택)
a = lpc(x_prev, lpcOrder);  % LPC 계수 (여기서는 다이버시파이어 필터 계수)

%% 2. (선택사항) 피치 주기 추정
% 간단한 자가상관법을 사용한 피치 추정 (여기서는 참고용)
[acor, lag] = xcorr(x_prev - mean(x_prev));
lag = lag(lag >= 1);  % 양의 지연만 사용
acor = acor(lag >= 1);
[~, idx] = max(acor);
pitchPeriod = lag(idx);
%fprintf('추정된 피치 주기: %d samples\n', pitchPeriod);

%% 3. 코드북 기반 여기 신호 선택
% Gaussian 코드북 생성 (각 열이 하나의 코드벡터)
codebookSize = 256;
codebook = randn(frameLen, codebookSize);

% 단순 비교 기준: 이전 프레임 말단과 이후 프레임 초반과의 연결 에러 최소화
bestIdx = 1;
minError = inf;
for i = 1:codebookSize
    excitation = codebook(:, i);
    % LPC 합성 필터로 복원 프레임 합성
    x_hat = filter(1, a, excitation);
    % 연결 부위 (예: 이전 프레임 마지막 16샘플과 이후 프레임 처음 16샘플)와의 차이를 최소화
    err = norm(x_hat(1:16) - x_prev(end-15:end)) + norm(x_hat(end-15:end) - x_next(1:16));
    if err < minError
        minError = err;
        bestIdx = i;
    end
end
bestExcitation = codebook(:, bestIdx);

%% 4. 합성: 선택된 여기 신호와 LPC 계수를 사용하여 손실된 프레임 복원
restored = filter(1, a, bestExcitation)/20;

disp(size(restored));




end

