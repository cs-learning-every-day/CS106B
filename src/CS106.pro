TEMPLATE = subdirs
SUBDIRS = Library Welcome \
    Lecture1Code/Lecture1/HelloWorld.pro

# ordered forces subprojects to build sequentially, according to SUBDIRS
CONFIG += ordered
