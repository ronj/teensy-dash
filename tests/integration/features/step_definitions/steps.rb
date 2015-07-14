Given /^I drive (\d+) kilometer per hour/ do |speed|
	set_simulator_speed speed
end

When /^I have selected the (.*) display/ do |screen|
	screen_map = {"speed" => 0, "gear" => 2}

	screen_map[screen].times do
		next_screen
	end
end

Then /^the speed should be (\d+) on the screen/ do |speed|
	query_screen
	response = @devicePort.readline

	expect(response.to_i / 10).to be_within(1).of(speed.to_i)
end
