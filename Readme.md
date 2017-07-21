This is a project created in order to write code using eclipse.<br>
This code is tested on Dji M4 board.<br>
Folder System is for gcc only,others folders are created by CubeMx<br>
<br>
version1,make some changes in offical codes:<br>
1. in bsp_flash.h ,GetSector is not static, while in bsp_flash.c it's static.<br>
::rm line GetSector's statement.
2. Change strcut __pid_t to anoymous,change pid_t to k_pid_t.
```bash
in files:
    chassis_task.c
    pid.c
    pid.h
    shangweiji.c
```bash
3. exculde following files in build.
i2c_oled.c
all sources in folder RTE

version2 add bsp packages support(in folder MDK_ARM).
