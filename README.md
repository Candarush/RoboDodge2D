# RoboDodge2D
Задание по практике. Акимов, Григорьев.  
  
Dockerfile запускал командами:  
"docker build -t robododge . "  
"docker run --rm -i -t -e DISPLAY=192.168.1.67:0 -v /tmp/.X11-unix:/tmp/.X11-unix robododge", где 192.168.1.67 - взял из xhost.
