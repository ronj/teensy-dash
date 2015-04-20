require 'serialport'

simulatorPort = SerialPort.new "/dev/tty.usbserial-A700eU6X", 57600
simulatorPort.sync = true

devicePort = SerialPort.new "/dev/tty.usbmodem743881", 57600
devicePort.sync = true
devicePort.read_timeout = 1000

at_exit do
	simulatorPort.close
	devicePort.close
end

class TeensyWorld
	def initialize(simulatorPort, devicePort)
		@simulatorPort = simulatorPort
		@devicePort = devicePort
	end

	def reset_teensy_cpu()
		@devicePort.write 'R'
		sleep 4 # Should read firmware version and log iso sleep!
		@devicePort.close
		@devicePort = SerialPort.new "/dev/tty.usbmodem743881", 57600
		@devicePort.sync = true
		@devicePort.read_timeout = 1000
	end
end

World { TeensyWorld.new(simulatorPort, devicePort) }
