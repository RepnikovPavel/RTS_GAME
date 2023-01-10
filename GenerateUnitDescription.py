import os

DescriptionFileDir = "C:\\unreal_projects\\RTS\\UnitDescription"
DescriptionFileName = "Unit1testfile.txt"
path = DescriptionFileDir + "\\" + DescriptionFileName

if not os.path.exists(DescriptionFileDir):
    os.makedirs(DescriptionFileDir)

file = open(path, 'w')

file.write("hallo")

file.close()