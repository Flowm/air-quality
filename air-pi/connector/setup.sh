#!/usr/bin/env bash
set -eux

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/service

for service in *.service; do
    if ! [ -f "$service" ]; then
        continue
    fi
    cp $service /etc/systemd/system/ || true
    sudo systemctl daemon-reload || true
    sudo systemctl enable $service || true
    sudo systemctl restart $service
done
