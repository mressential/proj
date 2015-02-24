import os
import glob

os.chdir("test/")
dir_files = glob.glob("*.txt")

a = "hello"
for i in range(len(dir_files)):
    name = dir_files[i]
    file=open(name,'r')
    text=file.read()
    if a in text:
        print "Ok in " + dir_files[i]
    else:
        print "No"
