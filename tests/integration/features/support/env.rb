require 'serialport'
require 'yaml'

class TeensyWorld
	def initialize()
		@config = YAML.load_file("features/config.yml")

		@simulatorPort = open_port(@config["serialports"]["simulator"])
		@devicePort = open_port(@config["serialports"]["device"])
	end

	def reset_teensy_cpu()
		@devicePort.write 'Q'
		sleep 5 # Should read firmware version and log iso sleep!
		@devicePort.close
		@devicePort = open_port(@config["serialports"]["device"])
	end

	def next_screen()
		@devicePort.write '+'
	end

	def previous_screen()
		@devicePort.write '-'
	end

	def query_screen()
		@devicePort.write '?'
		response = ""

		loop do
			response = @devicePort.readline
			break if response.include? "?:"
		end

		response.slice! "?:"
		return response
	end

	def open_port(name)
		port = SerialPort.new name, 115200
		port.sync = true
		port.read_timeout = 1000
		return port
	end

	def set_simulator_speed(kmh)
		@simulatorPort.write "S:#{kmh}"
	end

	def set_simulator_rpm(rpm)
		@simulatorPort.write "R:#{rpm}"
	end
end

World { TeensyWorld.new }
