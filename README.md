# RoboDodge2D + OpenGL. 
Задание по практике. Акимов, Григорьев.  
  
Сборка dockerfile:  
1. Перейти в директорию проекта.  
2. "docker build -t robododge . "  
3. "docker run --rm  -i -t -e DISPLAY=HOSTIPADRESS:0 -v /tmp/.X11-unix:/tmp/.X11-unix robododge"  
где HOSTIPADRESS заменить на свой ip.
