require 'serialport'

port = SerialPort.new "/dev/tty.usbserial-A700eU6X", 9600

Given /^I drive (\d+) kilometer per hour/ do |speed|
  port.write "speed:#{speed}"
end

When /^I have selected the speed display/ do
  
end

Then /^the speed should be (\d+) on the screen/ do |speed|
  
end
