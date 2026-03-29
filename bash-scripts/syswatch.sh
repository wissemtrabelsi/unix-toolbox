#!/bin/bash

INTERVAL=60 #default:check every 60 seconds
LOG="logs/syswatch.log" #log file created at runtime
DISK_THRESHOLD=80 #warn if DISK usage > 80
CPU_THRESHOLD=80  #warn if CPU usage > 80

while [[ $# -gt 0 ]]; do
    case $1 in
    --interval)
        #=~  checks the pattern,treats the right side as a regex pattern.
        if ! [[ $2 =~ ^[0-9]+$ ]]; then # !=,= no pattern matching, no regex,
            echo "Error: --interval must be a positive" >&2
            exit 1
        fi
        INTERVAL="$2"
        shift 2
        ;;
    --log)
        if [ -z "$2" ]; then # -z means "is this string empty"
            echo "Error: --log requires a file path" >&2
            exit 1
        fi
        LOG="$2"
        shift 2
        ;;
    --help)
        echo "Usage: $0 [options]"
        echo " --interval <seconds>  check interval (default: 60 seconds)"
        echo " --log <file>          log file (default: logs/syswatch.log)"
        echo " --help                show --help message"
        exit 0
        ;;
    *) #default any thing 
        echo "unknown arg: $1" >&2
        exit 1
        ;;
    esac
done


log_msg(){
    local level="$1" #INFO or WARN #local like static in c 
    local message="$2" #actual message
    local time_temp=$(date "+%Y-%m-%d %H:%M:%S") # +:tells DATE what follows is a format string
    
    mkdir -p logs
    echo "[$time_temp] $level $message" #stdout
    echo "[$time_temp] $level $message" >> $LOG
}

get_cpu(){ #returns CPU usage percentage
    if [[ "$OSTYPE" == "darwin"* ]];then
        #here i used tr then cut //-d '.'// cause cut splits and take the first part
        #tr just deletes the .
        top -l1 | grep "CPU usage" | awk '{print $3}' | tr -d '%' | cut -d '.' -f1
    else
        top -bn1 | grep "Cpu(s)" | awk '{print $2}' | tr -d '%us, '
    fi
}
get_ram(){ #returns Used/Total RAM
    if [[ "$OSTYPE" == "darwin"* ]];then
        Ram_tot_mac=$(sysctl -n hw.memsize | awk '{printf "%.1f GiB", $1/1024/1024/1024 }')
        # mac thinks about Ram not in Bytes but in **pages** 
        # a page is 4096 bytes afixed chunk of memory 
        # so the mac kernel speaks in **pages**
        #here i do the conversion from pages to GiB
        Ram_used_mac=$(vm_stat | awk '/Pages active/ {print $3}' | tr -d '.' | awk '{printf "%.1f GiB", $1*4096/1024/1024/1024'}) 
        echo "${Ram_used_mac}/${Ram_tot_mac}"
    else
        free -h | grep Mem | awk '{print $3 "/" $2}'
    fi
}
get_disk(){ #returns disk usage percentage of /
    # in general i use this method:
    # df -h / | grep -v Filesystem | cut -d' ' -f5 | tr -d '%'
    # awk is new to me so i tried it
    # awk '{print $5}' → extract 5th column (Use%) e.g "45%"
    df -h / |tail -1 | awk '{print $5}' | tr -d '%'
    # tr: translates or deletes characters from input
}
# signal handling on: CTRL + C
cleanup(){
    log_msg "INFO" "syswatch STOPPED"
    exit 0
}


# cleanup is called when SIGINT (Ctrl+C) or SIGTERM (kill) is received
# SIGINT  → user pressed Ctrl+C
# SIGTERM → kill command sent by another process or sysadmin
trap cleanup SIGINT SIGTERM
# flow of trap: register -> loop -> bash received signal -> bash checks
# do i have a trap for this signal ->YES ->bash calls cleanup() → exit 0


log_msg "INFO" "syswatch started | interval: ${INTERVAL} s | log: $LOG"
# the syswatch loop
while true; do
    CPU=$(get_cpu)
    RAM=$(get_ram)
    DISK=$(get_disk)

    # log info 
    log_msg "INFO" "CPU $CPU % | RAM: $RAM | DISK: $DISK %"

    # threshold checks
    if [ "$CPU" -gt "$CPU_THRESHOLD" ]; then
        log_msg "WARNING" "CPU spike detected: $CPU%"
    fi
    if [ "$DISK" -gt "$DISK_THRESHOLD" ]; then
        log_msg "WARNING" "DISK usage spike detected: $DISK%"
    fi
    
    sleep "$INTERVAL"
done