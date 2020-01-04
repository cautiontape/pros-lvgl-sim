import os
import glob

print('建立目标静态库路径链表')
lvgl = [""]
lvgl += glob.glob('include/lvgl/src/*/*.c')
# drives = [""]
# drives += glob.glob('include/lv_drivers/*/*.c')

command = "clang -c"  # 生成.o文件
print("-------------------------")
for index in lvgl:
    command += " "+index
# for index in drives:
#     command += " "+index
print('lvgl静态库建立中...')
os.system(command)
lvglLIB = [""]
lvglLIB += glob.glob('*.o')
command = "clang++ "  # 用动态库
for index in lvglLIB:
    command += " "+index
command += " -shared -fPIC -o .\\firmware\\liblvgl.so"
os.system(command)
print('lvgl静态库完成')
