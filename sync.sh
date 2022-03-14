rsync -avz --exclude 'www' --exclude 'firmware' --exclude 'gcodes' dsf@rancor:/opt/dsf/sd/ ./sd/
if [ "$(whoami)" == "pi" ]; then
    chown -R pi:pi sd
fi