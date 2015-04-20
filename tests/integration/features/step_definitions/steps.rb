Given /^I drive (\d+) kilometer per hour/ do |speed|
	@simulatorPort.write "speed:#{speed}"
end

When /^I have selected the speed display/ do
	4.times do
		@devicePort.write 'N'
	end
end

Then /^the speed should be (\d+) on the screen/ do |speed|
	avgspeed = 0
	samples = 5

	for i in 1..50
		@devicePort.readline
	end

	for i in 1..samples
		response = @devicePort.readline
		print "#{response}"
		avgspeed += response.to_i / 10
	end

	expect(avgspeed.to_i / samples).to equal(speed.to_i)
end
