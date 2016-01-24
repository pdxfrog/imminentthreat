

instrreset; %Resets all COM objects/ports
pause(1);   %Wait, so reset takes
ardi = serial('COM6', 'Baudrate', 115200);  %Create serial object
pause(1);               %Wait for completion
ardi.InputBufferSize = 1024;
fopen(ardi);            %Open serial object

scrsz = get(groot, 'ScreenSize');
H = figure('OuterPosition',[1 scrsz(4)/2 scrsz(3)/2 scrsz(4)/2],'Name','Hack Arizona FFT FTW',...
    'NumberTitle','off','NextPlot','add');

axesA = axes('OuterPosition', [0 0 1 1],'NextPlot', 'replace');
axesA.Title.String = 'FFT FTW';



ardi.readasync();       %Set asyncronous read 

fid = fopen('D:\Users\Kyle\HackAZFFT128_508', 'a');%open output file
H.CurrentAxes = axesA;
hold off;
firstTime = 1;
i=1;
while (1)                       %always true
   
    while(ardi.BytesAvailable <=0)
        ;
    end
    while(ardi.BytesAvailable > 0)
    
    %data = ardi.fscanf();       %Get Data
    data = fscanf(ardi, '%d');
    
   % dataVectorRow(1,i) = double(data);
    i = i+1;
    fprintf(1, '%d ', data);
    fprintf(1, '\n');
%       
             fprintf(fid, '%d ',data);             %Print Data to File
             fprintf(fid, '\n');
%             fprintf(1,'%d ',dataVectorRow{:}); %Print data to console
%             fprintf(1,'\n');

  
    
    end
    
    
    
    
    %fprintf(1,'%d ',dataMatrix(:,:));
   H.CurrentAxes = axesA;
    axesA.XLim
    plot([0:500/128:500 - (500/128)],data);
    ylim([0 100]);
    
    drawnow;
    %fprintf(1,'\n');
    

end                             %end Loop
fclose(fid);
