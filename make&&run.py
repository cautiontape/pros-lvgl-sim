import os
import glob

# print('正在添加include')
# include = ['-include ']
# include += glob.glob('include/*.hpp')
# include += glob.glob('include/*.h')
print('正在添加src')
src = []
src += glob.glob('src/*.cpp')
src += glob.glob('src/*.c')
src += glob.glob('include/lvgl/src/*/*.c')
src += glob.glob('include/lv_drivers/*/*.c')
command = "clang++ -D_CRT_SECURE_NO_WARNINGS"
print("-------------------------")
for index in src:
    command += " "+index
# for index in include:
#     command += " "+index
# 说明include目录位置
command += " -I .\\include"
# 链接LIB
command += " -L .\\firmware -lSDL2 -lSDL2main -Xlinker /subsystem:windows"
# 添加编译生成的EXE目标路径
command += " -o .\\bin\\main.exe"
print('编译中')
os.system(command)
print('编译结束,执行程序\n\n')
os.system(".\\bin\\main.exe")
