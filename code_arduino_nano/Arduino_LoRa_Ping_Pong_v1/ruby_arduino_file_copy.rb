#Ruby_arduino_file_copy.rb by Vincent Gosselin, copyright 2016.

#This simple script is made to get ride of the anoying Copy-Paste
#from sublime text into arduino IDE and texts editors to program the arduino.

#This is a script that copies sublime text files
#Arduino file (.ino), .cpp file and .h file into the respective 
#files.


#Source
source = File.readlines(Dir.pwd+"/Arduino_LoRa_Ping_Pong.cpp")


#Destination files
destionation = "/Users/vincentgosselin/Documents/Arduino/arduino_nano_Beliot/arduino_nano_Beliot.ino"


#COPY-PASTE
File.open(destionation, "w") do |f|
	f.puts source
end

puts "COPY-PASTE DONE"



