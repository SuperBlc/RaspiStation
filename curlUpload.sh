#! /bin/sh

#your userkey,which lewei can provide you
USERKEY='xxxxxxxxxxxxxxxxxxxxxxxx'

logfile='/home/pi/sensor_log/'`date '+%Y%m%d'`'.log'

echo "------------------------------------------------------" >> $logfile
echo "------------------------------------------------------"

#"enter time"
datetime=[`date '+%Y-%m-%d %u  %H:%M:%S'`]

#upload data
infos=`curl --request POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/01 --data "[{'Name':'T1','Value':'$1'}]" --header "userkey:$USERKEY"`

#print info
echo $datetime $infos >> $logfile
echo $datetime $infos

#echo a time information
echo [`date '+%Y-%m-%d %u  %H:%M:%S'`] "Receive temprature:" $1"oC" >> $logfile 
echo [`date '+%Y-%m-%d %u  %H:%M:%S'`] "Receive temprature:" $1"oC" 
echo ''