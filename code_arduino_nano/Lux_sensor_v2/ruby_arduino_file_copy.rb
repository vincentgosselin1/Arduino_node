#Ruby_arduino_file_copy.rb by Vincent Gosselin, copyright 2016.

#This simple script is made to get ride of the anoying Copy-Paste
#from sublime text into arduino IDE and texts editors to program the arduino.

#This is a script that copies sublime text files
#Arduino file (.ino), .cpp file and .h file into the respective 
#files.


#Source
source1 = File.readlines(Dir.pwd+"/Lux_sensor_v2.cpp")
source2 = File.readlines(Dir.pwd+"/libraries/Lux_sensor_library_v2/Lux_sensor_library_v2.cpp")
source3 = File.readlines(Dir.pwd+"/libraries/Lux_sensor_library_v2/Lux_sensor_library_v2.h")
source4 = File.readlines(Dir.pwd+"/libraries/Lux_sensor_library_v2/TSL2561_v2.h")
source5 = File.readlines(Dir.pwd+"/libraries/Lux_sensor_library_v2/TSL2561_v2.cpp")


#Destination files
destionation1 = "/Users/vincentgosselin/Documents/Arduino/Lux_sensor_v2/Lux_sensor_v2.ino"
destionation2 = "/Users/vincentgosselin/Documents/Arduino/libraries/Lux_sensor_library_v2/Lux_sensor_library_v2.cpp"
destionation3 = "/Users/vincentgosselin/Documents/Arduino/libraries/Lux_sensor_library_v2/Lux_sensor_library_v2.h"
destionation4 = "/Users/vincentgosselin/Documents/Arduino/libraries/Lux_sensor_library_v2/TSL2561_v2.h"
destionation5 = "/Users/vincentgosselin/Documents/Arduino/libraries/Lux_sensor_library_v2/TSL2561_v2.cpp"


#COPY-PASTE
File.open(destionation1, "w") do |f|
	f.puts source1
end
File.open(destionation2, "w") do |f|
	f.puts source2
end
File.open(destionation3, "w") do |f|
	f.puts source3
end
File.open(destionation4, "w") do |f|
	f.puts source4
end
File.open(destionation5, "w") do |f|
	f.puts source5
end

puts "COPY-PASTE DONE"



