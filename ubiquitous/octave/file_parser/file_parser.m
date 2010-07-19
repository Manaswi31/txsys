% clear all;  close all;  fclose all;
clear all;  close all;  fclose all;%20090905@sichun ziyang  modify by xinjiapeng
clc;
sourcedir = 'D:\caodongya\m_file_xjp_lgd\HSUPA\HSUPA_coderate_test' ;                 %%% .m file dir
dirstr = 'D:\caodongya\m_file_xjp_lgd\HSUPA\New Folder' ;     %%%
desstr = 'D:\caodongya\m_file_xjp_lgd\HSUPA\New Folder'
cd(dirstr) ;

dirn = dir('*prri*') ;         
dirc = length(dirn) ;

% open the file which is used to record the statistic data
fidStat = fopen('D:\caodongya\m_file_xjp_lgd\HSUPA\New Folder\StatisticResult.txt' ,'w');


cd(dirstr) ;
for jj=1:dirc
     aa = dirn(jj);     
     filename = aa.name;
     
       cd(dirstr);
       pwdd = pwd ;
        fp_source = fopen(filename, 'r');
        
        Progress_indicator=0;
        LineCounter=0;
        
      
        o_sjts_measure_report_user_record=[];                  % record the SNR RSCP ISCP infomation for EPUCH user
        o_hsts_upa_sche_info_record = [];                          % record the NACK ACK infomation
        o_ccts_edch_info_record = [];                                  % record the edch info
        
            
        
        o_sjts_measure_report_user_counter=0;
        o_hsts_upa_sche_info_counter = 0;
        o_ccts_edch_info_counter = 0;
     
        Line_PreRead=[];

        while(1)
            %Read 1 line
            if length(Line_PreRead)>0
                line=Line_PreRead;
                Line_PreRead='';
            else
                line=fgetl(fp_source);
                LineCounter=LineCounter+1;
            end
                  
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            %validity check
            if line==-1
                %end of the file, jump out
                break;
            end
            
            line_tmp=line(line~=' ');
            if length(line_tmp)<=1
                %empty line, go back the the beginning of this section
                continue;
            end
            
            %is it a valid line?
            if strcmp(line(1:2),'$5')~=1
                %it is not a good starting line, subsequent process is ignored
                continue;
            else
                %it is a good starting line, go on
            end
            %validity check end
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            
            
            sfn_long = line(4:11);
            pos = strfind(line,' ');
            log_type = line(pos(2)+1:pos(4)-1);
            
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            %message classification
            Message_Flag='';
           
            if isempty(strfind(log_type,'O_SJTS_MEASURE_REPORT_USER'))==0
                Message_Flag='O_SJTS_MEASURE_REPORT_USER';
            end
            
            if isempty(strfind(log_type,'O_HSTS_UPA_SCHE_INFO'))==0
                Message_Flag = 'O_HSTS_UPA_SCHE_INFO';
            end
            
            if isempty(strfind(log_type,'O_CCTS_EDCH_INFO'))==0
                Message_Flag = 'O_CCTS_EDCH_INFO';
            end            
            
            %message classification end
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            
            if length(Message_Flag)==0
                continue;
            end
