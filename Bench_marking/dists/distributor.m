rng('default');  % For reproducibility
exps = exprnd(1, 10000, 1);
disp(exps);
% In general, you can generate N random numbers in the interval (a,b) with the formula r = a + (b-a).*rand(N,1).
unif02 = 0 + (2-0)*rand(10000,1);
unif010 = 0 + (10-0)*rand(10000,1);
disp(unif02);
unif0911 = 0.9 + (1.1-0.9)*rand(10000,1);
disp(unif0911);
pd = makedist('Triangular','a',0,'b',0.75,'c',1.5);
triang = random(pd,10000,1);
disp(triang);


fid = fopen('exponential(1).txt','wt');
for ii = 1:size(exps,1)
    fprintf(fid,'%g\t',exps(ii,:));
    fprintf(fid,'\n');
end
fclose(fid);

fid = fopen('unif0-2.txt','wt');
for ii = 1:size(unif02,1)
    fprintf(fid,'%g\t',unif02(ii,:));
    fprintf(fid,'\n');
end
fclose(fid);

fid = fopen('unif09-11.txt','wt');
for ii = 1:size(unif0911,1)
    fprintf(fid,'%g\t',unif0911(ii,:));
    fprintf(fid,'\n');
end
fclose(fid);

fid = fopen('triang0-15.txt','wt');
for ii = 1:size(triang,1)
    fprintf(fid,'%g\t',triang(ii,:));
    fprintf(fid,'\n');
end
fclose(fid);

fid = fopen('unif0-10.txt','wt');
for ii = 1:size(unif010,1)
    fprintf(fid,'%g\t',unif010(ii,:));
    fprintf(fid,'\n');
end
fclose(fid);

%stairs(exps);
%stairs(unif02);
%stairs(unif0911);
%stairs(triang);
