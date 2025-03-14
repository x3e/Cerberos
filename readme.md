# Cerberos

## Issue
The screen is not working when powered from USB. In theory the internal CH552 voltage regulator should be able to provide enough current, and with a previous batch of screens, this was working. If you find the issue, please let us know by opening an issue or submitting a pull request.

## Compilation
To compile the software for this project, follow the instructions in the [ch55xduino](https://github.com/DeqingSun/ch55xduino) repository to set up your development environment. Use the following settings after selecting the CH552 board in Arduino:
 - Bootloader pin: P3.6 (D+) pull-up
 - Clock Source: 12 MHz (internal)
 - Upload method: USB
 - USB Settings: User Code w/ 0B USB ram

## License
This project is licensed under the Unlicense License. See the [LICENSE](LICENSE) file for details.

## Contact
If you have any questions or suggestions, feel free to open an issue.