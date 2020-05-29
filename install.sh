sudo apt install qtcreator qtbase5-dev qtdeclarative-dev doxygen
Ctrl + Shift + P : pour accéder à la configuration de visualcode 

# How to compress the html files

# Now that we have the .qhp and .qhcp files ready we can 
# perform the compression of the HTML files. For the 
# compression, we need to call the qcollectiongenerator in 
# the following form:

qcollectiongenerator summary.qhcp -o summary.qhc