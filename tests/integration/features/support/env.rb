require 'serialport'

class TeensyWorld
	def initialize()
		@simulatorPort = open_port("/dev/tty.usbserial-A700eU6X")
		@devicePort = open_port("/dev/tty.usbmodem743881")
	end

	def reset_teensy_cpu()
		@devicePort.write 'Q'
		sleep 4 # Should read firmware version and log iso sleep!
		@devicePort.close
		@devicePort = open_port("/dev/tty.usbmodem743881")
	end

	def open_port(name)
		port = SerialPort.new name, 57600
		port.sync = true
		port.read_timeout = 1000
		return port
	end

	def set_speed(kmh)
		@simulatorPort.write "S:#{kmh}"
	end

	def set_rpm(rpm)
		@simulatorPort.write "R:#{rpm}"
	end
end

World { TeensyWorld.new }
