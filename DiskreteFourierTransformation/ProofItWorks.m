%add octave to path
%octave-cli ProofItWorks.m

x = [0.0, 3.5355339059327378, 5.0, 3.5355339059327378, 6.123233995736766e-16, -3.5355339059327373, -5.0, -3.5355339059327386];
X = fft(x)

disp('x = '); disp(x);

disp('fft = '); disp(X)

disp('fft(Amplitude) = '); disp(abs(X));

disp('fft(Phase) = '); disp(unwrap(angle(X)));

%xs = [0.0, 5.0, 6.123233995736766e-16, -5.0];
%xss = [3.5355339059327378, 3.5355339059327378, -3.5355339059327373, -3.5355339059327386];

%disp('fft(xs) = '); disp(fft(xs));
%disp('fft(xss) = '); disp(fft(xss));

