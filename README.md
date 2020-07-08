# RoboDodge2D + OpenGL. 
Задание по практике. Акимов, Григорьев.  
  
Сборка dockerfile:  
1. Перейти в директорию проекта.  
2. "docker build -t robododge . "  
3. "docker run --rm  -i -t -e DISPLAY=HOSTIPADRESS:0 -v /tmp/.X11-unix:/tmp/.X11-unix robododge"  
где HOSTIPADRESS заменить на свой ip.

Управление (сначала надо выбрать активным окно OpenGL):
1. Стрелки вправо или влево для передвижения.
2. Стрелка вверх для изменения режима (из режима уклонения в режим ловли шаров или обратно).
