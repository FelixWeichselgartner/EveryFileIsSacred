%add octave to path
%octave-cli ProofItWorks.m

x = [0.0, 3.5355339059327378, 5.0, 3.5355339059327378, 6.123233995736766e-16, -3.5355339059327373, -5.0, -3.5355339059327386];
%x = [5, 5, 5, 5, 5, 5, 5, 5];

X = fft(x);

disp('x = '); disp(x);

disp('fft = '); disp(X)

disp('fft(Amplitude) = '); disp(abs(X));

disp('fft(Phase) = '); disp(angle(X));

%same result as disp(angle(X))
%for i = 1:length(X)
%    disp(angle(X(i)));
%    disp(atan2(imag(X(i)), real(X(i))));
%endfor

%matlab aint better than python
disp(atan2(0, -0))

%xs = [0.0, 5.0, 6.123233995736766e-16, -5.0];
%xss = [3.5355339059327378, 3.5355339059327378, -3.5355339059327373, -3.5355339059327386];

%disp('fft(xs) = '); disp(fft(xs));
%disp('fft(xss) = '); disp(fft(xss));

