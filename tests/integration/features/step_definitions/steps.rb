Given /^I drive (\d+) kilometer per hour/ do |speed|
	set_simulator_speed speed
end

And /^I rev the engine to (\d+) RPM/ do |rpm|
    set_simulator_rpm rpm
end

When /^I have selected the (.*) display/ do |screen|
	screen_map = {"speed" => 0, "gear" => 1}

	screen_map[screen].times do
		next_screen
	end
end

Then /^the speed should be (\d+) on the screen/ do |speed|
	sleep 4
	response = query_screen

	expect(response.to_i / 10).to be_within(1).of(speed.to_i)
end

Then /^the gear should be (.*) on the screen/ do |gear|
	sleep 2
    response = query_screen
    response = response.chomp("\r\n")

    expect(response).to eq(gear)
end
