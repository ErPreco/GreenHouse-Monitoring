# Greenhouse-Monitoring

A C++ project about a greenhouse monitoring software.

The project is in italian, made for educational purpose at the University of Padua.
It was made using gcc 11.3.0, Qt 6.2.4 and qmake 3.1 on Ubuntu 22.04 LTS. An OVA image (about 6GB) is available on https://drive.google.com/file/d/11X7JWm13h2Fqni7f-JTetIcJ-vC7PTzM/view?usp=share_link (user=student, password=student). It consists of:
* report (relazione.pdf)
* logic UML (logic.dia)
* compiled file (project)
* files to compile the project
  - project.pro
    - created by "qmake -project"
    - "QT += widgets" and "QT += core gui charts" are required but hand added
  - .qmake.stash
    - created by "qmake"
  - write "make" to compile
* source files
* assets files for icons
* demo json file (sensor-simulation.json)
