## Usage:

Use `make` to build the target `rnc.exe`

Use `make clean` to remove intermediate build and executable files

Use `make run` to run the application
- Usage is as follows:
	1. Enter the first Roman Numeral and press return
	1. Enter an operation (either `+` or `-`) and press return
	1. Enter a second Roman Numeral and press return
	
Use `make check` to run the tests

## Design Notes:

* A number of invalid inputs could be provided to this program. Some examples include:
  * A value entered that contains non roman numeral characaters, i.e. `H` or `HI`
  * A value entered contains valid roman numeral characters that are out of sequence `VIM`
  * Addition can result in a number higher than the max value of 3999 or `MMMCMXCIX`
  * Subtraction can result in a number less than or equal to 0
   
The above cases will result in an error being set on the `RNResult` struct which must be passed into the `add` and `subtract` methods.
