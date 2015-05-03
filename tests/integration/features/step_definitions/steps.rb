Given /^I drive (\d+) kilometer per hour/ do |speed|
	set_speed speed
end

When /^I have selected the speed display/ do
	2.times do
		@devicePort.write '+'
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
		avgspeed += response.to_i / 10
	end

	expect(avgspeed.to_i / samples).to be_within(1).of(speed.to_i)
end