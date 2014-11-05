%
%
%%
size_of_count = 100;
x_left = 0;
x_right = pi;
dx = (x_right - x_left)/size_of_count;
x = [x_left:dx:x_right];

Arr_of_sin = sin(x);
Arr_of_tg = tan(x);



X = cat(1, x, Arr_of_sin, Arr_of_tg)'; 


%%
fileName = 'myFile.html';
[m,n] = size(X);
file2HTML = fopen(fileName, 'w');     
if file2HTML == -1                     
    error('File is not opened'); 
end 

fwrite(file2HTML, '<table border = 1>');
for i = 1:m
    fwrite(file2HTML, '<tr>');
    for j = 1:n
    fwrite(file2HTML, '<td>');
        fwrite(file2HTML, num2str(X(i,j),'% 6.4f'));
    fwrite(file2HTML, '</td>');
    end;
    fwrite(file2HTML, '</tr>');
end;
fwrite(file2HTML, '</table>');
fclose(file2HTML);  
