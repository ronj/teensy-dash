require 'serialport'

simulatorPort = SerialPort.new "/dev/tty.usbserial-A700eU6X", 9600
simulatorPort.sync = true

devicePort = SerialPort.new "/dev/tty.usbmodem743881", 9600
devicePort.sync = true

Given /^I drive (\d+) kilometer per hour/ do |speed|
	simulatorPort.write "speed:#{speed}"
end

When /^I have selected the speed display/ do
	4.times do
		devicePort.write 'N'
	end
end

Then /^the speed should be (\d+) on the screen/ do |speed|
	avgspeed = 0
	samples = 5

	for i in 1..samples
		sleep 1
		response = devicePort.readline
		print "#{response}"
		avgspeed += response.to_i / 10
	end

	expect(avgspeed.to_i / samples).to equal(speed.to_i)
end
