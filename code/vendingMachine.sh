#!/bin/bash

$(./initIO 0)
$(./initIO 1)
$(./initIO 2)

PROJ[1]="/mnt/storage/projects-src/1-LifeBoard.zip"
PROJ[2]="/mnt/storage/projects-src/2-FireballBoard.zip"
PROJ[3]="/mnt/storage/projects-src/3-CVDTouch.zip"
PROJ[4]="/mnt/storage/projects-src/4-CloCore.zip"
PROJ[5]="/mnt/storage/projects-src/5-USBTinyISP.zip"
PROJ[6]="/mnt/storage/projects-src/6-HeartBoard.zip"
PROJ[7]="/mnt/storage/projects-src/7-Buzzers.zip"
PROJ[8]="/mnt/storage/projects-src/8-VendingMachine.zip"

SWITCH[1]=0
SWITCH[2]=0
SWITCH[3]=0
SWITCH[4]=0
SWITCH[5]=0
SWITCH[6]=0
SWITCH[7]=0
SWITCH[8]=0
GOSWITCH=0

STATE="OFF"

function setLED() {
  if [ "$1" = "1" ]; then
    BOARD=0
    LED=0
  elif [ "$1" = "2" ]; then
    BOARD=0
    LED=1
  elif [ "$1" = "3" ]; then
    BOARD=0
    LED=2
  elif [ "$1" = "4" ]; then
    BOARD=0
    LED=3
  elif [ "$1" = "5" ]; then  
    BOARD=1                    
    LED=0
  elif [ "$1" = "6" ]; then    
    BOARD=1                      
    LED=1    
  elif [ "$1" = "7" ]; then    
    BOARD=1                      
    LED=2 
  elif [ "$1" = "8" ]; then    
    BOARD=1                      
    LED=3 
  fi
  
  if [ "$2" = "GREEN" ]; then
    COLOR=2
  elif [ "$2" = "RED" ]; then
    COLOR=4
  elif [ "$2" = "BLUE" ]; then
    COLOR=1
  elif [ "$2" = "YELLOW" ]; then
    COLOR=6
  elif [ "$2" = "PURPLE" ]; then
    COLOR=5
  elif [ "$2" = "OFF" ]; then
    COLOR=0
  fi
  
  $(./setLED $BOARD $LED $COLOR) 
}

 
function setAllSwitchs() {
  SWITCH[1]="$(./readSwitch 0 0)$?"
  SWITCH[2]="$(./readSwitch 0 1)$?"
  SWITCH[3]="$(./readSwitch 0 2)$?"
  SWITCH[4]="$(./readSwitch 0 3)$?"
  SWITCH[5]="$(./readSwitch 1 0)$?"
  SWITCH[6]="$(./readSwitch 1 1)$?"
  SWITCH[7]="$(./readSwitch 1 2)$?"
  SWITCH[8]="$(./readSwitch 1 3)$?"
  GOSWITCH="$(./readSwitch 2 0)$?"
#  GOSWITCH="0"

  for i in "${!SWITCH[@]}"
  do
    if [ ${SWITCH[$i]} -eq "1" ]; then
      if [ "$STATE" = "READY" ]; then
        setLED $i GREEN
      else 
        setLED $i YELLOW
      fi   
    else
      setLED $i OFF
    fi
  done
}

function checkUSB() {
  if [ -d "/mnt/usb" ]; then            
    if [ "$STATE" = "OFF" ]; then
      STATE="READY"
    fi
  else                                  
    STATE="OFF"                         
  fi  
}

function copyFiles(){
  STATE="COPY"
  COPYCOUNT=0
  for i in "${!SWITCH[@]}"                     
  do
                                           
    if [[ ${SWITCH[$i]} -eq "1" ]]; then
      COPYCOUNT=$(($COPYCOUNT+1))
      setLED $i PURPLE 
      if [ -h /mnt/usb ]; then      
        $(cp -f ${PROJ[$i]} /mnt/usb/ > /dev/null 2>&1)     
        if [[ $? -eq "1" ]]; then
          STATE="ERROR"
          setLED $i RED
        else
          setLED $i BLUE
        fi
      else
        STATE=ERROR
        setLED $i RED
      fi
    fi                                        
    #  echo "key: $i , value: ${SWITCH[$i]}"      
  done
  if [ $COPYCOUNT -eq "0" ]; then
    STATE="READY"
  fi
   
  if [ "$STATE" = "COPY" ]; then 
    STATE="DONE"
    $(sync)
  fi
}

function setSelectedLEDS() {
  for i in "${SWITCH[@]}"
  do
    setLED $i $1
  done
}

while true; do
  if [ "$STATE" = "OFF" -o "$STATE" = "READY" ]; then  
    setAllSwitchs
  fi
  checkUSB
  
  if [ "$STATE" = "READY" -a $GOSWITCH -eq "1" ]; then
    copyFiles
  fi
  
  echo "$STATE"
done  


    
