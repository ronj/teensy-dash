Feature: Display selected gear
    In order to know what gear I am in
    As a driver
    I want to be told the currently selected gear

    Scenario Outline: Show correct gear for speed and RPM
        Given I drive <speed> kilometer per hour
            And I rev the engine to <revs> RPM
        When I have selected the gear display
        Then the gear should be <gear> on the screen

        Examples:
          | speed | revs | gear |
          |   80  | 3000 |   5  |
          |    0  |  900 |   N  |
