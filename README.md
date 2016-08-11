## Usage:
Use ```make``` to run the application
- Usage is as follows:
	1. Enter the first Roman Numeral and press return
	1. Enter an operation (either `+` or `-`) and press return
	1. Enter a second Roman Numeral and press return
	
Use ```make check``` to run the tests

Use ```make clean``` to remove intermediate build and executable files

## Design Notes:

- While completing this kata, I decided to handle upper and lower case letters. Having handled lower case roman numerals first, I started adding tests to add in upper case roman numeral conversion. I decided to include upper case letters in the cases of the switch statement instead of doing converting the input to upper or lower for a couple of reasons. Primarily, there were no requirements driving the additional logic to determine perform the conversion. I also decided that the switch statement was going to consume less processor time in C than another solution that involved converting. 

* A number of invalid inputs could be provided to this program. Some examples include:
  * A value entered that contains non roman numeral characaters, i.e. `H` or `HI`
  * A value entered contains valid roman numeral characters that are out of sequence `VIM`
  * Addition can result in a number higher than the max value of 3999 or `MMMCMXCIX`
  * Subtraction can result in a number less than or equal to 0
   
In product design it is important to weigh the tradeoffs and risks associated with hanlding such errors in software vs. in hardware. For example it would be unlikely for a Roman Numeral calulcator as a product to include methods of invalid input such as `H` and it would be unnecessary to validate this input in software. In systems were safety is a concern, there would likely be reduntant hardware and software checks to mitigate and/or prevent exception scenarios from occurring and reduce the impact to the user. I would be happy to discuss the desired user experience for invalid inputs to the system with a Product Owner and determine requirements for handling such exception scenarios.
