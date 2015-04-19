Feature: Display speed
    In order to know how fast I am driving
    As a driver
    I want to be told the current speed of my vehicle

    Scenario: Show single speed
    	Given I drive 80 kilometer per hour
    	When I have selected the speed display
    	Then the speed should be 80 on the screen
