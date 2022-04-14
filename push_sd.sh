rsync -avz --exclude 'www' --exclude 'firmware' --exclude 'gcodes' ./sd/ /opt/dsf/sd/
if [ "$(whoami)" == "pi" ]; then
    chown -R pi:pi sd
fi